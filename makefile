programa: main.o filemanager.o diskManager.o file.o
	g++ -o programa main.o filemanager.o diskManager.o file.o
	./programa

main.o: main.cpp filemanager.h file.h
	g++ -c main.cpp

file.o: file.cpp file.h
	g++ -c file.cpp

filemanager.o: filemanager.cpp filemanager.h diskManager.h
	g++ -c filemanager.cpp

diskManager.o: diskManager.cpp diskManager.h
	g++ -c diskManager.cpp

clean:
	rm -f *.o programa
