#include <map>
#include <string>
#include <string_view>

class PartsStore {

    struct Part {
        std::string _name;
        bool _isAvailable { false };
    };

public:
    PartsStore(const std::map<int, Part>& parts) : _parts(parts) { }

    bool Contains(std::string_view name) const;

    bool IsAvailable(std::string_view name);

    void SetAvailability(std::string_view name, bool isAvailable);

private:
    std::map<int, Part> _parts;
};

#include <iostream>
#include "store.h"

namespace {
    template <typename T>
    auto FindByNameImpl(std::string_view name, T& container) {
        auto it = std::find_if(begin(container), end(container), [&name](const auto& entry) {
            return entry.second._name == name;
        });

        return it != end(container) ? &it->second : nullptr;
    }
}

// implementation..
bool PartsStore::Contains(std::string_view name) const {
    return FindByNameImpl(name, _parts) != nullptr;
}

bool PartsStore::IsAvailable(std::string_view name) {
    auto it = FindByNameImpl(name, _parts);
    return it ? it->_isAvailable : false;
}

void PartsStore::SetAvailability(std::string_view name, bool isAvailable) {
    auto it = FindByNameImpl(name, _parts);
    if (it)
        it->_isAvailable = isAvailable;
}

int main() {
	PartsStore store( {
        { 1, { "box" } },
        { 2, { "tv" } },
    });

    std::cout << store.Contains("box") << '\n';
    std::cout << store.Contains("apple") << '\n';

    store.SetAvailability("box", false);
}