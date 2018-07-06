#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

#include "Polygons.hh"
#include "ConvexPolygons.hh"
#include "Circles.hh"
#include "PolygonManager.hh"
#include "ImageManager.hh"
#include "Wiggler.hh"
#include "HillClimbingScreen.hh"
#include "PolygonScreen.hh"


int main(int argc, char* argv[]){
//const char* poly_input
  srand(time(NULL));
  
  ///////////////////////////////////////////
  //LOAD IMAGE
  sf::Image imageIn;
  sf::Image imageOriginal;
  sf::Texture textureIn;
  sf::Texture textureOg;
  int pos_or_col = 0;

  std::string poly_type = "POLY";
  std::string cv_type = "CONVPOLY";
  std::string circ_type = "CIRC";
  int mode;

  std::cout << " >> STARTING ANALYSIS FOR " << argv[1] << std::endl;

  if( argv[1] == poly_type ){
    mode = 0;
  }
  else if( argv[1] == cv_type ){
    mode = 1;
  }
  else if( argv[1] == circ_type ){
    mode = 2;
  }
  
  if( imageIn.loadFromFile("amanda_2.png") ){
    std::cout << ">> IMAGE LOADED" << std::endl;
    
  }
  if( imageOriginal.loadFromFile("amanda_2.png") ){
    std::cout << ">> IMAGE LOADED" << std::endl;
  }

  std::string title = "AMANDA";
 
  //////////////////////////////////////////
  //APPLY IMAGE TO TEXTURE THEN SPRITE
  textureOg.loadFromImage(imageOriginal);
  sf::Sprite spriteOg;
  spriteOg.setTexture(textureOg,true);


  ////////////////////////////////////////////
  //WINDOW IMAGE INFORMATION
  sf::Vector2u imageIn_size = imageIn.getSize();

  double windowX = imageIn_size.x;
  double windowY = imageIn_size.y;
  double rendX = windowY;
  double rendY = windowX;

  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();;  
  int global_X = desktop.width/4 - rendX;
  int global_Y = desktop.height/2 - rendY;
  
  sf::Vector2i window_pos(global_X, global_Y);
  sf::Vector2i window3_pos(global_X + rendX, global_Y);

  ////////////////////////////////////////////////
  //SET SIZE OF WINDOW TO THAT OF IMAGE DIMENSIONS
  sf::RenderWindow window(sf::VideoMode(windowX,windowY,32),"Original");
  sf::RenderWindow window3(sf::VideoMode(windowX,windowY,32),"Rendered");  
  //sf::RenderWindow window3(sf::VideoMode(500,500,32),"Rendered");  
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
  int npolys_to_make = 10;
  std::string color_choice = "avg";
 
  /* USE TRIANGLES */
  std::vector<Polygons > polys = poly_manager.initPolygons(npolys_to_make,imageIn,color_choice);
  std::vector<Polygons > good_polys = good_poly_manager.initPolygons(npolys_to_make,imageIn,color_choice);

  /* USE N SIDED POLYGONS */
  std::vector<ConvexPolygons> conv_poly = poly_manager.initConvexPolygons(npolys_to_make, imageIn, color_choice, 7);
  std::vector<ConvexPolygons> good_conv_poly = good_poly_manager.initConvexPolygons(1, imageIn, color_choice, 7);

  /* USE CIRCLES */
  std::vector<Circles> circs = poly_manager.initCircles(npolys_to_make, imageIn, color_choice);
  std::vector<Circles> circs_good = poly_manager.initCircles(npolys_to_make, imageIn, color_choice); 
    
  Wiggler wiggle;
  wiggle.SetWigglerPositionLimts(&window3);
  
  ////////////////////////////////////////////////////////
  //DISPLAY BOTH ORIGINAL AND EDITED IMAGE  
  double loss = 0, previous_loss = 0;

  int counter = 0, batch = 0;

  ////////////////////////////////
  // TEST IMAGEMANAGER
  //

  ImageManager img_manager(imageIn);
  std::vector< sf::Image > image_section = img_manager.splitMainImage(4,4);
  std::cout << " >> NUMBER OF SCREENS TO CREATE " << image_section.size() << std::endl;
  std::vector<int> img_sizes = img_manager.getSplitImageSize();
  std::cout << " IMG SIZE " << img_sizes[3] << std::endl;

  std::vector< sf::RenderWindow* > my_windows;
  std::vector< sf::RenderWindow* > my_poly_windows;
  std::vector< HillClimbingScreen* > my_hcs;
  std::vector< PolygonScreen* > my_polys;
  std::vector< sf::Vector2i > my_window_pos;
  std::vector< sf::Vector2i > my_poly_window_pos;

  int shift_x = img_sizes[2];
  int shift_y = img_sizes[3];
  sf::Vector2u true_window_size( shift_x, shift_y );
  for( int i = 0; i < 4; i++ ){
    for( int j = 0; j < 4; j++ ){       
      int pos_x = global_X + i*shift_x;
      int pos_y = global_Y + j*shift_y + 50; // ADDING 10 TO ACCOUNT FOR THE BAR
      std::cout << " >> PLACING WINDOW " << pos_x << " " << pos_y << std::endl;
      sf::Vector2i temp_pos( pos_x, pos_y );
      my_window_pos.push_back(temp_pos);

      sf::Vector2i temp_pos1( pos_x + 4*shift_x, pos_y);
      my_poly_window_pos.push_back(temp_pos1);

    }
  }



  for(int s = 0; s < 16 ; s++ ){

    std::cout << " MAKING WINDOW FOR SECTION " << s << std::endl;
    my_windows.push_back( new sf::RenderWindow(sf::VideoMode(img_sizes[2], img_sizes[3], 32),"TESTSPLIT"));

    std::cout << " MAKING WINDOW FOR POLY SECTION " << s << std::endl;
    my_poly_windows.push_back( new sf::RenderWindow(sf::VideoMode(img_sizes[2], img_sizes[3], 32),"POLYGONS"));

    std::cout << " SETTING  WINDOW'S POSITION " << std::endl;
    my_windows[s]->setPosition(my_window_pos[s]);
    my_poly_windows[s]->setPosition(my_poly_window_pos[s]);
   
    my_hcs.push_back( new HillClimbingScreen( image_section[s], npolys_to_make, color_choice) );
    std::cout << " MAKING POLYGONS FOR SECTION " << s << std::endl;
    my_polys.push_back( new PolygonScreen(true_window_size, image_section[s], npolys_to_make, color_choice) );
    my_polys[s]->setWigglerLimits(*my_poly_windows[s]);

  }
  
  int screen = 1;
  int poly_screen = 1;
  while( screen >= 0 ){    
    for( int s = 0; s < 16; s++ ){
      //std::cout << " >> RUN WINDOW SECTION " << s << std::endl;
      screen = my_hcs[s]->Run( *(my_windows[s]) );
      poly_screen = my_polys[s]->Run( *(my_poly_windows[s] ));

      //std::cout << " screen value " << screen << std::endl;
    }
  }
  

  if( mode == 0 ){
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
      
      //CIRCLE SHAPES HERE
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

      sf::Image poly_img_b  =  poly_manager.getScreenshot(&window3);      
      double check_loss_1 = -poly_manager.getLoss( poly_img_b, imageIn);
      //std::cout<< " >> ITERATIONS " << counter << " LOSS BEFORE CHANGE " << check_loss_1 << " PREVIOUS LOSS " << previous_loss << std::endl;

      int poly_to_change_pos = rand() % polys.size(); 
      int poly_to_change_col = rand() % polys.size();
      int change_shape = rand() % npolys_to_make;

      int vertex_to_change = rand() % 3;
      pos_or_col = rand() % 2; 
      //std::cout << " WIGGLE CIRCLE SHAPE " << change_shape <<  std::endl;

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
	
      window3.clear(sf::Color::Black);
      for( int i = 0; i < polys.size(); i++ ){
	window3.draw( polys[i].vertex_array );     
      }

      sf::Image poly_img  =  poly_manager.getScreenshot(&window3);      
      loss = -poly_manager.getLoss( poly_img, imageIn);

      if( counter % 1000 == 0 ){
	std::cout << " >> ITERATION " << counter << " CURRENT LOSS " << loss << " LOSS TO BEAT " << previous_loss << std::endl;
      }


      if( loss > previous_loss ){
	previous_loss = loss;	
	//std::cout << " >> LOSS IMPROVED " << previous_loss << std::endl;
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
	window3.clear(sf::Color::Black);
	 
	for( int i = 0; i < polys.size(); i++ ){
	  window3.draw( polys[i].vertex_array );
	}      

	//sf::Image poly_img  =  poly_manager.getScreenshot(&window3);      
	//double check_loss = -poly_manager.getLoss( poly_img, imageIn);
	
	//std::cout<< " >> RESET POLYS TO GOOD POLYS CHECKING LOSS " << check_loss << std::endl;
      
      }
  
      //std::cout << " END OF EVENT " << std::endl;
      counter++;

      ////////////////////////////////////////////////
      //DRAW ONLY GOOD SET OF POLYGONS
      window3.clear(sf::Color::Black);
      for( int i = 0; i < good_polys.size(); i++ ){
	window3.draw( good_polys[i].vertex_array );     
      }

      bool saveimg = false;
      if( counter % 10000 == 0 && saveimg ){
	//SAVE PICTURE HERE TO SEE EVOLUTION
	sf::Image poly_img = poly_manager.getScreenshot(&window3);
	std::string extension = ".png";
	std::string path_to_img = title + std::to_string(counter) + extension;
	poly_img.saveToFile(path_to_img);
      }
     
      window3.display();
    }
  
  }

 if( mode == 1 ){
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
      
      //CIRCLE SHAPES HERE
      /* SET LOSS */     
      if( counter == 0 ){
	window3.clear(sf::Color::Black);
	
	for( int i = 0; i < circs.size(); i++ ){
	  window3.draw( circs[i].circle_shape );     
	}
	//window3.display();
	
	sf::Image poly_img  =  poly_manager.getScreenshot(&window3);
	previous_loss = -poly_manager.getLoss( poly_img, imageIn);
      }

      sf::Image poly_img_b  =  poly_manager.getScreenshot(&window3);      
      double check_loss_1 = -poly_manager.getLoss( poly_img_b, imageIn);
      //std::cout<< " >> ITERATIONS " << counter << " LOSS BEFORE CHANGE " << check_loss_1 << " PREVIOUS LOSS " << previous_loss << std::endl;

      int poly_to_change_pos = rand() % polys.size(); 
      int poly_to_change_col = rand() % polys.size();
      int change_shape = rand() % npolys_to_make;
      pos_or_col = rand() % 3; 
      //std::cout << " WIGGLE CIRCLE SHAPE " << change_shape <<  std::endl;

      if( pos_or_col == 0 ){
	sf::Vector2f temp_circ_pos = circs[change_shape].getCirclePosition();
	//std::cout << " >> BEFORE WIGGLE " << temp_circ_pos.x << " " << temp_circ_pos.y << std::endl;	
	wiggle.WigglePosition(temp_circ_pos);	
	circs[change_shape].setCirclePosition(temp_circ_pos);
	//std::cout << " >> AFTER  WIGGLE " << conv_point.x << " " << conv_point.y << std::endl;
      }
      else if ( pos_or_col == 1 ){
	sf::Color temp_circ_color = circs[change_shape].getCircleColor();
	wiggle.WiggleColor(temp_circ_color);
	circs[change_shape].setCircleColor(temp_circ_color);
      }
      else if (pos_or_col == 2 ){
	float temp_rad = circs[change_shape].getCircleRadius();
	//std::cout << " >> RAD BEFORE WIGGLE " << temp_rad <<  std::endl;
	wiggle.WiggleRadius(temp_rad);
	//std::cout << " >> RAD AFTER WIGGLE " << temp_rad <<  std::endl;
	circs[change_shape].setCircleRadius(temp_rad);
      }
	
      window3.clear(sf::Color::Black);
      for( int i = 0; i < circs.size(); i++ ){
	window3.draw( circs[i].circle_shape );     
      }

      sf::Image poly_img  =  poly_manager.getScreenshot(&window3);      
      loss = -poly_manager.getLoss( poly_img, imageIn);

      if( counter % 1000 == 0 ){
	std::cout << " >> ITERATION " << counter << " CURRENT LOSS " << loss << " LOSS TO BEAT " << previous_loss << std::endl;
      }

      if( loss > previous_loss ){
	previous_loss = loss;	
	//std::cout << " >> LOSS IMPROVED " << previous_loss << std::endl;
	//std::cout << " >> POLYGON " << poly_to_change_pos << " IMPROVED LOSS SCORE " << std::endl;
	//good_polys = polys;
	//good_conv_poly = conv_poly;

	circs_good = circs;
	
      }
      else{
	//std::cout << " >> SETTING BACK TO GOOD POLYGON SET " << std::endl;
	//polys = good_polys;
	//conv_poly = good_conv_poly;
	circs = circs_good;
	window3.clear(sf::Color::Black);
	 
	for( int i = 0; i < circs.size(); i++ ){
	  window3.draw( circs[i].circle_shape );
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
      for( int i = 0; i < circs_good.size(); i++ ){
	window3.draw( circs_good[i].circle_shape );     
      }

     
      window3.display();
    }
  
  } 


  if( mode == 2 ){
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
      
      //CIRCLE SHAPES HERE
      /* SET LOSS */     
      if( counter == 0 ){
	window3.clear(sf::Color::Black);
	
	for( int i = 0; i < circs.size(); i++ ){
	  window3.draw( circs[i].circle_shape );     
	}
	//window3.display();
	
	sf::Image poly_img  =  poly_manager.getScreenshot(&window3);
	previous_loss = -poly_manager.getLoss( poly_img, imageIn);
      }

      sf::Image poly_img_b  =  poly_manager.getScreenshot(&window3);      
      double check_loss_1 = -poly_manager.getLoss( poly_img_b, imageIn);
      //std::cout<< " >> ITERATIONS " << counter << " LOSS BEFORE CHANGE " << check_loss_1 << " PREVIOUS LOSS " << previous_loss << std::endl;

      int poly_to_change_pos = rand() % polys.size(); 
      int poly_to_change_col = rand() % polys.size();
      int change_shape = rand() % npolys_to_make;
      pos_or_col = rand() % 3; 
      //std::cout << " WIGGLE CIRCLE SHAPE " << change_shape <<  std::endl;

      if( pos_or_col == 0 ){
	sf::Vector2f temp_circ_pos = circs[change_shape].getCirclePosition();
	//std::cout << " >> BEFORE WIGGLE " << temp_circ_pos.x << " " << temp_circ_pos.y << std::endl;	
	wiggle.WigglePosition(temp_circ_pos);	
	circs[change_shape].setCirclePosition(temp_circ_pos);
	//std::cout << " >> AFTER  WIGGLE " << conv_point.x << " " << conv_point.y << std::endl;
      }
      else if ( pos_or_col == 1 ){
	sf::Color temp_circ_color = circs[change_shape].getCircleColor();
	wiggle.WiggleColor(temp_circ_color);
	circs[change_shape].setCircleColor(temp_circ_color);
      }
      else if (pos_or_col == 2 ){
	float temp_rad = circs[change_shape].getCircleRadius();
	//std::cout << " >> RAD BEFORE WIGGLE " << temp_rad <<  std::endl;
	wiggle.WiggleRadius(temp_rad);
	//std::cout << " >> RAD AFTER WIGGLE " << temp_rad <<  std::endl;
	circs[change_shape].setCircleRadius(temp_rad);
      }
	
      window3.clear(sf::Color::Black);
      for( int i = 0; i < circs.size(); i++ ){
	window3.draw( circs[i].circle_shape );     
      }

      sf::Image poly_img  =  poly_manager.getScreenshot(&window3);      
      loss = -poly_manager.getLoss( poly_img, imageIn);

      if( counter % 1000 == 0 ){
	std::cout << " >> ITERATION " << counter << " CURRENT LOSS " << loss << " LOSS TO BEAT " << previous_loss << std::endl;
      }

      if( loss > previous_loss ){
	previous_loss = loss;	
	//std::cout << " >> LOSS IMPROVED " << previous_loss << std::endl;
	//std::cout << " >> POLYGON " << poly_to_change_pos << " IMPROVED LOSS SCORE " << std::endl;
	//good_polys = polys;
	//good_conv_poly = conv_poly;

	circs_good = circs;
	
      }
      else{
	//std::cout << " >> SETTING BACK TO GOOD POLYGON SET " << std::endl;
	//polys = good_polys;
	//conv_poly = good_conv_poly;
	circs = circs_good;
	window3.clear(sf::Color::Black);
	 
	for( int i = 0; i < circs.size(); i++ ){
	  window3.draw( circs[i].circle_shape );
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
      for( int i = 0; i < circs_good.size(); i++ ){
	window3.draw( circs_good[i].circle_shape );     
      }

     
      window3.display();
    }
  
  }

  return 0;


}



