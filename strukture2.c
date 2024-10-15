#define GET_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct person* position;

typedef struct person {
	//data
	char fname[32], lname[32];
	int birthyear;
	//link
	position next;
}person;

position create_person(position head, char* fname,char* lname, int birthyear);
int prepend_list(position head, char* fname, char* lname, int birthyear);
int printf_list(position first);
int printf_last(position last);
int append_list(position head, char* fname, char* lname, int birthyear);
int insert_after(position previous, position to_insert);
position findbylname(position first, char* fname, char* lname, int birthyear);
//todelete funkcija: positiontodelete=NULL; todeelete=prev->next; prev->next=todelete->next; free(todelete); (prethodnik pokazuje na sljedbenika)

void main()
{
	person head = { .fname = "", .lname = "",.birthyear = 0, next=NULL };


}


position create_person(position head, char* fname, char* lname, int birthyear) {
	position new_person = NULL;

	new_person = (position*)malloc(sizeof(person));
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

int prepend_list(position head, char* fname, char* lname, int birthyear) {
	position new_person;

	new_person = create_person(fname, lname, birthyear);
		if (!new_person) {
			return -1;
		}

	new_person = head->next;
	head->next = new_person;

	return 0;

}


int printf_list(position first) {
	position temp = first;

	while (temp) {
		printf("First name: %s last name: %s birthday year: %d", temp->fname, temp->lname, temp->)
			temp = temp->next;
			return 1;
	}



}


int printf_last(position head) {

	position temp = head;

	while (temp) {
		printf("First name: %s last name: %s birthday year: %d", temp->fname, temp->lname, temp->)
		temp = temp->next;
		return temp;
	}


}

int append_list(position head, char* fname, char* lname, int birthyear);