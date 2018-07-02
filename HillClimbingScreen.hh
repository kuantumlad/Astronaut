#ifndef hillclimbingscreen_hh
#define hillclimbingscreen_hh

#include <SFML/Graphics.hpp>
#include "BaseWindow.hh"
#include "Polygons.hh"
#include "ConvexPolygons.hh"
#include "Circles.hh"
#include "PolygonManager.hh"
#include "ImageManager.hh"
#include "Wiggler.hh"

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
  void setInitColorChoice(std::string);
  void setPolygonChoice(std::string);
  
  PolygonManager poly_manager;
  PolygonManager good_poly_manager;

  std::vector<Polygons> polys;
  std::vector<Polygons> good_polys;

  std::vector<ConvexPolygons> conv_poly;
  std::vector<ConvexPolygons> good_conv_poly;

  std::vector<Circles> circs;
  std::vector<Circles> good_circs;

  

};
#endif
