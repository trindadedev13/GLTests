CC       = gcc
SRC_DIR  = src
OBJ_DIR  = obj
CFLAGS   = -Wall -std=c11 -DRUNNING_PATH="\"$(RUNNING_PATH)\"" -I/usr/include -Iinclude/
LDFLAGS  = -lglfw -lGL -lm -ldl

# 
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst %.c, %.o, $(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(SRCS)))

# main rule
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)