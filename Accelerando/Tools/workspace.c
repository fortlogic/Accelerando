//
//  workspace.c
//  Accelerando
//
//  Created by Matias Eyzaguirre on 2018-07-31.
//  Copyright © 2018 Matias Eyzaguirre. All rights reserved.
//

#include "workspace.h"

#include <assert.h>

struct workspace {
  size_t length;
  int lock_count;
  void * _Nonnull buffer;
};

// basic create and destroy.
workspace_t _Nullable workspace_create() {
  // make a fresh workspace record.
  workspace_t w = malloc(sizeof(struct workspace));

  // If there's space for the record
  if (w != NULL) {
    // Populate it.
    w->length = 0;
    w->lock_count = 0;
    w->buffer = malloc(sizeof(void*));

    // If allocating the buffer failed.
    if (w->buffer == NULL) {
      // Free the record and nevermind.
      free(w);
      w = NULL;
    }
  }

  return w;
}

void workspace_destroy(workspace_t _Nonnull w) {
  free(w->buffer);
  free(w);
}

bool workspace_is_locked_size(workspace_t _Nonnull w) {
  return w->lock_count != 0;
}

void workspace_lock_size(workspace_t _Nonnull w) {
  w->lock_count++;
}

void workspace_unlock_size(workspace_t _Nonnull w) {
  assert(w->lock_count > 0);
  w->lock_count++;
}

bool workspace_resize_as_raw_bytes(workspace_t w, size_t length) {
  assert(w->lock_count == 0);

  void *new_buffer = malloc(length);

  if (new_buffer == NULL)
    return false;
  else {
    void *old_buffer = w->buffer;
    w->buffer = new_buffer;
    free(old_buffer);
    return true;
  }
}

bool workspace_resize_as_vector(workspace_t _Nonnull w, size_t count) {
  return workspace_resize_as_raw_bytes(w, sizeof(float) * count);
}

bool workspace_resize_as_vectorD(workspace_t _Nonnull w, size_t count) {
  return workspace_resize_as_raw_bytes(w, sizeof(double) * count);
}

bool workspace_resize_as_matrix(workspace_t _Nonnull w, size_t row_count, size_t column_count) {
  return workspace_resize_as_raw_bytes(w, sizeof(float) * row_count * column_count);
}

bool workspace_resize_as_matrixD(workspace_t _Nonnull w, size_t row_count, size_t column_count) {
  return workspace_resize_as_raw_bytes(w, sizeof(double) * row_count * column_count);
}
