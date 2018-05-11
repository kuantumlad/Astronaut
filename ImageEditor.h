#ifndef imageeditor_hh
#define imageeditor_hh

#include <vector>
#include <map>

class ImageEditor{

 public:
  ImageEditor();
  ~ImageEditor();


 public:
  void LoadImage(sf::Image);
  sf::Image BlurImage(sf::Image);
  sf::Image SharpenImage(sf::Image);
  

};
#endif
