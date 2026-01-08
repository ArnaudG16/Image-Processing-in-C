all:proj
	
%.o: %.c
	gcc -Wall -Wextra -c -o $@ $<

filename.o: filename.h
pictures.o: pictures.h lut.h
lut.o: lut.h pictures.h

proj: main.o pictures.o filename.o lut.o
	gcc -Wall -Wextra -o $@ $^