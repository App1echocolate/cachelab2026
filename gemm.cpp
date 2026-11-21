/*
寄存器分块矩阵乘法。
cache 为 32 组直接映射、每块 4 个 int。
把 C 的一小块累加留在寄存器里，A 的一列和 B 的一段只读一次。
*/

#include "cachelab.h"

#define m case0_m
#define n case0_n
#define p case0_p

void gemm_case0(ptr_reg A, ptr_reg B, ptr_reg C, ptr_reg buffer)
{
  for (reg i = 0; i < m; ++i)
  {
    for (reg j = 0; j < p; ++j)
    {
      reg tmpc = 0;
      for (reg k = 0; k < n; ++k)
      {
        reg tmpa = A[i * n + k];
        reg tmpb = B[k * p + j];
        tmpc += tmpa * tmpb;
      }
      C[i * p + j] = tmpc;
    }
  }
}

#undef m
#undef n
#undef p

#define m case1_m
#define n case1_n
#define p case1_p

void gemm_case1(ptr_reg A, ptr_reg B, ptr_reg C, ptr_reg buffer)
{

  for (reg i = 0; i < m; i += 4)
  {
    for (reg j = 0; j < p; j += 4)
    {
      reg c[4][4];
      for (reg k = 0; k < n; ++k)
      {
        reg a0 = A[(i + 0) * n + k];
        reg a1 = A[(i + 1) * n + k];
        reg a2 = A[(i + 2) * n + k];
        reg a3 = A[(i + 3) * n + k];
        reg b0 = B[k * p + j];
        reg b1 = B[k * p + j + 1];
        reg b2 = B[k * p + j + 2];
        reg b3 = B[k * p + j + 3];
        c[0][0] += a0 * b0;
        c[0][1] += a0 * b1;
        c[0][2] += a0 * b2;
        c[0][3] += a0 * b3;
        c[1][0] += a1 * b0;
        c[1][1] += a1 * b1;
        c[1][2] += a1 * b2;
        c[1][3] += a1 * b3;
        c[2][0] += a2 * b0;
        c[2][1] += a2 * b1;
        c[2][2] += a2 * b2;
        c[2][3] += a2 * b3;
        c[3][0] += a3 * b0;
        c[3][1] += a3 * b1;
        c[3][2] += a3 * b2;
        c[3][3] += a3 * b3;
      }
      C[(i + 0) * p + j] = c[0][0];
      C[(i + 0) * p + j + 1] = c[0][1];
      C[(i + 0) * p + j + 2] = c[0][2];
      C[(i + 0) * p + j + 3] = c[0][3];
      C[(i + 1) * p + j] = c[1][0];
      C[(i + 1) * p + j + 1] = c[1][1];
      C[(i + 1) * p + j + 2] = c[1][2];
      C[(i + 1) * p + j + 3] = c[1][3];
      C[(i + 2) * p + j] = c[2][0];
      C[(i + 2) * p + j + 1] = c[2][1];
      C[(i + 2) * p + j + 2] = c[2][2];
      C[(i + 2) * p + j + 3] = c[2][3];
      C[(i + 3) * p + j] = c[3][0];
      C[(i + 3) * p + j + 1] = c[3][1];
      C[(i + 3) * p + j + 2] = c[3][2];
      C[(i + 3) * p + j + 3] = c[3][3];
    }
  }
}

#undef m
#undef n
#undef p

#define m case2_m
#define n case2_n
#define p case2_p

void gemm_case2(ptr_reg A, ptr_reg B, ptr_reg C, ptr_reg buffer)
{

  for (reg i = 0; i < m; i += 4)
  {
    for (reg j = 0; j < p; j += 4)
    {
      reg c[4][4];
      for (reg k = 0; k < n; ++k)
      {
        reg a0 = A[(i + 0) * n + k];
        reg a1 = A[(i + 1) * n + k];
        reg a2 = A[(i + 2) * n + k];
        reg a3 = A[(i + 3) * n + k];
        reg b0 = B[k * p + j];
        reg b1 = B[k * p + j + 1];
        reg b2 = B[k * p + j + 2];
        reg b3 = B[k * p + j + 3];
        c[0][0] += a0 * b0;
        c[0][1] += a0 * b1;
        c[0][2] += a0 * b2;
        c[0][3] += a0 * b3;
        c[1][0] += a1 * b0;
        c[1][1] += a1 * b1;
        c[1][2] += a1 * b2;
        c[1][3] += a1 * b3;
        c[2][0] += a2 * b0;
        c[2][1] += a2 * b1;
        c[2][2] += a2 * b2;
        c[2][3] += a2 * b3;
        c[3][0] += a3 * b0;
        c[3][1] += a3 * b1;
        c[3][2] += a3 * b2;
        c[3][3] += a3 * b3;
      }
      C[(i + 0) * p + j] = c[0][0];
      C[(i + 0) * p + j + 1] = c[0][1];
      C[(i + 0) * p + j + 2] = c[0][2];
      C[(i + 0) * p + j + 3] = c[0][3];
      C[(i + 1) * p + j] = c[1][0];
      C[(i + 1) * p + j + 1] = c[1][1];
      C[(i + 1) * p + j + 2] = c[1][2];
      C[(i + 1) * p + j + 3] = c[1][3];
      C[(i + 2) * p + j] = c[2][0];
      C[(i + 2) * p + j + 1] = c[2][1];
      C[(i + 2) * p + j + 2] = c[2][2];
      C[(i + 2) * p + j + 3] = c[2][3];
      C[(i + 3) * p + j] = c[3][0];
      C[(i + 3) * p + j + 1] = c[3][1];
      C[(i + 3) * p + j + 2] = c[3][2];
      C[(i + 3) * p + j + 3] = c[3][3];
    }
  }
}

