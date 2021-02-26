#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define CHECK_TIME_START QueryPerformanceFrequency ((_LARGE_INTEGER*)&freq); QueryPerformanceCounter((_LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a=(float)((float) (end - start)/freq)

#define CMAX 1000000000 
typedef union {
	struct {
		DWORD LowPart;    LONG HighPart;
	};
	struct {
		DWORD LowPart;    LONG HighPart;
	} u;
	LONGLONG QuadPart;
}  _LARGE_INTEGER;

int algorithm1(int *arr, int n);
int algorithm1SubSum(int *arr, int left, int right);
int algorithm2(int *arr, int n);
int algorithm3(int **arr, int n);
int algorithm4(int **arr, int n);
int algorithm5(int **arr, int n);
int max1 = 0;			//1d
int x1, y1, x2, y2;		//1d
int a1, b1, a2, b2;		//2d

int main() {
	__int64 start, freq, end;
	float	resultTime = 0;

	FILE *fp = fopen("HW1_config.txt", "r");
	FILE **input_fp;
	FILE **output_fp;
	int n;
	int num;

	int *al_num;
	char **input;
	char **output;

	fscanf(fp, "%d", &n);

	input_fp = (FILE**)malloc(sizeof(FILE*)*n);
	output_fp = (FILE**)malloc(sizeof(FILE*)*n);

	al_num = (int*)malloc(sizeof(int)*n);
	input = (char**)malloc(sizeof(char*)*n);
	for (int i = 0; i < n; i++) {
		input[i] = (char*)malloc(sizeof(char) * 32);
	}
	output = (char**)malloc(sizeof(char*)*n);
	for (int i = 0; i < n; i++) {
		output[i] = (char*)malloc(sizeof(char) * 32);
	}

	for (int i = 0; i < n; i++) {
		fscanf(fp, "%d %s %s", &al_num[i], input[i], output[i]);
	}

	for (int i = 0; i < n; i++) {
		int maxSum;
		input_fp[i] = fopen(input[i], "rb");
		output_fp[i] = fopen(output[i], "wb");
		fread(&num, sizeof(int), 1, input_fp[i]);
		resultTime = 0;
		switch (al_num[i]) {
		case 1: {
			int *data = (int*)malloc(sizeof(int)*num);
			fread(data, sizeof(int), num, input_fp[i]);
			CHECK_TIME_START;
			maxSum = algorithm1(data, num);
			CHECK_TIME_END(resultTime);
			printf("%d %d %d\n", maxSum, x1, y1);	//test
			fwrite(&maxSum, sizeof(int), 1, output_fp[i]);
			fwrite(&x1, sizeof(int), 1, output_fp[i]);
			fwrite(&y1, sizeof(int), 1, output_fp[i]);
			free(data);
			break;
		}
		case 2: {
			int *data = (int*)malloc(sizeof(int)*num);
			fread(data, sizeof(int), num, input_fp[i]);
			CHECK_TIME_START;
			maxSum = algorithm2(data, num);
			CHECK_TIME_END(resultTime);
			printf("%d %d %d\n", maxSum, x1, y1);	//test
			fwrite(&maxSum, sizeof(int), 1, output_fp[i]);
			fwrite(&x1, sizeof(int), 1, output_fp[i]);
			fwrite(&y1, sizeof(int), 1, output_fp[i]);
			free(data);
			break;
		}
		case 3: {
			int **data = (int**)malloc(sizeof(int*)*num);
			for (int k = 0; k < num; k++) {
				data[k] = (int*)malloc(sizeof(int)*num);
				fread(data[k], sizeof(int), num, input_fp[i]);
			}
			CHECK_TIME_START;
			maxSum = algorithm3(data, num);
			CHECK_TIME_END(resultTime);
			printf("%d %d %d %d %d\n", maxSum, b1, a1, b2, a2);	//test
			fwrite(&maxSum, sizeof(int), 1, output_fp[i]);
			fwrite(&b1, sizeof(int), 1, output_fp[i]);
			fwrite(&a1, sizeof(int), 1, output_fp[i]);
			fwrite(&b2, sizeof(int), 1, output_fp[i]);
			fwrite(&a2, sizeof(int), 1, output_fp[i]);
			for (int i = 0; i < num; i++)
				free(data[i]);
			free(data);
			break;
		}
		case 4: {
			
			int **data = (int**)malloc(sizeof(int*)*num);
			for (int k = 0; k < num; k++) {
				data[k] = (int*)malloc(sizeof(int)*num);
				fread(data[k], sizeof(int), num, input_fp[i]);
			}
			CHECK_TIME_START;
			maxSum = algorithm4(data, num);
			CHECK_TIME_END(resultTime);
			printf("%d %d %d %d %d\n", maxSum, b1, a1, b2, a2);	//test
			fwrite(&maxSum, sizeof(int), 1, output_fp[i]);
			fwrite(&b1, sizeof(int), 1, output_fp[i]);
			fwrite(&a1, sizeof(int), 1, output_fp[i]);
			fwrite(&b2, sizeof(int), 1, output_fp[i]);
			fwrite(&a2, sizeof(int), 1, output_fp[i]);
			for (int i = 0; i < num; i++)
				free(data[i]);
			free(data);
			break;
		}
		case 5: {
			int **data = (int**)malloc(sizeof(int*)*num);
			for (int k = 0; k < num; k++) {
				data[k] = (int*)malloc(sizeof(int)*num);
				fread(data[k], sizeof(int), num, input_fp[i]);
			}
			CHECK_TIME_START;
			maxSum = algorithm5(data, num);
			CHECK_TIME_END(resultTime);
			printf("%d %d %d %d %d\n", maxSum, b1, a1, b2, a2);	//test
			fwrite(&maxSum, sizeof(int), 1, output_fp[i]);
			fwrite(&b1, sizeof(int), 1, output_fp[i]);
			fwrite(&a1, sizeof(int), 1, output_fp[i]);
			fwrite(&b2, sizeof(int), 1, output_fp[i]);
			fwrite(&a2, sizeof(int), 1, output_fp[i]);
			for (int i = 0; i < num; i++)
				free(data[i]);
			free(data);
			break;
		}
		default:
			break;
		}
		printf("n:%d -> %f(ms).. \n", num, resultTime*1000); //test
		fclose(input_fp[i]);
		fclose(output_fp[i]);
	}


	free(al_num);
	for (int i = 0; i < n; i++)
		free(input[i]);
	free(input);
	for (int i = 0; i < n; i++)
		free(output[i]);
	free(output);
	fclose(fp);
	return 0;
}

