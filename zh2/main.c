#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// 1. Eredmeny struct
struct eredmeny {
    int eltoltott_ido;
    int szerzett_pont;
    char* neptun;
    int puskazott;
};

// 3. Kiir fuggveny
void kiir(struct eredmeny er) {
    printf("Eltoltott ido: %d, szerzett pont: %d, neptun: %s, puskazott: %d\n",
        er.eltoltott_ido, er.szerzett_pont, er.neptun, er.puskazott);
}

// 4. Pont/perc hatekonysag
float hatekonysag(struct eredmeny er) {
    float out = (float)er.szerzett_pont / (float)er.eltoltott_ido;
    return out;
}

// 5. Kiir egesz tombre
void tomb_kiir(struct eredmeny* tomb, int db) {
    for (int i = 0; i < db; i++) {
        kiir(tomb[i]);
    }
}

// 6. Legugyesebb diak
char* ugyes(struct eredmeny* tomb, int db) {
    int max_pont = 0;
    char* neptun_out = "";
    for (int i = 0; i < db; i++) {
        if (!tomb[i].puskazott && tomb[i].szerzett_pont > max_pont){
            neptun_out = tomb[i].neptun;      
            max_pont = tomb[i].szerzett_pont;
        }
        else if (!tomb[i].puskazott && tomb[i].szerzett_pont == max_pont) {
            if (strcmp(neptun_out, tomb[i].neptun) > 0) {
                neptun_out = tomb[i].neptun;
            }
        }
    }

    return neptun_out;
}

// 7. Ha puskazott, pontszam 0-ra allitasa
void nullaz_puskazo(struct eredmeny* e) {
    if (e->puskazott) {
        e->szerzett_pont = 0;
    }
}

// 8. Adott neptun kod pontszama (0, ha nincs)
int pont_neptun(struct eredmeny* tomb, int db, char* neptun) {
    for (int i = 0; i < db; i++) {
        if (strcmp(tomb[i].neptun, neptun) == 0) {
            return tomb[i].szerzett_pont;
        }
    }
    return 0;
}

// 9. Memoria felszabaditasa
void felszabadit(struct eredmeny* tomb, int db) {
    for (int i = 0; i < db; i++) {
        free(tomb[i].neptun);
    }
    free(tomb);
}

// 10. Fajlbol neptun kodok beolvasasa es pontok kiirasa
void file_neptun_pont(char* fname, struct eredmeny* tomb, int db) {
    FILE* fp = fopen(fname, "r");
    if (!fp) {
        printf("Nem sikerult megnyitni: %s\n", fname);
        return;
    }
    char sor[64];
    while (fgets(sor, sizeof(sor), fp)) {
        sor[6] = '\0';
        printf("---------%s-----------", sor);
        int p = pont_neptun(tomb, db, sor);
        printf("Neptun %s pont: %d\n", sor, p);
    }
    fclose(fp);
}

// 11. Max es atmeno pont beolvasasa, bukott es maxolt diakok szamolasa
void bukott_maxolo_szamolas(char* fname, struct eredmeny* tomb, int db) {
    FILE* fp = fopen(fname, "r");
    if (!fp) {
        printf("Nem sikerult megnyitni: %s\n", fname);
        return;
    }
    int max_pont, atmeno;
    if (fscanf(fp, "%d %d", &max_pont, &atmeno) != 2) {
        printf("Hibas formatum: %s\n", fname);
        fclose(fp);
        return;
    }
    fclose(fp);

    int bukott = 0, maxolt = 0;
    for (int i = 0; i < db; i++) {
        int p = tomb[i].szerzett_pont;
        if (p < atmeno) bukott++;
        if (p >= max_pont) maxolt++;
    }
    printf("Bukott diakok: %d\n", bukott);
    printf("Maxolt (vagy tobbet ert el): %d\n", maxolt);
}

// 12. Puskazassal korrigalt neptun/pont parok fajlba
void puskazo_korrigal(char* fname, struct eredmeny* tomb, int db) {
    FILE* fp = fopen(fname, "w");
    if (!fp) {
        printf("Nem sikerult megnyitni irasra: %s\n", fname);
        return;
    }
    for (int i = 0; i < db; i++) {
        int p = tomb[i].puskazott ? 0 : tomb[i].szerzett_pont;
        fprintf(fp, "%s;%d\n", tomb[i].neptun, p);
    }
    fclose(fp);
    printf("Korrigalt eredmenyek kiirva: %s\n", fname);
}

int main() {
    int db = 5;
    struct eredmeny* tomb = (struct eredmeny*)malloc(db * sizeof(struct eredmeny));
    
    struct eredmeny er1 = { 90, 35, "ABCDEF", 1 };
    struct eredmeny er2 = { 64, 15, "ABDTDL", 0 };
    struct eredmeny er3 = { 80, 100, "AF1GE5", 0 };
    struct eredmeny er4 = { 78, 0, "ASF3GT", 0 };
    struct eredmeny er5 = { 46, 56, "B464GE", 0 };
    tomb[0] = er1;
    tomb[1] = er2;
    tomb[2] = er3;
    tomb[3] = er4;
    tomb[4] = er5;

    kiir(er1);
    kiir(er2);
    kiir(er3);
    kiir(er4);
    kiir(er5);

    printf("\nHatekonysag: %lf\n", hatekonysag(er1));

    tomb_kiir(tomb, db);

    // L. egjobb nem puskazo
    printf("\nLegugyesebb diak: %s", ugyes(tomb, db));
    
    // 7. Puskazas torlese
    for (int i = 0; i < db; i++) {
        nullaz_puskazo(&tomb[i]);
    }
    printf("\nPuskazas torles utan:\n");
    tomb_kiir(tomb, db);

    // 8. Pont lekerdezes konkret koddal
    printf("\nPont lekerdezes (%s): %d\n", tomb[2].neptun, pont_neptun(tomb, db, tomb[2].neptun));

    // 10. fajlbol neptun pont kiiras
    printf("\nFajlbol pontok:\n");
    file_neptun_pont("neptunok.txt", tomb, db);

    // 11. statisztika
    printf("\nStatisztika:\n");
    bukott_maxolo_szamolas("maxmin.txt", tomb, db);

    // 12. Korrigalt iras
    puskazo_korrigal("korrigalt.txt", tomb, db);

    // 9. Felszabaditas
    //felszabadit(tomb, db);

    // 10. Neptunok
    file_neptun_pont("neptunok.txt", tomb, db);

    // 11. MaxMin
    bukott_maxolo_szamolas("maxmin.txt", tomb, db);

    // 12. Korrigalt
    puskazo_korrigal("korrigalt.txt", tomb, db);

    return 0;
}