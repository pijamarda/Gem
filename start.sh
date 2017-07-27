#!/bin/bash

rm out/*.o

g++ -c -std=c++0x Gem/*.cpp
mv *.o out/
g++ out/*.o -o out/gem -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#export LD_LIBRARY_PATH=/home/fgimenez/data/sdk/sfml-2.1/lib && ./sfml-app
