#ifndef wiggler_hh
#define wiggler_hh

#include <SFML/Graphics.hpp>

class Wiggler {

 public:
  Wiggler();
  ~Wiggler();

public:
  int min_lim;
  int max_lim;
  void SetWigglerPositionLimts(int, int);
  void WigglePosition(sf::Vector2f &temp_pos);
  void WiggleColor(sf::Color &temp_col);

};



#endif
