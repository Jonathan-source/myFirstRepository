#!/bin/bash

appRunning=1

while [ $appRunning == 1 ]; do
	echo [1] Compile and run, [2] Compile, [3] Exit
	read user

	if [[ $user == 1 ]]; then
		echo Compiling and then running ...
		g++ -c src/*.cpp -std=c++14 -Werror
		g++ *.o -o bin/Game -lsfml-graphics -lsfml-window -lsfml-system
		./bin/Game
	elif [[ $user == 2 ]]; then
		echo Compiling ...
		g++ -c src/*.cpp -std=c++14 -Werror
		g++ *.o -o bin/Game -lsfml-graphics -lsfml-window -lsfml-system
	elif [[ $user == 3 ]]; then
		exit
	fi
done
