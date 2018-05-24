#ifndef wiggler_hh
#define wiggler_hh

#include <SFML/Graphics.hpp>

class Wiggler {

 public:
  Wiggler();
  ~Wiggler();

public:
  void WigglePosition(sf::Vector2f &temp_pos);
  void WiggleColor(sf::Color &temp_col);

};



#endif
