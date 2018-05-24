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

void Wiggler::WigglePosition(sf::Vector2f &temp_pos){

  std::cout << " >> WIGGLE POS " << (temp_pos.x) << " " << (temp_pos.y) << std::endl;
  temp_pos.x = rand() % (int)temp_pos.x + (int)50;
  temp_pos.y = rand() % (int)temp_pos.x + (int)50;


}


void Wiggler::WiggleColor(sf::Color &temp_col){

  temp_col.r = rand() % 256;
  temp_col.g = rand() % 256;
  temp_col.b = rand() % 256;
  

}



