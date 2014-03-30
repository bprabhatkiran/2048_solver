all: solver

solver: bin/2048_solver.o bin/Board.o
	g++ bin/2048_solver.o bin/Board.o -o solver -g

bin/2048_solver.o: src/2048_solver.cpp
	g++ -c src/2048_solver.cpp -o bin/2048_solver.o -g

bin/Board.o: src/Board.cpp
	g++ -c src/Board.cpp -o bin/Board.o -g

clean:
	rm -rf solver
	rm -rf *~
	rm -rf *.o
	rm -rf ./bin/*.o