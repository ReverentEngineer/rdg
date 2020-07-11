#include "rdg_buffer.h"

#include <stdlib.h>
#include <string.h>

struct rdg_buffer {
  unsigned char* data;
  int size;
};

struct rdg_buffer* rdg_buffer_new(void) {
  return calloc(1, sizeof(struct rdg_buffer));
}



void rdg_buffer_append(struct rdg_buffer* buffer, const unsigned char* data, int size) {
  buffer->data = realloc(buffer->data, buffer->size + size);
  memcpy(buffer->data + buffer->size, data, size);
  buffer->size += size;
}

size_t rdg_buffer_size(const struct rdg_buffer* buffer) {
  return buffer->size;
}

unsigned char* rdg_buffer_release(struct rdg_buffer* buffer) {
  unsigned char* data = NULL;
  if (buffer) {
    if (buffer->data) {
      data = buffer->data;
    }
    free(buffer);
  }
  return data;
}
