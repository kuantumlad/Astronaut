#include "BaseWindow.hh"
#include "HillClimbingScreen.hh"
#include "Polygons.hh"
#include "Circles.hh"
#include <iostream>


#include <SFML/Graphics.hpp>


HillClimbingScreen::HillClimbingScreen(){


}

HillClimbingScreen::~HillClimbingScreen(){


}


HillClimbingScreen::HillClimbingScreen(sf::Image imageIn, int npolys_to_make, std::string color_choice ){

 /* GET ORIGINAL IMAGE SIZE */

  originalTexture.loadFromImage(imageIn);
  originalSprite.setTexture(originalTexture,true);

  poly_manager.getOriginalSize(imageIn);  
  good_poly_manager.getOriginalSize(imageIn);
  //std::vector<Polygons > polys = poly_manager.initPolygons(npolys_to_make,imageIn,color_choice);
  //std::vector<Polygons > good_polys = good_poly_manager.initPolygons(npolys_to_make,imageIn,color_choice);
  

}

HillClimbingScreen::HillClimbingScreen( std::string ){




}


int HillClimbingScreen::Run(sf::RenderWindow &App){

  sf::Event event;
  while( App.pollEvent(event) ){
    if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ){
      App.close();
      return -1;
    }
  }
  
  App.clear(sf::Color::Black);
  App.draw(originalSprite);
  App.display();

  return 1;

}


