#include <variant>
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <iomanip>
#include <chrono>
#include <algorithm>

using namespace std::string_literals;

template <typename CharT>
using tstring = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

template<typename CharT>
inline tstring<CharT> to_upper(tstring<CharT> text)
  {
  std::transform(std::begin(text), std::end(text), std::begin(text), toupper);
  return text;
  }

enum class Genre { Drama, Action, SF, Commedy };

struct Movie
  {
  std::string title;
  std::chrono::minutes length;
  std::vector<Genre> genre;
  };

struct Track
  {
  std::string title;
  std::chrono::seconds length;
  };

struct Music
  {
  std::string title;
  std::string artist;
  std::vector<Track> tracks;
  };

struct Software
  {
  std::string title;
  std::string vendor;
  };

using DVD = std::variant<Movie, Music, Software>;

int main()
  {
    {
      using namespace std::chrono_literals;

      std::vector<DVD> dvds
        {
        Movie{ "The Matrix"s, 2h + 16min,{ Genre::Action, Genre::SF } },
        Music{ "The Wall"s, "Pink Floyd"s,{ { "Mother"s, 5min + 32s },{ "Another Brick in the Wall"s, 9min + 8s } } },
        Software{ "Windows"s, "Microsoft"s },
        };

      // void visitor
      for (auto const & d : dvds)
        {
        std::visit(
          [](auto&& arg)
            {
            std::cout << arg.title << std::endl;
            },
          d);
        }

      // Value returning visitor
      for (const auto &d : dvds)
        {
        DVD result = std::visit(
          [](auto &&arg) -> DVD
            {
            auto cpy{ arg };
            cpy.title = to_upper(cpy.title);
            return cpy;
            }, d);

        std::visit(
          [](auto &&arg)
            {
            std::cout << arg.title << std::endl;
            }, result);
        }

      struct visitor_functor
        {
        void operator()(Movie const & arg) const
          {
          std::cout << "Movie" << std::endl;
          std::cout << "  Title: " << arg.title << std::endl;
          std::cout << "  Length: " << arg.length.count() << "min" << std::endl;
          }

        void operator()(Music const & arg) const
          {
          std::cout << "Music" << std::endl;
          std::cout << "  Title: " << arg.title << std::endl;
          std::cout << "  Artist: " << arg.artist << std::endl;

          for (auto const & t : arg.tracks)
            std::cout << "    Track: " << t.title << ", " << t.length.count() << "sec" << std::endl;
          }

        void operator()(Software const & arg) const
          {
          std::cout << "Software" << std::endl;
          std::cout << "  Title: " << arg.title << std::endl;
          std::cout << "  Vendor: " << arg.vendor << std::endl;
          }
        };

      for (const auto &d : dvds)
        std::visit(visitor_functor(), d);

      std::cout << "CONSTEXPR_IF \n";
      for (const auto & d : dvds)
        {
        std::visit([](auto&& arg)
          {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, Movie>)
            {
            std::cout << "Movie" << std::endl;
            std::cout << "  Title: " << arg.title << std::endl;
            std::cout << "  Length: " << arg.length.count() << "min" << std::endl;
            }
          else if constexpr (std::is_same_v<T, Music>)
            {
            std::cout << "Music" << std::endl;
            std::cout << "  Title: " << arg.title << std::endl;
            std::cout << "  Artist: " << arg.artist << std::endl;
            for (auto const & t : arg.tracks)
              std::cout << "    Track: " << t.title << ", " << t.length.count() << "sec" << std::endl;
            }
          else if constexpr (std::is_same_v<T, Software>)
            {
            std::cout << "Software" << std::endl;
            std::cout << "  Title: " << arg.title << std::endl;
            std::cout << "  Vendor: " << arg.vendor << std::endl;
            }
          }, d);
        }
      }

  struct foo
    {
    int value;

    explicit foo(int const i) : value(i) {}
    };

    {
      std::variant<int, double, std::string> v;
      v = 42;   // v contains int 42
      v = 42.0; // v contains double 42.0
      v = "42"; // v contains string "42"
    }

    {
      std::variant<int, double, std::string> v = 42;

      auto i1 = std::get<int>(v);
      auto i2 = std::get<0>(v);

      try
        {
        auto f = std::get<double>(v);
        }
      catch (const std::bad_variant_access  &e)
        {
        std::cout << e.what() << std::endl; // Unexpected index
        }
    }

    {
      std::variant<int, double, std::string> v = 42;
      static_assert(std::variant_size_v<decltype(v)> == 3);
      std::cout << "index = " << v.index() << std::endl;
      v = 42.0;
      std::cout << "index = " << v.index() << std::endl;
      v = "42";
      std::cout << "index = " << v.index() << std::endl;
    }

    {
      std::variant<int, double, std::string> v = 42;
      std::cout << "int? " << std::boolalpha << std::holds_alternative<int>(v) << std::endl; // int? true

      v = "42";
      std::cout << "int? " << std::boolalpha << std::holds_alternative<int>(v) << std::endl; // int? false
    }

    {
      std::variant<int, std::string, foo> v = 42;
      v.emplace<foo>(42);
    }

    {
      //std::variant<foo, int> v; // error

      std::variant<std::monostate, foo, int> v; // error
      v = 42;       // v contains int 42
      std::cout << std::get<int>(v) << std::endl;
      v = foo{ 42 }; // v contains foo{42}
      std::cout << std::get<foo>(v).value << std::endl;
    }

    {
      std::variant<int, double, std::string> v = 42;
      std::visit([](auto&& arg) {std::cout << arg << std::endl; }, v);
      v = 42.0;
      std::visit([](auto&& arg) {std::cout << arg << std::endl; }, v);

      std::visit([](auto&& arg)
        {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>)
          std::cout << "int " << arg << std::endl;
        else if constexpr (std::is_same_v<T, double>)
          std::cout << "double " << arg << std::endl;
        else if constexpr (std::is_same_v<T, std::string>)
          std::cout << "std::string " << arg << std::endl;
        }, v);
    }
  }

