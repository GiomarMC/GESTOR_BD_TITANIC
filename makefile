programa: main.o filemanager.o disco.o
	g++ -o programa main.o filemanager.o disco.o
	./programa

main.o: main.cpp filemanager.h
	g++ -c main.cpp

filemanager.o: filemanager.cpp filemanager.h disco.h
	g++ -c filemanager.cpp

disco.o: disco.cpp disco.h
	g++ -c disco.cpp

clean:
	rm -f *.o programa