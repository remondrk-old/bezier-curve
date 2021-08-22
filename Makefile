all:
	g++ -Iinclude -Llib -o bin/bezier_curve src/main.cpp src/curve.cpp src/render.cpp -lmingw32 -lSDL2main -lSDL2

clear:
	rm bin/bezier_curve