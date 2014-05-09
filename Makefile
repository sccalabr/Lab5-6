all: decode.cpp decode.hpp
	g++ -O2 -g decode.cpp -o decode

run:
	./decode -f input.sim

clean:
	rm -f *.o decode *~
