#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
	char c;

	do {
		system("cls||clear");
		ReadLines();

		printf("\nDesea probar otro archivo S/N? ");
		fflush(stdin);
		c = getchar();
	} while(c == 's' || c == 'S');
	

	return 0;
}