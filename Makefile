SRC := $(wildcard src/*.c)
CC	:= clang
OUT	:= evafetch

$(OUT) : $(SRC)
	$(CC) -Iinclude -Wall -Wextra $(SRC) -o $(OUT)
