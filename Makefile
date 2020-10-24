include .config

OUT := build
BIN := $(OUT)/bin
OBJ := $(OUT)/obj

KCONFIG_AUTOHEADER := $(OUT)/auto/config.h
export KCONFIG_AUTOHEADER

CC := gcc

CFLAGS := -Wall -I$(OUT) -I./include -lSDL2 -lGL

TARGET       := $(BIN)/${CONFIG_PLATFORM_SRC}/$(CONFIG_APP_NAME)

NES_SRCS       := $(shell ls nes/*.c)
CON_SRCS       := $(shell ls console/*.c)
PLATFORM_SRCS  := $(shell ls platforms/${CONFIG_PLATFORM_SRC}/*.c)
DEBUGGER_SRCS  := $(shell ls debugger/*.c debugger/supports/${CONFIG_DEBUGGER_SRC}/*.c)

NES_OBJS       := $(patsubst %,$(OBJ)/%.o,$(NES_SRCS))
CON_OBJS       := $(patsubst %,$(OBJ)/%.o,$(CON_SRCS))
PLATFORM_OBJS  := $(patsubst %,$(OBJ)/%.o,$(PLATFORM_SRCS))
DEBUGGER_OBJS  := $(patsubst %,$(OBJ)/%.o,$(DEBUGGER_SRCS))

app: .config $(OUT)/auto/config.h $(TARGET)

$(BIN)/$(CONFIG_PLATFORM_SRC)/$(CONFIG_APP_NAME): $(NES_OBJS) $(CON_OBJS) $(DEBUGGER_OBJS) $(PLATFORM_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $@ $(CFLAGS)

$(OBJ)/nes/%.c.o: nes/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/$(CONFIG_PLATFORM_SRC)/%.c.o: platforms/$(CONFIG_PLATFORM_SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/console/%.c.o: console/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OUT)/auto/config.h:
	@mkdir -p $(dir $@)
	@genconfig

clean:
	rm -rf build

clean-config:
	rm -rf .config .config.old

.PHONY: $(OUT)/auto/config.h
