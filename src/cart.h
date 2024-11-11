#ifndef CART_H_
#define CART_H_

#include <stdlib.h>
#include <string.h>

typedef struct btree {
	double data;
	int num_q;
	struct btree* left;
	struct btree* right;
} btree;

double calc_gini(const double* const x, const int m, const int* const y, const int noc, const int* const nums, const int sch, const double data, const int k, int* const left, int* const right);
void get_value_and_attribute(const double* const x, const int* const y, const int m, const int noc, const int* const num, const int sch, double* const val, int* const k);
char is_list(const int* const y, const int *numbers, int sch);
void create_bin_tree(btree *tree, const double *x, const int *y, const int m, const int *numbers, const int sch, const int noc);
int get_class(const btree* const tree, const double* const x, const int id);
void get_classes(const btree* const tree, const double* const x, int* const res, int n, const int m);
void free_bin_tree(btree *tree);

#endif
