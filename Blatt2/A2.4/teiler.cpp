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
	int nPrime = n;
	
	printf("Primfaktorzerlegung: ");
	// Count through all Numbers smaller than n
	for (int i = 2; i <= n; i++){
		
		// Check if prime number like in part b)
		for (int j = 1; j < i; j++){
			
			// if number i is no prime number -> break!
			if (j > 1 && i % j == 0){
				break;
			}
			
			// if number i is a prime number
			if (j == i-1) {
				// while nPrime is divisible by prime number(i) without remainder -> divide!
				while (nPrime % i == 0){
					nPrime = nPrime / i;
					printf("%d  ",i);
				}
			}
		}
		// If nPrime == 1 -> break!
		if (nPrime == 1){
			break;		
		}
	}
	
	getchar();
	return 0;
}
