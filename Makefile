CC      = gcc
SRCS    = main.c net.c rparse.c netfile.c http-parser/http_parser.c
TARGET  = net

UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
    LDFLAGS =
endif

ifeq ($(UNAME), Darwin)
    LDFLAGS =
endif

# Fallback for Windows (mingw/msys2)
ifeq ($(OS), Windows_NT)
    TARGET  = net.exe
    LDFLAGS = -lws2_32
endif

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