int algorithm1(int *arr, int n) {
	max1 = 0;
	int maxsum;
	maxsum = algorithm1SubSum(arr, 0, n - 1);
	if (maxsum == 0) {
		maxsum = arr[0];
		x1 = 0;
		y1 = 0;
		for (int i = 0; i < n; i++) {
			if (arr[i] > maxsum) {
				maxsum = arr[i];
				x1 = y1 = i;
			}
		}
	}

	return maxsum;
}
int algorithm1SubSum(int *arr, int left, int right) {
	int MaxLeftSum, MaxRightSum;
	int MaxLeftBorderSum, MaxRightBorderSum;
	int LeftBorderSum, RightBorderSum;
	int center, i;
	int borderX, borderY;


	if (left == right)
		if (arr[left] > 0)
			return arr[left];
		else
			return 0;

	center = (left + right) / 2;
	MaxLeftSum = algorithm1SubSum(arr, left, center);
	MaxRightSum = algorithm1SubSum(arr, center + 1, right);

	MaxLeftBorderSum = 0;
	LeftBorderSum = 0;
	for (i = center; i >= left; i--) {
		LeftBorderSum += arr[i];
		if (LeftBorderSum > MaxLeftBorderSum) {
			MaxLeftBorderSum = LeftBorderSum;
			borderX = i;
		}
	}

	MaxRightBorderSum = 0;
	RightBorderSum = 0;
	for (i = center + 1; i <= right; i++) {
		RightBorderSum += arr[i];
		if (RightBorderSum > MaxRightBorderSum) {
			MaxRightBorderSum = RightBorderSum;
			borderY = i;
		}
	}

	if (max1 < MaxLeftSum) {
		max1 = MaxLeftSum;
		x1 = left;
		y1 = center;
	}
	if (max1 < MaxRightSum) {
		max1 = MaxRightSum;
		x1 = center + 1;
		y1 = right;
	}
	if (max1 < MaxLeftBorderSum + MaxRightBorderSum) {
		max1 = MaxLeftBorderSum + MaxRightBorderSum;
		x1 = borderX;
		y1 = borderY;
	}

	return max1;
}
int algorithm2(int *arr, int n) {
	int sum;
	int start = 0;
	sum = max1 = 0;
	x1 = y1 = 0;
	for (int i = 0; i < n; i++) {
		sum += arr[i];

		if (sum < 0) {
			sum = 0;
			start = i + 1;
		}
		else if (sum > max1) {
			max1 = sum;
			x1 = start;
			y1 = i;
		}
	}

	if (max1 == 0) {
		max1 = arr[0];
		x1 = 0;
		y1 = 0;
		for (int i = 0; i < n; i++) {
			if (arr[i] > max1) {
				max1 = arr[i];
				x1 = y1 = i;
			}
		}
	}

	return max1;
}
int algorithm3(int **arr, int n) {
	int max = 0;
	int sum = 0;
	int **sat;
	int value;
	sat = (int**)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++) {
		sat[i] = (int*)malloc(sizeof(int)*n);
	}
	for (int i = 0; i < n; i++) {
		value = 0;
		for (int j = 0; j < n; j++) {
			value += arr[i][j];
			if (i > 0) {
				sat[i][j] = sat[i - 1][j] + value;
			}
			else {
				sat[i][j] = value;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			for (int k = 0; k < n; k++) {
				for (int l = k; l < n; l++) {
					if (k > 0 && i > 0) {
						sum = sat[l][j] - sat[k - 1][j] - sat[l][i - 1] + sat[k - 1][i - 1];
					}
					else if (k > 0) {
						sum = sat[l][j] - sat[k - 1][j];
					}
					else if (i > 0) {
						sum = sat[l][j] - sat[l][i - 1];
					}
					else {
						sum = sat[l][j];
					}
					if (sum > max) {
						max = sum;
						b1 = k;
						a1 = i;
						b2 = l;
						a2 = j;
					}
				}
			}
		}
	}

	if (max == 0) {
		max = arr[0][0];
		a1 = 0;
		b1 = 0;
		a2 = 0;
		b2 = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (arr[i][j] > max) {
					max = arr[i][j];
					a1 = a2 = j;
					b1 = b2 = i;
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		free(sat[i]);
	}
	free(sat);

	return max;
}
int algorithm4(int **arr, int n) {
	int max = 0;
	int *temp;
	int sum;
	temp = (int*)malloc(sizeof(int)*n);

	for (int i = 0; i < n; i++) {
		memset(temp, 0, sizeof(int)*n);
		for (int j = i; j < n; j++) {
			for (int k = 0; k < n; k++) {
				temp[k] += arr[k][j];
			}
			sum = algorithm1(temp, n);

			if (sum > max) {
				max = sum;
				b2 = y1;
				b1 = x1;
				a1 = i;
				a2 = j;
			}
		}
	}

	if (max == 0) {
		max = arr[0][0];
		a1 = 0;
		b1 = 0;
		a2 = 0;
		b2 = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (arr[i][j] > max) {
					max = arr[i][j];
					a1 = a2 = j;
					b1 = b2 = i;
				}
			}
		}
	}
	free(temp);
	return max;
}
int algorithm5(int **arr, int n) {
	int max = 0;
	int *temp;
	int sum;
	temp = (int*)malloc(sizeof(int)*n);

	for (int i = 0; i < n; i++) {
		memset(temp, 0, sizeof(int)*n);
		for (int j = i; j < n; j++) {
			for (int k = 0; k < n; k++) {
				temp[k] += arr[k][j];
			}
			sum = algorithm2(temp, n);

			if (sum > max) {
				max = sum;
				b2 = y1;
				b1 = x1;
				a1 = i;
				a2 = j;
			}
		}
	}

	if (max == 0) {
		max = arr[0][0];
		a1 = 0;
		b1 = 0;
		a2 = 0;
		b2 = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (arr[i][j] > max) {
					max = arr[i][j];
					a1 = a2 = j;
					b1 = b2 = i;
				}
			}
		}
	}
	free(temp);
	return max;
}