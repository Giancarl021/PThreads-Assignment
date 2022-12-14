CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wno-unused-result -std=gnu99 -O3
CLIBS=
SRC=primes parallel
OUT=T
SRC_DIR=src
BUILD_DIR=build

SRC_PATH=$(addprefix $(SRC_DIR:=/),$(SRC))
BUILD_OUT=$(addprefix $(BUILD_DIR:=/),$(SRC))

all: $(OUT)

T: main.c $(BUILD_OUT:=.o)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

clean:
	rm -f $(OUT) **/*.o *.dev.*

$(BUILD_OUT:=.o): $(SRC_PATH:=.c) $(SRC_PATH:=.h)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c "$(SRC_DIR)/$(notdir $(basename $@).c)" -o $@
