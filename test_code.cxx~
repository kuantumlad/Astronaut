  /////////////////////////////////////////////////  
  //MANIPULATE IMAGE HERE
  for( int i = 0; i < imageIn_size.x; i++){
    for( int j = 0; j < imageIn_size.y; j++ ){
      sf::Color pixel = imageIn.getPixel(i,j);
      int red = (int)pixel.r * 1;
      int blue = (int)pixel.b * 1;
      int green = (int)pixel.g * 1;
      
      int alpha = (int)pixel.a * 1;
      //int avg = (int)( (red + blue + green)/3 ); //GRAYSCALE
      std::vector<int> v_clr{red,blue,green}; //LIGHTNESS
      int mx_clr = *std::max_element(v_clr.begin(), v_clr.end());
      int mn_clr = *std::min_element(v_clr.begin(), v_clr.end());
      //int avg = (mx_clr + mn_clr)/2;
      //int avg = (int)( (red*0.72 + blue*0.07 + green*0.21)/3); //LUMINOSITY
      //int avg = mx_clr; //DECOMPOSING
      int avg = blue;
      //sf::Color new_pixel = sf::Color(sf::Color((sf::Uint8)red,(sf::Uint8)blue,(sf::Uint8)green,(sf::Uint8)alpha));
      sf::Color new_pixel = sf::Color(sf::Color((sf::Uint8)avg,(sf::Uint8)avg,(sf::Uint8)avg,(sf::Uint8)alpha));
      
      imageIn.setPixel(i,j,new_pixel);
    }
  }


  textureIn.loadFromImage(imageIn);
  sf::Sprite spriteIn;
  spriteIn.setTexture(textureIn,true);
