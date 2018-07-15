#include "Stitcher.hh"

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <cmath>


Stitcher::Stitcher(){


}


Stitcher::~Stitcher(){



}

void Stitcher::setIterationImage(int temp_iteration){

  iteration = temp_iteration;
  s_iteration = std::to_string(iteration);
}


void Stitcher::getImages(sf::Image sect_img, int x_shift, int y_shift){

  //std::cout << " LOOPING OVER IMAGE " << maxX << " " << maxY << std::endl;
  for(int x = 0; x < maxX; x++ ){
    for( int y = 0; y < maxY; y++ ){
      //std::cout << " X " << x << " Y " << y << std::endl;
      //std::cout << " SECT IMG PIXEL COLOR " << x << " " << y << " COLOR " << (int)sect_img.getPixel(x,y).r << std::endl;
      //std::cout << stitched_image.getSize().x << " " << stitched_image.getSize().y << std::endl;
      stitched_image.setPixel( x + x_shift, y + y_shift, sect_img.getPixel(x,y) );         
    }
  }

}



void Stitcher::getStitch(){




}


sf::Image Stitcher::getStitchedImage(std::string temp_path_to, int x_dim, int y_dim){

  int shift_x = 0;
  int shift_y = 0;
  
  int section = x_dim*y_dim;
  int s = 0;
  for( int i = 0; i < x_dim; i++ ){
    for( int j = 0; j < y_dim; j++ ){

      
      sf::Image sect_img;
      std::string s_sect = std::to_string(s);
      if( !sect_img.loadFromFile(temp_path_to + "MONA_LISA_" + s_sect + "_" + s_iteration + ".png" ) ){
	std::cout << " ERROR LOADING FILE " << std::endl;
      }           
      sf::Vector2u img_size = sect_img.getSize();
      setSectImageProperties(img_size);
      shift_x = i*img_size.x;
      shift_y = j*img_size.y;
      
      //std::cout << " SECTION " << s << " X SHIFT " << shift_x << " Y SHIFT " << shift_y << std::endl;
      getImages(sect_img, shift_x, shift_y);


    
      s++;
    }
  }

  return stitched_image;

}


void Stitcher::setSectImageProperties(sf::Vector2u temp_size ){

  maxX = temp_size.x;
  maxY = temp_size.y;

}


void Stitcher::initStitchedImage(sf::Image original_image){

  sf::Vector2u og_size = original_image.getSize();
  //std::cout << " ORIGINAL SIZE " << std::endl;
  stitched_image.create(og_size.x, og_size.y, sf::Color::Black);

}
