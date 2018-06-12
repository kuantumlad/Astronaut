#include "Polygons.hh"
#include <SFML/Graphics.hpp>  
#include <vector>
#include <iostream>


Polygons::Polygons(){

  /*
  Polygon.AddPoint(0, -50,  sf::Color(255, 0, 0),     sf::Color(0, 128, 128));
  Polygon.AddPoint(50, 0,   sf::Color(255, 85, 85),   sf::Color(0, 128, 128));
  Polygon.AddPoint(50, 50,  sf::Color(255, 170, 170), sf::Color(0, 128, 128));
  Polygon.AddPoint(0, 100,  sf::Color(255, 255, 255), sf::Color(0, 128, 128));
  Polygon.AddPoint(-50, 50, sf::Color(255, 170, 170), sf::Color(0, 128, 128));
  Polygon.AddPoint(-50, 0,  sf::Color(255, 85, 85),   sf::Color(0, 128, 128));
  */

  
}


Polygons::~Polygons(){

}


Polygons::Polygons(std::vector<sf::Vector2f> pos, std::vector<sf::Color> col, int vertices ){

  vertex_pos = pos;
  vertex_col = col;

  vertex_array.setPrimitiveType(sf::Triangles);
  vertex_array.resize(3);
  
  setPolygonsPosition(pos);
  setPolygonsColor(col);
  
}


Polygons::Polygons( int vertices ){

  convex_shape.setPointCount(vertices);


}

void Polygons::setPolygonsColor( std::vector<sf::Color> col ){

  vertex_col = col;

  //std::cout << (int)col[1].r << std::endl;
  //std::cout << (int)col[1].g << std::endl;
  //std::cout << (int)col[1].b << std::endl;
  
  (vertex_array[0]).color = vertex_col[0];
  (vertex_array[1]).color = vertex_col[1];
  (vertex_array[2]).color = vertex_col[2];

  
}


void Polygons::setPolygonsPosition( std::vector<sf::Vector2f> pos ){

  vertex_pos = pos;
  (vertex_array[0]).position = vertex_pos[0];
  (vertex_array[1]).position = vertex_pos[1];
  (vertex_array[2]).position = vertex_pos[2];

  
}



std::vector<sf::Vector2f> Polygons::getPolygonsPosition(){

  return vertex_pos;

}

std::vector<sf::Color> Polygons::getPolygonsColor(){

  return vertex_col;

}

void Polygons::setConvexPolygonsColor( std::vector<sf::Color> col ){



}


void Polygons::setConvexPolygonsPosition( std::vector<sf::Vector2f> pos){


}

