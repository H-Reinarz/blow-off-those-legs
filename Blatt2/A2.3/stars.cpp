// ===== Aufgabe 2.3 =====
#include <stdio.h>

int main(void) {
	
	int n = 0;
	
	// User Input
	scanf("%d",&n);
	
	// Part a)
	for (int i = 0; i < n; i++){
		printf("*");
	}
	
	printf("\n");
	
	// Part b)
	for (int i = 0; i < n; i++){
		
		for (int j = 0; j <= i; j++){
			printf("*");
		}
		printf("\n");
	}
	
	// Part c)
	int stop = 2*n-1;
	int space = 0;
	
	for (int i = 1; i <= stop; i += 2){
		space = (stop-i)/2;
		for (int j = 0; j < space; j++){
			printf(" ");
		}
		for (int x = 0; x < i; x++){
			printf("*");
		}
		printf("\n");
	}
	
	getchar();
	return 0;
}

