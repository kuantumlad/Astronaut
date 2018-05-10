//#include <SFML/Image.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main(){


  sf::Image imageIn;
  sf::Texture textureIn;
  
  if( imageIn.loadFromFile("buzz.jpg") ){
    std::cout << ">> IMAGE LOADED" << std::endl;
  }

  textureIn.loadFromImage(imageIn);
  sf::Sprite spriteIn;
  spriteIn.setTexture(textureIn,true);
  sf::Vector2u imageIn_size = imageIn.getSize();

  std::cout << ">> IMAGE IN SIZE " << imageIn_size.x << " " << imageIn_size.y << std::endl;
  double windowX = imageIn_size.x;
  double windowY = imageIn_size.y;
  
  sf::RenderWindow window(sf::VideoMode(windowX,windowY,32),"Test");

  
  while (window.isOpen() ){


    sf::Event event;
    while( window.pollEvent(event) ){
      if(event.type == sf::Event::Closed){
	window.close();
      }
      window.clear(sf::Color::Black);
      window.draw(spriteIn);
      window.display();
    }
   
  }

  return 0;
}
