CFLAGS=-W -Wall -pedantic
LDFLAGS= -lSDL -lGL -lGLU
EXEC=sorting

all: $(EXEC)

$(EXEC): sdl.o main.o
	gcc -o bin/$(EXEC) src/main.o src/sdl.o $(LDFLAGS)
	rm -rf src/*.o

main.o: src/main.c src/global.h src/sdl.h
	gcc -o src/main.o -c src/main.c $(CFLAGS)

sdl.o: src/sdl.c
	gcc -o src/sdl.o -c src/sdl.c $(CFLAGS)

clean:
	rm -rf src/*.o

mrproper:
	rm -rf bin/$(EXEC)
