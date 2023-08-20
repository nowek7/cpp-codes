#include <array>
#include <vector>
#include <memory>
#include <cmath>
#include <unordered_map>
#include <algorithm>

#include <iostream>

namespace {
    using Cargo = std::array<int, 7>;

    using IntPair = std::pair<int, int>;
    using PairGroup = std::vector<IntPair>;
 
    bool arePairDistinct(const IntPair& lhs, const IntPair& rhs) {
        // Pairs are in order <==> (x, y) where x < y
        if (lhs.first == rhs.first || lhs.first == rhs.second) {
            return false;
        }
        if (lhs.second == rhs.first || lhs.second == rhs.second) {
            return false;
        }

        return true;
    }

    void printGroupOfPairs(const std::vector<IntPair> group) {
        for (auto i = 0; i < group.size() - 1; ++i) {
            std::cout << "(" << group[i].first << ", " << group[i].second << ")" << ", ";
        }
        std::cout << "(" << (*group.rbegin()).first << ", " << (*group.rbegin()).second << ")" << '\n';
    }
}

int extendedEuclidean(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        const int gcd = extendedEuclidean(b, a % b, x, y);
    
        const int tmp = x;
        x = y;
        y = tmp - (a / b) * y;
        
        return gcd;
    }
}

std::vector<IntPair> findAllSolutionsOfDiophantineEquation(int a, int b, int c) {
    int x0;
    int y0;
    const int gcd = extendedEuclidean(a, b, x0, y0);

    std::vector<IntPair> solutions;
    if (c % gcd == 0) {
        int factor = c / gcd;
        int x = x0 * factor;
        int y = y0 * factor;

        /*
            A solution to a Diophantine equation is not unique. It is possible to form an infinite number of solutions 
            if we know one solution. If a pair(x, y) is a solution, then also all pairs
                (x + (k * b/ gcd(a, b)), y - (k * a / gcd(a, b)))
            are solutions, where k is any integer.
        */

        // Compute only solutions from 0 to 5*gcd. Estimated by the heauristic approach.
        for (int k = 0; k < 5 * gcd; ++k) {
            solutions.push_back({ x + k * (b / gcd), y - k * (a / gcd) });
        }
    }

    return solutions;
}

std::unordered_map<int, std::vector<IntPair>> groupPairsByDifference(const Cargo& arr) {
    std::unordered_map<int, std::vector<IntPair>> pairsContainer;
    for (int i = 0; i < arr.size() - 1; ++i) {
        for (int j = i + 1; j < arr.size(); ++j) {
            const auto diff = std::abs(arr[i] - arr[j]);
            pairsContainer[diff].push_back({arr[i], arr[j]});
        }
    }

    return pairsContainer;
}

int findMaxOfDistractionFromGroupsOfPairsByDifference(const std::unordered_map<int, std::vector<IntPair>>& groupsOfPairs) {
    int maxDistraction = 1;
    for (const auto item: groupsOfPairs) {
        if (item.first > maxDistraction) {
            maxDistraction = item.first;
        }
    }
    
    return maxDistraction;
}

std::vector<IntPair> findFirstTriplePossibleSolution(int x, int y, int c, const std::unordered_map<int, std::vector<IntPair>>& groupsOfPairs) {
    // Get distinct pairs.
    const auto& xGroup = groupsOfPairs.at(std::abs(x));
    const auto& yGroup = groupsOfPairs.at(std::abs(y));
    const auto& cGroup = groupsOfPairs.at(std::abs(c));

    for (int i = 0; i < xGroup.size(); ++i) {
        auto itemX = xGroup.at(i);
        for (int j = 0; j < yGroup.size(); ++j) {
            auto itemY = yGroup.at(j);
            if (!arePairDistinct(itemX, itemY)) {
                continue;
            }

            for (int k = 0; k < cGroup.size(); ++k) {
                auto itemC = cGroup.at(k);
                if (arePairDistinct(itemX, itemC) && arePairDistinct(itemY, itemC)) {
                    /*
                        Swap for correct ordering.
                        (x_0 - x_6) -> -x
                        (x_1 - x_5) -> -y
                        (x_2 - x_4) -> c
                    */
                    if (itemX.first - itemX.second == x) {
                        std::swap(itemX.first, itemX.second);
                    }
                    if (itemY.first - itemY.second == y) {
                        std::swap(itemY.first, itemY.second);
                    }
                    if (itemC.first - itemC.second == -c) {
                        std::swap(itemC.first, itemC.second);
                    }
                    
                    return { itemX, itemY, itemC };
                }
            }
        }    
    }

    return {};
}

