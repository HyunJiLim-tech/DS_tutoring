#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define INPUT 1001
#define BUCKETS 64 // 24-bit ���� 4 segments�� �����ϱ� 1���� segment�� 6-bit
#define DIGITS 4

int generate_rand() { // 110101101 ���� ������ ���¸� �ٷ� �������� �ٲ�
	int num = 0, mul = 1;

	for (int i = 0; i < 24; i++) {
		int rd = rand() % 2; // 0 or 1
		num += (rd * mul);
		mul *= 2;
	}
	return num;
}

void radix_sort(int A[], int n) {
	int C[BUCKETS], B[INPUT] = { 0, };
	int factor = 1;
	int i;

	for (int d = 0; d < DIGITS; d++) {
		//counting sort
		memset(C, 0, sizeof(int) * BUCKETS); //�迭 C�� 0���� �ʱ�ȭ
		for (i = 0; i < n; i++)
			C[(A[i] / factor) % BUCKETS] += 1;
		for (i = 1; i < BUCKETS; i++)
			C[i] = C[i] + C[i - 1];
		for (i = n - 1; i > 0; i--) {
			B[C[(A[i] / factor) % BUCKETS]] = A[i];
			C[(A[i] / factor) % BUCKETS] -= 1;
		}

		for (i = 1; i < n; i++)
			A[i] = B[i];
		factor *= BUCKETS;
	}
}

bool check_sort(int A[], int n) { //����� ���ĵȰ��� Ȯ��
	for (int i = 2; i < n; i++) {
		if (A[i] < A[i - 1])
			return false;
	}
	return true;
}

int main() {
	srand((unsigned)time(NULL));
	int A[INPUT];
	
	//��� 1 : ���������� 32767 ���� ū �Ҽ��� ���Ե��� �ʰ�, ����� ���� �ռ��� ���ַ� ���� ����� ���ɼ��� ����
	for (int i = 1; i < INPUT; i++) {
		int front = rand() + 1; // 1 ~ 2^15
		int back = rand() % 512 + 1; // 1 ~ 2^9
		int num = front * back - 1; // 1 ~ 2^24-1

		A[i] = num;
	}

	//��� 2 : �ش� ���� ��� ���� ������ �� �ְ�, ���⵵ ������ ���� �̷��Ա���?
	for (int i = 1; i < INPUT; i++) {
		A[i] = generate_rand();
	}
	
	radix_sort(A, INPUT);

	if (check_sort(A, INPUT)) { //����� ���ĵƴٸ� ó�� 10���� ������ 10�� �����͸� ���
		for (int i = 1; i <= 10; i++)
			printf("%d\n", A[i]);
		printf("...\n");
		for (int i = 991; i <= 1000; i++)
			printf("%d\n", A[i]);
	}
	else
		printf("Wrong\n");
}