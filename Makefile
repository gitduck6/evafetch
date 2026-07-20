SRC := $(wildcard src/*.c)
CC	:= clang
OUT	:= fetch

$(OUT) : $(SRC)
	$(CC) -Iinclude -Wall -Wextra $(SRC) -o $(OUT)
