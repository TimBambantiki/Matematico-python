#include <Python.h>

/* libovolne menitelne definice */
#define		NULOVY_BOD		0		/* udava nulovy bod. Pokud je 0, pak jsou souradnice min. [0,0], pokud 1, pak [1,1]. Pro graficke rozhrani je nutne mit [0,0] */

#define		DVOJICE 		10		/* 1+1 */
#define		DVE_DVOJICE		30		/* 1+1, 2+2 */
#define		TROJICE			40		/* 1+1+1 */
#define		POSTUPKA		50		/* 1+2+3+4+5 */
#define		FULLHAUSE		80		/* 3+3+3, 2+2 */
#define		SPECIAL 		100		/* 1+1+13+13+13 */
#define		CTVERICE 		160		/* 1+1+1+1 */

#define		PLUS_UHLOPRICKA	10		/* pokud je kombinace v uhlopricce pricte se */

/* nedoporucuji menit */
#define		NEJVETSI_CISLO	13		/* do jakeho cisla se bude generovat. Default 13 (1-13) */
#define		MAXIMALNI_POCET	4		/* maximalni pocet tazeni jednoho cisla (kolikrat smi cislo padnout) */

#define		VELIKOST_POLE	5		/* to by se asi nemelo menit :) */
#define		POCET_KOL		VELIKOST_POLE*VELIKOST_POLE

/* vars */
//int cisla[POCET_KOL]; 		/* ukladani tazenych cisel, mozna zbytecne, uvidime */
int pocet_cisel[NEJVETSI_CISLO+1]; /* kolikrat ktere cislo padlo */

int hodnoty[VELIKOST_POLE+NULOVY_BOD][VELIKOST_POLE+NULOVY_BOD]; /* ukladani tazenych cisel do tabulky podle souradnic */


/* functions */
static	PyObject * velikostPole(); /* vraci VELIKOST_POLE */
static	PyObject * restart(); /* vymazani hry */
static	PyObject * generujCislo(); /* ziskani nahodneho cisla a zaroven overeni, zda uz neni tazeno mockrat */
static	PyObject * kontrolaSouradnic(int x, int y); /* overeni zda neni bunka plna */
static	PyObject * mSS(int *arr); /* specialni modifikace shell sortu */
static	PyObject * nahodneCislo(int od, int k);
static	PyObject * sectiBody(); /* vysledne secteni bodu, ziskani skore */
static	PyObject * ulozSouradnice(PyObject *self, PyObject *args); //(int x, int y, int cislo); /* ziskani souradnic, ulozeni do promenne hodnoty */
static	PyObject * zjistiBody(int *data); /* zjisti z hodnot v radku kombinace */

PyDoc_STRVAR(matematico__doc__, "matematico");
PyDoc_STRVAR(velikostPole__doc__, "velikostPole()");
PyDoc_STRVAR(pocetKol__doc__, "pocetKol()");
PyDoc_STRVAR(restart__doc__, "restart()");
PyDoc_STRVAR(generujCislo__doc__, "generujCislo()");
PyDoc_STRVAR(kontrolaSouradnic__doc__, "kontrolaSouradnic(x, y)");
PyDoc_STRVAR(mSS__doc__, "minus(arr)");
PyDoc_STRVAR(nahodneCislo__doc__, "nahodneCislo(od, k)");
PyDoc_STRVAR(sectiBody__doc__, "sectiBody(arr)");
PyDoc_STRVAR(ulozSouradnice__doc__, "ulozSouradnice(x, y, cislo)");
PyDoc_STRVAR(zjistiBody__doc__, "zjistiBody(data)");


static PyObject * velikostPole() {
	return PyInt_FromLong((long) VELIKOST_POLE);
}

static PyObject * pocetKol() {
	return PyInt_FromLong((long) POCET_KOL);
}

static PyObject * restart() {
	int i, j;

	for(i=1; i<=NEJVETSI_CISLO+1; i++) {
		pocet_cisel[i] = 0;
	}

	for(i=0; i<VELIKOST_POLE+NULOVY_BOD; i++) {
		for(j=0; j<VELIKOST_POLE+NULOVY_BOD; j++) {
			hodnoty[i][j] = 0;
		}
	}

	return PyInt_FromLong((long) 1);;
}

/**
 *	Vytvoreni noveho nahodneho cisla. Nejdrive se cislo vygeneruje v intervalu od
 *  1 do NEJVETSI_CISLO. Pote se overi, zda jiz cislo nebylo vygenerovano vicekrat nez
 *  je povolene. Pokud ano, generuje se nove cislo. Pokud je v poradku, zanese se informace
 *  o zvyseni poctu a cislo se vrati.
 */
