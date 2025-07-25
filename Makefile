# Makefile	

TARGET = smart_door_ecu

SRC_DIR = src

INC_DIR = include

OBJ_DIR = build/obj

SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

LIBS = -lm

CFLAGS = -Wall -Wextra -I$(INC_DIR) -O2

LDFLAGS = -L$(OBJ_DIR) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	@mkdir -p build/bin
	gcc $(OBJS) -o build/bin/$(TARGET) $(LDFLAGS)	

clean:
	rm -rf $(OBJ_DIR)/*.o build/bin/$(TARGET)

run: $(TARGET)
	./build/bin/$(TARGET)

all: $(TARGET)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)	

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

build/bin:	
	@mkdir -p build/bin	

