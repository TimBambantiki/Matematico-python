//      matematico.c
//
//      Copyright 2009 Juda Kaleta <juda.kaleta@gmail.com>
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


/**
 * Matematico
 * ============
 *
 * Matematico je logicka hra, ve kterem mate za ukol vyplnovat tabulku tazenymi cisly tak,
 * aby na jednotlivych radcich, sloupcich a uhloprickach vznikali pozadovane kombinace
 * (kombinace jsou zadane jako definice nize). Kazda kombinace ma pak sve bodove ohodnoceni.
 * Kazde cislo je tazeno maximalne 4x.
 *
 */

#ifdef DEBUG
	#define		PRINT	/* zapnuti vystupu pri ladeni */
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libmatematico.h"


/* functions */
void	test(); /* automaticke zahrani */
void 	vykresliTabulku(); /* vykresleni tabulky, vypsani zadanych cisel */

//PyDoc_STRVAR(generujCislo__doc__, "generujCislo" );
//PyDoc_STRVAR(nahodneCislo__doc__, "nahodneCislo(od, k)" );
//PyDoc_STRVAR(minus__doc__, "minus(x,y)" );

int main() {
	int i, cislo;

	#ifdef DEBUG
	test();
	return 0;
	#endif


	for(i=0; i<POCET_KOL; i++) {
		cislo = generujCislo();

		#ifdef PRINT
			printf("%i. kolo\n", i+1);
			printf("Bylo tazeno cislo: %i\n", cislo);
		#endif

		ulozSouradnice(cislo);

		#ifdef PRINT
			puts("\n ------------------------ \n");

			vykresliTabulku();
		#endif
	}

	#ifdef PRINT
		printf("Celkem bodu: %i\n", sectiBody());
	#endif

    return 0;
}

#ifdef PRINT
void vykresliTabulku() {
	int row, col;

	printf("X||\t");
	for(col=0; col<VELIKOST_POLE; col++) {
		printf("%i\t|\t", col+NULOVY_BOD);
	}
	puts("\n================================================================================");

	for(row=0; row<VELIKOST_POLE; row++) {
		for(col=0; col<VELIKOST_POLE; col++) {
			if(col==0) {
				printf("%i||\t", row+NULOVY_BOD);
			}
			printf("%i\t|\t", hodnoty[row+NULOVY_BOD][col+NULOVY_BOD]);
		}
		puts("\n--------------------------------------------------------------------------------");
		//puts("\n");
	}
}
#endif

#ifdef DEBUG
	void test() {
		int i, cislo;

		for(i=0; i<POCET_KOL; i++) {
			cislo = generujCislo();

			printf("%i. kolo\n", i+1);
			printf("Bylo tazeno cislo: %i\n", cislo);

			ulozSouradnice(cislo);

			puts("\n ------------------------ \n");

			vykresliTabulku();
		}

		printf("Celkem bodu: %i\n", sectiBody());
	}
#endif
