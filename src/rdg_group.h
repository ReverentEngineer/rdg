/**
 * @file rdg_group.h
 *
 * @brief Group of branching options
 */

#ifndef __RDG_GROUP_H__
#define __RDG_GROUP_H__

struct rdg_branch;

/** RDG group */
struct rdg_group;

/** RDG group iterator */
struct rdg_group_iterator;

/**
 * @brief Creates a new group
 *
 * @returns A new group
 */
struct rdg_group* rdg_group_new(void);

/** 
 * @brief Frees a regex group
 *
 * @param[in] group Group to free
 **/
void rdg_group_free(struct rdg_group* group);

/** 
 * @brief Adds a branch to a group
 *
 * @param[in,out] group Group
 * @param[in] branch Branch to add to group
 **/
void rdg_group_add_branch(struct rdg_group* group, struct rdg_branch* branch);

/**
 * @brief Resets and returns the group iterator
 *
 * @parma[in] group Group
 *
 * @returns The group iterator
 */
struct rdg_group_iterator* rdg_group_begin(struct rdg_group* group);

/**
 * @brief Attempts to iterate over the group
 *
 * @param[in,out] iterator Group iterator
 * 
 * @returns Whether the iteration was successful
 */
int rdg_group_next(struct rdg_group_iterator* iterator);

/**
 * @brief Retrieves the current branch
 *
 * @param[in] iterator Group iterator
 *
 * @returns The current branch
 */
struct rdg_branch* rdg_group_get(const struct rdg_group_iterator* iterator);

/**
 * @brief Gets the number of permutations in the group
 *
 * @param[in] group The group
 *
 * @returns The number of permutations in the group
 */
int rdg_group_permutations(const struct rdg_group* group);

/**
 * @brief Gets the maximum size in the group
 *
 * @param[in] group The group
 *
 * @returns The maxmimum size of the group
 */
int rdg_group_max_size(const struct rdg_group* group);

#endif /* __GROUP_H__ */
