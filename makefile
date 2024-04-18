programa: main.o disco.o lista.o pasajeros.o filemanager.o
	g++ -o programa main.o disco.o lista.o pasajeros.o filemanager.o
	./programa

main.o: main.cpp disco.h
	g++ -c main.cpp

disco.o: disco.cpp disco.h lista.h
	g++ -c disco.cpp

pasajeros.o: pasajeros.cpp pasajeros.h
	g++ -c pasajeros.cpp

lista.o: lista.cpp lista.h pasajeros.h
	g++ -c lista.cpp

filemanager.o: filemanager.cpp filemanager.h
	g++ -c filemanager.cpp

clean:
	rm -f *.o programa