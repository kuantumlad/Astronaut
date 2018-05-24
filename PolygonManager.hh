#ifndef polygonmanager_hh
#define polygonmanager_hh


class PolygonManager{

public:
  PolygonManager();
  ~PolygonManager();


public:
  sf::Image orig_img;
  sf::Image poly_img;
  sf::Vector2f windowSize;
  
  

public:
  void updateImage();
  double getLoss();

  void captureScreen(sf::Texture);
  void captureOriginal(sf::Image);
  

  

};
#endif
