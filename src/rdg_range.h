/**
 * @file rdg_range.h
 *
 * @brief Represents a range of bytes/characters in an expression
 */
#ifndef __RDG_RANGE_H__
#define __RDG_RANGE_H__

/** RDG range */
struct rdg_range;
/** RDG range iterator */
struct rdg_range_iterator;

/** 
 * @brief Creates a new range
 *
 * @returns A new range
 */
struct rdg_range* rdg_range_new(void);

/** 
 * @brief Creates a new regex range using an inclusive range of characteers
 *
 * @param[in] from The starting charater
 * @param[in] to The ending character
 *
 * @return A new range with the included characters
 */
struct rdg_range* rdg_range_new_inclusive(const unsigned char from, const unsigned char to);

/**
 * @brief Frees the range
 *
 * @param[in] range Range to free
 */
void rdg_range_free(struct rdg_range* range);

/**
 * @brief Gets the number of permutations 
 *
 * @param[in] range Range
 *
 * @returns Number of permutations
 */
int rdg_range_permutations(const struct rdg_range* range);

/**
 * @brief Appends elements in a range to a range
 *
 * @param[in,out] to Range to which to append
 * @param[in] from Range to append
 */
void rdg_range_append(struct rdg_range* to, struct rdg_range* from);

/**
 * @brief Appends an atom to a range
 *
 * @param[in,out] range Range
 * @param[in] atom Atom to append
 */
void rdg_range_append_atom(struct rdg_range* range, unsigned char atom);

/**
 * @brief Resets and returns the iterator
 *
 * @param[in] range Range
 *
 * @returns The range iterator
 */
struct rdg_range_iterator* rdg_range_begin(struct rdg_range* range);

/**
 * @brief Retrieves current atom
 *
 * @param[in] iterator Range iterator
 *
 * @returns The current atom in range
 */
unsigned char rdg_range_get(const struct rdg_range_iterator* iterator);

/**
 * @brief Attempts to iterate the range
 *
 * @param[in] iterator Range iterator 
 *
 * @returns Whether there's a next atom
 */
int rdg_range_next(struct rdg_range_iterator* iterator);

#endif /* __RDG_RANGE_H_ */
