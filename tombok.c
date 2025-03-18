// 2d array
#include <stdio.h>
#include <stdlib.h>

int main() {
    int stat_matrix[5][4] = {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}};

    printf("Minden elem kiirasa kulon:\n");
    for(int s=0;s<5;s++) {
        for(int o=0;o<4;o++) {
            printf("(%d, %d) = %d\n", s, o, stat_matrix[s][o]);
        }
    }

    printf("Minden elem matrix kiirasa:\n");
    for(int s=0;s<5;s++) {
        for(int o=0;o<4;o++) {
            printf("%d ", stat_matrix[s][o]);
        }
        printf("\n");
    }

    int s_szam, o_szam;
    printf("Sor oszlop: ");
    scanf("%d %d", &s_szam, &o_szam);

    printf("%d %d\n", s_szam, o_szam);

    int* din_matrix = (int*)malloc(sizeof(int)*s_szam*o_szam);

    printf("Generalas...\n");
    for(int s=0;s<s_szam;s++) {
        for(int o=0;o<o_szam;o++) {
            din_matrix[s*o_szam+o] = s*o_szam+o;
        }
    }

    printf("Dinamikus matrix:\n");
    for(int s=0;s<s_szam;s++) {
        for(int o=0;o<o_szam;o++) {
            printf("%d   ", din_matrix[s*o_szam+o]);
        }
        printf("\n");
    }

    free(din_matrix);


    return 0;
}