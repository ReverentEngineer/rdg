#include "rdg_buffer.h"

#include <stdlib.h>
#include <string.h>

struct rdg_buffer {
  unsigned char* data;
  int max_size;
  int size;
};

struct rdg_buffer* rdg_buffer_new(int size) {
  struct rdg_buffer* buffer = malloc(sizeof(struct rdg_buffer));
  buffer->data = malloc(size);
  buffer->max_size = size;
  buffer->size = 0;
  return buffer;
}

void rdg_buffer_append(struct rdg_buffer* buffer, const unsigned char* data, int size) {
  if (size + buffer->size > buffer->max_size) {
    abort();
    // TODO: Handle better
  }
  memcpy(buffer->data + buffer->size, data, size);
  buffer->size += size;
}

size_t rdg_buffer_size(const struct rdg_buffer* buffer) {
  return buffer->size;
}

const unsigned char* rdg_buffer_get(const struct rdg_buffer* buffer) {
  const unsigned char* data = NULL;
  if (buffer) {
    if (buffer->data) {
      data = buffer->data;
    }
  }
  return data;
}

void rdg_buffer_reset(struct rdg_buffer* buffer) {
  buffer->size = 0;
}


void rdg_buffer_free(struct rdg_buffer* buffer) {
  if (buffer) {
    if (buffer->data) {
      free(buffer->data);
    }
    free(buffer);
  }
}
