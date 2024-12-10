#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024
#define GRESKA_PRI_OTVARANJU_DATOTEKE -1
#define GRESKA_PRI_ALOKACIJI -2
#define GRESKA_PRI_UNOSU -3

struct artikal;
typedef struct artikal* PozicijaArtikla;
typedef struct artikal {
    char naziv[20];
    int kolicina;
    int cijena;
    PozicijaArtikla sljedeci;
} Artikal;

struct racun;
typedef struct racun* PozicijaRacuna;
typedef struct racun {
    char datum[10];
    Artikal glavaArtikla;
    PozicijaRacuna sljedeci;
} Racun;

int dodajArtikal(PozicijaArtikla glava, PozicijaArtikla artikal);
int dodajRacun(PozicijaRacuna glava, PozicijaRacuna racun);
int ucitajRacun(char* imeDatoteke, PozicijaRacuna glavaRacuna);
int ispisiArtikle(PozicijaArtikla artikal);
int ispisiRacune(PozicijaRacuna racun);
int pronadiArtikalUPeriodu(PozicijaRacuna trenutniRacun, char* artikal, char* pocetniDatum, char* krajnjiDatum, int* prihod, int* broj);
int obrisiArtikle(PozicijaArtikla glavaArtikla);
int obrisiRacune(PozicijaRacuna glavaRacuna);

int main()
{
    int prihod = 0, broj = 0;
    char artikal[100] = { 0 };
    char pocetniDatum[20] = { 0 }, krajnjiDatum[20] = { 0 };
    char trenutniRacun[MAX] = { 0 };
    FILE* datoteka = NULL;
    Racun glavniRacun = {
        .datum = {0},
        .glavaArtikla = { .sljedeci = NULL },
        .sljedeci = NULL
    };

    datoteka = fopen("racuni.txt", "r");
    if (datoteka == NULL) {
        printf("Pogreška pri otvaranju datoteke.\n");
        return GRESKA_PRI_OTVARANJU_DATOTEKE;
    }

    while (!feof(datoteka)) {
        fgets(trenutniRacun, MAX, datoteka);
        trenutniRacun[strcspn(trenutniRacun, "\n")] = 0; // Uklanja '\n'
        printf("%s\n", trenutniRacun);
        ucitajRacun(trenutniRacun, &glavniRacun);
    }

    ispisiRacune(glavniRacun.sljedeci);

    printf("\nUnesite naziv artikla: ");
    if (scanf("%s", artikal) != 1) return GRESKA_PRI_UNOSU;
    printf("Unesite poèetni datum (GGGG-MM-DD): ");
    if (scanf("%s", pocetniDatum) != 1) return GRESKA_PRI_UNOSU;
    printf("Unesite krajnji datum (GGGG-MM-DD): ");
    if (scanf("%s", krajnjiDatum) != 1) return GRESKA_PRI_UNOSU;

    pronadiArtikalUPeriodu(&glavniRacun, artikal, pocetniDatum, krajnjiDatum, &prihod, &broj);
    printf("Zarada od %d komada %s: %d\n", broj, artikal, prihod);

    obrisiRacune(&glavniRacun);
    fclose(datoteka);

    return 0;
}

int dodajArtikal(PozicijaArtikla glava, PozicijaArtikla artikal)
{
    PozicijaArtikla trenutni = glava;

    while (trenutni->sljedeci != NULL && strcmp(trenutni->sljedeci->naziv, artikal->naziv) < 0)
        trenutni = trenutni->sljedeci;

    artikal->sljedeci = trenutni->sljedeci;
    trenutni->sljedeci = artikal;

    return 0;
}

int dodajRacun(PozicijaRacuna glava, PozicijaRacuna racun)
{
    PozicijaRacuna trenutni = glava;

    while (trenutni->sljedeci != NULL && strcmp(trenutni->sljedeci->datum, racun->datum) <= 0)
        trenutni = trenutni->sljedeci;

    racun->sljedeci = trenutni->sljedeci;
    trenutni->sljedeci = racun;

    return 0;
}

