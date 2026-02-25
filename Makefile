CC      = gcc
SRCS    = main.c strutils.c net.c rparse.c netfile.c http-parser/http_parser.c
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

# Sources shared by all test binaries (everything except main.c)
COMMON_SRCS = strutils.c netfile.c rparse.c net.c http-parser/http_parser.c

TEST_BINS = test/test_strutils test/test_netfile test/test_rparse test/test_net

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(LDFLAGS)

test: $(TEST_BINS)
	./test/test_strutils
	./test/test_netfile
	./test/test_rparse
	./test/test_net
	@echo ""
	@echo "All test suites passed."

test/test_%: test/test_%.c $(COMMON_SRCS)
	$(CC) -o $@ $^ $(LDFLAGS) -I.

clean:
	rm -f $(TARGET) $(TEST_BINS)

.PHONY: all test clean
