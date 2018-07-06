#include "BaseWindow.hh"
#include "PolygonScreen.hh"
#include <iostream>

#include <SFML/Graphics.hpp>

PolygonScreen::PolygonScreen(){


}


PolygonScreen::~PolygonScreen(){


}


PolygonScreen::PolygonScreen( sf::Image imageIn, int npolys_to_make, std::string color_choice){
  
  iteration_counter = 0;
  global_loss = 0.0;

  getTrueImage(imageIn);

  poly_manager.getOriginalSize(imageIn);  
  good_poly_manager.getOriginalSize(imageIn);

  std::cout << " >> INIT POLYGONS IN POLYGONSCREEN CLASS: " << npolys_to_make << " " << color_choice << std::endl;
  polys = poly_manager.initPolygons(npolys_to_make, imageIn, color_choice);
  good_polys = good_poly_manager.initPolygons(npolys_to_make, imageIn, color_choice);
 

}

PolygonScreen::PolygonScreen( sf::Vector2u true_size, sf::Image imageIn, int npolys_to_make, std::string color_choice){
  
  iteration_counter = 0;
  global_loss = 0.0;

  getTrueImage(imageIn);

  poly_manager.setWindowSize( true_size);//getOriginalSize(imageIn);  
  good_poly_manager.setWindowSize( true_size );//good_poly_manager.getOriginalSize(imageIn);

  std::cout << " >> INIT POLYGONS IN POLYGONSCREEN CLASS: " << npolys_to_make << " " << color_choice << std::endl;
  polys = poly_manager.initPolygons(npolys_to_make, imageIn, color_choice);
  good_polys = good_poly_manager.initPolygons(npolys_to_make, imageIn, color_choice);
 

}

void PolygonScreen::setWigglerLimits( sf::RenderWindow &tempWindow){

  wiggle.SetWigglerPositionLimts(&tempWindow);

}


void PolygonScreen::setWindowSize( sf::Vector2u temp_size ){

  std::cout << " POLYGONS SCREEN GET WINDOW SIZE " << temp_size.x << " " << temp_size.y << std::endl;
  poly_manager.setWindowSize( temp_size );
  good_poly_manager.setWindowSize( temp_size );

}


void PolygonScreen::getTrueImage(sf::Image temp_img){

  true_img = temp_img;

}

int PolygonScreen::Run(sf::RenderWindow &App){

  sf::Event event;
  while( App.pollEvent(event) ){
    if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ){
      App.close();
    }
  }
  App.clear(sf::Color::Black);

  //std::cout << " >> ITERATION " << iteration_counter << std::endl;
  if( iteration_counter == 0 ){
    for( int i = 0; i < polys.size(); i++ ){
      App.draw( polys[i].vertex_array );     
    }

    sf::Image poly_img  =  poly_manager.getScreenshot(&App);
    global_loss = -poly_manager.getLoss( poly_img, true_img);
  }

 
  
  int poly_to_change_pos = rand() % polys.size(); 
  int poly_to_change_col = rand() % polys.size();
  int change_shape = rand() % polys.size();
  
  int vertex_to_change = rand() % 3;
  int pos_or_col = rand() % 2; 
  //std::cout << " WIGGLE CIRCLE SHAPE " << change_shape <<  std::endl;


  //std::cout << " POS PR COL " << pos_or_col << std::endl;  
  if( pos_or_col == 0 ){
    std::vector<sf::Vector2f> temp_pos = polys[change_shape].getPolygonsPosition();
    //std::cout << " >> BEFORE WIGGLE " << temp_circ_pos.x << " " << temp_circ_pos.y << std::endl;	
    wiggle.WigglePosition(temp_pos[vertex_to_change]);	
    polys[change_shape].setPolygonsPosition(temp_pos);
    //std::cout << " >> AFTER  WIGGLE " << conv_point.x << " " << conv_point.y << std::endl;
  }
  else{
    std::vector<sf::Color> temp_color = polys[change_shape].getPolygonsColor();
    wiggle.WiggleColor(temp_color[vertex_to_change]);
    polys[change_shape].setPolygonsColor(temp_color);
  }  

  App.clear(sf::Color::Black);
  for( int i = 0; i < polys.size(); i++ ){
    App.draw( polys[i].vertex_array );     
  }
  
  sf::Image poly_img_after  =  poly_manager.getScreenshot(&App);      
  double loss = -poly_manager.getLoss( poly_img_after, true_img);
  
  if( iteration_counter % 1000 == 0 ){
    std::cout << " >> ITERATION " << iteration_counter << " CURRENT LOSS " << loss << " LOSS TO BEAT " << global_loss << std::endl;
  }
  

  if( loss > global_loss ){
    global_loss = loss;	
    //  std::cout << " >> LOSS IMPROVED " << global_loss << std::endl;
    //std::cout << " >> POLYGON " << poly_to_change_pos << " IMPROVED LOSS SCORE " << std::endl;
    //good_polys = polys;
    //good_conv_poly = conv_poly;
    good_polys = polys;
  }
  else{
    //std::cout << " >> SETTING BACK TO GOOD POLYGON SET " << std::endl;
    //polys = good_polys;
    //conv_poly = good_conv_poly;
    polys = good_polys;
    App.clear(sf::Color::Black);
    
    for( int i = 0; i < polys.size(); i++ ){
      App.draw( polys[i].vertex_array );
    }     
  }

  iteration_counter++;

  App.clear(sf::Color::Black);
  for( int i = 0; i < good_polys.size(); i++ ){
    App.draw( good_polys[i].vertex_array );     
  }

  App.display();

  return 1;

}

