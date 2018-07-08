#ifndef polygonscreen_hh
#define polygonscreen_hh

#include <SFML/Graphics.hpp>
#include "BaseWindow.hh"
#include "Polygons.hh"
#include "ConvexPolygons.hh"
#include "Circles.hh"
#include "PolygonManager.hh"
#include "ImageManager.hh"
#include "Wiggler.hh"
#include "HillClimbingScreen.hh"


#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

class PolygonScreen : public BaseWindow{

public:
  PolygonScreen();
  ~PolygonScreen();
  PolygonScreen( sf::Image, int, std::string);
  PolygonScreen( sf::Vector2u, sf::Image, int, std::string);

public:
  sf::Event event;
  virtual int Run(sf::RenderWindow &App);

private:
  int iteration_counter;
  sf::Image true_img;
  double global_loss;
  int n_screen;
  std::string save_path;
  
public:
  void getImageToCompare(sf::RenderWindow &inWindow);
  void setWigglerLimits( sf::RenderWindow &tempWindow);
  void getTrueImage(sf::Image);
  void setWindowSize(sf::Vector2u);
  void setScreenNumber(int);
  void saveScreen(std::string, int,sf::RenderWindow &App);
  void setSavePath( std::string);
  
  Wiggler wiggle;
  PolygonManager poly_manager;
  PolygonManager good_poly_manager;

  std::vector<Polygons> polys;
  std::vector<Polygons> good_polys;

  //std::vector<ConvexPolygons> conv_poly;
  //std::vector<ConvexPolygons> good_conv_poly;

  //std::vector<Circles> circs;
  //std::vector<Circles> good_circs;

};
#endif
