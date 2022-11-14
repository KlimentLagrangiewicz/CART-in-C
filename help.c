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

void fprintfResult(const int *y, const int n, long long l1, long long l2, const char *fn) {
	FILE *fl;
	if ((fl = fopen(fn, "a")) == NULL) {
		printf("Error in opening %s result file\n", fn);
		exit(1);
	}
	fprintf(fl, "Result of CART classification...\nCreation binary tree time:  %lld number of processor clock cycles;\n"
			    "Time of receiving classes:  %lld number of processor clock cycles;\n"
			    "Time of CART:  %lld number of processor clock cycles;\n", l1, l2, l1 + l2);
	int i = 0;
	while (i < n) {
		fprintf(fl, "Object[%d]: %d;\n", i, y[i]);
		i++;
	}
	fprintf(fl, "\n");
	fclose(fl);
}

void fprintfFullRes(const int *y, const int n, const double a, long long l1, long long l2, const char *fn) {
	FILE *fl;
	if ((fl = fopen(fn, "a")) == NULL) {
		printf("Error in opening %s result file\n", fn);
		exit(1);
	}
	fprintf(fl, "Result of CART classification...\n"
			    "Accuracy of classification = %lf;\n"
			    "Creation binary tree time:  %lld number of processor clock cycles;\n"
			    "Time of receiving classes:  %lld number of processor clock cycles;\n"
			    "Time of CART:  %lld number of processor clock cycles;\n", a, l1, l2, l1 + l2);
	int i = 0;
	while (i < n) {
		fprintf(fl, "Object[%d]: %d;\n", i, y[i]);
		i++;
	}
	fprintf(fl, "\n");
	fclose(fl);
}

int getNumOfClass(const int *y, const int n) {
	int i, j, cur;
	char *v = (char*)malloc(n * sizeof(char));
	memset(v, 0, n * sizeof(char));
	for (i = 0; i < n; i++) {
		while ((v[i]) && (i < n)) i++;
		cur = y[i];
		for (j = i + 1; j < n; j++) {
			if (y[j] == cur)
				v[j] = 1;
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
