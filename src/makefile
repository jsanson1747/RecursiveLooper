graphicsDemo: main.o Pen.o
	g++ main.o Pen.o -o graphicsDemo.exe
main.o:	main.cpp Pen.o 
	g++ -c main.cpp
Pen.o: Pen.cpp Pen.h
	g++ -c Pen.cpp
clean:
	rm -f *.o
	rm graphicsDemo.exe
run: graphicsDemo.exe
	./graphicsDemo.exe