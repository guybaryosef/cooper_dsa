CC = g++ # compiler
CXXFLAGS = -std=c++11 # flags

make: heap.o hash.o graph.o proj3.o
	$(CC) $(CXXFLAGS) -o useGraph.exe proj3.o heap.o hash.o graph.o

debug: heap.o hash.o graph.o proj3.o
	$(CC) $(CXXFLAGS) -g -o debugUseGraph.exe heap.cpp hash.cpp graph.cpp proj3.cpp

proj3.o: proj3.cpp
	$(CC) $(CXXFLAGS) -c proj3.cpp

heap.o: heap.cpp heap.h
	$(CC) $(CXXFLAGS) -c heap.cpp

hash.o: hash.cpp hash.h
	$(CC) $(CXXFLAGS) -c hash.cpp

graph.o: graph.cpp graph.h
	$(CC) $(CXXFLAGS) -c graph.cpp

clean:
	rm -f *.exe *.o

