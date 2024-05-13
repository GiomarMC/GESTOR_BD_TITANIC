programa: main.o filemanager.o diskManager.o
	g++ -o programa main.o filemanager.o diskManager.o
	./programa

main.o: main.cpp filemanager.h
	g++ -c main.cpp

filemanager.o: filemanager.cpp filemanager.h diskManager.h
	g++ -c filemanager.cpp

diskManager.o: diskManager.cpp diskManager.h
	g++ -c diskManager.cpp

clean:
	rm -f *.o programa