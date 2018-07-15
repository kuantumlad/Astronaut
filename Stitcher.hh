#ifndef stitcher_hh
#define stitcher_hh

#include <SFML/Graphics.hpp>

class Stitcher{


public:
  Stitcher();
  ~Stitcher();

  void getImages(sf::Image,int, int);
  void getStitch();
  sf::Image getStitchedImage(std::string, int, int);
  void setIterationImage(int);
  void setSectImageProperties(sf::Vector2u);
  void initStitchedImage(sf::Image);

  sf::Image stitched_image;
  int iteration;
  std::string s_iteration;

  int maxX, maxY;
  int shiftX, shiftY;


  


};
#endif
