#include "help.h"

void fscanfTrainData(double *x, int *y, const int n, const int m, const char *fn) {
	FILE *fl = fopen(fn, "r");
	if (!fl) {
		printf("Error in opening %s file...\n", fn);
		exit(1);
	}
	int i, j, k;
	for (i = 0; i < n && !feof(fl); i++) {
		k = i * m;
		for (j = 0; j < m && !feof(fl); j++) {
			if (fscanf(fl, "%lf", x + k + j) == 0) {}
		}
		if (!feof(fl)) {
			if (fscanf(fl, "%d", y + i) == 0) {}
		}
	}
	fclose(fl);
}

void fscanfTestData(double *x, const int n, const char *fn) {
	FILE *fl = fopen(fn, "r");
	if (!fl) {
		printf("Error in opening %s file...\n", fn);
		exit(1);
	}
	int i;
	for (i = 0; i < n && !feof(fl); i++) {
		if (fscanf(fl, "%lf", x + i) == 0) {}
	}
	fclose(fl);
}

void fscanfIdealSpliting(int *id, const int n, const char *fn) {
	FILE *fl = fopen(fn, "r");
	if (!fl) {
		printf("Error in opening %s file...\n", fn);
		exit(1);
	}
	int i;
	for (i = 0; i < n && !feof(fl); i++) {
		if (fscanf(fl, "%d", id + i) == 0) {}
	}
	fclose(fl);
}

double calcAccuracy(const int *x, const int *y, const int n) {
	int i = 0, j = 0;
	while (i++ < n) if (*(x++) == *(y++)) j++;
	return (double)j / (double)n;
}

void fprintfResult(const int *y, const int n, const double t1, const double t2, const char *fn) {
	FILE *fl = fopen(fn, "a");
	if (!fl) {
		printf("Error in opening %s result file\n", fn);
		exit(1);
	}
	fprintf(fl, "Result of CART classification...\n"
		"Creation binary tree time:  %lf s.;\n"
		"Time of receiving classes:  %lf s.;\n"
		"Time of CART:  %lf s.;\n", t1, t2, t1 + t2);
	int i = 0;
	while (i++ < n) fprintf(fl, "Object[%d]: %d;\n", i, *(y++));
	fputc('\n', fl);
	fclose(fl);
}

void fprintfFullRes(const int *y, const int n, const double a, const double t1, const double t2, const char *fn) {
	FILE *fl = fopen(fn, "a");
	if (!fl) {
		printf("Error in opening %s result file\n", fn);
		exit(1);
	}
	fprintf(fl, "Result of CART classification...\n"
		"Accuracy of classification = %lf;\n"
		"Creation binary tree time:  %lf s.;\n"
		"Time of receiving classes:  %lf s.;\n"
		"Time of CART:  %lf s.;\n", a, t1, t2, t1 + t2);
	int i = 0;
	while (i++ < n) fprintf(fl, "Object[%d]: %d;\n", i, *(y++));
	fputc('\n', fl);
	fclose(fl);
}

int getNumOfClass(const int* const y, const int n) {
	int i, j, cur;
	char *v = (char*)malloc(n * sizeof(char));
	memset(v, 0, n * sizeof(char));
	for (i = 0; i < n; i++) {
		while (i < n && v[i]) i++;
		cur = y[i];
		for (j = i + 1; j < n; j++) {
			if (y[j] == cur) v[j] = 1;
		}
	}
	i = cur = 0;
	while (i < n) {
		if (v[i] == 0) cur++;
		i++;
	}
	free(v);
	return cur;
}
