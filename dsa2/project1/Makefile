CC = g++ # compiler
CXXFLAGS = -std=c++11 # c++ version


spell.exe: spellcheck.o hash.o
	$(CC) $(CXXFLAGS) -o spell.exe spellcheck.o hash.o

spellcheck.o: spellcheck.cpp hash.h
	$(CC) $(CXXFLAGS) -c spellcheck.cpp

hash.o: hash.cpp hash.h
	$(CC) $(CXXFLAGS) -c hash.cpp

debug:
	$(CC) $(CXXFLAGS) -g -o spellDebug.exe spellcheck.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
