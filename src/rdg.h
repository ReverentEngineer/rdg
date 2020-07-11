/**
 * @file rdg.h
 * 
 * @brief Public interface for librdg.
 */

#ifndef __RDG_H__
#define __RDG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/** A regex (regular expression) data generator */
struct rdg;

/**
 * @brief Creates a new data generator based off the provided expression
 *
 * @param[in] expression A regular expression (within the defined subset)
 * 
 * @return A data generator
 */
struct rdg* rdg_new(const char* expression);

/**
 * @brief Generates the next result from the data generator 
 *
 * @param[in] rdg A data generator
 * 
 * @return A result showing the data gnerated
 */
int rdg_generate(unsigned char **result, size_t *size, struct rdg* rdg);

/**
 * @brief Calculates the number of permutations
 *
 * @param[in] rdg A data generator
 *
 * @return The number of permutations the data generator can create.
 */
int  rdg_permutations(const struct rdg* rdg);

/**
 * @brief Frees the data generator object
 *
 * @param[in] rdg The data generator
 */
void rdg_free(struct rdg* rdg);

#ifdef __cplusplus
}
#endif

#endif /* __RDG_H__ */
