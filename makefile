# Pre Project 1
# Generate a simple Polygon
proj2: proj2.cpp colors.h
	g++ proj2.cpp -std=c++11 -o proj2 glut32.lib -lGL -lglut -lGLU

proj1: proj1.cpp circle.h colors.h
	g++ proj1.cpp -o proj1 glut32.lib -lGL -lglut -lGLU


fish: fish.c
	g++ fish.c -o fish glut32.lib -lGL -lglut -lGLU

# Pre Project 1
# Rotate a Polygon in X or Y direction based up
# left or right mouse click
rotate: rotate.c
	gcc rotate.c -o rotate glut32.lib -lGL -lglut -lGLU

# Pre Project 2
# Prespective Viewing and movement of camera not objects
# Move Camera based on keys 1, 2, 3, 4 (quadrants of the screen)
# Reset Camera
camera: camera.c
	gcc camera.c -o camera glut32.lib -lGL -lGLU -lglut

