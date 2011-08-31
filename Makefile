RM_F = rm -f
CFLAGS = -std=c99 -Wall -pedantic -ggdb -g -DUSE_TERMIOS
LIBTOOL = libtool
LDFLAGS = -lc
CC = clang

LIB_PREFIX = lib
LIB_SUFFIX = .dylib

mulklib_C_SOURCES = bitmapped_patricia_tree.c
mulklib_OBJECTS = $(patsubst %.c,%.o,$(mulklib_C_SOURCES))
mulklib_TARGET = $(LIB_PREFIX)mulklib$(LIB_SUFFIX)

bpttest_C_SOURCES = bpt_test.c
bpttest_OBJECTS = $(patsubst %.c,%.o,$(bpttest_C_SOURCES))
bpttest_TARGET = bpt_test

.PHONY: all clean

all: $(mulklib_TARGET) $(bpttest_TARGET)

clean:
	$(RM_F) $(mulklib_OBJECTS)
	$(RM_F) $(mulklib_TARGET)
	$(RM_F) $(bpttest_OBJECTS)
	$(RM_F) $(bpttest_TARGET)


$(mulklib_TARGET): $(mulklib_OBJECTS)
	$(LIBTOOL) -dynamic $(LDFLAGS) -o $@ $(mulklib_OBJECTS)

bitmapped_patricia_tree.o: bitmapped_patricia_tree.c bitmapped_patricia_tree.h

$(bpttest_TARGET): $(bpttest_OBJECTS) $(mulklib_TARGET)
	$(CC) -o $@ $+
