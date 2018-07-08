#include "BaseWindow.hh"
#include "HillClimbingScreen.hh"
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


