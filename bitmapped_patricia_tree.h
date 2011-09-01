// -*- mode: c; coding: utf-8 -*- */
//
// Copyright 2010, 2011, Matthias Andreas Benkard.
//
//-----------------------------------------------------------------------------
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------------
//

// An implementation of a bitmapped Patricia tree.

#ifndef __BITMAPPED_PATRICIA_TREE_H
#define __BITMAPPED_PATRICIA_TREE_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BPT_ENABLE_DEALLOC_HOOKS 1

typedef int32_t bpt_key_t;
typedef int32_t bpt_key_bitmask_t;

enum bpt_tag {
  BPT_LEAF,
  BPT_INNER_NODE
};

struct bpt;
typedef struct bpt *bpt_t;

void *bpt_get(bpt_t bpt, bpt_key_t key);
bool bpt_has_key(bpt_t bpt, bpt_key_t key);
void **bpt_get_pointer(bpt_t bpt, bpt_key_t key);
bpt_t bpt_assoc(bpt_t bpt, bpt_key_t key, void *item);
bpt_t bpt_dissoc(bpt_t bpt, bpt_key_t key);
void init_bpt_leaf(bpt_t leaf, bpt_key_t key, void *value);
bpt_t bpt_make_leaf(bpt_key_t key, void *value);
void bpt_retain(bpt_t bpt);
void bpt_release(bpt_t bpt);
void bpt_dealloc(bpt_t bpt);
void bpt_seal(bpt_t bpt);

#ifdef BPT_ENABLE_DEALLOC_HOOKS
void bpt_set_dealloc_hook(bpt_t bpt, bpt_key_t key, void (*hook)(bpt_key_t key, void* value));
#endif

#ifdef __cplusplus
}
#endif
#endif