static PyObject * generujCislo() {
	int cislo;

	do {
		cislo = (int) PyInt_AsLong(nahodneCislo(1, NEJVETSI_CISLO));
	} while(pocet_cisel[cislo]>=MAXIMALNI_POCET);

	pocet_cisel[cislo]++;

	return PyInt_FromLong((long) cislo);
}

/**
 * Funkce pro vygenerovani nahodneho cisla v zadanem intervalu
 */
static PyObject * nahodneCislo(int od, int k) {
	int cislo;

	srand(time(NULL)+(rand()%10000));
	cislo = (rand() % (k-od+1))+od;

	return PyInt_FromLong((long) cislo);
}


/**
 *	Cyklus ve kterem se opakovane ziskavaji souradnice, pak nasleduje jejich kontrola a pokud
 * 	- jsou v poradku cislo se do danych souradnic ulozi
 * 	- nejsou v poradku, vypise se dotaz znovu.
 */
static PyObject * ulozSouradnice(PyObject *self, PyObject *args) { //(int x, int y, int cislo) {
	int x, y, cislo;
	PyArg_ParseTuple(args, "iii", &x, &y, &cislo);

	#ifdef DEBUG
	do {
		puts("Zadej souradnice: ");

		x = nahodneCislo(NULOVY_BOD, VELIKOST_POLE+NULOVY_BOD-1);
		y = nahodneCislo(NULOVY_BOD, VELIKOST_POLE+NULOVY_BOD-1);
		printf("%i %i\n", x, y);
	} while(kontrolaSouradnic(x, y) == 1);
	#endif


	if(kontrolaSouradnic(x, y) == 0) {
		hodnoty[x][y] = cislo;
	}

	return PyInt_FromLong((long) cislo);
}


/**
 *	1. Zjisteni, zda jsou zadane body platnymi souradnicemi tabulky. Musi se brat v ohled nulovy bod.
 * 	2. Overeni, ze v dane bunce o danych souradnicich jeste neni nic napsano.
 */
static PyObject * kontrolaSouradnic(int x, int y) {
	if(x>=VELIKOST_POLE+NULOVY_BOD || y>=VELIKOST_POLE+NULOVY_BOD || x<NULOVY_BOD || y<NULOVY_BOD) {
		#ifdef PRINT
			printf("Mimo vysec :) . Tabulka ma rozmery %ix%i (zadano %i %i)\n", VELIKOST_POLE, VELIKOST_POLE, x, y);
		#endif

		return PyInt_FromLong((long) 1);
	}

	if(hodnoty[x][y]>0) {
		#ifdef PRINT
			puts("Bunka je obsazena");
		#endif
		return PyInt_FromLong((long) 1);
	}

	return 0;
}


/**
 * Nejdrive se prevedou jednotlive radky, sloupce a uhlopricky do poli, ktere maji
 * stejny format. Pote se z nich pocitaji body, ktere se scitaji.
 */
static PyObject * sectiBody() {
	int row, col, body, i, j[2], uhl;
	int rows[VELIKOST_POLE][VELIKOST_POLE], cols[VELIKOST_POLE][VELIKOST_POLE], uhlopricky[2][VELIKOST_POLE];

	// pro ukladani indexu uhlopricek
	j[0] = 0;
	j[1] = 0;
	body = 0;

	// prevadeni do stejnych poli s indexy od 0.
	// asi by to slo udelat nejak efektivneji, ale nebudu sahat na neco co funguje :D
	for(row=0; row<VELIKOST_POLE; row++) {
		for(i=0; i<VELIKOST_POLE; i++) {
			// ulozeni do radku
			rows[row][i] = hodnoty[row+NULOVY_BOD][i+NULOVY_BOD];
			// ulozeni do sloupce
			cols[i][row] = hodnoty[row+NULOVY_BOD][i+NULOVY_BOD];

			if(i-row==0) {
				// ulozeni do uhlopricky zleva
				uhlopricky[0][j[0]] = hodnoty[row+NULOVY_BOD][i+NULOVY_BOD];
				j[0]++;
			}

			if(i+row==VELIKOST_POLE-1) {
				// ulozeni do uhlopricky zprava
				uhlopricky[1][j[1]] = hodnoty[row+NULOVY_BOD][i+NULOVY_BOD];
				j[1]++;
			}
		}
	}

	// radky
	for(row=0; row<VELIKOST_POLE; row++) {
		body += (int) zjistiBody(rows[row]);
	}
	#ifdef PRINT
	printf("Body po radkach: %i\n", body);
	#endif

	// sloupce
	for(col=0; col<VELIKOST_POLE; col++) {
		body += (int) zjistiBody(cols[col]);
	}
	#ifdef PRINT
	printf("Body po sloupcich: %i\n", body);
	#endif

	// uhlopricky
	for(i=0; i<2; i++) {
		uhl = (int) zjistiBody(uhlopricky[i]);

		if(uhl!=0) {
			body += uhl+10;
		}
	}
	#ifdef PRINT
	printf("Body po uhloprickach: %i\n", body);
	#endif

	return PyInt_FromLong((long) body);
}

