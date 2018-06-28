#ifndef wiggler_hh
#define wiggler_hh

#include <SFML/Graphics.hpp>
#include "PolygonManager.hh"

class Wiggler {

 public:
  Wiggler();
  ~Wiggler();

public:

  PolygonManager poly_mang;

  int min_lim_x;
  int max_lim_x;
  int min_lim_y;
  int max_lim_y;
  void SetWigglerPositionLimts(sf::RenderWindow *window);
  void WigglePosition(sf::Vector2f &temp_pos);
  void WiggleColor(sf::Color &temp_col);
  void WiggleConvexPolygon(ConvexPolygons, sf::Vector2f &temp_pos);
  void WiggleRadius(float &temp);

};



#endif
