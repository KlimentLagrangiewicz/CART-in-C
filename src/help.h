#ifndef HELP_H_
#define HELP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fscanfTrainData(double *x, int *y, const int n, const int m, const char *fn);
void fscanfTestData(double *x, const int n, const char *fn);
void fscanfIdealSpliting(int *id, const int n, const char *fn);
double calcAccuracy(const int *x, const int *y, const int n);
void fprintfResult(const int *y, const int n, const double t1, const double t2, const char *fn);
void fprintfFullRes(const int *y, const int n, const double a, const double t1, const double t2, const char *fn);
int getNumOfClass(const int* const y, const int n);

#endif
