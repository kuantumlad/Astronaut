#include "PolygonManager.hh"

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

PolygonManager::PolygonManager(){

  //temploss = 0;
  srand(time(0));


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

  return color;
  
}

void PolygonManager::setWindowSize( sf::Vector2u temp_size ){

  windowSize.x = temp_size.x;
  windowSize.y = temp_size.y ;

  //std::cout << " TRUE WINDOW SIZE IS " << windowSize.x << " " << windowSize.y << std::endl;
  
}
				    

std::vector<int> PolygonManager::getAverageImgColor(sf::Image image){

  std::vector<int> avg_color = {0,0,0};

  int tot_red = 0, tot_blue = 0, tot_green = 0;
  int counter = 0;
  //std::cout << " GET AVERAGE COLOR " << windowSize.x << " " << windowSize.y << std::endl;
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

  std::cout << " >> AVG PIXEL VALUE COUNTER " << counter << std::endl;
  avg_color[0] = tot_red/counter;
  avg_color[1] = tot_blue/counter;
  avg_color[2] = tot_green/counter;

  return avg_color;

}


//std::vector<Polygons *> PolygonManager::initPolygons(int npolys, sf::Image image, std::string clr_choice){
std::vector<Polygons> PolygonManager::initPolygons(int npolys, sf::Image image, std::string clr_choice){

  /* INIT POLYGON PROPERTIES */
  double x = 0.0;
  double y = 0.0;
  double alpha = 0.0;
  double rendX = windowSize.x; //FIX RENDERING AREA 
  double rendY = windowSize.y;

  //std::cout << " CHECKING INIT POLYGONS SIZE " << rendX << " " << rendY << std::endl;
  
  double delx = 0.0;
  double dely = 0.0;
  //std::vector<Polygons *> polys;
  std::vector<Polygons> polys;

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

  //std::cout << " >> INIT COLOR VALUES R " << r << " G " << g << " B " << b << std::endl;
  
  int n_triangles = npolys;
  std::vector<sf::Vector2f> pos;
  std::vector<sf::Color> col;
  for( int i = 0; i < n_triangles; i++ ){
    delx = rand() % 5 - 2;
    dely = rand() % 5 - 2 ;
    x = (rand() % (int)rendX) + delx;
    y = (rand() % (int)rendY) + dely;
    sf::Vector2f pos_0(x, y);
    delx = rand() % 5 - 2;
    dely = rand() % 5 - 2 ;
    x = (rand() % (int)rendX) + delx;
    y = (rand() % (int)rendY) + dely;
    sf::Vector2f pos_1(x, y);
    delx = rand() % 5 - 2 ;
    dely = rand() % 5 - 2 ;
    x = (rand() % (int)rendX) + delx;
    y = (rand() % (int)rendY) + dely; //IF BREAKS CHANGE TO -1 SHOULD BE OKAY NOW
    sf::Vector2f pos_2(x, y);

    alpha = rand() % 255;
    //std::cout << " >> ALPHA 1 " << alpha << std::endl;
    sf::Color col_0(r,g,b,alpha);
    alpha = rand() % 255;
    //std::cout << " >> ALPHA 2 " << alpha << std::endl;
    sf::Color col_1(r,g,b,alpha);
    alpha = rand() % 255;
    //std::cout << " >> ALPHA 3 " << alpha << std::endl;
    sf::Color col_2(r,g,b,alpha);

    pos.push_back(pos_0);
    pos.push_back(pos_1);
    pos.push_back(pos_2);

    col.push_back(col_0);
    col.push_back(col_1);
    col.push_back(col_2);
    //polys.push_back( new Polygons( pos, col, 3 ) );
    polys.push_back( Polygons( pos, col, 3 ) );
    
    pos.clear();
    col.clear();

  }

  return polys;

}


