#ifndef CART_H_
#define CART_H_

#include <stdlib.h>
#include <string.h>
#include <float.h>

typedef struct btree btree;
struct btree {
	double data;
	int num_q;
	btree* left;
	btree* right;
};

double calcGini(const double* const x, const int m, const int* const y, const int noc, const int* const nums, const int sch, const double data, const int k, int* const left, int* const right);
void getValueAndAtr(const double* const x, const int* const y, const int m, const int noc, const int* const num, const int sch, double* const val, int* const k);
char list(const int* const y, const int *numbers, const int sch);
void createBinTree(btree *tree, const double *x, const int *y, const int m, const int *numbers, const int sch, const int noc);
int getClass(const btree* const tree, const double* const x, const int id);
void getClasses(const btree* const tree, const double* const x, int* const res, const int n, const int m);
void freeBinTree(btree *tree);

#endif
