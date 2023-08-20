#pragma once

#include <type_traits>
#include <algorithm>
#include <cstring>
#include <string>

template<typename Char>
class String
{
    public:
        String(const char* chars)
        {
            const std::size_t length = strlen(chars);

            m_chars = new char[length + 1];
            for (std::size_t i = 0; i < length; ++i)
            {
                m_chars[i] = chars[i];
            }
            m_chars[length] = '\0';
        }

        String(std::string str) :
            String(str.c_str())
        {
        }

        String(const String& rhs)
        {
            if (this != &rhs)
            {
                delete[] m_chars;
                m_chars = nullptr;
                if (rhs.m_chars)
                {
                    const std::size_t length = rhs.length();

                    m_chars = new char[length + 1];
                    for (std::size_t i = 0; i < length; ++i)
                    {
                        m_chars[i] = rhs.m_chars[i];
                    }
                    m_chars[length] = '\0';
                }
            }
        }

        ~String()
        {
            if (m_chars)
            {
                delete[] m_chars;
                m_chars = nullptr;
            }
        }

        template<typename OtherChar>
        String& operator+(const String<OtherChar>& rhs)
        {
            const std::size_t rhsLength = rhs.length();
            if (rhsLength > 0)
            {
                const std::size_t length = this->length();
                char* tmp = new char[length + rhsLength];

                std::size_t i = 0;
                for (; i < length; ++i)
                {
                    tmp[i] = m_chars[i];
                }

                for (; i < length + rhsLength; ++i)
                {
                    tmp[i] = rhs.m_chars[i];
                }
                m_chars[length + rhsLength] = '\0';

                delete[] m_chars;
                m_chars = tmp;
            }
            return *this;
        }

        bool operator==(const String& rhs)
        {
            if (this == &rhs)
            {
                return true;
            }

            if (length() != rhs.length())
            {
                return false;
            }

            for (std::size_t i = 0; i < length(); ++i)
            {
                if (m_chars[i] != rhs.m_chars[i])
                {
                    return false;
                }
            }

            return true;
        }

        bool operator!=(const String& rhs)
        {
            return !(*this == rhs);
        }

        String& operator+=(Char c)
        {
            if (m_chars)
            {
                const std::size_t length = this->length();
                char* tmp = new char[length + 2];

                for (std::size_t i = 0; i < length; ++i)
                {
                    tmp[i] = m_chars[i];
                }
                tmp[length] = c;
                tmp[length + 1] = '\0';

                delete[] m_chars;
                m_chars = tmp;
            }
            else
            {
                m_chars = new char[2]{c, '\0'};
            }

            return *this;
        }

        Char& operator[](const int& idx)
        {
            if (m_chars)
            {
                if (idx >= 0 && strlen(m_chars) > static_cast<std::size_t>(idx))
                {
                    return m_chars[idx];
                }
                else
                {
                    throw std::out_of_range("Index value not in expected range!");
                }
            }
            else
            {
                throw std::logic_error("Unexpected access to uninitialized variable!");
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const String<Char>& me)
        {
            os << me.m_chars;
            return os;
        }

        std::size_t length() const
        {
            return m_chars ? strlen(m_chars) : 0;
        }

        bool empty()
        {
            return m_chars ? strlen(m_chars) == 0 : false;
        }

    private:
        Char* m_chars = nullptr;
};