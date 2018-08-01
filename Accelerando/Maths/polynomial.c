//
//  polynomial.c
//  Accelerando
//
//  Created by Matias Eyzaguirre on 2018-07-31.
//  Copyright © 2018 Matias Eyzaguirre. All rights reserved.
//

#include "polynomial.h"

#include <Accelerate/Accelerate.h>

void polynomial_evaluate(const float * _Nonnull coeff,  long coeff_stride, unsigned long degree,
                         const float * _Nonnull input,  long input_stride, unsigned long input_count,
                               float * _Nonnull output, long output_stride) {
  vDSP_vpoly(coeff, coeff_stride, input, input_stride, output, output_stride, input_count, degree);
}

void polynomial_evaluate_double(const double * _Nonnull coeff,  long coeff_stride, unsigned long degree,
                                const double * _Nonnull input,  long input_stride, unsigned long input_count,
                                      double * _Nonnull output, long output_stride) {
  vDSP_vpolyD(coeff, coeff_stride, input, input_stride, output, output_stride, input_count, degree);
}

void polynomial_multiply(const float * _Nonnull a, long a_stride, unsigned long a_degree,
                         const float * _Nonnull b, long b_stride, unsigned long b_degree,
                               float * _Nonnull c, long c_stride, unsigned long c_degree,
                         workspace_t _Nullable workspace) {
  // there has to be room in c.
  assert(c_degree >= a_degree + b_degree);

  // outer product dimensions need to fit in an int.
  assert((a_degree*b_degree) < INT_MAX);

  // we need enough workspace.
  workspace_t w = workspace == NULL ? workspace_create() : workspace;
  workspace_resize_as_matrix(w, false, a_degree, b_degree);

  // grab the buffer and zero it out.
  float *outer_product = (float*) workspace_buffer(w);
  catlas_sset((int)(a_degree*b_degree), 0.0, outer_product, 1);

  // compute the outer product of the two polynomials
  // o := outer(a,b)
  // dim(o) == {rows: a_degree, cols: b_degree}
  cblas_sger(CblasRowMajor,
             (int)a_degree, (int)b_degree,
             1.0,
             a, (int)a_stride,
             b, (int)b_stride,
             outer_product,
             (int)b_degree);


  // c[i] := sum( diagonal(o, i) )
  // such that diagonal(m, n) is the vector of all the entries m[x,y] in m such that x+y=n.
  for (int i = 0 ; i < a_stride ; i++) {
    // add each row of the outer product to the result. For each row we offset the result address that we start copying into by one.
    float *outer_row = outer_product + (i * b_degree);
    float *result_offset = c + i;
    vDSP_vadd(result_offset, 1,
              outer_row, 1,
              result_offset, 1, b_degree);
  }
}

void polynomial_multiply_double(const double * _Nonnull a, long a_stride, unsigned long a_degree,
                                const double * _Nonnull b, long b_stride, unsigned long b_degree,
                                      double * _Nonnull c, long c_stride, unsigned long c_degree,
                                workspace_t _Nullable workspace) {
  // there has to be room in c.
  assert(c_degree >= a_degree + b_degree);

  // outer product dimensions need to fit in an int.
  assert((a_degree*b_degree) < INT_MAX);

  // we need enough workspace.
  workspace_t w = workspace == NULL ? workspace_create() : workspace;
  workspace_resize_as_matrixD(w, false, a_degree, b_degree);

  // grab the buffer and zero it out.
  double *outer_product = (double*) workspace_buffer(w);
  catlas_dset((int)(a_degree*b_degree), 0.0, outer_product, 1);

  // compute the outer product of the two polynomials
  // o := outer(a,b)
  // dim(o) == {rows: a_degree, cols: b_degree}
  cblas_dger(CblasRowMajor,
             (int)a_degree, (int)b_degree,
             1.0,
             a, (int)a_stride,
             b, (int)b_stride,
             outer_product,
             (int)b_degree);


  // c[i] := sum( diagonal(o, i) )
  // such that diagonal(m, n) is the vector of all the entries m[x,y] in m such that x+y=n.
  for (int i = 0 ; i < a_stride ; i++) {
    // add each row of the outer product to the result. For each row we offset the result address that we start copying into by one.
    double *outer_row = outer_product + (i * b_degree);
    double *result_offset = c + i;
    vDSP_vaddD(result_offset, 1,
               outer_row, 1,
               result_offset, 1, b_degree);
  }
}
