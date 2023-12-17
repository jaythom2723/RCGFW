CC=gcc
BUILD_DIR=./build
VENDOR_DIR=./vendor

RCGFW_LDFLAGS=-lm -lglfw3 -lGL -L$(VENDOR_DIR)/glad -lglad -L$(VENDOR_DIR)/cglm -lcglm -lX11 -lpthread -lXrandr -lXi -ldl
RCGFW_PPFLAGS=-std=c99 -c -ggdb -O3 -I./rcgfw2/include -I$(VENDOR_DIR)/glad/include -I$(VENDOR_DIR)/cglm/include -I$(VENDOR_DIR)/stbimage/include

GAME_LDFLAGS=-L$(VENDOR_DIR)/rcgfw -lrcgfw2 $(RCGFW_LDFLAGS)
GAME_PPFLAGS=-std=c99 -ggdb -O3 -I./game/include -I$(VENDOR_DIR)/rcgfw/include -I$(VENDOR_DIR)/glad/include -I$(VENDOR_DIR)/cglm/include -I$(VENDOR_DIR)/stbimage/include

.PHONY: all
all: $(BUILD_DIR)/librcgfw2.a

$(BUILD_DIR)/librcgfw2.a: $(wildcard *.o)
	$(CC) $(RCGFW_PPFLAGS) $(wildcard ./rcgfw2/src/*.c) $(RCGFW_LDFLAGS)
	ar rcs $@ $^
	cp $@ $(VENDOR_DIR)/rcgfw/librcgfw2.a
	cp -r ./rcgfw2/include/*.h $(VENDOR_DIR)/rcgfw/include/rcgfw/

game: $(wildcard ./game/src/*.c)
	$(C)) $(RCGFW_PPFLAGS) $^ $(RCGFW_LDFLAGS) -o $(BUILD_DIR)/a.out

.PHONY: clean
clean:
	rm -f ./build/librcgfw2.a
	rm -f ./build/a.out

.PHONY: run
run: ./build/a.out
	$^