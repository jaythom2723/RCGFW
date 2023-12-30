CC=gcc
BUILD_DIR=./build
VENDOR_DIR=./vendor

RCGFW_LDFLAGS=-lm -lglfw3 -lGL -L$(VENDOR_DIR)/glad -lglad -L$(VENDOR_DIR)/cglm -lcglm -lX11 -lpthread -lXrandr -lXi -ldl
RCGFW_PPFLAGS=-std=c99 -c -ggdb -O3 -I./rcgfw2/include -I$(VENDOR_DIR)/glad/include -I$(VENDOR_DIR)/cglm/include -I$(VENDOR_DIR)/stbimage/include

GAME_LDFLAGS=-L$(VENDOR_DIR)/rcgfw -lrcgfw2 $(RCGFW_LDFLAGS)
GAME_PPFLAGS=-std=c99 -ggdb -O3 -I./game/include -I$(VENDOR_DIR)/rcgfw/include -I$(VENDOR_DIR)/glad/include -I$(VENDOR_DIR)/cglm/include -I$(VENDOR_DIR)/stbimage/include

.PHONY: all
all: rcgfw2 game

rcgfw2: rcgfw2/
	make -C $^

game: $(wildcard ./game/src/*.c)
	$(CC) $(GAME_PPFLAGS) $^ $(GAME_LDFLAGS) -o $(BUILD_DIR)/a.out

.PHONY: clean
clean:
	rm -f ./build/librcgfw2.a
	rm -f ./build/a.out
	make clean -C rcgfw2/

.PHONY: run
run: ./build/a.out
	$^
