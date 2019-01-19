ENGINE = hades_iter.h hades_iter.c hades_hmap.h hades_hmap.c hades_object.h hades_object.c hades_objset.h hades_objset.c hades_timer.h hades_timer.c hades_sprite.h hades_sprite.c hades_texture.h hades_texture.c hades_error.c hades_error.h hades_game.c hades_game.h
CC = gcc
COMPILER_FLAGS = -Wall
LINKER_FLAGS = -lSDL2 -lSDL2_image

test:
	$(CC) $(COMPILER_FLAGS) -o test $(ENGINE) test.c $(LINKER_FLAGS)

snake:
	$(CC) $(COMPILER_FLAGS) -o snake $(ENGINE) snake.c $(LINKER_FLAGS)
