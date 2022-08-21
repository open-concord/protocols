G=g++ -std=c++20 -c
H=inc/csp.hpp
I=-I./lib/uttu/inc
L=-L./lib/uttu -luttu
default: $(H)
	$(G) $(I) src/csp.cpp -o bin/csp.o $(L)
	ar cr bin/libcsp.a bin/csp.o
	ranlib bin/libcsp.a

clean:
	rm -rf bin/*
