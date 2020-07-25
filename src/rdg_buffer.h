/**
 * @file rdg_buffer.h
 *
 * @brief A buffer for managing appending data
 */

#ifndef __RDG_BUFFER_H__
#define __RDG_BUFFER_H__

#include <stddef.h>

/** A data buffer */
struct rdg_buffer;

/**
 * @brief Creates a new data buffer
 *
 * @param[in] size Size of pre-allocated buffer
 *
 * @returns A data buffer
 */
struct rdg_buffer* rdg_buffer_new(int size);

/**
 * @brief Appends data to the buffer
 * 
 * @param[in,out] buffer Buffer to which to append data
 * @param[in] data Data to append
 * @param[in] size Size of data to append
 */
void rdg_buffer_append(struct rdg_buffer* buffer, const unsigned char* data, int size);

/**
 * @brief Gets the size of the current data stored in the buffer
 *
 * @param[in] buffer Buffer from which to retrieve size
 *
 * @returns Size of stored data
 */
size_t rdg_buffer_size(const struct rdg_buffer* buffer);

/**
 * @brief Returns the pointer to backed data
 *
 * @param[in] buffer Buffer
 *
 * @return Pointer to stored data
 */
const unsigned char* rdg_buffer_get(const struct rdg_buffer* buffer);

/**
 * @brief Resets the stored data pointer
 *
 * @pram[in] buffer Buffer
 */
void rdg_buffer_reset(struct rdg_buffer* buffer);

/**
 * @brief Frees the data buffer
 *
 * @param[in] buffer Buffer to free
 */
void rdg_buffer_free(struct rdg_buffer* buffer);

#endif /* __RDG_BUFFER_H__ */
