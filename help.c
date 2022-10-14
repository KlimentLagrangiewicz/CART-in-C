
#include "help.h"

void fscanfTrainData(double *x, int *y, const int n, const int m, const char *fn) {
	FILE *fl;
	if ((fl = fopen(fn, "r")) == NULL) {
		printf("Error in opening %s file...\n", fn);
		exit(1);
	}
	int i, j, k;
	for (i = 0; i < n && !feof(fl); i++) {
		k = i * m;
		for (j = 0; j < m && !feof(fl); j++) {
			if (fscanf(fl, "%lf", &x[k + j]) == 0) {}
		}
		if (!feof(fl)) {
			if (fscanf(fl, "%d", &y[i]) == 0) {}
		}
	}
	fclose(fl);
}

void fscanfTestData(double *x, const int n, const char *fn) {
	FILE *fl;
	if ((fl = fopen(fn, "r")) == NULL) {
		printf("Error in opening %s file...\n", fn);
		exit(1);
	}
	int i;
	for (i = 0; i < n && !feof(fl); i++) {
		if (fscanf(fl, "%lf", &x[i]) == 0) {}
	}
	fclose(fl);
}

void fscanfIdealSpliting(int *id, const int n, const char *fn) {
	FILE *fl;
	if ((fl = fopen(fn, "r")) == NULL) {
		printf("Error in opening %s file...\n", fn);
		exit(1);
	}
	int i;
	for (i = 0; i < n && !feof(fl); i++) {
		if (fscanf(fl, "%d", &id[i]) == 0) {}
	}
	fclose(fl);
}

double calcAccuracy(const int *y, const int *id, const int n) {
	int i = 0, j = 0;
	while (i < n) {
		if (y[i] == id[i]) j++;
		i++;
	}
	return (double)j / (double)n;
}

void fprintfResult(const int *y, const int n, const char *fn) {
	FILE *fl;
	if ((fl = fopen(fn, "a")) == NULL) {
		printf("Error in opening %s result file\n", fn);
		exit(1);
	}
	int i;
	fprintf(fl, "Result of CART classification...\n");
	for (i = 0; i < n; i++)
		fprintf(fl, "Object[%d]: %d;\n", i, y[i]);
	fprintf(fl, "\n");
	fclose(fl);
}

void fprintfFullRes(const int *y, const int n, const double a, const char *fn) {
	FILE *fl;
	if ((fl = fopen(fn, "a")) == NULL) {
		printf("Error in opening %s result file\n", fn);
		exit(1);
	}
	int i;
	fprintf(fl, "Result of CART classification...\n");
	fprintf(fl, "Accuracy of classification = %lf;\n", a);
	for (i = 0; i < n; i++)
		fprintf(fl, "Object[%d]: %d;\n", i, y[i]);
	fprintf(fl, "\n");
	fclose(fl);
}

int getNumOfClass(const int *y, const int n) {
	int i, j, cur;
	short *v = (short*)malloc(n * sizeof(short));
	memset(v, 0, n * sizeof(short));
	for (i = 0; i < n; i++) {
		while ((v[i]) && (i < n)) i++;
		cur = y[i];
		for (j = i + 1; j < n; j++) {
			if (y[j] == cur)
				v[j] = 1;
		}
	}
	cur = 0;
	for (i = 0; i < n; i++) {
		if (v[i] == 0) cur++;
	}
	free(v);
	return cur;
}



