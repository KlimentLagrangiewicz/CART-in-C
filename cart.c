#include "cart.h"

double calcGini(const double *x, const int m, const int *y, const int noc, const int *nums, const int sch, const double data, const int k, int *left, int *right) {
	int i, L, R, buf;
	i = L = R = 0;
	while (i < sch) {
		buf = nums[i];
		if (x[buf * m + k] > data) {
			R++;
			right[y[buf]]++;
		} else {
			L++;
			left[y[buf]]++;
		}
		i++;
	}
	unsigned int lefts, rights;
	i = lefts = rights = 0;
	while (i < noc) {
		lefts += left[i] * left[i];
		rights += right[i] * right[i];
		i++;
	}
	return (double)sch - (((double)lefts / (L == 0) ? 1 : L) + ((double)rights / (R == 0) ? 1 : R));
}

void getValueAndAtr(const double *x, const int *y, const int m, const int noc, const int *num, const int sch, double *val, int *k) {
	double opt_data = x[num[0] * m], cur_gini;
	int i, j, buf, opt_k = 0;
	const size_t size = noc * sizeof(int);
	int *left = (int*)malloc(size);
	int *right = (int*)malloc(size);
	double min_gini = DBL_MAX;
	for (j = 0; j < sch; j++) {
		buf = num[j] * m;
		for (i = 0; i < m; i++) {
			memset(left, 0, size);
			memset(right, 0, size);
			cur_gini = calcGini(x, m, y, noc, num, sch, x[buf + i], i, left, right);
			if (cur_gini < min_gini) {
				min_gini = cur_gini;
				opt_k = i;
				opt_data = x[buf + i];
			}
		}
	}
	free(left);
	free(right);
	*val = opt_data;
	*k = opt_k;
}

char list(const int *y, const int *numbers, const int sch) {
	int i = 0, value = y[*numbers];
	while (i < sch) {
		if (y[*(numbers)] != value)
			return 0;
		numbers++;
		i++;
	}
	return 1;
}

void addIntVect(int **vect, int *size, const int value) {
	*vect = (int*)realloc(*vect, (*size + 1) * sizeof(int));
	*(*vect + *size) = value;
	*size += 1;
}

void createBinTree(btree *tree, const double *x, const int *y, const int m, const int *numbers, const int sch, const int noc) {
	if (list(y, &numbers[0], sch)) {
		tree->left = NULL;
		tree->right = NULL;
		tree->num_q = y[numbers[0]];
	} else {
		double val;
		int i, k, nol, nor;
		getValueAndAtr(x, y, m, noc, numbers, sch, &val, &k);
		tree->data = val;
		tree->num_q = k;
		int *lefts = (int*)malloc(0 * sizeof(int));
		int *rights = (int*)malloc(0 * sizeof(int));
		i = nol = nor = 0;
		while (i < sch) {
			if (x[numbers[i] * m + k] > val) {
				addIntVect(&rights, &nor, numbers[i]);
			} else {
				addIntVect(&lefts, &nol, numbers[i]);
			}
			i++;
		}
		tree->right = (btree*)malloc(sizeof(btree));
		tree->left = (btree*)malloc(sizeof(btree));
		createBinTree(tree->right, x, y, m, rights, nor, noc);
		free(rights);
		createBinTree(tree->left, x, y, m, lefts, nol, noc);
		free(lefts);
	}
}

int getClass(const btree *tree, const double *x, const int m, const int l) {
	if ((tree->left == NULL) || (tree->right == NULL))
		return tree->num_q;
	return ((x[m * l + tree->num_q] > (tree->data)) ? getClass(tree->right, x, m, l) : getClass(tree->left, x, m, l));
}

void getClasses(const btree *tree, const double *x, int *res, const int n, const int m) {
	int i = 0;
	while (i < n) {
		res[i] = getClass(tree, x, m, i);
		i++;
	}
}

void freeBinTree(btree *tree) {
	if (tree != NULL) {
		freeBinTree(tree->left);
		freeBinTree(tree->right);
		free(tree);
	}
}
