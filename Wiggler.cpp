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

}

Wiggler::~Wiggler(){


}

void Wiggler:: SetWigglerPositionLimts(int min, int max){


}

void Wiggler::WigglePosition(sf::Vector2f &temp_pos){

  //std::cout << " >> WIGGLE POS " << (temp_pos.x) << " " << (temp_pos.y) << std::endl;
  int pos_x = (temp_pos.x);
  int pos_y = (temp_pos.y);

  int delx = (rand() % 3)-1;
  int dely = (rand() % 3)-1;

  temp_pos.x = temp_pos.x + delx;
  temp_pos.y = temp_pos.y + dely;

}


void Wiggler::WiggleColor(sf::Color &temp_col){

  temp_col.r += rand() % 3 - 1; //CHANGE
  temp_col.g += rand() % 3 - 1;
  temp_col.b += rand() % 3 - 1;
  temp_col.a += rand() % 3 - 1;
  

}



