#define GET_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
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

position create_person(position head, char* fname, char* lname, int birthyear);
int print_list(position first);
int printf_last(position last);
int prepend_list(position head, char* fname, char* lname, int birthyear);
int append_list(position head, char* fname, char* lname, int birthyear);
int insert_after(position previous, position to_insert);
position findbylname(position first, char* lname);
int count(position head);
position findPrevious(position first, position target);
position delete_person(position head, position target);
//todelete funkcija: positiontodelete=NULL; todeelete=prev->next; prev->next=todelete->next; free(todelete); (prethodnik pokazuje na sljedbenika)

int main()
{
	person head = { .fname = "", .lname = "",.birthyear = 0, .next = NULL };
	
	position personone = create_person(&head, "Ivan", "Anic", 2002);
	position persontwo = create_person(&head, "Luka", "Lukic", 2004);
	position personthree = create_person(&head, "Mario", "Matic", 2006);
	position personfour = append_list(&head, "Mario", "Matic", 2006);
	insert_after( &personone, &personthree);
	delete_person(&head, persontwo);
	print_list(head.next);
	int x = count(head.next);
	printf("\nBroj elemenata u  vezanoj listi: %d\n", x);


	printf("Ime: %s %s\t Godina rođenja: %d\t ADRESA: %p\n",personfour->fname, personfour->lname, personfour->birthyear, personfour->next);
	//printf("Ime: %s %s\t Godina rođenja: %d\t ADRESA: %p", neww->fname, neww->lname, neww->birthyear, neww->next);

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

	new_person->next = head->next;
	head->next = new_person;

	return new_person;

}
int count(position head) {
	position current=head;
	int counter=0;

	while (current != NULL) {
		counter++;
		current = current->next;

	}

	return counter;

}
int prepend_list(position head, char* fname, char* lname, int birthyear) {
	position new_person;

	new_person = create_person(head, fname, lname, birthyear);
	if (!new_person) {
		return -1;
	}

	new_person = head->next;
	head->next = new_person;

	return 0;

}
int print_list(position first) {
	position temp = first;

	while (temp) {
		printf("First name: %s last name: %s birthday year: %d\n", temp->fname, temp->lname, temp->birthyear);
			temp = temp->next;
		
	}
return 0;


}
int printf_last(position head) {

	position temp = head;

	while (temp) {
		printf("First name: %s last name: %s birthday year: %d\n", temp->fname, temp->lname, temp->birthyear);
			temp = temp->next;
		return temp;
	}


}
int append_list(position head, char* fname, char* lname, int birthyear) {

	



	position temp = head;
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


	while (temp->next != NULL) { //pripazit na uvijet petlje (NE MOZE "while(!temp)")

		temp = temp->next;

	}

	temp->next = new_person;

	return new_person;
}
int insert_after(position previous, position to_insert) {

	if (previous == NULL)
	{
		printf("Prethodni ne moze bit null");
		return NULL;

	}
	position new = NULL;
	new = (person*)malloc(sizeof(person));
	if (!new) {
		printf("Greska prilikom alokacije");
		return NULL;
	}

	new = to_insert;



	new->next = previous->next;
	previous->next = new;

	return new;




}

position findbylname(position first, char* lname) {

	position temp = NULL;
	temp = first;
	while (temp) {
		if (strcmp(temp->lname, lname) == 0) {
			return temp;
		}
		temp = temp->next;
	}

	return NULL;


}


position findPrevious(position first, position target) {

	position temp = NULL;
	temp = first;
	if (first == target) {
		printf("Poslali ste prvi element liste.");
		return NULL;
	}
	if (first == NULL) {
		return NULL;
	}
	while (temp->next != NULL && temp->next != target) {

		temp = temp->next;
	}

	return temp;

}

position delete_person(position head, position toDelete) {
	position temp = NULL;
	temp = toDelete;
	position previous = NULL;
	if (head == NULL || toDelete == NULL) {
		return head;
	}
	if (head == toDelete) {
		position new_head = head->next;
		free(head);
		return new_head;
	}

	previous = findPrevious(head, toDelete);
	if (previous == NULL) {
		
		return head;
	}
	previous->next = toDelete->next;
	free(toDelete);
	return head;

}

