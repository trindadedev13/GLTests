CC            = clang
SRC_DIRS      = src extern/src
OBJ_DIR       = obj
VAR_FLAGS     = -DRUNNING_PATH="\"$(RUNNING_PATH)\"" -D$(PLATFORM)
INCLUDE_FLAGS = -I/usr/include -Iinclude/ -Iextern/include/
CFLAGS        = -Wall $(VAR_FLAGS) $(INCLUDE_FLAGS)
LDFLAGS       = -lglfw -lGL -lm -ldl

SRCS := $(foreach dir,$(SRC_DIRS),$(shell find $(dir) -name '*.c'))
OBJS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)