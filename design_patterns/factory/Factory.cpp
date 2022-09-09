#include <functional>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <typeinfo>

using namespace std::string_literals;

class Image
{
};

class BitmapImage: public Image
{
};

class PngImage: public Image
{
};

class JpgImage: public Image
{
};

struct IImageFactory
{
  virtual std::shared_ptr<Image> Create(std::string_view type) = 0;
};

struct ImageFactoryClassic: public IImageFactory
{
  virtual std::shared_ptr<Image> Create(std::string_view type) override
  {
    if (type == "bmp")
    {
      return std::make_shared<BitmapImage>();
    }
    else if (type == "png")
    {
      return std::make_shared<PngImage>();
    }
    else if (type == "jpg")
    {
      return std::make_shared<JpgImage>();
    }

    return nullptr;
  }
};

struct ImageFactory: public IImageFactory
{
  virtual std::shared_ptr<Image> Create(std::string_view type) override
  {
    static std::map<std::string, std::function<std::shared_ptr<Image>()>> factoryMap
    {
      { "bmp", []() { return std::make_shared<BitmapImage>(); } },
      { "png", []() { return std::make_shared<PngImage>(); } },
      { "jpg", []() { return std::make_shared<JpgImage>(); } }
    };

    auto it = factoryMap.find(type.data());
    return it != factoryMap.end() ? it->second() : nullptr;
  }
};

struct IImageFactoryByType
{
  virtual std::shared_ptr<Image> Create(std::type_info const& type) = 0;
};

struct ImageFactoryByType: public IImageFactoryByType
{
  virtual std::shared_ptr<Image> Create(std::type_info const& type) override
  {
    auto it = factoryMap.find(&type);
    return it != factoryMap.end() ? it->second() : nullptr;
  }

private:
  static std::map<std::type_info const*, std::function<std::shared_ptr<Image>()>> factoryMap;
};

std::map<std::type_info const*, std::function<std::shared_ptr<Image>()>> ImageFactoryByType::factoryMap
{
  { &typeid(BitmapImage), []() { return std::make_shared<BitmapImage>(); } },
  { &typeid(PngImage), []() { return std::make_shared<PngImage>(); } },
  { &typeid(JpgImage), []() { return std::make_shared<JpgImage>(); } }
};

int main()
{
  {
    auto factory = ImageFactoryClassic{};
    auto image = factory.Create("png");
  }

  {
    auto factory = ImageFactory{};
    auto image = factory.Create("png");
  }

  {
    auto factory = ImageFactoryByType{};
    auto movie = factory.Create(typeid(PngImage));
  }
}