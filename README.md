## MSZO IPA 1ZH konzi

A **minta_zh.c** tartalmazza a **minta_zh.png** képen olvasható minta zh megoldását. Az konzin megbeszélt tömbökről szóló elméletet a **tombok.c** fájl tartalmazza. A konzin megoldott kő papír olló feladat az **orai_ko_papir.c** fájlban olvasható.

### Bekérésnél használatos %-ok
```c++
%d -> int
%ld -> long (int)
%lld -> long long (int)
%f -> float, double
%c -> char
%s -> string
```
Ha ki akarok iratni valamennyi decimál pontig (pl. 3):
```c++
double d = 1.12345678;
printf("%.3f", d);
```

### Pár trükkös hibakereső példa (később még bővülhet):
#### 1.
```c++
   printf(“Adj meg egy egesz szamot”);
   int n;
   scanf_s(“%f“, n);
``` 
<details>
  <summary>Megoldás</summary>

  Két hiba is van az utolsó sorban:  
  - %f van %d helyett
  - scanf_s-ben n van &n helyett
</details>

#### 2.
```c++
    int* ptr;
    *ptr = 10;
``` 
<details>
  <summary>Megoldás</summary>
  Uninicializált pointernek akarunk értéket adni -> Segmentation fault-hoz fog vezetni. Nem jó szokás csak úgy létrehozni egy pointert, legalább egy nullpointerré   
  tegyük ha ilyet csinálunk és ellenőrizzük hogy nem nullpointer-e, mert annak a dereference-álása undefined behaviour.  
  Helyesebb megoldás (ne nagyon csináljunk ilyet):

  ```c++
  int* ptr = NULL;
  if (ptr != NULL) {
      *ptr = 10;
  }
  ```
  
</details>

Jó készülést kívánunk a ZH időszakra!




