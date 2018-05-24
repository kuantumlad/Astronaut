#include "PolygonManager.hh"


#include <vector>
#include <iostream>


PolygonManager::PolygonManager(){



}


PolygonManager::~PolygonManager(){


}

void PolygonManager::captureOriginal(sf::Image temp_org_image ){

  windowSize = temp_org_image.getSize();

}


double PolygonManager::getLoss(){

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

  return temp_loss;

}

void PolygonManager::captureScreen(sf::Texture temp_texture){

  sf::Texture texture;
  texture.create(windowSize.x, windowSize.y);
  texture.update(window3);
  sf::Image screenshot = texture.copyToImage();


}


void PolygonManager::updateImage(){


}
