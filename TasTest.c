#include "Tas.h"
#include <stdio.h>


void testCouleurSuivante() {
	printf("\ntestCouleurSuivante:\n");
	Couleur C = Trefle;

	printf("%d", C == Trefle);
	C = CouleurSuivante(C);
	printf("%d", C == Carreau);
	C = CouleurSuivante(C);
	printf("%d", C == Coeur);
	C = CouleurSuivante(C);
	printf("%d", C == Pique);
	C = CouleurSuivante(C);
	printf("%d", C == Trefle);
}

void testRangSuivant() {
	printf("\ntestRangSuivant\n");
	Rang rang = Deux;
	printf("%d", rang == Deux);
	rang = RangSuivant(rang);
	printf("%d", rang == Trois);
	
	rang = RangSuivant(rang);
	rang = RangSuivant(rang);
	rang = RangSuivant(rang);
	rang = RangSuivant(rang);
	rang = RangSuivant(rang);
	rang = RangSuivant(rang);
	rang = RangSuivant(rang);
	rang = RangSuivant(rang);
	rang = RangSuivant(rang);
	rang = RangSuivant(rang);
	printf("%d", rang == Roi);
	rang = RangSuivant(rang);
	printf("%d", rang == As);
}

void testRangInferieur() {
	printf("\ntestRangInferieur\n");
	Carte carte1, carte2, carte3;
	carte1.RC = Deux;
	carte2.RC = Deux;
	carte3.RC = Trois;

	printf("%d", RangInferieur(carte1, carte3));
	printf("%d", !RangInferieur(carte1, carte2));
	printf("%d", !RangInferieur(carte1, carte1));
	printf("%d", !RangInferieur(carte3, carte2));
}

void main() {
	testCouleurSuivante();
	testRangSuivant();
	testRangInferieur();
	printf("\n");
}
