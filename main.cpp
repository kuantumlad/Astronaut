#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 


#include "Polygons.hh"

int main(){

  srand(time(NULL));
  

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
  double rendX = windowY;
  double rendY = windowX;

  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();;  
  int global_X = desktop.width/2 - rendX;
  int global_Y = desktop.height/2 - rendY;
  
  sf::Vector2i window_pos(global_X, global_Y);
  sf::Vector2i window3_pos(global_X + rendX, global_Y);
  ////////////////////////////////////////////////
  //SET SIZE OF WINDOW TO THAT OF IMAGE DIMENSIONS
  sf::RenderWindow window(sf::VideoMode(windowX,windowY,32),"Original");
  sf::RenderWindow window3(sf::VideoMode(windowX,windowY,32),"Rendered");  
  window.setPosition(window_pos);
  window3.setPosition(window3_pos);

  std::vector<sf::VertexArray*> triangles;
  std::vector<Polygons *> polys;
  /* generate secret number between 1 and 10: */

  double x = 0.0;
  double y = 0.0;
  double alpha = 0.0;
  
  int n_triangles = 100;
  std::vector<sf::Vector2f> pos;
  std::vector<sf::Color> col;
  for( int i = 0; i < n_triangles; i++ ){
    x = rand() % (int)rendX;
    y = rand() % (int)rendX;
    sf::Vector2f pos_0(x, y);
    x = rand() % (int)rendX;
    y = rand() % (int)rendX;
    sf::Vector2f pos_1(x, y);
    x = rand() % (int)rendX;
    y = rand() % (int)rendX;
    sf::Vector2f pos_2(x, y);

    alpha = rand() % 255;
    sf::Color col_0(10,100,200,alpha);
    alpha = rand() % 255;
    sf::Color col_1(200,200,200,alpha);
    alpha = rand() % 255;
    sf::Color col_2(50,50,50,alpha);

    pos.push_back(pos_0);
    pos.push_back(pos_1);
    pos.push_back(pos_2);

    col.push_back(col_0);
    col.push_back(col_1);
    col.push_back(col_2);
    polys.push_back( new Polygons( pos, col, 3 ) );

    pos.clear();
    col.clear();
  }

  ////////////////////////////////////////////////////////////////////////////
  //CALCULATE THE LOSS
  sf::Vector2u windowSize = window3.getSize();
  sf::Texture texture;
  texture.create(windowSize.x, windowSize.y);
  texture.update(window3);
  sf::Image screenshot = texture.copyToImage();

  
  double temploss = 0;
  for( int i = 0; i < windowSize.x; i++ ){
    for( int j = 0; j < windowSize.y; j++ ){
      sf::Color screenshot_pixel = screenshot.getPixel(i,j);
      sf::Color original_pixel = imageIn.getPixel(i,j);

      int red = (int)screenshot_pixel.r;
      int blue = (int)screenshot_pixel.b;
      int green = (int)screenshot_pixel.g;      
      int alpha = (int)screenshot_pixel.a;

      int og_red = (int)original_pixel.r;
      int og_blue = (int)original_pixel.b;
      int og_green = (int)original_pixel.g;      
      int og_alpha = (int)original_pixel.a;

      int delta_red = pow( red - og_red, 2);
      int delta_blue = pow( blue - og_blue, 2);
      int delta_green = pow( green - og_green, 2);
      int delta_alpha = pow( alpha - og_alpha, 2);
      double pixel_chi = (delta_red + delta_blue + delta_green + delta_alpha)/(256.0*256.0*16.0);
      
      temploss = temploss + pixel_chi;
      //std::cout << " >> " << temploss << std::endl;
    }
  }
  ////////////////////////////////////////////////////////////////////////////

  
  ////////////////////////////////////////////////////////
  //DISPLAY BOTH ORIGINAL AND EDITED IMAGE  
  while (window.isOpen() ){
    sf::Event event;
    while( window.pollEvent(event) ){
      if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ){
	window.close();
	window3.close();
      }
      window.clear(sf::Color::Black);
      window.draw(spriteOg);
      window.display();
    
      
      window3.clear(sf::Color::Black);
      for( int i = 0; i < polys.size(); i++ ){
	window3.draw( polys[i]->vertex_array );     
      }
      window3.display();


      
   
    }
  }
  
  return 0;
}
