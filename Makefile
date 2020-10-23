NAME := reversing-nes

OUT := build
BIN := $(OUT)/bin
OBJ := $(OUT)/obj

KCONFIG_AUTOHEADER := $(OUT)/auto/config.h
export KCONFIG_AUTOHEADER

CC := gcc

CFLAGS := -Wall -I$(OUT) -I./include -lSDL2 -lGL

TARGET := $(BIN)/sdl/$(NAME)

NES_SRCS := $(shell ls nes/*.c)
SDL_SRCS := $(shell ls sdl/*.c)

NES_OBJS := $(patsubst %,$(OBJ)/%.o,$(NES_SRCS))
SDL_OBJS := $(patsubst %,$(OBJ)/%.o,$(SDL_SRCS))

sdl: .config $(OUT)/auto/config.h $(TARGET)

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

menuconfig:
	menuconfig

$(OUT)/auto/config.h:
	echo $@
	@mkdir -p $(dir $@)
	genconfig

clean:
	rm -rf build

clean-config:
	rm -rf .config .config.old
