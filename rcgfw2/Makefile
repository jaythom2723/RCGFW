CC=gcc
BUILD_DIR=../build/
VENDOR_DIR=../vendor/

RCGFW_LDFLAGS=-lm -lglfw3 -lGL -L$(VENDOR_DIR)/glad -lglad -L$(VENDOR_DIR)/cglm -lcglm -lX11 -lpthread -lXrandr -lXi -ldl
RCGFW_PPFLAGS=-std=c99 -c -ggdb -O3 -I include/ -I $(VENDOR_DIR)/glad/include/ -I $(VENDOR_DIR)/cglm/include/ -I $(VENDOR_DIR)/stbimage/include/

$(BUILD_DIR)/librcgfw2.a: $(wildcard *.o)
	$(CC) $(RCGFW_PPFLAGS) $(wildcard src/*.c) $(RCGFW_LDFLAGS)
	ar rcs $@ $^
	cp $@ $(VENDOR_DIR)/rcgfw/librcgfw2.a
	cp -r include/*.h $(VENDOR_DIR)/rcgfw/include/rcgfw/

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/librcgfw2.a
	rm -f $(wildcard *.o)