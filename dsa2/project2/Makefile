CC = g++ # compiler
CXXFLAGS = -std=c++11 #vc++ version

useHeap.exe: useHeap.o heap.o hash.o
	$(CC) $(CXXFLAGS) -o useHeap.exe useHeap.o heap.o hash.o

useHeap.o: useHeap.cpp
	$(CC) $(CXXFLAGS) -c useHeap.cpp

heap.o: heap.cpp heap.h
	$(CC) $(CXXFLAGS) -c heap.cpp

hash.o: hash.cpp hash.h
	$(CC) $(CXXFLAGS) -c hash.cpp

debug:
	$(CC) $(CXXFLAGS) -g -o useHeapDebug.exe useHeap.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
