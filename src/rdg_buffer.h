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
 * @returns A data buffer
 */
struct rdg_buffer* rdg_buffer_new(void);

/**
 * @brief Appends data to the buffer
 * 
 * @param[in,out] buffer Buffer to which to append data
 * @param[in] data Data to append
 * @param[in] size Size of data to append
 */
void rdg_buffer_append(struct rdg_buffer* buffer, const unsigned char* data, int size);

/**
 * @brief Gets the size of the buffer
 *
 * @param[in] buffer Buffer from which to retrieve size
 *
 * @returns Size of buffer
 */
size_t rdg_buffer_size(const struct rdg_buffer* buffer);

/**
 * @brief Returns the data and frees the data
 *
 * @param[in] buffer Buffer to release
 *
 * @return Data stored in buffer.
 */
unsigned char* rdg_buffer_release(struct rdg_buffer* buffer);


#endif /* __RDG_BUFFER_H__ */
