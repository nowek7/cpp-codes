#include <cstdio>
#include <string>
#include <vector>

class Bird
{
  std::string theString;

public:
  Bird() = default;

  auto setSong(const std::string& aString) -> void
  {
    printf("Copy assignment\n");
    theString = aString;
  }

  auto setSong(std::string&& aString) -> void
  {
    printf("Move assignment\n");
    theString = std::move(aString);
  }
};

auto makeRoastSong() -> std::string
{
  return std::string{"I'm a Roast"};
}

int main()
{
  auto bird = Bird();
  auto song = std::string("Coco");

  // Copy assignment
  bird.setSong(song);

  // Move assignment
  bird.setSong(std::move(song));

  // Move assigned
  bird.setSong(makeRoastSong());

  // Copy assignment
  auto roastSong = makeRoastSong();
  bird.setSong(roastSong);

  // Move assignment
  auto moveRoastSong = makeRoastSong();
  bird.setSong(std::move(moveRoastSong));
}