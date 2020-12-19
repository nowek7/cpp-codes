#include <iostream>

int main()
	{
	auto equation = [](const double &aValue)
		{
		return (aValue * aValue) - 5;
		};

	double left = 1;
	const double right = 10;
	std::cout << "Find solution of equation -> x * x - 5 = 0 in interval [1, 10]" << std::endl;

	double error = 1;
	while (error > 0.0001)
		{
		left = -((equation(left) * (right - left)) / (equation(right) - equation(left))) + left;
		error = std::abs(equation(left) * 0.5);

		#ifdef _DEBUG
			std::cout << "Error -> " << error << std::endl;
		#endif // !_DEBUG
		}

	std::cout << "Solution of equation -> " << left << std::endl;
	std::cout << "Error -> " << error << std::endl;

	return 0;
	}
