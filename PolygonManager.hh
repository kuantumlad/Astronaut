#ifndef polygonmanager_hh
#define polygonmanager_hh

#include <SFML/Graphics.hpp>


class PolygonManager{

public:
  PolygonManager();
  ~PolygonManager();


public:
  sf::Image orig_img;
  sf::Image poly_img;
  sf::Vector2f windowSize;
  
  

public:
  void updateImage();
  double getLoss(sf::Image,sf::Image);

  void captureScreen(sf::Texture);
  void captureOriginal(sf::Image);
  sf::Image getScreenshot(sf::RenderWindow *window);

  

};
#endif
