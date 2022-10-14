
#ifndef CART_H_
#define CART_H_

#include <stdlib.h>
#include <string.h>

typedef struct btree btree;

struct btree {
	double data;
	int num_q;
	btree* left;
	btree* right;
};

double calcGini(const double *x, const int m, const int *y, const int noc, const int *nums, const int sch, const double data, const int k, int *left, int *right);
void getValueAndAtr(const double *x,const int *y, const int m, const int noc, const int *num, const int sch, double *val, int *k);
short list(const int *y, const int *numbers, const int sch);
void addIntVect(int **vect, int *size, const int value);
void createBinTree(btree *tree, const double *x, const int *y, const int m, const int *numbers, const int sch, const int noc);
int getClass(const btree *tree, const double *x, const int m, const int l);
void getClasses(const btree *tree, const double *x, int *res, const int n, const int m);
void freeBinTree(btree *tree);

#endif
