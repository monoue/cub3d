COMPILER_FLAGS = -L/Users/monoue/homebrew/lib

LINKER_FLAGS = -lSDL2

build:
	gcc -std=c99 -g ./src/*.c ./cub3d.a $(COMPILER_FLAGS) $(LINKER_FLAGS) -o raycast;

run:
	./raycast;

clean:
	rm raycast;
