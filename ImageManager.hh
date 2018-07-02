#ifndef imagemanager_hh
#define imagemanager_hh

#include <SFML/Graphics.hpp>

class ImageManager{

public:
  ImageManager();
  ImageManager(sf::Image);
  ~ImageManager();

  sf::Image temp_img;

public:

  int min_img_x;
  int min_img_y;
  int max_img_x;
  int max_img_y;

  std::vector<sf::Image> splitMainImage(int, int); // MAY RETURN IMAGE ?
  sf::Image splitImage(int, int, int, int);
  std::vector<sf::Sprite> splitImageToSprite(int,int);
  std::vector<int> getSplitImageSize();

};
#endif
