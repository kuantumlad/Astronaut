#include "ConvexPolygons.hh"
#include <SFML/Graphics.hpp>  
#include <vector>
#include <iostream>


ConvexPolygons::ConvexPolygons(){


  
}


ConvexPolygons::~ConvexPolygons(){

}


ConvexPolygons::ConvexPolygons(std::map< int, sf::Vector2f > con_map, sf::Vector2f pos, sf::Color col, int vertices ){

  convex_shape.setPointCount(vertices);
  
  for (std::map<int,sf::Vector2f >::iterator it=con_map.begin(); it!=con_map.end(); ++it){
    std::cout << " >> IN CP " << it->first << " " << it->second.x << " " << it->second.y << std::endl;
    convex_shape.setPoint( it->first, it->second ); 
  }

  convex_shape.setFillColor(col);
  convex_shape.setPosition(pos);  
  
}



void ConvexPolygons::setConvexPolygonsColor( sf::Color col ){

  convex_shape.setFillColor(col);
  
}


void ConvexPolygons::setConvexPolygonsPosition( sf::Vector2f pos ){

  convex_shape.setPosition(pos);
  
}


void ConvexPolygons::setConvexPolygonsPoint( int vertex, sf::Vector2f pos ){

  convex_shape.setPoint(vertex, pos);
  
}


sf::Vector2f ConvexPolygons::getConvexPolygonsPosition(){

  return convex_shape.getPosition();
  

}

sf::Vector2f ConvexPolygons::getConvexPolygonsPoint(int vertex){

  return convex_shape.getPoint(vertex);
  

}

sf::Color ConvexPolygons::getConvexPolygonsColor(){

  return convex_shape.getFillColor();

}

int ConvexPolygons::getNumVertices(){

  return convex_shape.getPointCount();
}


int ConvexPolygons::getFurthestVertex(){

  int n_vertices = getNumVertices();
  sf::Vector2f center = convex_shape.getOrigin();
  std::cout<< " >> CENTER ? " << center.x << " " << center.y << std::endl;
  double max_dist = 0.0;
  int max_index = -1;
  for( int i = 0; i < n_vertices; i++ ){
    
    double x = getConvexPolygonsPoint(i).x;
    double y = getConvexPolygonsPoint(i).y;

    double dist = sqrt( (x-center.x)*(x-center.x) + (y - center.y)*(y - center.y));
    std::cout << " >> DIST " << dist << " MAX DIST " << max_dist << std::endl;
    if( dist > max_dist ){
      max_dist = dist;
      max_index = i;
    }
  }

  return max_index;
}
