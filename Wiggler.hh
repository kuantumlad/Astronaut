#ifndef wiggler_hh
#define wiggler_hh

#include <SFML/Graphics.hpp>

class Wiggler {

 public:
  Wiggler();
  ~Wiggler();

public:
  int min_lim_x;
  int max_lim_x;
  int min_lim_y;
  int max_lim_y;
  void SetWigglerPositionLimts(sf::RenderWindow *window);
  void WigglePosition(sf::Vector2f &temp_pos);
  void WiggleColor(sf::Color &temp_col);

};



#endif
