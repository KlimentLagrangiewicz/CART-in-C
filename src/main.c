#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "help.h"
#include "cart.h"


int main(int argc, char **argv) {
	if (argc < 7) {
		printf("Not enough parameters...\n");
		exit(1);
	}
	const int n = atoi(argv[1]), m = atoi(argv[2]), n2 = atoi(argv[3]);
	int i, noc;
	double *xtrain = (double*)malloc(n * m * sizeof(double));
	int *y = (int *)malloc(n * sizeof(int));
	fscanfTrainData(xtrain, y, n, m, argv[4]);
	double *xtest = (double*)malloc(n2 * m * sizeof(double));
	fscanfTestData(xtest, n2 * n, argv[5]);
	int *res = (int*)malloc(n2 * sizeof(int));
	double t1, t2;
	t1 = clock();
	btree *tree = (btree*)malloc(sizeof(btree));
	noc = getNumOfClass(y, n);
	int *startNums = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; i++) {
		startNums[i] = i;
	}
	create_bin_tree(tree, xtrain, y, m, startNums, n, noc);
	t1 = clock() - t1;
	t1 /= CLOCKS_PER_SEC;
	t2 = clock();
	get_classes(tree, xtest, res, n2, m);
	t2 = clock() - t2;
	t2 /= CLOCKS_PER_SEC;
	if (argc > 7) {
		int *id = (int*)malloc(n2 * sizeof(int));
		fscanfIdealSpliting(id, n2, argv[7]);
		double a = calcAccuracy(res, id, n2);
		fprintfFullRes(res, n2, a, t1, t2, argv[6]);
		free(id);
		printf("Accuracy of classification by CART  = %lf;\n", a);
	} else {
		fprintfResult(res, n2, t1, t2, argv[6]);
	}
	printf("Creation binary tree time:  %lf s.;\n", t1);
	printf("Time of receiving classes:  %lf s.;\n", t2);
	printf("Time of CART:  %lf s.;\n", t1 + t2);
	printf("The work of the program is completed\n");
	free(startNums);
	free(res);
	free(xtest);
	free(xtrain);
	free(y);
	free_bin_tree(tree);
	return 0;
}
