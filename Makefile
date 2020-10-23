NAME := reversing-nes

BIN := build/bin
OBJ := build/obj

CC := gcc

CFLAGS := -Wall -I./include -lSDL2 -lGL

TARGET := $(BIN)/sdl/$(NAME)

NES_SRCS := $(shell ls nes/*.c)
SDL_SRCS := $(shell ls sdl/*.c)

NES_OBJS := $(patsubst %,$(OBJ)/%.o,$(NES_SRCS))
SDL_OBJS := $(patsubst %,$(OBJ)/%.o,$(SDL_SRCS))

sdl: $(TARGET)

$(BIN)/sdl/$(NAME): $(NES_OBJS) $(SDL_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $@ $(CFLAGS)

$(OBJ)/nes/%.c.o: nes/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/SDL/%.c.o: sdl/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf build