#undef m
#undef n
#undef p

#define m case3_m
#define n case3_n
#define p case3_p
#define BASE_B (m * n)
#define BASE_C (m * n + n * p)

#define KERNEL_4(I, J, JN) \
  { \
    reg c0[JN]; \
    reg c1[JN]; \
    reg c2[JN]; \
    reg c3[JN]; \
    for (reg k = 0; k < n; ++k) \
    { \
      reg a0 = A[((I) + 0) * n + k]; \
      reg a1 = A[((I) + 1) * n + k]; \
      reg a2 = A[((I) + 2) * n + k]; \
      reg a3 = A[((I) + 3) * n + k]; \
      for (reg t = 0; t < (JN); ++t) \
      { \
        reg b = A[BASE_B + k * p + (J) + t]; \
        c0[t] += a0 * b; \
        c1[t] += a1 * b; \
        c2[t] += a2 * b; \
        c3[t] += a3 * b; \
      } \
    } \
    for (reg t = 0; t < (JN); ++t) \
      A[BASE_C + ((I) + 0) * p + (J) + t] = c0[t]; \
    for (reg t = 0; t < (JN); ++t) \
      A[BASE_C + ((I) + 1) * p + (J) + t] = c1[t]; \
    for (reg t = 0; t < (JN); ++t) \
      A[BASE_C + ((I) + 2) * p + (J) + t] = c2[t]; \
    for (reg t = 0; t < (JN); ++t) \
      A[BASE_C + ((I) + 3) * p + (J) + t] = c3[t]; \
  }

#define KERNEL_3(I, J, JN) \
  { \
    reg c0[JN]; \
    reg c1[JN]; \
    reg c2[JN]; \
    for (reg k = 0; k < n; ++k) \
    { \
      reg a0 = A[((I) + 0) * n + k]; \
      reg a1 = A[((I) + 1) * n + k]; \
      reg a2 = A[((I) + 2) * n + k]; \
      for (reg t = 0; t < (JN); ++t) \
      { \
        reg b = A[BASE_B + k * p + (J) + t]; \
        c0[t] += a0 * b; \
        c1[t] += a1 * b; \
        c2[t] += a2 * b; \
      } \
    } \
    for (reg t = 0; t < (JN); ++t) \
      A[BASE_C + ((I) + 0) * p + (J) + t] = c0[t]; \
    for (reg t = 0; t < (JN); ++t) \
      A[BASE_C + ((I) + 1) * p + (J) + t] = c1[t]; \
    for (reg t = 0; t < (JN); ++t) \
      A[BASE_C + ((I) + 2) * p + (J) + t] = c2[t]; \
  }

void gemm_case3(ptr_reg A, ptr_reg B, ptr_reg C, ptr_reg buffer)
{
  {
    ptr_reg drop_b = std::move(B);
    ptr_reg drop_c = std::move(C);
    ptr_reg drop_buffer = std::move(buffer);
  }
  KERNEL_4(0, 0, 7)
  KERNEL_4(0, 7, 7)
  KERNEL_4(0, 14, 7)
  KERNEL_4(0, 21, 6)
  KERNEL_4(4, 0, 7)
  KERNEL_4(4, 7, 7)
  KERNEL_4(4, 14, 7)
  KERNEL_4(4, 21, 6)
  KERNEL_4(8, 0, 7)
  KERNEL_4(8, 7, 7)
  KERNEL_4(8, 14, 7)
  KERNEL_4(8, 21, 6)
  KERNEL_4(12, 0, 7)
  KERNEL_4(12, 7, 7)
  KERNEL_4(12, 14, 7)
  KERNEL_4(12, 21, 6)
  KERNEL_4(16, 0, 7)
  KERNEL_4(16, 7, 7)
  KERNEL_4(16, 14, 7)
  KERNEL_4(16, 21, 6)
  KERNEL_4(20, 0, 7)
  KERNEL_4(20, 7, 7)
  KERNEL_4(20, 14, 7)
  KERNEL_4(20, 21, 6)
  KERNEL_3(24, 0, 7)
  KERNEL_3(24, 7, 7)
  KERNEL_3(24, 14, 7)
  KERNEL_3(24, 21, 6)
}

#undef KERNEL_4
#undef KERNEL_3
#undef BASE_B
#undef BASE_C
#undef m
#undef n
#undef p
