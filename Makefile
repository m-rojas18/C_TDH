all:
	g++ hanoi_muestra.cpp \
	Disco.cpp \
	-lncurses -o run
clean:
	rm run