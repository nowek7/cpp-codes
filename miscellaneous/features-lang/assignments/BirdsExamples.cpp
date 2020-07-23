#include <iostream>
#include <vector>
#include <string>

class Bird
  {
  public:
    Bird()
      {}

    // Copy assign
    auto setSong(const std::string &aString) { theString = aString; }

    // Move assign.
    auto setSong(std::string &&aString) { theString = std::move(aString); }

    // Fields.
    std::string theString;
  };

auto makeRoastSong()
  {
  return std::string{"I'm a Roast"};
  }

int main()
  {
  auto bird = Bird();
  auto song = std::string("Coco");

  // Copy-assigned
  bird.setSong(song);

  // Move-assigned
  bird.setSong(std::move(song));

  // Copy-assigned
  bird.setSong(makeRoastSong());

  // Copy-assigned
  auto roastSong = makeRoastSong();
  bird.setSong(roastSong);

  // Copy-assigned
  const auto roastSong = makeRoastSong();
  bird.setSong(std::move(roastSong));
  }