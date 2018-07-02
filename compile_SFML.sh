#!/bin/sh

echo "Compiling..."
echo " "
#cd src/
g++ -c main.cpp Polygons.cpp ConvexPolygons.cpp Circles.cpp Wiggler.cpp PolygonManager.cpp ImageManager.cpp HillClimbingScreen.cpp -std=gnu++11 -I/usr/local/Cellar/SFML/2.4.2/include/SFML -L/usr/local/Cellar/SFML/2.4.2/lib
#mv *.o ../linker/


#cd ../linker/
echo "Linking..."
echo " "
g++ -o sfml-app main.o Polygons.o ConvexPolygons.o Circles.o Wiggler.o PolygonManager.o ImageManager.o HillClimbingScreen.o -I/usr/local/Cellar/SFML/2.4.2/include/SFML -L/usr/local/Cellar/SFML/2.4.2/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#mv sfml-app ../
echo "Executing..."
echo " "
#cd ../
./sfml-app $1

if [ -e compile_SFML.sh~ ]
then 
    rm compile_SFML.sh~
fi
