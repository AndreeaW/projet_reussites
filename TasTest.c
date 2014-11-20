#include "Tas.h"
#include "AUnit.h"
#include <stdio.h>
#include <stdlib.h>

void AassertLocEquals(Localisation l1, Localisation l2) {
	printf("%d", l1.NL == l2.NL);
	printf("%d", l1.NC == l2.NC);
}

void AassertLocNEquals(Localisation l1, Localisation l2) {
	printf("%d", l1.NL != l2.NL);
	printf("%d", l1.NC != l2.NC);
}

void AassertCartesEquals(Carte c1, Carte c2) {
	printf("%d", c1.CC == c2.CC);
	printf("%d", c1.RC == c2.RC);
}

void testCouleurSuivante() {
	printf("\ntestCouleurSuivante ");

	Couleur C = Trefle;
	Aassert(C == Trefle);

	C = CouleurSuivante(C);
	Aassert(C == Carreau);

	C = CouleurSuivante(C);
	Aassert(C == Coeur);

	C = CouleurSuivante(C);
	Aassert(C == Pique);

	C = CouleurSuivante(C);
	Aassert(C == Trefle);
}

void testRangSuivant() {
	printf("\ntestRangSuivant ");

	Rang rang = Deux;

	Aassert(rang == Deux);
	rang = RangSuivant(rang);
	Aassert(rang == Trois);
	
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
	Aassert(rang == Roi);
	rang = RangSuivant(rang);
	Aassert(rang == As);
}

void testRangInferieur() {
	printf("\ntestRangInferieur ");

	Carte carte1, carte2, carte3;
	carte1.RC = Deux;
	carte2.RC = Deux;
	carte3.RC = Trois;

	Aassert(RangInferieur(carte1, carte3));
	Aassert(!RangInferieur(carte1, carte2));
	Aassert(!RangInferieur(carte1, carte1));
	Aassert(!RangInferieur(carte3, carte2));
}

void testEstCarteAvant() {
	printf("\ntestEstCarteAvant ");
	Carte asDeCoeur, roiDeTrefle, septDePique, huitDePique;
	asDeCoeur.RC = As;
	asDeCoeur.CC = Coeur;
	roiDeTrefle.RC = Roi;
	roiDeTrefle.CC = Trefle;
	septDePique.RC = Sept;
	septDePique.CC = Pique;
	huitDePique.RC = Huit;
	huitDePique.CC = Pique;
	
	Aassert(EstCarteAvant(septDePique, huitDePique));
	Aassert(!EstCarteAvant(huitDePique, septDePique));
	Aassert(EstCarteAvant(roiDeTrefle, asDeCoeur));
}

void testCreerTasVide() {
	printf("\ntestCreerTasVide ");
	Localisation loc;
	Tas tas;

	CreerTasVide(loc, empile, &tas);

	Aassert(tas.MT == empile);
	AassertLocEquals(tas.LT, loc);
	Aassert(tas.RT == actif);
	Aassert(tas.HT == 0);
	Aassert(tas.tete == NULL);
	Aassert(tas.queue == NULL);
}

void testSupprimerTasVide() {
	printf("\ntestSupprimerTasVide ");
	Localisation loc;
	loc.NC = 1;
	loc.NL = 1;
	Tas tas;
	CreerTasVide(loc, empile, &tas);

	SupprimerTasVide(&tas);

	Aassert(tas.RT == inactif);
	AassertLocNEquals(tas.LT, loc);
}

void testCreerJeuNeuf() {
	/*
		TODO : segfault dans AjouterCarte*Tas
	*/
	printf("\ntestCreerJeuNeuf ");
	Localisation l;
	l.NL = 0;
	l.NC = 0;

	Tas tas;

	CreerJeuNeuf(32, l, &tas);
	Aassert(tas.MT == empile);
	Aassert(tas.RT == actif);
	Aassert(NbCartes == 32);
	Aassert(PremierRang == Sept);
	Carte carte;
	carte.CC = PremiereCouleur;
	carte.RC = PremierRang;
	AassertCartesEquals(IemeCarte(tas, 1), carte);
	AassertLocEquals(tas.LT, l);
}

void main() {
	testCouleurSuivante();
	testRangSuivant();
	testRangInferieur();
	testEstCarteAvant();
	testCreerTasVide();
	testSupprimerTasVide();
	testCreerJeuNeuf();
	printf("\n");
}
