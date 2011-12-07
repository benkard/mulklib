RM_F = rm -f
ADDITIONAL_CFLAGS =
CFLAGS = -std=c99 -Wall -pedantic -ggdb -g -DUSE_TERMIOS $(ADDITIONAL_CFLAGS)
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

config_C_SOURCES = config.c
config_OBJECTS = $(patsubst %.c,%.o,$(config_C_SOURCES))
config_TARGET = config

.PHONY: all clean cleanconfig

all: $(mulklib_TARGET) $(bpttest_TARGET)

clean:
	$(RM_F) $(mulklib_OBJECTS)
	$(RM_F) $(mulklib_TARGET)
	$(RM_F) $(bpttest_OBJECTS)
	$(RM_F) $(bpttest_TARGET)
	$(RM_F) $(config_OBJECTS)
	$(RM_F) $(config_TARGET)

cleanconfig:
	$(RM_F) $(config_OBJECTS)
	$(RM_F) $(config_TARGET)


$(mulklib_TARGET): $(mulklib_OBJECTS)
	$(LIBTOOL) -dynamic $(LDFLAGS) -o $@ $(mulklib_OBJECTS)

$(bpttest_TARGET): $(bpttest_OBJECTS) $(mulklib_TARGET)
	$(CC) -o $@ $+

$(config_TARGET): $(config_OBJECTS)
	$(CC) -o $@ $+

bitmapped_patricia_tree.o: bitmapped_patricia_tree.c bitmapped_patricia_tree.h
bpt_test.o: bpt_test.c bitmapped_patricia_tree.h
config.o: config.c
