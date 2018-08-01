//
//  workspace.c
//  Accelerando
//
//  Created by Matias Eyzaguirre on 2018-07-31.
//  Copyright © 2018 Matias Eyzaguirre. All rights reserved.
//

#include "workspace.h"

struct workspace {
  size_t length;
  void * _Nonnull buffer;
};

workspace_t _Nullable workspace_create() {
  // make a fresh workspace record.
  workspace_t w = malloc(sizeof(struct workspace));

  // If there's space for the record
  if (w != NULL) {
    // Populate it.
    w->length = 0;
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

size_t workspace_buffer_size(workspace_t _Nonnull w) {
  return w->length;
}
void * _Nonnull workspace_buffer(workspace_t _Nonnull w) {
  return w->buffer;
}

bool workspace_resize_as_raw_bytes(workspace_t w, bool shouldShrink, size_t length) {
  if ((length > w->length) || shouldShrink ) {
    void *old_buffer = w->buffer;
    void *new_buffer = malloc(length);

    if (new_buffer == NULL)
      return false;
    else {
      w->buffer = new_buffer;
      free(old_buffer);
      return true;
    }
  } else
    return true;
}

bool workspace_resize_as_vector(workspace_t _Nonnull w, bool shouldShrink, size_t count) {
  return workspace_resize_as_raw_bytes(w, shouldShrink, sizeof(float) * count);
}

bool workspace_resize_as_vectorD(workspace_t _Nonnull w, bool shouldShrink, size_t count) {
  return workspace_resize_as_raw_bytes(w, shouldShrink, sizeof(double) * count);
}

bool workspace_resize_as_matrix(workspace_t _Nonnull w, bool shouldShrink, size_t row_count, size_t column_count) {
  return workspace_resize_as_raw_bytes(w, shouldShrink, sizeof(float) * row_count * column_count);
}

bool workspace_resize_as_matrixD(workspace_t _Nonnull w, bool shouldShrink, size_t row_count, size_t column_count) {
  return workspace_resize_as_raw_bytes(w, shouldShrink, sizeof(double) * row_count * column_count);
}
