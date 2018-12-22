ENGINE = hades_object.h hades_object.c hades_timer.h hades_timer.c hades_structure.h hades_sprite.h hades_sprite.c hades_texture.h hades_texture.c hades_error.c hades_error.h hades_game.c hades_game.h
CC = gcc
COMPILER_FLAGS = -Wall
LINKER_FLAGS = -lSDL2 -lSDL2_image

test:
	$(CC) $(COMPILER_FLAGS) -o test $(ENGINE) test.c $(LINKER_FLAGS)

snake:
	$(CC) $(COMPILER_FLAGS) -o snake $(ENGINE) snake.c $(LINKER_FLAGS)
