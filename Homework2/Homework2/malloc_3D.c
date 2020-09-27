#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double*** mem_alloc_3D_double(int x, int y, int z) {
	double*** matrix = (double***)malloc(sizeof(double**) * x); //1���� �Ҵ�
	for (int i = 0; i < x; i++) {
		matrix[i] = (double**)malloc(sizeof(double*) * y); //2���� �Ҵ�
		for (int j = 0; j < y; j++) {
			matrix[i][j] = (double*)malloc(sizeof(double) * z); //3���� �Ҵ�
		}
	}
	return matrix;
}

void numbering(double*** matrix, int x, int y, int z) {
	srand(time(NULL));
	double start_num = (rand() % 10) + 10; //10~19 ������ ���� ����

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < z; k++) { //ó�� ������ ���� �ϳ��� �����ϸ� ����
				matrix[i][j][k] = start_num;
				start_num++;
			}
		}
	}
}

void addition_3D(double*** m1, double*** m2, int x, int y, int z) { //���ؼ� �ٷ� ����Ʈ �ϴ� �Լ�
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < z; k++)
				printf("%.2f ", m1[i][j][k] + m2[i][j][k]);
			printf("\n");
		}
		printf("\n");
	}
	printf("\n");
}

void mem_dealloc_3D_double(double*** m) {
	if (m != NULL) {
		free(m[0][0]); //3���� ����
		free(m[0]); //2���� ����
		free(m); //1���� ����
		m = NULL;
	}
}

int main() {
	double*** A = mem_alloc_3D_double(2, 3, 4);
	double*** B = mem_alloc_3D_double(2, 3, 4);

	numbering(A, 2, 3, 4);
	numbering(B, 2, 3, 4);

	addition_3D(A, B, 2, 3, 4);

	mem_dealloc_3D_double(A);
	mem_dealloc_3D_double(B);
}