#include <stdio.h>
#include <stdbool.h>
#define MAX_TERMS 10

typedef struct {
	int row;
	int col;
	int value;
}element;

typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;
	int cols;
	int terms;
}SparseMatrix;

void transpose_matrix(SparseMatrix *m1, SparseMatrix *m2) {
	m2->rows = m1->rows;
	m2->cols = m1->cols;
	m2->terms = m1->terms;
	for (int i = 0; i < m1->terms; i++) { //col�� row�� �ٲ��ֱ�
		m2->data[i].col = m1->data[i].row;
		m2->data[i].row = m1->data[i].col;
		m2->data[i].value = m1->data[i].value;
	}
}

void print_matrix(SparseMatrix m) { //��� 1
	bool isZero; //0�� ����Ʈ �ؾ��ϴ��� �Ǵ��ϴ� bool ����

	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.cols; j++) {
			isZero = true;
			for (int k = 0; k < m.terms; k++) { //row, col ������������ �̸� �����Ѵٸ� ���� �Ź� �����͸� ��� Ȯ���� �ʿ� ����
				if (i == m.data[k].row && j == m.data[k].col) {
					isZero = false; //�ش� ��ġ�� value���� �ִٴ� ���̹Ƿ� isZero�� false��
					printf("%d ", m.data[k].value);
					break;
				}
			}
			if (isZero) //������ �� �� isZero�� true��� 0�� ����Ʈ 
				printf("0 ");
		}
		printf("\n");
	}
	printf("\n");
}

void print_matrix_2(SparseMatrix m) { //��� 2
	//SparseMatrix ũ���� 2���� �迭�� ���� �Ҵ�
	int** temp = (int**)malloc(sizeof(int*) * m.rows);
	for (int i = 0; i < m.rows; i++)
		temp[i] = (int*)malloc(sizeof(int) * m.cols);

	for (int i = 0; i < m.rows; i++) { //2���� �迭�� ��� ���� 0���� �ʱ�ȭ
		for (int j = 0; j < m.cols; j++)
			temp[i][j] = 0;
	}
	for (int i = 0; i < m.terms; i++) //SparseMatrix�� value���� 2���� �迭�� ����
		temp[m.data[i].row][m.data[i].col] = m.data[i].value;

	for (int i = 0; i < m.rows; i++) { //���
		for (int j = 0; j < m.cols; j++)
			printf("%d ", temp[i][j]);
		printf("\n");
	}
	printf("\n");
}

int main() {
	SparseMatrix B = { {{0,3,7},{1,0,9},{1,5,8},{3,0,6},{3,1,5},{4,5,1},{5,2,2}},6,6,7 };
	SparseMatrix B_t;
	
	transpose_matrix(&B, &B_t); //B_t �ʱ�ȭ ���� �ʾƼ� �����ͷ� �ȹ����� ���� ����
	print_matrix(B);
	print_matrix_2(B_t);
}