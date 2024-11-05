#define _CRT_SECURE_NO_WARNINGS
#define GET_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct person* position;

typedef struct person {
	//data
	char fname[32], lname[32];
	int birthyear;
	//link
	position next;
}person;

//2. zad
position create_person(position head, char* fname, char* lname, int birthyear);
int prepend_list(position head, char* fname, char* lname, int birthyear);
int append_list(position head, char* fname, char* lname, int birthyear);
position findbylname(position first, char* lname);
int print_list(position first);
position delete_person(position head, int target);


//3.zad
int insert_after(position head, char* fname, char* lname, int birthyear, int previousposition);
int insert_before(position head, char* fname, char* lname, int birthyear, int nextposition);
int listtodat(position head);
position listfromdat(position head);

int main()
{
	person head = { .fname = "", .lname = "",.birthyear = 0, .next = NULL };


	/*
	prepend_list(&head, "Ivan", "Ivic", 2004);
	prepend_list(&head, "Ivano", "Ivioc", 2004);
	prepend_list(&head, "Marko", "Markic", 2004);
	append_list(&head, "Marko", "Markic", 2004); //dodavanje na kraj

	insert_before(&head, "Stipe", "Stipic", 2009, 3);
	insert_after(&head, "Jure", "Juric", 2009, 3);


	print_list(&head);
	printf("###############BRISANJE#############\n");
	delete_person(&head, 1);
	print_list(&head);

	findbylname(&head, "Ivic");
	*/

	//char* filename;
	//scanf("%s", &filename);
	listfromdat(&head);



	print_list(&head);
	return 0;

}



position create_person(position head, char* fname, char* lname, int birthyear) {//unosi elemente na pocetku
	position new_person = NULL;

	new_person = malloc(sizeof(person));
	if (!new_person) {
		printf("MAlloc failed");
		return NULL;
	}

	strcpy(new_person->fname, fname);
	strcpy(new_person->lname, lname);
	new_person->birthyear = birthyear;
	new_person->next = NULL;

	return new_person;

}
position prepend_person(position head, char* fname, char* lname, int birthyear) {
	position new_person = (position)malloc(sizeof(person));
	if (!new_person) {
		printf("Memory allocation failed.\n");
		return NULL;
	}
	strcpy(new_person->fname, fname);
	strcpy(new_person->lname, lname);
	new_person->birthyear = birthyear;

	// Dodaj novi èvor na poèetak liste
	new_person->next = head->next;
	head->next = new_person;

	return new_person;
}
int append_list(position head, char* fname, char* lname, int birthyear) {

	position new_person;


	new_person = create_person(head, fname, lname, birthyear);
	if (!new_person) {
		return -1;
	}

	while (head->next != NULL) {

		head = head->next;
	}

	new_person->next = head->next;
	head->next = new_person;

	return 0;




}
int print_list(position head) {

	position temp = head->next;

	while (temp) {
		printf("First name: %s \tlast name: %s \tbirthday year: %d\n", temp->fname, temp->lname, temp->birthyear);
		temp = temp->next;
	}
	return 0;
}
position findbylname(position first, char* lname) {

	position temp = NULL;
	temp = first;
	int counter = 0;
	while (temp) {
		if (strcmp(temp->lname, lname) == 0) {
			printf("%s je na poziciji %d\n", temp->lname, counter);
			return temp;
		}
		counter++;
		temp = temp->next;
	}

	return NULL;


}
position delete_person(position head, int target) {

	int i = 0;
	position temp = head->next;


	while ((i + 1) != target) {

		temp = temp->next;
		head = head->next;
		i++;

	}
	head->next = temp->next;
	free(temp);




	return head;
}
int insert_after(position head, char* fname, char* lname, int birthyear, int previousposition) {

	int i = 0;
	position new_person;

	new_person = create_person(head, fname, lname, birthyear);
	if (!new_person) {
		return -1;
	}


	while ((i) != previousposition) {

		head = head->next;
		i++;
	}

	new_person->next = head->next;
	head->next = new_person;


	return 0;
}
int insert_before(position head, char* fname, char* lname, int birthyear, int nextposition) {

	int i = 0;
	position new_person;

	new_person = create_person(head, fname, lname, birthyear);
	if (!new_person) {
		return -1;
	}
	if (nextposition == 1) {
		new_person->next = head->next;
		head->next = new_person;

	}
	else {
		while ((i + 2) != nextposition) {

			head = head->next;
			i++;
		}

		new_person->next = head->next;
		head->next = new_person;

	}

	return 0;
}
int listtodat(position head) {

	FILE* fp;

	fp = fopen("linkedlist.txt", "w");

	if (fp == NULL)
	{
		printf("Opening error!\n");
		return -1;
	}
	while (head->next != NULL) {
		fprintf(fp, "Name %s %s \t Age %d\n", head->next->fname, head->next->lname, head->next->birthyear);
		head = head->next;
	}

	fclose(fp);
	return 0;
}

position listfromdat(position head) {
	FILE* fp;
	position temp;

	fp = fopen("linkedlist.txt", "r");
	if (!fp) {
		printf("Failed to open file.\n");
		return head;
	}

	while (1) {
		// Alocirajte memoriju za novi èvor
		temp = (position)malloc(sizeof(person));
		if (!temp) {
			printf("Memory allocation failed.\n");
			fclose(fp);
			return head;
		}

		// Èitajte podatke u `temp`, prekid ako ne može proèitati sve tri vrednosti
		if (fscanf(fp, "%s %s %d", temp->fname, temp->lname, &temp->birthyear) != 3) {
			free(temp);
			break;
		}

		// Dodajte osobu na poèetak liste
		prepend_person(head, temp->fname, temp->lname, temp->birthyear);
	}

	fclose(fp);

	// Ispišite listu
	//print_list(head);

	return head;
}




