#ifndef basewindow_hh
#define basewindow_hh

#include <SFML/Graphics.hpp>

class BaseWindow{

public:
  virtual int Run( sf::RenderWindow &App) = 0;

};
#endif
