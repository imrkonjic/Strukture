#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR_OPENING_FILE -1
#define BUFFER_SIZE 1024


struct {
	char ime[10];
	char prezime[10];
	int	postotak;
}typedef student;


int izbroji(char* filename);
int pohrana(char*, student*);
double postotak(int, int);

int main() {
	int i;
	char ime_datoteke[20];
	int br_studenata;
	student* studenti;

	printf("Unesi ime datoteke koju zelite otvoriti: ");
	scanf("%s", ime_datoteke);

	br_studenata = izbroji(ime_datoteke);

	printf("Broj studenata je: %d\n", br_studenata);

	studenti = (student*)malloc(sizeof(student) * br_studenata);

	pohrana(ime_datoteke, studenti);

	printf("\n(Maksimalni broj Bodova je 30)\n");
	printf("Studenti:\n");
	printf("Ime\tPrezime\tBodovi\tPostotak\t\n");
	for (i = 0; i < br_studenata; i++) {

		printf("%s\t%s\t%d\t%1f\n", studenti[i].ime, studenti[i].prezime, studenti[i].postotak, postotak(studenti[i].postotak, 30));

	}

	return EXIT_SUCCESS;
}

int izbroji(char* filename) {

	char buffer[BUFFER_SIZE];
	int count = 0;
	FILE* fp = NULL;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		return ERROR_OPENING_FILE;
	}

	while (!feof(fp)) {

		fgets(buffer, BUFFER_SIZE, fp);
		++count;
	}
	fclose(fp);
	return count;
}

int pohrana(char* filename, student* niz) {
	int i = 0;
	char ime[10];
	char prezime[10];
	int	postotak;

	FILE* fp = NULL;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		return ERROR_OPENING_FILE;
	}

	while (!feof(fp)) {

		fscanf(fp, "%s %s %d", ime, prezime, &postotak);

		strcpy(niz[i].ime, ime);
		strcpy(niz[i].prezime, prezime);
		niz[i].postotak = postotak;
		i++;
	}

	fclose(fp);

};
double postotak(int br_bodova, int max_bodovi) {

	double post;

	post = ((double)br_bodova / max_bodovi) * 100;

	return post;

}




