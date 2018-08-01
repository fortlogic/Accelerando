//
//  polynomial.h
//  Accelerando
//
//  Created by Matias Eyzaguirre on 2018-07-31.
//  Copyright © 2018 Matias Eyzaguirre. All rights reserved.
//

#ifndef polynomial_h
#define polynomial_h

#include <Accelerando/workspace.h>

void polynomial_evaluate(const float * _Nonnull coeff,  long coeff_stride, unsigned long degree,
                         const float * _Nonnull input,  long input_stride, unsigned long input_count,
                               float * _Nonnull output, long output_stride);

void polynomial_evaluate_double(const double * _Nonnull coeff,  long coeff_stride, unsigned long degree,
                                const double * _Nonnull input,  long input_stride, unsigned long input_count,
                                      double * _Nonnull output, long output_stride);

void polynomial_multiply(const float * _Nonnull a, long a_stride, unsigned long a_degree,
                         const float * _Nonnull b, long b_stride, unsigned long b_degree,
                               float * _Nonnull c, long c_stride, unsigned long c_degree,
                         workspace_t _Nullable workspace);

void polynomial_multiply_double(const double * _Nonnull a, long a_stride, unsigned long a_degree,
                                const double * _Nonnull b, long b_stride, unsigned long b_degree,
                                      double * _Nonnull c, long c_stride, unsigned long c_degree,
                                workspace_t _Nullable workspace);

#endif /* polynomial_h */
