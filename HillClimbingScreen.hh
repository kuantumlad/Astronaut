#ifndef hillclimbingscreen_hh
#define hillclimbingscreen_hh

#include "BaseWindow.hh"

#include <SFML/Graphics.hpp>

class HillClimbingScreen : public BaseWindow {


public:
  HillClimbingScreen();
  ~HillClimbingScreen();

  HillClimbingScreen(sf::Image, int, std::string);// std::vector<Polygons>, std::vector<Polygons>);
  HillClimbingScreen(std::string);


public:
  virtual int Run(sf::RenderWindow &App);

public:

  sf::Image originalImage;
  sf::Texture originalTexture;
  sf::Sprite originalSprite;

  int n_polys;
  std::string init_color;
  

};
#endif
