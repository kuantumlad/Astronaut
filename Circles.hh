#ifndef circles_hh
#define circles

#include <vector>
#include <SFML/Graphics.hpp>

class Circles{

public:
  Circles();
  ~Circles();


  Circles(sf::Vector2f, sf::Color, float);

  sf::CircleShape circle_shape;
  sf::Vector2f circle_pos;
  sf::Color circle_col;

  void setCircleColor( sf::Color );
  void setCirclePosition( sf::Vector2f );
  void setCircleRadius( float );

  sf::Vector2f getCirclePosition();
  sf::Color getCircleColor();
  float getCircleRadius();

    
    
};
#endif
