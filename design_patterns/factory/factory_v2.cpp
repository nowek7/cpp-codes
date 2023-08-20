#include <assert.h>

enum class CharacterType
{
    DEMON_HUNTER,
    BARBARIAN,
    UNDEFINED
};

class Character
{
public:
    Character() = default;
    virtual CharacterType getType() const
    {
        return CharacterType::UNDEFINED;
    }
};

class DemonHunter : public Character
{
public:
    CharacterType getType() const
    {
        return CharacterType::DEMON_HUNTER;
    }
};

class Barbarian : public Character
{
public:
    CharacterType getType() const
    {
        return CharacterType::BARBARIAN;
    }
};

class FactoryCharacter
{
public:
    Character createByType(CharacterType type)
    {
        if (type == CharacterType::DEMON_HUNTER) {
            return DemonHunter();
        } else if (type == CharacterType::BARBARIAN) {
            return Barbarian();
        } else {
            return Character();
        }
    }
};

int main()
{
    FactoryCharacter fch = FactoryCharacter();
    
    {
        auto character = fch.createByType(CharacterType::DEMON_HUNTER);
        assert(character.getType() == CharacterType::DEMON_HUNTER);
    }

    {
        auto character = fch.createByType(CharacterType::BARBARIAN);
        assert(character.getType() == CharacterType::BARBARIAN);
    }
    
    return 0;
}