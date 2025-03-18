#include <stdio.h>
#include <stdlib.h>
#include <time.h>
	
int main() {

	printf("Adj meg egy N szamot!\n");
	int N;
	scanf_s("%d", &N);
	int* tomb = (int*)malloc(N * sizeof(int));
	
	if (tomb == NULL) {
		printf("Tomb foglalas sikertelen.\n");
		return 1;
	}

	for (int i = 0; i < N; i++) {
		tomb[i] = -1;
	}

	printf("N szam beolvasasa:\n");
	for (int i = N - 1; i >= 0; i--) {
		printf("Add meg az %d. indexu szamot: ", i);
		scanf_s("%d", &tomb[i]);
	}

	printf("A szam tartalma egy sorban:\n");
	for (int i = 0; i < N; i++) {
		printf("%d ", tomb[i]);
	}

	printf("\nAdj meg egy M szamot:\n");
	int M;
	scanf_s("%d", &M);

	printf("Szerepel ez a szam a tombben?\n");
	int szerepel = 0;
	for (int i = 0; i < N; i++) {
		if (tomb[i] == M) {
			szerepel = 1;
			break;
		}
	}

	// Itt nem hasznalok {}, mert csak 1 sor van az if-en belül, azonban 
	// debuggolás szempontjából érdemes lehet használni. De így is mûködik.
	if (szerepel)
		printf("IGEN\n");
	else
		printf("NEM\n");

	printf("Adj meg egy A szamot.\n");
	int A;
	scanf_s("%d", &A);
	int egyenlo = 0, nagyobb = 0, kisebb = 0;
	for (int i = 0; i < N; i++) {
		if (tomb[i] == A)
			egyenlo += 1;
		else if (tomb[i] > A)
			nagyobb += 1;
		else
			kisebb += 1;
	}
	printf("A-nal %d szigoruan nagyobb, %d egyenlo es %d szigoruan kisebb szam van az eredeti tombben.\n", nagyobb, egyenlo, kisebb);

	free(tomb);
	

	printf("\n\n----- KO-PAPIR-OLLO ------\n");
	printf("KO: 1; PAPIR : 2; OLLO: 3\n");
	
	int jatek_on = 1, i = 0;
	srand(time(NULL));
	int ember_nyert = 0, gep_nyert = 0;
	while (jatek_on) {
		printf("Add meg a valasztasod: ");
		int ember;
		scanf_s("%d", &ember);

		if (ember > 3 || ember < 0) {
			printf("Nincs ilyen valasztasi lehetoseg. Probald ujra.\n");
			continue;
		}

		int generalt = rand() % 3 + 1;
		printf("Gep altal generalt: %d\n", generalt);

		// gondoljuk át miért mûködik, ha negatív számot modulozunk az marad negítív
		int m = (ember - generalt + 6) % 3; 

		if (!m) {
			printf("Ugyanaz a valasztas.\n");
			continue;
		}

		if (m == 1) {
			printf("Ember nyert.\n");
			ember_nyert += 1;
		}
		else {
			printf("Gep nyert.\n");
			gep_nyert += 1;
		}

		if (ember_nyert >= 3) {
			printf("Ember nyert 3-szor.");
			jatek_on = 0;
		}
		else if (gep_nyert >= 3) {
			printf("Gep nyert 3-szor.");
			jatek_on = 0 ;
		}
	}
}