int ucitajRacun(char* imeDatoteke, PozicijaRacuna glavaRacuna)
{
    char stringDatuma[20] = { 0 };
    FILE* datoteka = NULL;
    PozicijaRacuna noviRacun = NULL;
    PozicijaArtikla noviArtikal = NULL;

    datoteka = fopen(imeDatoteke, "r");
    if (datoteka == NULL) {
        printf("Pogreška pri otvaranju datoteke.\n");
        return GRESKA_PRI_OTVARANJU_DATOTEKE;
    }

    noviRacun = (PozicijaRacuna)malloc(sizeof(Racun));
    if (noviRacun == NULL) {
        printf("Pogreška pri alokaciji memorije.\n");
        return GRESKA_PRI_ALOKACIJI;
    }

    fgets(stringDatuma, 20, datoteka);
    stringDatuma[strcspn(stringDatuma, "\n")] = 0;

    strcpy(noviRacun->datum, stringDatuma);
    noviRacun->glavaArtikla.sljedeci = NULL;

    while (!feof(datoteka)) {
        noviArtikal = (PozicijaArtikla)malloc(sizeof(Artikal));
        if (noviArtikal == NULL) {
            printf("Pogreška pri alokaciji memorije.\n");
            return GRESKA_PRI_ALOKACIJI;
        }

        if (fscanf(datoteka, "%[^,], %d, %d ", noviArtikal->naziv, &noviArtikal->kolicina, &noviArtikal->cijena) != 3) {
            printf("Pogreška pri unosu podataka.\n");
            return GRESKA_PRI_UNOSU;
        }

        dodajArtikal(&noviRacun->glavaArtikla, noviArtikal);
    }

    dodajRacun(glavaRacuna, noviRacun);

    fclose(datoteka);

    return 0;
}

int ispisiArtikle(PozicijaArtikla trenutni)
{
    while (trenutni != NULL) {
        printf("\t%s, %d, %d\n", trenutni->naziv, trenutni->kolicina, trenutni->cijena);
        trenutni = trenutni->sljedeci;
    }

    return 0;
}

int ispisiRacune(PozicijaRacuna trenutni)
{
    while (trenutni != NULL) {
        printf("Racun datuma %s:\n", trenutni->datum);
        ispisiArtikle(trenutni->glavaArtikla.sljedeci);
        trenutni = trenutni->sljedeci;
    }

    return 0;
}

int pronadiArtikalUPeriodu(PozicijaRacuna trenutniRacun, char* artikal, char* pocetniDatum, char* krajnjiDatum, int* prihod, int* broj)
{
    PozicijaArtikla trenutniArtikal = NULL;

    while (trenutniRacun != NULL && strcmp(trenutniRacun->datum, pocetniDatum) < 0)
        trenutniRacun = trenutniRacun->sljedeci;

    while (trenutniRacun != NULL && strcmp(trenutniRacun->datum, krajnjiDatum) <= 0) {
        trenutniArtikal = trenutniRacun->glavaArtikla.sljedeci;
        while (trenutniArtikal != NULL) {
            if (strcmp(trenutniArtikal->naziv, artikal) == 0) {
                *prihod += trenutniArtikal->kolicina * trenutniArtikal->cijena;
                *broj += trenutniArtikal->kolicina;
            }
            trenutniArtikal = trenutniArtikal->sljedeci;
        }
        trenutniRacun = trenutniRacun->sljedeci;
    }

    return 0;
}

int obrisiArtikle(PozicijaArtikla glavaArtikla)
{
    PozicijaArtikla privremeno = NULL;

    while (glavaArtikla->sljedeci != NULL) {
        privremeno = glavaArtikla->sljedeci;
        glavaArtikla->sljedeci = privremeno->sljedeci;
        free(privremeno);
    }

    return 0;
}

int obrisiRacune(PozicijaRacuna glavaRacuna)
{
    PozicijaRacuna privremeno = NULL;

    while (glavaRacuna->sljedeci != NULL) {
        privremeno = glavaRacuna->sljedeci;
        glavaRacuna->sljedeci = privremeno->sljedeci;
        obrisiArtikle(&privremeno->glavaArtikla);
        free(privremeno);
    }

    return 0;
}
