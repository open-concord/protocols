CC = G++
CFLAGS = -std=c++20 -c
# include path for your local installation of the core library
I = -I./path/to/core/library/inc

G=$(CC) $(CFLAGS) $(I)

H=inc/hclc.hpp ../../lib/inc/uttu.hpp
default: $(H)
	$(G) src/hclc.cpp -o bin/hclc.o
	ar cr bin/libhclc.a bin/hclc.o
	ranlib bin/libhclc.a

clean:
	rm bin/*
