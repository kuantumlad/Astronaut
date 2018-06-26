#include "Wiggler.hh"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 


Wiggler::Wiggler(){

  std::cout << " WIGGLER SET  " << std::endl;
  srand(time(NULL));

  min_lim_x = 0;//-window->getSize().x * 0.25;
  min_lim_y = 0;//-window->getSize().y * 0.25;
  max_lim_x = 0;//windX + windX*0.25;
  max_lim_y = 0;//windY + windY*0.25;

}

Wiggler::~Wiggler(){


}

void Wiggler:: SetWigglerPositionLimts(sf::RenderWindow *window){

  int windX = window->getSize().x;
  int windY = window->getSize().y;
  min_lim_x = -(window->getSize().x * 0.25);
  min_lim_y = -( window->getSize().y * 0.25);
  max_lim_x = windX + windX*0.25;
  max_lim_y = windY + windY*0.25;
  /*  std::cout << " >> " << max_lim_x<< std::endl;
  std::cout << " >> " << min_lim_x<< std::endl;
  std::cout << " >> " << max_lim_y<< std::endl;
  std::cout << " >> " << min_lim_y<< std::endl;
  */
}

void Wiggler::WigglePosition(sf::Vector2f &temp_pos){

  //std::cout << " >> WIGGLE POS " << (temp_pos.x) << " " << (temp_pos.y) << std::endl;
  int pos_x = (temp_pos.x);
  int pos_y = (temp_pos.y);

  int delx = (rand() % 5)-2; //3, 1
  int dely = (rand() % 5)-2; 

  temp_pos.x = temp_pos.x + delx;
  temp_pos.y = temp_pos.y + dely;

  //std::cout << " >> NEW POS " << temp_pos.x << " "  << temp_pos.y << std::endl;
  if( temp_pos.x <= min_lim_x ){
    temp_pos.x = min_lim_x + 1 ;
  }
  if( temp_pos.y <= min_lim_y ){
    temp_pos.y = min_lim_y + 1;
  }
  if( temp_pos.x >= max_lim_x ){
    temp_pos.x = max_lim_x - 1;
  }
  if( temp_pos.y >= max_lim_y ){
    temp_pos.y = max_lim_y - 1;
  }

}

void Wiggler::WiggleConvexPolygon(ConvexPolygons conv_poly, sf::Vector2f &temp_pos){

 //std::cout << " >> WIGGLE POS " << (temp_pos.x) << " " << (temp_pos.y) << std::endl;
  int pos_x = (temp_pos.x);
  int pos_y = (temp_pos.y);

  int delx = (rand() % 5)-2; //3, 1
  int dely = (rand() % 5)-2; 

  temp_pos.x = temp_pos.x + delx;
  temp_pos.y = temp_pos.y + dely;

  //std::cout << " >> NEW POS " << temp_pos.x << " "  << temp_pos.y << std::endl;
  if( temp_pos.x <= min_lim_x ){
    temp_pos.x = min_lim_x + 1 ;
  }
  if( temp_pos.y <= min_lim_y ){
    temp_pos.y = min_lim_y + 1;
  }
  if( temp_pos.x >= max_lim_x ){
    temp_pos.x = max_lim_x - 1;
  }
  if( temp_pos.y >= max_lim_y ){
    temp_pos.y = max_lim_y - 1;
  }

  /////////////////////////////////
  //CHECK IS ANY SIDES ARE CONCAVE
  //IF IT IS FALSE SET THE BAD POINT
  //EQUAL DISTANCE FROM CENTER AS THE FURTHEST 
  //POINT
  std::cout << " >> CHECKING IF CONVX " << std::endl;
  std::vector<int> result =  poly_mang.checkConvexShape(conv_poly);
  std::cout << " SIZE OF RESULT VECTOR " << result.size() << std::endl;
  int check_convex = result[0];
  int check_vertex = result[1];
  if( check_convex == 0 ){
    std::cout << " FIXING POINT " << check_vertex << std::endl;
    int furthest_vertex = conv_poly.getFurthestVertex();
    sf::Vector2f far_point = conv_poly.getConvexPolygonsPoint(furthest_vertex);
    temp_pos.x = far_point.x + delx;
    temp_pos.y = far_point.y + dely;
    
    if( temp_pos.x <= min_lim_x ){
      temp_pos.x = min_lim_x + 1 ;
    }
    if( temp_pos.y <= min_lim_y ){
      temp_pos.y = min_lim_y + 1;
    }
    if( temp_pos.x >= max_lim_x ){
      temp_pos.x = max_lim_x - 1;
    }
    if( temp_pos.y >= max_lim_y ){
      temp_pos.y = max_lim_y - 1;
    }
    
   }

}



void Wiggler::WiggleColor(sf::Color &temp_col){

  temp_col.r += rand() % 3 - 1; //CHANGE
  temp_col.g += rand() % 3 - 1;
  temp_col.b += rand() % 3 - 1;
  temp_col.a += rand() % 3 - 1;
  

}



