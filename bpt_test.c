#include "stdio.h"
#include "stdlib.h"
#include "bitmapped_patricia_tree.h"

void print_deallocation(bpt_key_t key, void *value) {
  printf("Deallocated: %s\n", value);
}

void print_mapping(bpt_key_t key, void *value, void *user_data) {
  printf(" %d -> %s\n", key, value);
}

void print_tree(bpt_t b) {
  bpt_for_mappings(b, print_mapping, NULL);
}

bpt_t bpt_assoc_and_release(bpt_t bpt, bpt_key_t key, void *value) {
  bpt_t new_bpt = bpt_assoc(bpt, key, value);
  bpt_release(bpt);
  return new_bpt;
}

bpt_t bpt_dissoc_and_release(bpt_t bpt, bpt_key_t key) {
  bpt_t new_bpt = bpt_dissoc(bpt, key);
  bpt_release(bpt);
  return new_bpt;
}

int main() {
  bpt_t b1, b2;

  b1 = bpt_assoc            (NULL, 0, "zero");
  b1 = bpt_assoc_and_release(b1,   1, "one");
  b1 = bpt_assoc_and_release(b1,   2, "two");
  b1 = bpt_assoc_and_release(b1,   3, "three");
  b1 = bpt_assoc_and_release(b1,   4, "four");
  bpt_seal(b1);

  b2 = bpt_assoc            (b1,   0, "null");
  b2 = bpt_assoc_and_release(b2,   3, "a triple");

  b1 = bpt_assoc_and_release(b1,   5, "five");

  printf("Map 1:\n");
  print_tree(b1);
  printf("\nMap 2:\n");
  print_tree(b2);

  bpt_set_dealloc_hook(b1, 0, print_deallocation);
  bpt_set_dealloc_hook(b1, 1, print_deallocation);
  bpt_set_dealloc_hook(b1, 2, print_deallocation);
  bpt_set_dealloc_hook(b1, 3, print_deallocation);
  bpt_set_dealloc_hook(b1, 4, print_deallocation);
  bpt_set_dealloc_hook(b1, 5, print_deallocation);

  bpt_set_dealloc_hook(b2, 0, print_deallocation);
  bpt_set_dealloc_hook(b2, 3, print_deallocation);

  bpt_release(b1);
  bpt_release(b2);

  return EXIT_SUCCESS;
}
