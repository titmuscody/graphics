# Pre Project 1
# Generate a simple Polygon
proj5: proj5.cpp colors.h point.h level.h ball.h
	g++ proj5.cpp -std=c++11 -o proj5 glut32.lib -lGL -lglut -lGLU

proj4: proj4.cpp colors.h fish.h point.h wall.h
	g++ proj4.cpp -std=c++11 -o proj4 glut32.lib -lGL -lglut -lGLU

proj3: proj3.cpp colors.h pyramid.h fish.h point.h
	g++ proj3.cpp -std=c++11 -o proj3 glut32.lib -lGL -lglut -lGLU

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

