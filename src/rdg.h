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
 * @brief Gets the library version string
 *
 * @returns A pointer to the static version string
 */
const char* rdg_get_version(void);

/**
 * @brief Creates a new data generator based off the provided expression
 *
 * Creates the rdg object that stores the state of the generated regular
 * expression. It is the application's responsibility to free with rdg_free();
 *
 * @param[in] expression A regular expression (within the defined subset)
 * 
 * @return A data generator
 */
struct rdg* rdg_new(const char* expression);

/**
 * @brief Generates the next result from the data generator 
 *
 * @warning This is not thread-safe.
 *
 * @param[out] result Generated data
 * @param[out] size Size of generated data
 * @param[in] rdg A data generator
 * 
 * @return Whether a value was generated
 */
int rdg_generate(unsigned char **result, size_t *size, struct rdg* rdg);

/**
 * @brief Calculates the number of permutations
 *
 * @param[in] rdg A data generator
 *
 * @return The number of permutations the data generator can create.
 */
size_t rdg_permutations(const struct rdg* rdg);

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
