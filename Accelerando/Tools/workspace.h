//
//  workspace.h
//  Accelerando
//
//  Created by Matias Eyzaguirre on 2018-07-31.
//  Copyright © 2018 Matias Eyzaguirre. All rights reserved.
//

#ifndef workspace_h
#define workspace_h

#include <stdlib.h>
#include <stdbool.h>

struct workspace;
typedef struct workspace *workspace_t;

// basic create and destroy.
workspace_t _Nullable workspace_create(void);
void workspace_destroy(workspace_t _Nonnull w);

bool workspace_is_locked_size(workspace_t _Nonnull w);
void workspace_lock_size(workspace_t _Nonnull w);
void workspace_unlock_size(workspace_t _Nonnull w);

// changing the size.
bool workspace_resize_as_raw_bytes(workspace_t _Nonnull w, size_t length);
bool workspace_resize_as_vector(workspace_t _Nonnull w, size_t count);
bool workspace_resize_as_vectorD(workspace_t _Nonnull w, size_t count);
bool workspace_resize_as_matrix(workspace_t _Nonnull w, size_t row_count, size_t column_count);
bool workspace_resize_as_matrixD(workspace_t _Nonnull w, size_t row_count, size_t column_count);



#endif /* workspace_h */
