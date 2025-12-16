#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ARR_SIZE 14282

void padNumberWithZeros(int num, int desiredLength, char *buffer) {
	char temp[20];
	sprintf(temp, "%d", num);
	int len = strlen(temp);
	int zeros = desiredLength - len;
	for (int i = 0; i < zeros; i++) {
		buffer[i] = '0';
	}
	strcpy(buffer + zeros, temp);
	buffer[desiredLength] = '\0';
}

int rnd(int min, int max) {
	return rand() % (max - min) + min;
}

int main() {
	printf("Calculating...\n");

	char arr[MAX_ARR_SIZE][6];
	int arrCount = 0;

	char numStr[6];

	for (int i = 0; i < 100000; i++) {
		padNumberWithZeros(i, 5, numStr);

		int sum = 0;
		for (int j = 0; j < 5; j++) {
			sum += numStr[j] - '0';
		}

		if (sum % 7 == 0) {
			if (arrCount < MAX_ARR_SIZE) {
				strcpy(arr[arrCount++], numStr);
			}
		}

		if (i % 1000 == 0) {
			printf("Calculating...\n %d%%\n", (i * 100) / 100000);
		}
	}

	srand((unsigned int)time(NULL));

	char one[4], two[3], three[6], four[6];

	padNumberWithZeros(rnd(1, 366), 3, one);
	padNumberWithZeros(rnd(95, 99), 2, two);

	if (arrCount == 0) {
		printf("No valid serial parts found.\n");
		return 1;
	}

	strcpy(three, arr[rnd(0, arrCount)]);
	strcpy(four, arr[rnd(0, arrCount)]);

	char key[50];
	sprintf(key, "%s%s-OEM-00%s-%s", one, two, three, four);
	printf("%s\n", key);

	return 0;
}
