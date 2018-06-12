#ifndef convexpolygons_hh
#define convexpolygons_hh

#include <vector>
#include <SFML/Graphics.hpp>

class ConvexPolygons{

public:
  
  ConvexPolygons();
  ~ConvexPolygons();

  ConvexPolygons(std::map< int, sf::Vector2f >, sf::Vector2f, sf::Color, int vertices);
  
  std::vector<sf::Vector2f> vertex_pos;
  std::vector<sf::Color> vertex_col;

  sf::ConvexShape convex_shape;
  
  void setConvexPolygonsColor( sf::Color );
  void setConvexPolygonsPosition( sf::Vector2f );
  void setConvexPolygonsPoint( int, sf::Vector2f );
    
  sf::Vector2f getConvexPolygonsPosition();
  sf::Color getConvexPolygonsColor();
  sf::Vector2f getConvexPolygonsPoint(int);
  int getNumVertices();
  
};
#endif
