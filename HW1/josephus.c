/* The Josephus Problem */
/* author: Jonathan Lim */
/* created: 9/29/17     */

#include <stdio.h>
#include <stdbool.h>

bool killedCheck(int size, int *ppl) {
	int aliveCount = 0;
	for (int i = 0; i < size; i++) {
		aliveCount += ppl[i];
	}
	return aliveCount == 1;
}
int whosAlive(int size, int *ppl) {
	for (int i = 0; i < size; i++) {
		if (ppl[i]) {
			return i;
		}
	}
	return size+=1;
} 
void calculation(int size) {
	int ppl[size];
	for (int i = 0; i < size; i++) {
		ppl[i] = 1;
	}
	bool killed = true;
	int count = 0;
	while (!killedCheck(size, ppl)) {
		if (ppl[count%size]) {
			if(!killed) {
				ppl[count%size] = 0;
			}
			if (killed) {
				killed = false;
			} else {
				killed = true;
			}
		}
		count++;
	}
	printf("The safe spot is %d.\n", whosAlive(size, ppl)+1);
}

int main(void) {
	int size;
	printf("Welcome to the Josephus Problem.\nHow many people are in the circle? ");
	scanf("%d", &size);
	calculation(size);
	return 0;
}

/* EOF */