/**
 *	Zkouma posloupnost cisel a hleda definovane kombinace.
 */
static PyObject * zjistiBody(int *data) {
	int a, b, c, d, e;
	mSS(data);

	a = data[0];
	b = data[1];
	c = data[2];
	d = data[3];
	e = data[4];

	#ifdef SPECIAL
	if(a==1 && b==1 && c==13 && d==13 && e==13) {
		#ifdef PRINT
		printf("special (%i): %i %i %i %i %i\n", SPECIAL, a, b, c, d, e);
		#endif

		return SPECIAL;
	}
	#endif

	#ifdef CTVERICE
	if(b==c && b==d && (a==b || b==e)) {
		#ifdef PRINT
		printf("ctverice (%i): %i %i %i %i %i\n", CTVERICE, a, b, c, d, e);
		#endif

		return CTVERICE;
	}
	#endif

	#ifdef FULLHAUSE
	if((a==b && c==d && c==e) || (a==b && a==c && d==e)) {
		#ifdef PRINT
		printf("fullhause (%i): %i %i %i %i %i\n", FULLHAUSE, a, b, c, d, e);
		#endif

		return FULLHAUSE;
	}
	#endif

	#ifdef POSTUPKA
	if((a+1)==b && (a+2)==c && (a+3)==d && (a+4)==e) {
		#ifdef PRINT
		printf("postupka (%i): %i %i %i %i %i\n", POSTUPKA, a, b, c, d, e);
		#endif

		return POSTUPKA;
	}
	#endif

	#ifdef TROJICE
	if((a==b && a==c) || (b==c && b==d) || (c==d && c==e)) {
		#ifdef PRINT
		printf("trojice (%i): %i %i %i %i %i\n", TROJICE, a, b, c, d, e);
		#endif

		return TROJICE;
	}
	#endif

	#ifdef DVE_DVOJICE
	if((a==b && c==d) || (a==b && d==e) || (b==c && d==e)) {
		#ifdef PRINT
		printf("dve dvojice (%i): %i %i %i %i %i\n", DVE_DVOJICE, a, b, c, d, e);
		#endif
		return DVE_DVOJICE;
	}
	#endif

	#ifdef DVOJICE
	if(a==b || b==c || c==d || d==e) {
		#ifdef PRINT
		printf("dvojice (%i): %i %i %i %i %i\n", DVOJICE, a, b, c, d, e);
		#endif
		return DVOJICE;
	}
	#endif

	return 0;
}

/**
 * Upraveny shell sort. Radi radky nebo sloupce v tabulce, proto je velikost
 * konstantni (VELIKOST_POLE).
 */
static PyObject * mSS(int *arr) {
	int i, mezera, j, tmp;

    mezera = VELIKOST_POLE / 2;

    while (mezera > 0) {
        for (i = 0; i < VELIKOST_POLE-mezera; i++) {
            j = i + mezera;
            tmp = arr[j];

            while (j >= mezera && tmp < arr[j-mezera]) {
                arr[j] = arr[j-mezera];
                j -= mezera;
            }
            arr[j] = tmp;
        }

        if(mezera==2) {
			mezera = 1;
		} else {
			mezera /= 2;
		}
    }

    return NULL;
}

static PyObject * matematico() {
	return NULL;
}

static PyMethodDef matematico_methods[] = {
  { "matematico",  matematico, METH_VARARGS, matematico__doc__ },
  { "velikostPole",  velikostPole, METH_VARARGS, velikostPole__doc__ },
  { "pocetKol",  pocetKol, METH_VARARGS, pocetKol__doc__ },
  { "restart",  restart, METH_VARARGS, restart__doc__ },
  { "generujCislo",  generujCislo, METH_VARARGS, generujCislo__doc__ },
  { "kontrolaSouradnic",  kontrolaSouradnic, METH_VARARGS, kontrolaSouradnic__doc__ },
  { "mSS",  mSS, METH_VARARGS, mSS__doc__ },
  { "nahodneCislo",  nahodneCislo, METH_VARARGS, nahodneCislo__doc__ },
  { "sectiBody",  sectiBody, METH_VARARGS, sectiBody__doc__ },
  { "ulozSouradnice",  ulozSouradnice, METH_VARARGS, ulozSouradnice__doc__ },
  { "zjistiBody",  zjistiBody, METH_VARARGS, zjistiBody__doc__ },
  { "ulozSouradnice",  ulozSouradnice, METH_VARARGS, ulozSouradnice__doc__ },
  { NULL, NULL }
};


PyMODINIT_FUNC initmatematico( void )
{
  Py_InitModule3("matematico", matematico_methods, matematico__doc__ );
}
