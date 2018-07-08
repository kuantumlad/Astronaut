#ifndef polygonmanager_hh
#define polygonmanager_hh

#include <SFML/Graphics.hpp>
#include "Polygons.hh"
#include "ConvexPolygons.hh"
#include "Circles.hh"

class PolygonManager{

public:
  PolygonManager();
  ~PolygonManager();


public:
  sf::Image orig_img;
  sf::Image poly_img;
  sf::Vector2u windowSize;
  //double temploss;
  //std::vector<Polygons *> polys;

  

public:
  
  void updateImage();
  double getLoss(sf::Image,sf::Image);
  int getPolyVertexToChange();

  void captureScreen(sf::Texture);
  void getOriginalSize(sf::Image);
  sf::Image getScreenshot(sf::RenderWindow &window);

  int getRandomPolygonToChange(int,int, std::vector<int> );
  std::vector<int> checkConvexShape(ConvexPolygons);
  void setWindowSize( sf::Vector2u );

  //std::vector<Polygons *> initPolygons(int,sf::Image,std::string clr_choice);
  std::vector<Polygons> initPolygons(int,sf::Image,std::string clr_choice);
  std::vector<ConvexPolygons> initConvexPolygons(int,sf::Image,std::string clr_choice, int);
  std::vector<Circles> initCircles(int, sf::Image, std::string clr_choice);
  std::vector<int> getAverageImgColor(sf::Image image);
  std::vector<int> setPolyColor(std::string);
  

};
#endif
