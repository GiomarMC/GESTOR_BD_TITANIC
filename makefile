programa: main.o disco.o lista.o pasajeros.o
	g++ -o programa main.o disco.o lista.o pasajeros.o
	./programa

main.o: main.cpp disco.h
	g++ -c main.cpp

disco.o: disco.cpp disco.h lista.h
	g++ -c disco.cpp

pasajeros.o: pasajeros.cpp pasajeros.h
	g++ -c pasajeros.cpp

lista.o: lista.cpp lista.h pasajeros.h
	g++ -c lista.cpp

clean:
	rm -f *.o programa