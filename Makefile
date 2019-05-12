run: main.o huffman.o
	g++ -std=c++17 main.o huffman.o -o run

debug:
	g++ -g -std=c++17 main.cpp huffman.cpp huffman.hpp

main.o: main.cpp
	g++ -c main.cpp

huffman.o: huffman.cpp huffman.hpp
	g++ -c huffman.cpp

clean:
	rm *.o

clean_all:
	rm run && rm *.o && rm *.exe && rm *.out