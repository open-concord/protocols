G=g++ -std=c++20 -c
H=inc/csp.hpp

default: $(H)
	$(G) src/csp.cpp -o bin/csp.o
	ar cr bin/libcsp.a bin/csp.o
	ranlib bin/libcsp.a
