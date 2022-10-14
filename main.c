#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "help.h"
#include "cart.h"

long long TimeValue = 0;

unsigned long long time_RDTSC() {
	union ticks {
		unsigned long long tx;
		struct dblword {
			long tl, th;
		} dw;
	} t;
	__asm__ ("rdtsc\n"
	  : "=a" (t.dw.tl), "=d"(t.dw.th)
	  );
	return t.tx;
}

void time_start() { TimeValue = time_RDTSC(); }

long long time_stop() { return time_RDTSC() - TimeValue; }

int main(int argc, char **argv) {
	if (argc < 7) {
		printf("Not enough parameters...\n");
		exit(1);
	}
	int n = atoi(argv[1]), m = atoi(argv[2]), n2 = atoi(argv[3]), noc, i;
	double *xtrain = (double*)malloc(n * m * sizeof(double));
	int *y = (int *)malloc(n * sizeof(int));
	fscanfTrainData(xtrain, y, n, m, argv[4]);
	double *xtest = (double*)malloc(n2 * m * sizeof(double));
	fscanfTestData(xtest, n2 * n, argv[5]);
	int *res = (int*)malloc(n2 * sizeof(int));
	long long l1, l2;
	time_start();
	btree *tree = (btree*)malloc(sizeof(btree));
	noc = getNumOfClass(y, n);
	int *startNums = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; i++) {
		startNums[i] = i;
	}
	createBinTree(tree, xtrain, y, m, startNums, n, noc);
	l1 = time_stop();
	time_start();
	getClasses(tree, xtest, res, n2, m);
	l2 = time_stop();
	if (argc > 7) {
		int *id = (int*)malloc(n2 * sizeof(int));
		fscanfIdealSpliting(id, n2, argv[7]);
		double a = calcAccuracy(res, id, n2);
		fprintfFullRes(res, n2, a, argv[6]);
		free(id);
	} else {
		fprintfResult(res, n2, argv[6]);
	}
	printf("Creation binary tree time:  %lld number of processor clock cycles;\n", l1);
	printf("Time of receiving classes:  %lld number of processor clock cycles;\n", l2);
	printf("Time of CART:  %lld number of processor clock cycles;\n", l1 + l2);
	printf("The work of the program is completed!\n");
	free(startNums);
	free(res);
	free(xtest);
	free(xtrain);
	free(y);
	freeBinTree(tree);
	return 0;
}
