#include <stdio.h>

int main (void){
	int n = 0;
	
	// User Input
	printf("Bitte Zahl n eingeben: ");
	scanf("%d",&n);
	
	// Part a)
	printf("Ganzzahlige Teiler von n: ");
	for (int i = 1; i <= n; i++){
		if (n % i == 0){
			printf("%d  ",i);
		}
	}
	printf("\n");
	
	// Part b)
	for (int i = 1; i < n; i++){
		
		if (i > 1 && n % i == 0){
			printf("Die Zahl %d ist keine Primzahl.", n);
			break;
		}
		
		if (i == n-1) {
			printf("Die Zahl %d ist eine Primzahl.", n);
		}
	}

	
	printf("\n");
	
	// Part c)
	
	
	getchar();
	return 0;
}
