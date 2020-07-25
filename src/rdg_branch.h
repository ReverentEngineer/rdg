/**
 * @file rdg_branch.h
 *
 * @brief A linear set of regular expression components
 */
#ifndef __RDG_BRANCH_H__
#define __RDG_BRANCH_H__

struct rdg_buffer;
struct rdg_range;
struct rdg_group;

/** @brief RDG branch */
struct rdg_branch;

/** @brief RDG branch iterator */
struct rdg_branch_iterator;

/**
 * @brief Creates a new regex branch
 *
 * @returns A new branch
 */
struct rdg_branch* rdg_branch_new(void);

/**
 * @brief Frees the branch
 *
 * @param[in] branch Branch to free
 */
void rdg_branch_free(struct rdg_branch* branch);

/**
 * @brief Appends an atom o a branch
 *
 * @param[in,out] branch Branch to which to append
 * @param[in] atom Atom to append
 */
void rdg_branch_add_atom(struct rdg_branch* branch, char atom);

/**
 * @brief Appends a range to a brnach
 *
 * @param[in,out] branch Branch to which to append
 * @param[in] range Range to append
 */
void rdg_branch_add_range(struct rdg_branch* branch, struct rdg_range* range);

/**
 * @briefs Appends a group to a brnach
 *
 * @param[in,out] branch Branch to which to append
 * @param[in] group Group to append
 */
void rdg_branch_add_group(struct rdg_branch* branch, struct rdg_group* group);

/**
 * @brief Sets the branch iterator to the beginning and retrieves it
 *
 * @note Each branch has only one iterator so it is not thread-safe
 *
 * @param[in] branch Branch to iterate over
 * 
 * @returns The branch iterator
 */
struct rdg_branch_iterator* rdg_branch_begin(struct rdg_branch* branch);

/**
 * @brief Attempts to iterate
 *
 * @param[in] iterator Branch iterator
 *
 * @returns Whether there was a next permutation
 */
int rdg_branch_next(struct rdg_branch_iterator* iterator);

/**
 * @brief Retrieves the current permutation of the branch
 *
 * @param[in,out] buffer Buffer to fill
 * @param[in] iterator Branch iterator
 *
 * @returns A buffer containing the current permutation
 */
void rdg_branch_get(struct rdg_buffer* buffer, struct rdg_branch_iterator* iterator);

/**
 * @brief Gets the number of permutations in a branch
 *
 * @returns Number of permutations
 */
int rdg_branch_permutations(const struct rdg_branch* branch);

/**
 * @brief Gets the maximum size of the branch
 *
 * @param[in] branch The branch
 *
 * @returns Maximum size of the branch
 */
int rdg_branch_max_size(const struct rdg_branch* branch);

#endif /* __BRANCH_H__ */
