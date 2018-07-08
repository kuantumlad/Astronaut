#include "ImageManager.hh"

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <cmath>


ImageManager::ImageManager(){


}

ImageManager::ImageManager(sf::Image inImage){

  
  temp_img = inImage;
  

}

ImageManager::~ImageManager(){


}


std::vector<sf::Image> ImageManager::splitMainImage(int nx_split, int ny_split){

  sf::Vector2u img_size = temp_img.getSize(); 

  std::cout << ">> ORIGINAL IMAGE SIZE: " << img_size.x << " " << img_size.y << std::endl;

  int interval_x = (int)img_size.x/nx_split;
  int interval_y = (int)img_size.y/ny_split;

  std::cout << " >> SPLIT IN X  WITH " << nx_split << " INTERVALS " << std::endl;
  std::cout << " >> SPLIT IN Y  WITH " << ny_split << " INTERVALS " << std::endl;

  std::cout << " >> INTERVAL X  WITH " << interval_x << std::endl;
  std::cout << " >> INTERVAL Y  WITH " << interval_y << std::endl;

  int x_min = 0;
  int y_min = 0;
  int x_max = nx_split;
  int y_max = ny_split;

  min_img_x = x_min;
  min_img_y = y_min;
  max_img_x = interval_x;
  max_img_y = interval_y;
  
  std::vector< sf::Image > v_imgs; //SPLIT IMAGE INTO SECTIONS AND FILL VECTOR WITH THOSE IMAGES
  for( int i = 0; i < nx_split; i++ ){
    for( int j = 0; j < ny_split; j++ ){
      std::cout << " SECTION " << i << " " << j << std::endl;
      
      x_min = i*interval_x;
      y_min = j*interval_y;

      x_max = x_min + interval_x;
      y_max = y_min + interval_y;

      std::cout << " >> " << x_min << " " << x_max << " " << y_min << " " << y_max << std::endl;
     
      v_imgs.push_back(splitImage(x_min, x_max, y_min, y_max ));

    }
  }

  return v_imgs;
}


sf::Image ImageManager::splitImage(int x_min, int x_max, int y_min, int y_max ){

  std::cout << " X MIN " << x_min << " X MAX " << x_max << std::endl;
  std::cout << " Y MIN " << y_min << " Y MAX " << y_max << std::endl;
  
  int x_img_dim = x_max - x_min;
  int y_img_dim = y_max - y_min;

  std::cout << " >> IMAGE SIZE " << x_img_dim << " " << y_img_dim << std::endl; 

  sf::Image split_img;
  split_img.create(x_img_dim,y_img_dim,sf::Color::Black);

  for( int i = x_min; i < x_max; i++ ){
    for( int j = y_min; j < y_max; j++ ){
      sf::Color temp_col = temp_img.getPixel(i,j);      
      split_img.setPixel(i - x_min, j - y_min, temp_col); // subtract min to position image in window correctly
    }
  }

  return split_img;

}

std::vector<sf::Sprite> ImageManager::splitImageToSprite(int nx_split, int ny_split ){

  std::vector<sf::Sprite> v_sprite;
  std::vector<sf::Image> v_img = splitMainImage(nx_split,ny_split);

  for( int i = 0; i < v_img.size(); i++ ){
    sf::Texture temp_tex;
    temp_tex.loadFromImage( v_img[i] );
    sf::Sprite temp_sprite;
    temp_sprite.setTexture(temp_tex,true);

    v_sprite.push_back(temp_sprite);
  }
  return v_sprite;

}


std::vector<int> ImageManager::getSplitImageSize(){

  std::vector<int> img_size;
  img_size.push_back(min_img_x);
  img_size.push_back(min_img_y);
  img_size.push_back(max_img_x);
  img_size.push_back(max_img_y);

  return img_size;

}
