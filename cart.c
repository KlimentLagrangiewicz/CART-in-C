#include "cart.h"

double calcGini(const double *x, const int m, const int *y, const int noc, const int *nums, const int sch, const double data, const int k, int *left, int *right) {
	double gini = 0.0;
	int i, j, L = 0, R = 0, buf;
    for (i = 0; i < sch; i++) {
		buf = nums[i];
    	if (x[buf * m + k] > data) {
    		R++;
    		for (j = 0; j < noc; j++)
    			if (y[buf] == j)
    				right[j]++;
    	} else {
    		L++;
    		for (j = 0; j < noc; j++)
    			if (y[buf] == j)
    				left[j]++;
    	}
    }
    for (i = 0; i < noc; i++) {
    	gini += ((L != 0) ? ((double)left[i] * left[i] / L) : 0.0) + ((R != 0) ? ((double)right[i] * right[i] / R) : 0.0);
    }
	return (double)sch - gini;
}

void getValueAndAtr(const double *x,const int *y, const int m, const int noc, const int *num, const int sch, double *val, int *k) {
	double opt_data = x[num[0]], cur_gini;
	int i, j, buf, opt_k = 0;
	int *left = (int*)malloc(noc * sizeof(int));
	int *right = (int*)malloc(noc * sizeof(int));
	memset(left, 0, noc * sizeof(int));
	memset(right, 0, noc * sizeof(int));
	double min_gini = calcGini(x, m, y, noc, num, sch, opt_data, opt_k, left, right);
	for (j = 0; j < sch; j++) {
		buf = num[j];
		for (i = 0; i < m; i++) {
			memset(left, 0, noc * sizeof(int));
			memset(right, 0, noc * sizeof(int));
			cur_gini = calcGini(x, m, y, noc, num, sch, x[buf * m + i], i, left, right);
			if (cur_gini < min_gini) {
				min_gini = cur_gini;
				opt_k = i;
				opt_data = x[buf * m + i];
			}
		}
	}
	free(left);
	free(right);
	*val = opt_data;
	*k = opt_k;
}

short list(const int *y, const int *numbers, const int sch) {
	int i, value = y[numbers[0]];
	for (i = 0; i < sch; i++) {
		if (y[numbers[i]] != value)
			return 0;
	}
	return 1;
}

void addIntVect(int **vect, int *size, const int value) {
	*vect = (int*)realloc(*vect, (*size + 1) * sizeof(int));
	*(*vect + *size) = value;
	*size += 1;
}

void createBinTree(btree *tree, const double *x, const int *y, const int m, const int *numbers, const int sch, const int noc) {
	if (!list(y, numbers, sch)) {
		double val;
		int i, k, nol = 0, nor = 0;
		getValueAndAtr(x, y, m, noc, numbers, sch, &val, &k);
		tree->data = val;
		tree->num_q = k;
		int *lefts = (int*)malloc(0 * sizeof(int));
		int *rights = (int*)malloc(0 * sizeof(int));
		for (i = 0; i < sch; i++) {
			if (x[numbers[i]* m + k] > val) {
				addIntVect(&rights, &nor, numbers[i]);
			} else {
				addIntVect(&lefts, &nol, numbers[i]);
			}
		}
		tree->right = (btree*)malloc(sizeof(btree));
		tree->left = (btree*)malloc(sizeof(btree));
		createBinTree(tree->right, x, y, m, rights, nor, noc);
		free(rights);
		createBinTree(tree->left, x, y, m, lefts, nol, noc);
		free(lefts);
	} else {
		tree->left = NULL;
		tree->right = NULL;
		tree->num_q = y[numbers[0]];
	}
}

int getClass(const btree *tree, const double *x, const int m, const int l) {
	int cl;
	if ((tree->left == NULL) || (tree->right == NULL))
		cl = tree->num_q;
	else cl = ((x[m * l + tree->num_q] > (tree->data)) ? getClass(tree->right, x, m, l) : getClass(tree->left, x, m, l));
	return cl;
}

void getClasses(const btree *tree, const double *x, int *res, const int n, const int m) {
	int i;
	for (i = 0; i < n; i++) {
		res[i] = getClass(tree, x, m, i);
	}
}

void freeBinTree(btree *tree) {
	if (tree != NULL) {
		freeBinTree(tree->left);
		freeBinTree(tree->right);
		free(tree);
	}
}
