# Mulklib: purely functional integer maps for C

## Summary

This library implements [Patricia Trees][] in C, providing fast,
purely functional maps keyed by integers.

## Motivation

 1. Patricia trees are very amenable to structure sharing.

 2. Furthermore, big-endian Patricia trees are especially efficient
    when indices are allocated sequentially.

 3. Finally, bitmapping improves the performance of copying because
    copying an array is much cheaper than copying an equivalent branch
    in a tree.

## Preparation

Build with something like the following:

```sh
make CC=gcc LIB_PREFIX=lib LIB_SUFFIX=.so
```

The defaults are `CC=clang LIB_PREFIX=lib LIB_SUFFIX=.dylib`, which is
all right for Mac OS X but not so great on other systems. They are
also subject to change, since they depend on my development
environment. (Of course, if you feel the urge to make the build system
a little smarter, patches are always welcome.)

If building and installing a library consisting of a single object
file seems like overkill to you (it sure does to me), you may prefer
simply integrating the source files (`bitmapped_patricia_tree.c`,
`bitmapped_patricia_tree.h`) into your own project directly.

## Usage
### Main Concepts

A Bitmapped Patricia Tree (**BPT**) maps integer keys to `void*` values.

BPTs provide a functional, Lisp-like interface. All modifying
operations (`bpt_assoc` and `bpt_dissoc`, which add and remove
entries, respectively) return a new BPT with the requested changes
applied, although by default, they **may destructively modify** the
original BPT for improved performance.

Destructive modification can be prohibited by **sealing** the original
BPT using the `bpt_seal` procedure.  Note that there is practically no
performance overhead in sealing (the seal being just a boolean flag),
so there is nothing wrong with using bitmapped Patricia Trees in a
purely functional manner by calling `bpt_seal` after every operation.

An **empty BPT** is represented as `NULL`.

### Example

```c
//
// This is a very basic example of using BPTs that blissfully neglects memory
// management in favor of didactic simplicity.
//
// For a more complete example, see bpt_test.c in the source distribution.
//

#include "stdio.h"
#include "stdlib.h"
#include "bitmapped_patricia_tree.h"

void print_tree(bpt_t b) {
  int i;
  for (i = 0; i < 10; i++) {
    if (bpt_has_key(b, i)) {
      printf(" %d -> %s\n", i, bpt_get(b, i));
    }
  }
}

int main() {
  bpt_t b1, b2;

  // Create b1.
  b1 = bpt_assoc(NULL, 0, "zero");     //functional (obviously)
  b1 = bpt_assoc(b1,   1, "one");      //|
  b1 = bpt_assoc(b1,   2, "two");      //|destructive!
  b1 = bpt_assoc(b1,   3, "three");    //|
  b1 = bpt_assoc(b1,   4, "four");     //|

  // Make b1 functional.
  bpt_seal(b1);

  // Make b2 a structure-sharing copy of b1.
  b2 = bpt_assoc(b1,   0, "null");     //functional, as b1 is sealed
  b2 = bpt_assoc(b2,   3, "a triple"); //destructive

  // Modifying b1 does not affect b2.
  b1 = bpt_assoc(b1,   5, "five");     //destructive

  printf("Map 1:\n");
  print_tree(b1);
  printf("\nMap 2:\n");
  print_tree(b2);

  return EXIT_SUCCESS;
}
```

Output:

```
Map 1:
 0 -> zero
 1 -> one
 2 -> two
 3 -> three
 4 -> four
 5 -> five

Map 2:
 0 -> null
 1 -> one
 2 -> two
 3 -> a triple
 4 -> four
```

### API

```c
typedef int32_t bpt_key_t;

// Querying
void *bpt_get(bpt_t bpt, bpt_key_t key);
bool bpt_has_key(bpt_t bpt, bpt_key_t key);

// Adding and Removing Entries
bpt_t bpt_assoc(bpt_t bpt, bpt_key_t key, void *item);
bpt_t bpt_dissoc(bpt_t bpt, bpt_key_t key);

// Managing Memory
void bpt_retain(bpt_t bpt);
void bpt_release(bpt_t bpt);
void bpt_dealloc(bpt_t bpt);
void bpt_set_dealloc_hook(bpt_t bpt, bpt_key_t key, void (*hook)(bpt_key_t key, void* value));

// Making Maps Functional
void bpt_seal(bpt_t bpt);
```


[Patricia Trees]: http://citeseer.ist.psu.edu/okasaki98fast.html
