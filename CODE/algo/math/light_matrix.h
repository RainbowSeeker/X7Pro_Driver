// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#ifndef X7PRO_DRIVER_LIGHT_MATRIX_H
#define X7PRO_DRIVER_LIGHT_MATRIX_H

#define MAT_TYPE   float
#define MAT_MALLOC MALLOC
#define MAT_FREE   FREE
#define MAT_PRINTF printf

typedef struct {
    int row, col;
    MAT_TYPE** element;
    MAT_TYPE* buffer;
} Mat;

Mat* MatCreate(Mat* mat, int row, int col);
void MatDelete(Mat* mat);
Mat* MatSetVal(Mat* mat, MAT_TYPE* val);
void MatDump(const Mat* mat);

Mat* MatZeros(Mat* mat);
Mat* MatEye(Mat* mat);

Mat* MatAdd(Mat* src1, Mat* src2, Mat* dst);
Mat* MatSub(Mat* src1, Mat* src2, Mat* dst);
Mat* MatMul(Mat* src1, Mat* src2, Mat* dst);
Mat* MatTrans(Mat* src, Mat* dst);
MAT_TYPE MatDet(Mat* mat);
Mat* MatAdj(Mat* src, Mat* dst);
Mat* MatInv(Mat* src, Mat* dst);

MAT_TYPE MatNorm(Mat* mat);
void MatEig(Mat* mat, MAT_TYPE* eig_val, Mat* eig_vec, MAT_TYPE eps, int njt);

void MatCopy(Mat* src, Mat* dst);

#endif //X7PRO_DRIVER_LIGHT_MATRIX_H
