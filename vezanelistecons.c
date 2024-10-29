#define GET_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct osoba* pozicija;

typedef struct osoba {

	int br;
	
	pozicija sljedeci;
}osoba;

void printaj(pozicija head);
pozicija kreiraj(pozicija head, int vrj);
pozicija dodajpoc(pozicija head, int vrj);
pozicija dodajkraj(pozicija head, int vrj);
pozicija dodajiza(pozicija prethodni, int vrj);
pozicija dodajispred(pozicija head,pozicija naredni, int vrj);
int trazi(pozicija head, int trazeni);
pozicija trazipreth(pozicija Head, int vrj);
int brisi(pozicija head, int vrj);



void main() {

	// Alociraj memoriju za head (glavu liste)
	pozicija head = (osoba*)malloc(sizeof(osoba));
	pozicija prvi, drugi, treci;
	// Inicijalizacija glave liste
	head->br = 0;
	head->sljedeci = NULL;

	printf("Vrijednost head elementa liste je %d\n", head->br);
	printf("Adresa head elementa liste je %p\n", head->sljedeci);
	printf("\n################## KREIRANJE NOVIH ELEMENATA ##################\n\n");
	
	prvi = kreiraj(head, 7);
	drugi = kreiraj(prvi, 8);
	treci = kreiraj(drugi, 10);
	dodajpoc(head, 12);
	dodajkraj(head, 15);
	dodajiza(drugi, 20);
	dodajispred(head, drugi, 100);
	
	printaj(head);


	printf("####################################\n");

	brisi(head, 100);

	printaj(head);

	//trazi(head, 20);

	//pozicija p=trazipreth(head, 20);

	//printf("%d", p->br);

}

void printaj(pozicija head) {
	pozicija trenutni = head;
do {
	printf("Vrijednost: %d\t Adresa %p\tNext: %p\n",trenutni->br,&trenutni->br,trenutni->sljedeci);
	trenutni = trenutni->sljedeci;
	}
	while (trenutni);

}
pozicija kreiraj(pozicija head, int vrj) {

	pozicija novi = NULL;
	novi = (osoba*)malloc(sizeof(osoba));
	if (!novi) {
		printf("Greška prilikom alokacije memorije!\n");
		return NULL;
	}
	novi->br = vrj;
	novi->sljedeci = NULL;

	head->sljedeci = novi;
	return novi;

}
pozicija dodajpoc(pozicija head, int vrj) {

	pozicija temp;
	pozicija novi = NULL;
	novi = (osoba*)malloc(sizeof(osoba));
	if (!novi) {
		printf("Greska prilikom alokacije");
		return NULL;
	}

	novi->br = vrj;
	
	temp = head;
	
	novi->sljedeci = temp->sljedeci; //Bitan redosljed ove i sljedece linije
	head->sljedeci = novi;

	return novi;
}
pozicija dodajkraj(pozicija head, int vrj) {

	pozicija temp=head;
	pozicija novi = NULL;
	novi = (osoba*)malloc(sizeof(osoba));
	if (!novi) {
		printf("Greska prilikom alokacije");
		return NULL;
	}

	novi->br = vrj;
	novi->sljedeci = NULL;
	
		while (temp->sljedeci!=NULL) { //pripazit na uvijet petlje (NE MOZE "while(!temp)")
		
			temp = temp->sljedeci;

		}
		
	temp->sljedeci = novi;

	return novi;
}
pozicija dodajiza(pozicija prethodni, int vrj) {

	if (prethodni == NULL)
	{
		printf("Prethodni ne moze bit null");
		return NULL;
	
	}
	pozicija novi = NULL;
	novi = (osoba*)malloc(sizeof(osoba));
	if (!novi) {
		printf("Greska prilikom alokacije");
		return NULL;
	}

	novi->br = vrj;
	novi->sljedeci = prethodni->sljedeci;
	prethodni->sljedeci = novi;

	return novi;
}
pozicija dodajispred(pozicija head,pozicija naredni, int vrj) {

	if (naredni == NULL)
	{	
		printf("Naredni ne moze bit null");
		return NULL;
	}
	pozicija novi = NULL;
	pozicija temp = head;
	novi = (osoba*)malloc(sizeof(osoba));
	if (!novi) {
		printf("Greska prilikom alokacije");
		return NULL;
	}

	novi->br = vrj;

	while (temp->sljedeci!= naredni) { 

		temp = temp->sljedeci;

	}


	novi->sljedeci = temp->sljedeci;
	temp->sljedeci = novi;

	return novi;
}
int trazi(pozicija head, int trazeni) {
	
	pozicija temp = head;
	int brojac = 0;
	while (temp != NULL) {
		
		if (temp->br == trazeni) {
			break;
		
		}
		else{
			brojac++;
			temp = temp->sljedeci;

		}

	}
	
	printf("Broj %d nalazi se na %d mjestu liste.", trazeni, brojac + 1);
	return brojac;

}
pozicija trazipreth(pozicija Head, int trazeni) {

	
	while (Head->sljedeci != NULL && Head->sljedeci->br!=trazeni) {
		Head = Head->sljedeci;
	}
	if (Head->sljedeci == NULL)
		return NULL;
	else
		return Head;

	}

int brisi(pozicija head, int vrj) {

	pozicija preth = trazipreth(head, vrj);
	
	while (head->br != vrj)
	{
		head = head->sljedeci;

	}

	preth->sljedeci = head->sljedeci;

	free(head);

	return 0;

}

