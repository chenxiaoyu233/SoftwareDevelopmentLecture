main: main.cpp solver.o Generator.o Automaton.o Point.o User.o Graph.o Tools.o Light.o
	g++ main.cpp solver.o Generator.o Automaton.o Point.o User.o Graph.o Tools.o Light.o \
	-framework OpenGL -framework GLUT -framework Foundation -g -o main.cpp.out
solver.o: solver.cpp solver.h
	g++ solver.cpp -c -g
Generator.o: Generator.cpp Generator.h
	g++ Generator.cpp -c -g
Automaton.o: Automaton.cpp Automaton.h
	g++ Automaton.cpp -c -g
Point.o: Point.cpp Point.h
	g++ Point.cpp -c -g
User.o: User.cpp Automaton.h
	g++ User.cpp -c -g
Graph.o: Graph.cpp Automaton.h
	g++ Graph.cpp -c -g
Tools.o: Tools.cpp Tools.h
	g++ Tools.cpp -c -g
Light.o: Light.cpp Light.h
	g++ Light.cpp -c -g

clean: 
	rm -r *.out* *.o

