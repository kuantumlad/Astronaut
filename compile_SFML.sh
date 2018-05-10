#!/bin/sh

echo "Compiling..."
echo " "
#cd src/
g++ -c main.cpp -std=gnu++11 -I/usr/local/Cellar/SFML/2.4.2/include/SFML -L/usr/local/Cellar/SFML/2.4.2/lib
#mv *.o ../linker/


#cd ../linker/
echo "Linking..."
echo " "
g++ main.o -o sfml-app -I/usr/local/Cellar/SFML/2.4.2/include/SFML -L/usr/local/Cellar/SFML/2.4.2/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#mv sfml-app ../
echo "Executing..."
echo " "
#cd ../
./sfml-app

if [ -e compile_SFML.sh~ ]
then 
    rm compile_SFML.sh~
fi
