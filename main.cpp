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

  if( imageIn.loadFromFile("black_triangle.jpg") ){
    std::cout << ">> IMAGE LOADED" << std::endl;
    
  }
  if( imageOriginal.loadFromFile("black_triangle.jpg") ){
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
  int npolys_to_make = 150;
  std::string color_choice = "avg";
  //  std::vector<Polygons *> polys = poly_manager.initPolygons(npolys_to_make,imageIn,color_choice);
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
	sf::Image poly_img  =  poly_manager.getScreenshot(&window3);
	previous_loss = -poly_manager.getLoss( poly_img, imageIn);
      }


      //CHOOSE POLYGON TO CHANGE
      int vertex_to_change = rand() % 3;
      pos_or_col = rand() % 2; // 0 CHANGES POSITION WHILE 1 CHANGES COLOR
      
      int poly_to_change_pos = rand() % polys.size(); 
      int poly_to_change_color = rand() % polys.size();
      
      std::cout<< " >> CHANGING POLYGON " << poly_to_change_pos << " VERTEX " << vertex_to_change <<std::endl;
      if( pos_or_col == 0 ){
	std::cout<<" >> CHANGING POSITION " << std::endl;
	std::vector<sf::Vector2f> temp_poly_pos = polys[poly_to_change_pos].getPolygonsPosition();
	wiggle.WigglePosition( temp_poly_pos[vertex_to_change] );
	polys[poly_to_change_pos].setPolygonsPosition(temp_poly_pos);
      }
      else if( pos_or_col == 1 ){
	std::cout<< " >> CHANGING COLOR " << std::endl;
	std::vector<sf::Color> temp_poly_col = polys[poly_to_change_pos].getPolygonsColor();
	wiggle.WiggleColor( (temp_poly_col[vertex_to_change]) );
	polys[poly_to_change_pos].setPolygonsColor(temp_poly_col);
      }
      
      sf::Image poly_img  =  poly_manager.getScreenshot(&window3);      
      loss = -poly_manager.getLoss( poly_img, imageIn);
      std::cout<< " >> ITERATIONS " << counter << " LOSS " << loss << " PREVIOUS LOSS " << previous_loss << std::endl;

      if( loss > previous_loss ){
	previous_loss = loss;	
	std::cout << " >> LOSS IMPROVED " << previous_loss << std::endl;
	std::cout << " >> POLYGON " << poly_to_change_pos << " IMPROVED LOSS SCORE " << std::endl;
	std::vector<Polygons> temp_polys = polys;
	polys = temp_polys;
	good_polys = temp_polys;
      }
      else{
	//	std::cout << " >> SETTING BACK TO GOOD POLYGON SET " << std::endl;
	polys = good_polys;

	//for( int i = 0; i < good_polys.size(); i++ ){
	//  polys[i]->setPolygonsPosition( good_polys[i]->getPolygonsPosition() );
	//  polys[i]->setPolygonsColor( good_polys[i]->getPolygonsColor() );

	//}
	if (poly_to_change_pos == 50 ){
	int k = 50;
	int test_1x = good_polys[k].getPolygonsPosition()[0].x;
	int test_1y = good_polys[k].getPolygonsPosition()[0].y;
	int test_2x = good_polys[k].getPolygonsPosition()[0].x;
	int test_2y = good_polys[k].getPolygonsPosition()[0].y;
	int test_3x = good_polys[k].getPolygonsPosition()[0].x;
	int test_3y = good_polys[k].getPolygonsPosition()[0].y;

	int t1x = polys[k].getPolygonsPosition()[0].x;
	int t1y = polys[k].getPolygonsPosition()[0].y;
	int t2x = polys[k].getPolygonsPosition()[0].x;
	int t2y = polys[k].getPolygonsPosition()[0].y;
	int t3x = polys[k].getPolygonsPosition()[0].x;
	int t3y = polys[k].getPolygonsPosition()[0].y;
	
	//std::cout << " >> SHOULDNT BE CHANGING UNESS LOSS IMPROVED " << std::endl;
	std::cout << " >> " << test_1x << " " << test_1y << " " << test_2x << " " << test_2y << " " << test_3x << " " << test_3y << std::endl;
	std::cout << " >> TEST POLY " << t1x << " " << t1y << " " << t2x << " " << t2y << " " << t3x << " " << t3y << std::endl;
	}
      }
      counter++;

      ////////////////////////////////////////////////
      //CHECK TO SEE IF POLYGONS ARE CHANGING WHEN THEY SHUOLDNT 
      
      window3.clear(sf::Color::Black);
       for( int i = 0; i < polys.size(); i++ ){
	window3.draw( good_polys[i].vertex_array );     
      }
     
      window3.display();
    
  }
  
  return 0;
}


