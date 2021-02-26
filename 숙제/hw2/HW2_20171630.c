#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void score(char* strX, char* strY, int m, int n, int s, int f, int p, FILE* fp);
int max3(int a, int b, int c);

int cnt = 0;
int cntA = 0;
int cntB = 0;

int main() {

	char testcase[50];
	char* strX;
	char* strY;
	int s, f, p;
	int X, Y;
	int res;

	FILE *fp1 = fopen("input.txt", "rt");
	if (fp1 == NULL) {
		printf("Input file open error!");
		exit(1);
	}
	fscanf(fp1, "%s", testcase);
	fscanf(fp1, "%d %d %d", &s, &f, &p);

	FILE *fp2 = fopen(testcase, "rb");
	if (fp2 == NULL) {
		printf("Binary file open error!");
		exit(1);
	}
	fread(&X, sizeof(X), 1, fp2);
	fread(&Y, sizeof(Y), 1, fp2);

	strX = (char*)malloc(sizeof(char)*(X + 1));
	strY = (char*)malloc(sizeof(char)*(Y + 1));

	strX[X] = 0;
	strY[Y] = 0;

	fread(strX, sizeof(char), X, fp2);
	fread(strY, sizeof(char), Y, fp2);

	FILE *fp3 = fopen("output.txt", "wt");
	if (fp3 == NULL) {
		printf("Output file open error!");
		exit(1);
	}
	score(strX, strY, X, Y, s, f, p, fp3);

	free(strX);
	free(strY);

	res = fclose(fp1);
	if (res != 0) {
		printf("input file close error!");
		exit(1);
	}
	res = fclose(fp2);
	if (res != 0) {
		printf("Binary file close error!");
		exit(1);
	}
	res = fclose(fp3);
	if (res != 0) {
		printf("Output file close error!");
		exit(1);
	}

	return 0;
}

void score(char* strX, char* strY, int m, int n, int s, int f, int p, FILE* fp) {
	int match = 0;
	int i = 0, j = 0;
	int a = 0, b = 0, c = 0;
	int flag = 0;
	int len = 0;
	int** S = (int**)malloc(sizeof(int*)*(m + 1));
	for (i = 0; i < m + 1; i++) {
		S[i] = (int*)malloc(sizeof(int)*(n + 1));
	}

	int** P = (int**)malloc(sizeof(int*)*(m + 1));
	for (i = 0; i < m + 1; i++) {
		P[i] = (int*)malloc(sizeof(int)*(n + 1));
	}



	for (i = 1; i <= m; i++) {
		S[i][0] = (-1) * p*i;
		P[i][0] = 3;
	}
	for (i = 0; i <= n; i++) {
		S[0][i] = (-1) * p*i;
		P[0][i] = 2;
	}

	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (strX[i - 1] == strY[j - 1])
				match = s;
			else
				match = (-1)*f;

			a = S[i - 1][j - 1] + match;
			b = S[i][j - 1] - p;
			c = S[i - 1][j] - p;
			flag = max3(a, b, c);
			if (flag == 1) {
				S[i][j] = a;
				P[i][j] = 1;
			}
			else if (flag == 2) {
				S[i][j] = b;
				P[i][j] = 2;
			}
			else if (flag == 3) {
				S[i][j] = c;
				P[i][j] = 3;
			}
		}
	}

	i = m;
	j = n;
	while (1) {
		if (P[i][j] == 1) {
			i--;
			j--;
		}
		else if (P[i][j] == 2) {
			j--;
			cntA++;
		}
		else {
			i--;
			cntB++;
		}
		cnt++;
		if (i == 0 && j == 0) break;
	}
	len = cnt;
	i = m;
	j = n;
	a = 0;
	b = 0;
	int* A = (int*)malloc(sizeof(int)*cnt);
	int* B = (int*)malloc(sizeof(int)*cnt);
	while (len != 0)
	{
		if (P[i][j] == 1) {
			i--;
			j--;
		}
		else if (P[i][j] == 2) {
			A[cntA - 1 - a] = len;
			a++;
			j--;
		}
		else {
			B[cntB - 1 - b] = len;
			b++;
			i--;

		}
		len--;
	}
	fprintf(fp, "%d\n", S[m][n]);
	fprintf(fp, "%d\n", cnt);
	fprintf(fp, "%d\n", cntA);
	for (int i = 0; i < cntA; i++) {
		fprintf(fp, "%d\n", A[i]);
	}
	fprintf(fp, "%d\n", cntB);
	for (int i = 0; i < cntB; i++) {
		fprintf(fp, "%d\n", B[i]);
	}

	for (i = 0; i < m + 1; i++) {
		free(S[i]);
		free(P[i]);
	}
	free(S);
	free(P);
	free(A);
	free(B);
}

int max3(int a, int b, int c) {
	if (a >= b) {
		if (a >= c)
			return 1;
		else
			return 3;
	}
	else {
		if (b > c)
			return 2;
		else
			return 3;
	}

}