#include "Circles.hh"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

Circles::Circles(){



}


Circles::~Circles(){


}

Circles::Circles( sf::Vector2f pos, sf::Color col, float radius ){

  circle_shape.setRadius(radius);
  circle_shape.setPosition(pos);
  circle_shape.setFillColor(col);
  
}


void Circles::setCircleColor( sf::Color col ){

  circle_shape.setFillColor(col);

}

void Circles::setCirclePosition( sf::Vector2f pos ){

  circle_shape.setPosition(pos);

}


void Circles::setCircleRadius( float radius ){

  circle_shape.setRadius( radius );

}


sf::Vector2f Circles::getCirclePosition(){

  return circle_shape.getPosition();

}

sf::Color Circles::getCircleColor(){

  return circle_shape.getFillColor();

}

float Circles::getCircleRadius(){

  return circle_shape.getRadius();

}
