#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main(){

  ///////////////////////////////////////////
  //LOAD IMAGE
  sf::Image imageIn;
  sf::Image imageOriginal;
  sf::Texture textureIn;
  sf::Texture textureOg;

  if( imageIn.loadFromFile("buzz.jpg") ){
    std::cout << ">> IMAGE LOADED" << std::endl;
  }
  if( imageOriginal.loadFromFile("buzz.jpg") ){
    std::cout << ">> IMAGE LOADED" << std::endl;
  }

  

  //////////////////////////////////////////
  //APPLY IMAGE TO TEXTURE THEN SPRITE
  textureOg.loadFromImage(imageOriginal);
  sf::Sprite spriteOg;
  spriteOg.setTexture(textureOg,true);

  sf::Vector2u imageIn_size = imageIn.getSize();

   //std::cout << ">> IMAGE IN SIZE " << imageIn_size.x << " " << imageIn_size.y << std::endl;
  double windowX = imageIn_size.x;
  double windowY = imageIn_size.y;
  ////////////////////////////////////////////////
  //SET SIZE OF WINDOW TO THAT OF IMAGE DIMENSIONS
  sf::RenderWindow window(sf::VideoMode(windowX,windowY,32),"Test");
  sf::RenderWindow window2(sf::VideoMode(windowX,windowY,32),"Original");

  /////////////////////////////////////////////////  
  //MANIPULATE IMAGE HERE
  for( int i = 0; i < imageIn_size.x; i++){
    for( int j = 0; j < imageIn_size.y; j++ ){
      sf::Color pixel = imageIn.getPixel(i,j);
      int red = (int)pixel.r * 1;
      int blue = (int)pixel.b * 1;
      int green = (int)pixel.g * 1;
      
      int alpha = (int)pixel.a * 1;
      //int avg = (int)( (red + blue + green)/3 ); //GRAYSCALE
      std::vector<int> v_clr{red,blue,green}; //LIGHTNESS
      int mx_clr = *std::max_element(v_clr.begin(), v_clr.end());
      int mn_clr = *std::min_element(v_clr.begin(), v_clr.end());
      //int avg = (mx_clr + mn_clr)/2;
      //int avg = (int)( (red*0.72 + blue*0.07 + green*0.21)/3); //LUMINOSITY
      //int avg = mx_clr; //DECOMPOSING
      int avg = blue;
      //sf::Color new_pixel = sf::Color(sf::Color((sf::Uint8)red,(sf::Uint8)blue,(sf::Uint8)green,(sf::Uint8)alpha));
      sf::Color new_pixel = sf::Color(sf::Color((sf::Uint8)avg,(sf::Uint8)avg,(sf::Uint8)avg,(sf::Uint8)alpha));
      
      imageIn.setPixel(i,j,new_pixel);
    }
  }

  textureIn.loadFromImage(imageIn);
  sf::Sprite spriteIn;
  spriteIn.setTexture(textureIn,true);

  ////////////////////////////////////////////////////////
  //DISPLAY BOTH ORIGINAL AND EDITED IMAGE
  while (window2.isOpen() ){
    sf::Event event;
    while( window2.pollEvent(event) ){
      if(event.type == sf::Event::Closed){
	window2.close();
      }
      window2.clear(sf::Color::Black);
      window2.draw(spriteOg);
      window2.display();

      window.clear(sf::Color::Black);
      window.draw(spriteIn);
      window.display();
    }
  }


  

  

  return 0;
}
