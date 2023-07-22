#include "cart.h"

double calcGini(const double* const x, const int m, const int* const y, const int noc, const int* const nums, const int sch, const double data, const int k, int* const left, int* const right) {
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
	return (double)sch - ((L == 0) ? 1.0 : ((double)lefts / L)) - ((R == 0) ? 1.0 : ((double)rights / R));
}

void getValueAndAtr(const double* const x, const int* const y, const int m, const int noc, const int* const num, const int sch, double* const val, int* const k) {
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

char list(const int* const y, const int *numbers, const int sch) {
	int i = 0, value = y[*numbers];
	while (i < sch) {
		if (y[*(numbers)] != value)
			return 0;
		numbers++;
		i++;
	}
	return 1;
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
			    rights = (int*)realloc(rights, (nor + 1) * sizeof(int));
			    rights[nor] = numbers[i];
			    nor++;				
			} else {
				lefts = (int*)realloc(lefts, (nol + 1) * sizeof(int));
				lefts[nol] = numbers[i];
			    nol++;	
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

int getClass(const btree* const tree, const double* const x, const int id) {
	if ((tree->left == NULL) || (tree->right == NULL))
		return tree->num_q;
	return ((x[id + tree->num_q] > (tree->data)) ? getClass(tree->right, x, id) : getClass(tree->left, x, id));
}

void getClasses(const btree* const tree, const double* const x, int* const res, const int n, const int m) {
	int i = 0, j = 0;
	while (i < n) {
		res[i] = getClass(tree, x, j);
		j += m;
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
