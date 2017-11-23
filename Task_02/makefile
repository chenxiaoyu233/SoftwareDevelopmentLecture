main: my.cpp solver.o Generator.o
	g++ my.cpp solver.o Generator.o -framework OpenGL -framework GLUT -framework Foundation -g -o my.cpp.out
solver.o: solver.cpp solver.h
	g++ solver.cpp -c -g
Generator.o: Generator.cpp Generator.h
	g++ Generator.cpp -c -g
clean: 
	rm -r *.out* *.o

