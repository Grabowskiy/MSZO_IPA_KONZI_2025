#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct vec {
	double x;
	double y;
};

int main() {
	// Struct példa
	/*
	int n;
	scanf_s("%d", &n);
	struct vec* vectorom = (struct vec*)malloc(sizeof(struct vec) * n);
	struct vec v1;
	struct vec* vec_ptr;
	v1.x = 20.2012;
	v1.y = 230310.01210;

	(*vec_ptr).x = 30.1;
	vec_ptr->y = 30.1;

	free(vectorom)
	
	*/

	// Ko Papir Ollo Game
	printf("KO PAPIR OLLO\n");
	printf("ko:1, papir:2, ollo:3\n");
	srand(time(NULL));

	int jatek_on = 1;
	int ember_nyert = 0, gep_nyert = 0;
	while (jatek_on) {
		printf("Adj meg egy szamot.\n");
		int ember = -1;
		scanf_s("%d", &ember);
		if (ember < 1 || ember > 3) {
			printf("Nincs ilyen lehetoseg.");
			continue;
		}

		int generalt = rand() % 3 + 1;

		printf("Ember valsztott: %d\n", ember);
		printf("Generalt: %d\n", generalt);

		int m = (ember - generalt + 3) % 3;
		if (m == 0) {
			printf("Ugyanaz a valasztas.\n");
		}
		else if (m == 1) {
			printf("Ember nyert.\n");
			ember_nyert += 1;
		}
		else {
			printf("Gep nyert.\n");
			gep_nyert += 1;
		}

		if (ember_nyert >= 3) {
			printf("--- !EMBER NYERT! ---");
			jatek_on = 0;
		}

		if (gep_nyert >= 3) {
			printf("--- !GEP NYERT! ---");
			jatek_on = 0;
		}
	}

	return 0;
}