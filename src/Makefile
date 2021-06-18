CPPFLAGS = -I/usr/include/irrlicht -I"../include" 
CXXFLAGS = -Wall -Wextra -O2 -g -std=c++11 -Wno-unused
OPT= -L"/usr/lib" ../bin/linux-gcc-64/libIrrKlang.so -pthread 

game: main.o game.o player.o camera.o gameEvent.o 
	g++ $^ -o $@ -lIrrlicht $(OPT)

clean:
	rm -f *.o
mrproper: clean
	rm -f irrlicht
