#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

#include "Polygons.hh"
#include "PolygonManager.hh"
#include "Wiggler.hh"

int main(){

  srand(time(NULL));
  
  ///////////////////////////////////////////
  //LOAD IMAGE
  sf::Image imageIn;
  sf::Image imageOriginal;
  sf::Texture textureIn;
  sf::Texture textureOg;
  int pos_or_col = 0;

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

  std::vector<int> poly_pos;
  std::vector<int> poly_clr;

  PolygonManager poly_manager;
  PolygonManager good_poly_manager;
  /* GET ORIGINAL IMAGE SIZE */
  poly_manager.getOriginalSize(imageIn);  
  good_poly_manager.getOriginalSize(imageIn);  
 
 /* INIT POLYGONS */
  int npolys_to_make = 250;
  std::string color_choice = "avg";
  //std::vector<Polygons *> polys = poly_manager.initPolygons(npolys_to_make,imageIn,color_choice);
  //std::vector<Polygons *> good_polys = good_poly_manager.initPolygons(npolys_to_make,imageIn,color_choice);
  std::vector<Polygons > polys = poly_manager.initPolygons(npolys_to_make,imageIn,color_choice);
  std::vector<Polygons > good_polys = good_poly_manager.initPolygons(npolys_to_make,imageIn,color_choice);
    
  Wiggler wiggle;
  wiggle.SetWigglerPositionLimts(&window3);
  
  ////////////////////////////////////////////////////////
  //DISPLAY BOTH ORIGINAL AND EDITED IMAGE  
  double loss = 0, previous_loss = 0;
  std::vector<  std::vector<Polygons *> > img_config;
  int counter = 0, batch = 0;
  while (window.isOpen() ){
    sf::Event event;
    while( window.pollEvent(event) ){
      if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ){
	window.close();
	window3.close();
      }
    }
      window.clear(sf::Color::Black);
      window.draw(spriteOg);
      window.display();
    
      
     
      /* SET LOSS */     
      if( counter == 0 ){
	window3.clear(sf::Color::Black);
	for( int i = 0; i < polys.size(); i++ ){
	  window3.draw( polys[i].vertex_array );     
	}      
	//window3.display();
	
	sf::Image poly_img  =  poly_manager.getScreenshot(&window3);
	previous_loss = -poly_manager.getLoss( poly_img, imageIn);
      }
      //      std::cout << " >> BEGIN EVENT " << std::endl;

      sf::Image poly_img_b  =  poly_manager.getScreenshot(&window3);      
      double check_loss_1 = -poly_manager.getLoss( poly_img_b, imageIn);
      //std::cout<< " >> ITERATIONS " << counter << " LOSS BEFORE CHANGE " << check_loss_1 << " PREVIOUS LOSS " << previous_loss << std::endl;

      
      //CHOOSE POLYGON TO CHANG
      // 0 CHANGES POSITION WHILE 1 CHANGES COLORE
      int vertex_to_change = rand() % 3;
      pos_or_col = rand() % 2; 
      
      int poly_to_change_pos = rand() % polys.size(); 
      int poly_to_change_col = rand() % polys.size();
      
      //std::cout<< " >> CHANGING POLYGON " << poly_to_change_pos << " VERTEX " << vertex_to_change <<std::endl;
      if( pos_or_col == 0 ){
	//std::cout<<" >> CHANGING POSITION " << std::endl;
	std::vector<sf::Vector2f> temp_poly_pos = polys[poly_to_change_pos].getPolygonsPosition();
	wiggle.WigglePosition( temp_poly_pos[vertex_to_change] );
	polys[poly_to_change_pos].setPolygonsPosition(temp_poly_pos);
      }
      else if( pos_or_col == 1 ){
	//std::cout<< " >> CHANGING COLOR " << std::endl;
	std::vector<sf::Color> temp_poly_col = polys[poly_to_change_col].getPolygonsColor();
	wiggle.WiggleColor( (temp_poly_col[vertex_to_change]) );
	polys[poly_to_change_col].setPolygonsColor(temp_poly_col);
      }

      window3.clear(sf::Color::Black);
      for( int i = 0; i < polys.size(); i++ ){
	window3.draw( polys[i].vertex_array );     
      }      
      //window3.display();
      
      sf::Image poly_img  =  poly_manager.getScreenshot(&window3);      
      loss = -poly_manager.getLoss( poly_img, imageIn);
      ///std::cout<< " >> ITERATIONS " << counter << " LOSS " << loss << " PREVIOUS LOSS " << previous_loss << std::endl;

      if( counter % 1000 == 0 ){
	std::cout << " >> ITERATION " << counter << " CURRENT LOSS " << loss << " LOSS TO BEAT " << previous_loss << std::endl;
      }

      
      if( loss > previous_loss ){
	previous_loss = loss;	
	//std::cout << " >> LOSS IMPROVED " << previous_loss << std::endl;
	//std::cout << " >> POLYGON " << poly_to_change_pos << " IMPROVED LOSS SCORE " << std::endl;
	good_polys = polys;
      }
      else{
	//std::cout << " >> SETTING BACK TO GOOD POLYGON SET " << std::endl;
	polys = good_polys;
	window3.clear(sf::Color::Black);
	for( int i = 0; i < polys.size(); i++ ){
	  window3.draw( polys[i].vertex_array );     
	}      
	sf::Image poly_img  =  poly_manager.getScreenshot(&window3);      
	double check_loss = -poly_manager.getLoss( poly_img, imageIn);
	
	//std::cout<< " >> RESET POLYS TO GOOD POLYS CHECKING LOSS " << check_loss << std::endl;
      
      }
  
      //std::cout << " END OF EVENT " << std::endl;
      counter++;

      ////////////////////////////////////////////////
      //DRAW ONLY GOOD SET OF POLYGONS
      
      window3.clear(sf::Color::Black);
       for( int i = 0; i < polys.size(); i++ ){
	window3.draw( good_polys[i].vertex_array );     
      }     
      window3.display();
    
  }
  
  return 0;
}