void print_cargo(const Cargo& cargo) {
    std::cout << "{";
    for(int i = 0; i < cargo.size(); i++) {
        std::cout << cargo[i];
        if (i < cargo.size() - 1) std::cout << ", ";
    }
    std::cout << "}" << std::endl;
}

int calculate_cargo_balance(const Cargo& cargo) {
    int balance = 0;

    for(int i = 0; i < cargo.size(); i++) {
        balance += cargo[i] * (i - cargo.size() / 2);
    }
    return balance;
}

Cargo repack_cargo(Cargo cargo) {
    /*
        0 <= -3x_0 + 2x_1 + 1x_2 + 0x_3 + 1x_4 + 2x_5 + 3x_6 <= 7 ---->
        Let's find x_i when above inequality transform to eqaulity if it is equal to zero.
        3(x_6 - x_0) + 2(x_5 - x_1) + 1(x_4 - x_2) + 0x_3 = 0; => 3x + 2y + z = 0 => 3x + 2y = -z     
        We only need find at least one solution for x, y when z is in [-max, max] and then break; where 
        max is maximum of distraction between two number from [a=1, b=7];

        From precalculation we notice, that max of distraction of two number from array is 6, so then min is -6;
    */

    constexpr int a = 3;
    constexpr int b = 2;
    
    // NOTE: It possible to find all solutions by make small modifications.
    std::vector<IntPair> firstTriplePossibleSolution;

    const auto groupsOfPairs = groupPairsByDifference(cargo);
    const auto max = findMaxOfDistractionFromGroupsOfPairsByDifference(groupsOfPairs);
    for (int c = -max ; c <= max && firstTriplePossibleSolution.empty(); ++c) {
        std::vector<IntPair> solutions = findAllSolutionsOfDiophantineEquation(a, b, c);

        // std::cout << "All solutions to the Diophantine equation " << a << "x + " << b << "y = " << c << " are:" << '\n';
        for (int i = 0; i < solutions.size() && firstTriplePossibleSolution.empty(); ++i) {
            int x = solutions[i].first;
            int y = solutions[i].second;

            // Pairs are stored by key, that is as absolute value of distraction. For find pair it doesn't matter.

            // Skip pairs if distraction of pair is different than x or y.
            if (static_cast<bool>(groupsOfPairs.count(std::abs(x)) == false) || 
                static_cast<bool>(groupsOfPairs.count(std::abs(y)) == false) || 
                static_cast<bool>(groupsOfPairs.count(std::abs(c)) == false)) {
                    continue;
                }

            if ((std::abs(x) == std::abs(y)) && (std::abs(x) == std::abs(c)) && (groupsOfPairs.at(std::abs(x)).size() < 3)) {
                continue;
            }

            firstTriplePossibleSolution = findFirstTriplePossibleSolution(x, y, c, groupsOfPairs);
        }
    }
    /*
        {(x_0, x_6), (x_1, x_5), (x_2, x_4) } -> representaion of solutions 
        x_3 -> remain number from set
    */
    // Arithemetic sum of sequence [1, 2, ..., 7]
    const int checksum = (cargo[0] + cargo[cargo.size() - 1]) * 0.5 * cargo.size();

    int sum = 0;
    for (auto i = 0; i < firstTriplePossibleSolution.size(); ++i) {
        const auto& item = firstTriplePossibleSolution[i];

        cargo[i] = item.first;
        cargo[cargo.size() - 1 - i] = item.second;
        sum += item.first + item.second;
        
        cargo[cargo.size() * 0.5] = checksum - sum;
    }

    return cargo;
}

int main()
{
    Cargo cargo = {1, 2, 3, 4, 5, 6, 7};

    int sum = 0;
    for(auto item : cargo)
        sum += item;
    int limit = sum / 4;
    
    cargo = repack_cargo(cargo);
    int balance = calculate_cargo_balance(cargo);
    print_cargo(cargo);

    std::cout << "Balance = " << balance << ", while offset limit = " << limit << std::endl
              << "Cargo is" << ((std::abs(balance) <= limit) ? " " : " not ") << "balanced" << '\n';
    
    return 0;
}
