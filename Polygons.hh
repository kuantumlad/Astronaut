#ifndef polygons_hh
#define polygons_hh

#include <vector>
#include <SFML/Graphics.hpp>

class Polygons{

public:
  
  Polygons();
  ~Polygons();

  Polygons(std::vector<sf::Vector2f> temp_pos, std::vector<sf::Color> temp_color, int vertices );
  
  std::vector<sf::Vector2f> vertex_pos;
  std::vector<sf::Color> vertex_col;

  sf::VertexArray vertex_array;
  
  void setPolygonsColor( std::vector<sf::Color> );
  void setPolygonsPosition( std::vector<sf::Vector2f> );
  std::vector<sf::Vector2f> getPolygonsPosition();
  std::vector<sf::Color> getPolygonsColor();
  
  
};
#endif