std::vector<ConvexPolygons> PolygonManager::initConvexPolygons(int n_polys, sf::Image image, std::string clr_choice , int n_vertices){

  double x = 0.0;
  double y = 0.0;
  double alpha = 0.0;
  double rendX = windowSize.x; //FIX RENDERING AREA 
  double rendY = windowSize.y;
  double delx = 0.0;
  double dely = 0.0;
  
  std::vector<ConvexPolygons> conv_poly;

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
  

  for( int i = 0; i  < n_polys; i++ ){
    std::map<int, sf::Vector2f> temp_conv;
        
    delx = rand() % 1 - 5;
    dely = rand() % 1 - 5;
    
    x = (rand() % (int)rendX) + delx;
    y = (rand() % (int)rendY) + dely;
    
    alpha = rand() % 255;
    sf::Color col(r,g,b,alpha);

    sf::Vector2f pos;
    pos.x = x;
    pos.y = y;

    int v_rand = rand() % n_vertices + 3;

    //std::cout<< " >> CENTRAL POS " << pos.x << " " << pos.y << std::endl;

    double tot_deg = 360.0;
    double deg_to_rotate = tot_deg/(double)n_vertices;
    
    for( int v = 0; v <= v_rand; v++ ){

      double dist = rand() % 10 + 25;
      double ang = v*deg_to_rotate;
      double rad = ang * 3.141592658 / 180.0;
      double x_v  = dist*cos(rad);
      double y_v  = dist*sin(rad);

      // std::cout << " >> v" << v << " r " << dist << " x " << x_v << " y " << y_v << " ang " << ang << std::endl;
      
      sf::Vector2f v_pos;
      v_pos.x = x_v;
      v_pos.y = y_v;
      temp_conv[v] = v_pos;       
    }
    
    conv_poly.push_back( ConvexPolygons(temp_conv, pos, col, v_rand + 1) );
    temp_conv.clear();

  }
  

  return conv_poly;
  
  
}

std::vector<Circles> PolygonManager::initCircles(int n_polys, sf::Image image, std::string clr_choice){

  double x = 0.0;
  double y = 0.0;
  double alpha = 0.0;
  double rendX = windowSize.x; //FIX RENDERING AREA 
  double rendY = windowSize.y;
  double delx = 0.0;
  double dely = 0.0;
  double max_rad = 50.0;//rendX/4.0;
  
  std::vector<Circles> circs;

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
  

  for( int i = 0; i  < n_polys; i++ ){
        
    delx = rand() % 1 - 5;
    dely = rand() % 1 - 5;
    
    x = (rand() % (int)rendX);// + delx;
    y = (rand() % (int)rendY);// + dely;
    
    alpha = rand() % 255;
    sf::Color col(r,g,b,alpha);

    sf::Vector2f pos;
    pos.x = x;
    pos.y = y;

    float rad = (float)((rand() % (int)max_rad + 2));

    //std::cout<< " >> CENTRAL POS " << pos.x << " " << pos.y << " RADIUS " << rad << std::endl;
    
    circs.push_back( Circles(pos, col, rad) );

  }
  
    return circs;

}
					 

void PolygonManager::getOriginalSize(sf::Image temp_org_image ){

  windowSize = temp_org_image.getSize();
  //std::cout << " >> ORIGINAL WINDOW SIZE IN POLYGONMANAGER CLASS " << windowSize.x << " " << windowSize.y << std::endl;
}


sf::Image PolygonManager::getScreenshot( sf::RenderWindow &window ){

  sf::Texture texture;
  //std::cout << " >> GETTING SCREEN SHOT OF WINDOW WITH DIMENSION " << windowSize.x << " " <<  windowSize.y << std::endl;
  texture.create(windowSize.x, windowSize.y);
  texture.update(window);
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

std::vector<int> PolygonManager::checkConvexShape(ConvexPolygons temp_poly ){
  std::vector<int> result; 
  // FIRST INDEX IS 0 OR 1 - IS CONVEX OR NOT
  // SECOND INDEX IS THE SIDE THAT IS BAD

  int n_points = temp_poly.getNumVertices();
  int n_shift = 1;
  int nn_shift = 2;
  int bad_vertex = -1;
  double cross_product_sign = 0;
  bool is_convex = true;
  std::cout << " >> TOTAL NUMBER OF POINTS " << n_points << std::endl;
  if( n_points > 3 ){
    for( int i = 0; i < n_points; i++ ){
      
      sf::Vector2f cp = temp_poly.getConvexPolygonsPoint(i);
      
      if( i == n_points - 2 ){
	n_shift = 1;
	nn_shift = -i;
      }
      std::cout << " >> CREATING VECTORS FOR POINTS " << i << " " << i + n_shift << " " << i+nn_shift << std::endl;

      sf::Vector2f nnp = temp_poly.getConvexPolygonsPoint(i+n_shift);
      sf::Vector2f np = temp_poly.getConvexPolygonsPoint(i+nn_shift);
      
      sf::Vector2f v_AB = cp - np;
      sf::Vector2f v_BC = nnp - np;
      
      cross_product_sign = v_AB.x * v_BC.y - v_AB.y *v_BC.x;
      std::cout << " >> " << cross_product_sign << std::endl;
      
      if( cross_product_sign < 0 ){
	is_convex = false;
	bad_vertex = i + n_shift;
	break;
      }
      std::cout << " NPOINT " << n_points << " " << i << std::endl;
      if( i == n_points - 2 ) break;
    }
  }
  result.push_back( is_convex );
  result.push_back(bad_vertex);
  std::cout << " RESULT " << result[0] << " " << result[1] << std::endl;

  return result;
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



