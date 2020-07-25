#include "rdg_branch.h"
#include "rdg_buffer.h"
#include "rdg_group.h"
#include "rdg_range.h"

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main() {
    struct rdg_branch* trunk = NULL;
    struct rdg_group* group = NULL;
    struct rdg_branch *branch1 = NULL, *branch2 = NULL;
    struct rdg_range* range = NULL;
    struct rdg_branch_iterator *iter = NULL;
    struct rdg_buffer *buffer = NULL;
    const unsigned char* data = NULL;
    trunk = rdg_branch_new();
    assert(trunk != NULL);
    
    (void) rdg_branch_add_atom(trunk, 'a'); /* a */
    assert(rdg_branch_permutations(trunk) == 1);
    
    (void) rdg_branch_add_atom(trunk, 'b');
    assert(rdg_branch_permutations(trunk) == 1); /* ab */
    
    (void) rdg_branch_add_atom(trunk, 'c'); /* abc */
    assert(rdg_branch_permutations(trunk) == 1);
    
    range = rdg_range_new_inclusive('a', 'z'); /* abc[a-z] */
    (void) rdg_branch_add_range(trunk, range);
    assert(rdg_branch_permutations(trunk) == 26);
   
    branch1 = rdg_branch_new();
    assert(branch1 != NULL);

    branch2 = rdg_branch_new();
    assert(branch2 != NULL);

    (void) rdg_branch_add_atom(branch1, '1');
    assert(rdg_branch_permutations(branch1) == 1);

    (void) rdg_branch_add_atom(branch2, 'Z');
    assert(rdg_branch_permutations(branch2) == 1);

    group = rdg_group_new();
    assert(group != NULL);

    (void) rdg_group_add_branch(group, branch1); /* abc[a-z](1|Z) */
    (void) rdg_group_add_branch(group, branch2);
    (void) rdg_branch_add_group(trunk, group);
    assert(rdg_branch_permutations(trunk) == 52);
    
    iter = rdg_branch_begin(trunk);
    assert(iter != NULL);

    buffer = rdg_buffer_new(rdg_branch_max_size(trunk));
    assert(buffer != NULL);
    
    (void) rdg_buffer_reset(buffer); 
    (void) rdg_branch_get(buffer, iter);
    data = rdg_buffer_get(buffer);
    assert(memcmp(data, "abca1", 5) == 0);

    assert(rdg_branch_next(iter));
    (void) rdg_buffer_reset(buffer); 
    (void) rdg_branch_get(buffer, iter);
    data = rdg_buffer_get(buffer);
    assert(memcmp(data, "abcaZ", 5) == 0);
    
    assert(rdg_branch_next(iter));

    (void) rdg_buffer_free(buffer); 
    (void) rdg_branch_free(trunk);
    return 0;
}
