#include "PolygonManager.hh"

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <cmath>
#include <stdlib.h>     /* srand, rand */

PolygonManager::PolygonManager(){

  //temploss = 0;
  srand(time(NULL));


}


PolygonManager::~PolygonManager(){


}

std::vector<int> PolygonManager::setPolyColor(std::string init_color ){

  std::vector<int> color = {0,0,0};
  if( init_color == "black" ){
    color = {0,0,0};
  }
  else if( init_color == "white" ){
    color = {255,255,255};
  }
  else if( init_color == "red" ){
    color = {255,0,0};
  }
  else if( init_color == "blue" ){
    color = {0,255,0};
  }
  else if( init_color == "green" ){
    color = {0,0,255};
  }
  else{
    exit;
  }
  
}

std::vector<int> PolygonManager::getAverageImgColor(sf::Image image){

  std::vector<int> avg_color = {0,0,0};

  int tot_red = 0, tot_blue = 0, tot_green = 0;
  int counter = 0;
  for( int i = 0; i < windowSize.x; i++ ){
    for( int j = 0; j < windowSize.y; j++ ){
      sf::Color pixel = image.getPixel(i,j);

      int red = (int)pixel.r;
      int blue = (int)pixel.b;
      int green = (int)pixel.g;      
      //std::cout << " PIXEL " << i << " " << j << " " << red << " " << blue << " " << green << std::endl;
      tot_red += red;
      tot_blue += blue;
      tot_green += green;
      counter++;
    }
 }

  avg_color[0] = tot_red/counter;
  avg_color[1] = tot_blue/counter;
  avg_color[2] = tot_green/counter;

  return avg_color;

}


std::vector<Polygons *> PolygonManager::initPolygons(int npolys, sf::Image image, std::string clr_choice){

  /* INIT POLYGON PROPERTIES */
  double x = 0.0;
  double y = 0.0;
  double alpha = 0.0;
  double rendX = windowSize.x; //FIX RENDERING AREA 
  double rendY = windowSize.y;
  double delx = 0.0;
  double dely = 0.0;
  std::vector<Polygons *> polys;

  /* GET AVERAGE PICTURE IMAGE TO SET TRIANGLES TO */
  std::vector<int> avg_col = {0,0,0};
  if(clr_choice == "avg"){
    avg_col = getAverageImgColor(image);
  }
  else{
    avg_col = setPolyColor(clr_choice);
  }
  int r = avg_col[0];
  int g = avg_col[1];
  int b = avg_col[2];

  int n_triangles = npolys;
  std::vector<sf::Vector2f> pos;
  std::vector<sf::Color> col;
  for( int i = 0; i < n_triangles; i++ ){
    delx = rand() % 101 - 50;
    dely = rand() % 101 - 50;
    x = (rand() % (int)rendX) + delx;
    y = (rand() % (int)rendY) + dely;
    sf::Vector2f pos_0(x, y);
    delx = rand() % 101 - 50;
    dely = rand() % 101 - 50;
    x = (rand() % (int)rendX) + delx;
    y = (rand() % (int)rendY) + dely;
    sf::Vector2f pos_1(x, y);
    delx = rand() % 101 - 50;
    dely = rand() % 101 - 50;
    x = (rand() % (int)rendX) + delx;
    y = (rand() % (int)rendY) + dely;
    sf::Vector2f pos_2(x, y);

    alpha = rand() % 255;
    sf::Color col_0(r,g,b,alpha);
    alpha = rand() % 255;
    sf::Color col_1(r,g,b,alpha);
    alpha = rand() % 255;
    sf::Color col_2(r,g,b,alpha);

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

  return polys;

}


void PolygonManager::getOriginalSize(sf::Image temp_org_image ){

  windowSize = temp_org_image.getSize();

}


sf::Image  PolygonManager::getScreenshot( sf::RenderWindow *window ){

  sf::Texture texture;
  texture.create(window->getSize().x, window->getSize().y);
  texture.update(*window);
  sf::Image screenshot = texture.copyToImage();

  return screenshot;
}


double PolygonManager::getLoss(sf::Image screenshot, sf::Image imageIn){

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
      double pixel_chi = (delta_red + delta_blue + delta_green + delta_alpha)/(255.0*255.0*255*16.0);
      
      temploss = temploss + pixel_chi;
      //std::cout << " >> " << temploss << std::endl;
    }
  }

  return temploss;

}

int PolygonManager::getRandomPolygonToChange(int min, int max, std::vector<int> exclude ){

  int range = max - min - exclude.size();
  //std::cout << " >> RANGE " << range << std::endl;
  int rnd_poly = rand() % range;
  //std::cout << " >> RND POLY INIT " << rnd_poly << std::endl;
  for( int i = 0; i < exclude.size(); i++ ){
    if( rnd_poly < exclude[i] ){
      //std::cout << " >> EXCLUDE " << exclude[i] << std::endl;
      break;
    }
    rnd_poly++;
  }
  //std::cout << " >> FINAL RND POLY " << rnd_poly << std::endl;
  return rnd_poly;
 
}

void PolygonManager::updateImage(){


}
