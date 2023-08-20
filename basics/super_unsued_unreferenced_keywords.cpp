#include <iostream>

void print([[maybe_unused]]bool fullVerbosed)
{
#ifdef USED_VALUE
    std::cout << "Hello - verbose" << '\n';
#endif // USED_VALUE
 // rest
}

#ifdef Win32
void print_WIN(bool fullVerbose)
{
    UNREFERENCED_PARAMETER(fullVerbose);
    std::cout << "Hello from Windows" << '\n';
}
#endif

// keyword super

class Parent
{
public:
    virtual void validate() {
        std::cout << "Validate from Parent" << '\n';
    };
};

typedef Parent _super;

class Child : public Parent
{
public:
    void validate() override {
        _super::validate();
        std::cout << "Validate from Child" << '\n';
    };
};

typedef Child __super;

class BlondeChild final : public Child
{
public:
    void validate() override
    {
        __super::validate();
    }
};


[[deprecated ("NDIS 6.8 does not support filters registry")]]
void EnableFilters()
{

}

int main()
{
    Parent parent;
    Child child;

    Parent* ptr =  new [[no_except]] Parent();
    delete ptr;

    return 0;
}