#include "PolygonScreen.hh"
#include "BaseWindow.hh"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <time.h> 

PolygonScreen::PolygonScreen(){


}


PolygonScreen::~PolygonScreen(){


}


PolygonScreen::PolygonScreen( sf::Image imageIn, int npolys_to_make, std::string color_choice){
  
  srand(time(0));

  iteration_counter = 0;
  global_loss = -100000.0;
  

  getTrueImage(imageIn);

  poly_manager.getOriginalSize(imageIn);  
  good_poly_manager.getOriginalSize(imageIn);

  std::cout << " >> INIT POLYGONS IN POLYGONSCREEN CLASS: " << npolys_to_make << " " << color_choice << std::endl;
  polys = poly_manager.initPolygons(npolys_to_make, imageIn, color_choice);
  good_polys = poly_manager.initPolygons(npolys_to_make, imageIn, color_choice);
  

}

PolygonScreen::PolygonScreen( sf::Vector2u true_size, sf::Image imageIn, int npolys_to_make, std::string color_choice){
  
  srand(time(0));

  iteration_counter = 0;
  global_loss = -1000000.0;

  getTrueImage(imageIn);

  poly_manager.setWindowSize( true_size);//getOriginalSize(imageIn);  
  good_poly_manager.setWindowSize( true_size );//good_poly_manager.getOriginalSize(imageIn);

  std::cout << " >> INIT POLYGONS IN POLYGONSCREEN CLASS: " << npolys_to_make << " " << color_choice << std::endl;
  polys = poly_manager.initPolygons(npolys_to_make, imageIn, color_choice);
  good_polys = poly_manager.initPolygons(npolys_to_make, imageIn, color_choice);
 
  std::cout << " POLY VECTOR SIZE " << polys.size() << " GOOD POLYS " << good_polys.size() << std::endl;

}

void PolygonScreen::setWigglerLimits( sf::RenderWindow &tempWindow){

  std::cout << " >> SET WIGGLER POSITION LIMITS IN POLYSCREEN " << tempWindow.getSize().x << " " << tempWindow.getSize().y << std::endl;
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

  while(App.isOpen()){

  while( App.pollEvent(event) ){
    if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ){
      App.close();
      return -1;
   }
  }
  

  //std::cout << " >> ITERATION " << iteration_counter << std::endl;
  //if( iteration_counter == 0 ){
  //  App.clear(sf::Color::Black);
  //  for( int i = 0; i < polys.size(); i++ ){
  //    App.draw( polys[i].vertex_array );     
  // }

  // sf::Image poly_img = poly_manager.getScreenshot(App);
  // loss = -poly_manager.getLoss( poly_img, true_img);
  //}
  
 
  
  int poly_to_change_pos = rand() % polys.size(); 
  int poly_to_change_col = rand() % polys.size();

  //std::cout << " POLY VECTOR SIZE " << polys.size() << " GOOD POLYS " << good_polys.size() << std::endl;

  //std::cout << " >> POLY TO CHANGE POS " << poly_to_change_pos << " TO CHANGE COLOR " << poly_to_change_col << " "<<  std::endl;
 
  int vertex_to_change = rand() % 3;
  int pos_or_col = rand() % 2; 

  //std::cout << " >> CHANGING VERTEX " << vertex_to_change << " POS OR COL " << pos_or_col << std::endl;

  //std::cout << " POS OR COL " << pos_or_col << std::endl;  
  if( pos_or_col == 0 ){
    //std::cout << " CHANGING POS OF POLYGON NUMVER " << poly_to_change_pos << std::endl;
    std::vector<sf::Vector2f> temp_pos = polys[poly_to_change_pos].getPolygonsPosition();
    //std::cout << " >> BEFORE WIGGLE " << temp_pos.x << " " << temp_pos.y << std::endl;	
    wiggle.WigglePosition(temp_pos[vertex_to_change]);	
    polys[poly_to_change_pos].setPolygonsPosition(temp_pos);
    //std::cout << " >> AFTER  WIGGLE " << temp_pos.x << " " << temp_pos.y << std::endl;
  }
  else if( pos_or_col == 1 ){
    //std::cout << " CHANGING COLOR OF POLYGON NUMVER " << poly_to_change_col << std::endl;
    std::vector<sf::Color> temp_color = polys[poly_to_change_col].getPolygonsColor();
    wiggle.WiggleColor(temp_color[vertex_to_change]);
    polys[poly_to_change_col].setPolygonsColor(temp_color);
  }  

  App.clear(sf::Color::Black);
  for( int i = 0; i < polys.size(); i++ ){
    App.draw( polys[i].vertex_array );     
  }
  

  sf::Image poly_img_after  =  poly_manager.getScreenshot(App);      
  double loss = -poly_manager.getLoss( poly_img_after, true_img);
  
  if( iteration_counter % 1000 == 0 ){
    std::cout << " >> ITERATION " << iteration_counter << " CURRENT LOSS " << loss << " LOSS TO BEAT " << global_loss << std::endl;
  }
  
  //std::cout << " >> ITERATION " << iteration_counter << " CURRENT LOSS " << loss << " LOSS TO BEAT " << global_loss << std::endl;
  if( loss > global_loss ){
    global_loss = loss;	
    //std::cout << " >> LOSS IMPROVED " << global_loss << std::endl;
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
    //App.clear(sf::Color::Black);
    
    //for( int i = 0; i < polys.size(); i++ ){
    //  App.draw( polys[i].vertex_array );
    //}     
  }

  App.clear(sf::Color::Black);
  for( int i = 0; i < good_polys.size(); i++ ){
    App.draw( good_polys[i].vertex_array );     
  }

  if( iteration_counter % 10000 == 0 ){
    saveScreen(save_path, iteration_counter, App);
  }

  App.display();
  iteration_counter++;

  
  return 1;
  }
}

void PolygonScreen::setScreenNumber( int nth_screen ){

  n_screen = nth_screen;

}

void PolygonScreen::saveScreen(std::string title, int counter, sf::RenderWindow &App){

    //SAVE PICTURE HERE TO SEE EVOLUTION
    sf::Image poly_img = poly_manager.getScreenshot(App);
    std::string extension = ".png";
    std::string space = "_";
    std::string path_to_img = title + space + std::to_string(n_screen) + space + std::to_string(counter) + extension;
    poly_img.saveToFile(path_to_img);
 
}


void PolygonScreen::setSavePath( std::string temp_save_path ){
  
  save_path = temp_save_path;

}
