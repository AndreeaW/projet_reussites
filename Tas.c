/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005, 
   d'apres les algorithmes de Pierre-Claude Scholl              
   modifie par F. Carrier, juillet 2012
   --> types enumeres : Couleur, Rang
   --> tas representes par des listes chainees
----------------------------------------------------------------*/

#include "Tas.h"
#include "Alea.h"

/*-----------------------------------*/
/* Specifications des objets de base */
/*-----------------------------------*/

/* Couleurs et rangs */

/* Couleurs */
/* Ordre croissant sur les couleurs: trefle, carreau, coeur, pique */

Couleur CouleurSuivante(Couleur C) {
	Couleur couleur; 
	if (C < DerniereCouleur)
		couleur = C+1;
	else
		couleur = PremiereCouleur;

	return couleur;
}

/* Rangs */
/* Ordre croissant sur les rangs: deux, ..., dix, valet, dame, roi, as */

Rang RangSuivant(Rang R) {
	Rang rang;

	if (R < DernierRang)
		rang = R+1;
	else
		rang = PremierRang; 

	return rang;
}

/*--------------------------------------------------------------------*/
/* Representation des primitives de manipulation des cartes et des tas*/
/*--------------------------------------------------------------------*/

/* Representation des cartes */

	/* Testeurs et selecteurs */
	
Rang LeRang(Carte C) {
	return C.RC;
}

Couleur LaCouleur(Carte C) {
	return C.CC;
}

Visibilite EstCachee(Carte C) {
	return C.VC == Cachee;
}

Visibilite EstDecouverte(Carte C) {
	return C.VC == Decouverte; 
}

	/* Comparaison de cartes */
	
booleen RangInferieur(Carte C1, Carte C2) {
	return C1.RC < C2.RC; 
}

booleen MemeRang(Carte C1, Carte C2) {
	return C1.RC == C2.RC;
}

booleen CouleurInferieure(Carte C1, Carte C2) {
	return C1.CC < C2.CC;
}

booleen MemeCouleur(Carte C1, Carte C2) {
	return C1.CC == C2.CC; 
}

booleen EstCarteAvant(Carte C1, Carte C2) {
	return CouleurInferieure(C1,C2) || (MemeCouleur(C1,C2) && RangInferieur(C1,C2));
}

/* Representation des tas */
	
	/* Testeurs et selecteurs */
	
booleen TasActif(Tas T) {
	return T.RT == actif; 
}

booleen TasVide(Tas T) {
	return T.HT == 0;
}

booleen TasEmpile(Tas T) {
	return T.MT == empile;
}

booleen TasEtale(Tas T) {
	return T.MT == etale; 
}

int LaHauteur(Tas T) {
	return T.HT;	
}

Localisation LaPlace(Tas T) {
	return T.LT;
}

	/* Constructeurs */
	
/* *************************************************************
void CreerTasVide(Localisation L, Mode M, Tas *T)
associe à T un tas vide actif placé en L et de mode d'étalement M.
Pré-condition : l'emplacement L est disponible
**************************************************************** */
void CreerTasVide(Localisation L, Mode M, Tas *T) {
	T = (Tas *) malloc(sizeof(Tas));
	(*T).LT = L; 
	(*T).MT = M; 
	(*T).RT = actif;
	(*T).HT = 0;
	(*T).tete = NULL;
	(*T).queue = NULL;
}

/* *************************************************************
void SupprimerTasVide(Tas *T)
rend le tas vide inactif. En particulier, la place qu'il occupait
devient libre pour un autre tas.
Pré-condition : le tas T est vide et actif
**************************************************************** */
void SupprimerTasVide(Tas *T) {
	free(T);
	T = NULL;
}

/* *************************************************************
void CreerJeuNeuf(int N, Localisation L, Tas *T)
forme en L le tas empilé T avec l'ensemble des N cartes du jeu dans
l'ordre des cartes et faces cachées.
Donne leur valeur aux variables globales NbCartes et PremierRang.
Pré-condition : l'emplacement L est libre
                N==52 ou N==32
**************************************************************** */
void CreerJeuNeuf(int N, Localisation L, Tas *T) {
	T->MT=empile;
	T->LT=L;
	T->tete->elt.VC=Cachee;
	T->queue->elt.VC=Cachee;
	if (N==32) PremierRang=Sept;
	else PremierRang=Deux;
}

	/* Consultation des cartes d'un tas: ne deplace pas la carte */
	
/* *************************************************************
Carte CarteSur(Tas T) {
carte situee au dessus du tas
**************************************************************** */
Carte CarteSur(Tas T) {
	return (T.queue)->elt;
}

/* *************************************************************
Carte CarteSous(Tas T) {
carte situee au dessous du tas
**************************************************************** */
Carte CarteSous(Tas T) {
	return (T.tete)->elt;
}

/* *************************************************************
Carte IemeCarte(Tas T, int i)
ieme carte dans T (de bas en haut).
Précondition : i <= LaHauteur(T)
**************************************************************** */
Carte IemeCarte(Tas T, int i) {
	int j;
	struct adCarte * courant = T.tete;

	for (j = 0 ; j < i ; j++) {
		courant = courant->suiv;
	}

	return courant->elt;
}

	/* Retournement d'une carte sur un tas */
	
/* *************************************************************
void RetournerCarteSur(Tas *T)
retourne la carte située au dessus du tas T.
Pré-condition : T non vide
**************************************************************** */
void RetournerCarteSur(Tas *T) {
	/* T->queue->elt.VC = (T->queue->elt.VC + 1) % 2; */

	if (T->queue->elt.VC == Decouverte) {
		T->queue->elt.VC = Cachee;
	} else {
		T->queue->elt.VC = Decouverte;
	}
}

/* *************************************************************
void RetournerCarteSous(Tas *T)
retourne la carte située au dessous du tas T.
Pré-condition : T non vide
**************************************************************** */
void RetournerCarteSous(Tas *T) {
       if (T->tete->elt.VC == Decouverte) {
		T->tete->elt.VC = Cachee;
	} else {
		T->tete->elt.VC = Decouverte;
	}
}

	/* Modification d'un tas */

/* *************************************************************
void EmpilerTas(Tas *T)
void EtalerTas(Tas *T)
modification du mode d'etalement d'un tas
**************************************************************** */
void EmpilerTas(Tas *T) {
	T->MT = empile;
}

void EtalerTas(Tas *T) {
	T->MT = etale;  
}

struct adCarte * retrouver_adCarte(int index, Tas T) {
	int i;
	struct adCarte * carte = T.tete;

	for (i = 0 ; i <= index ; i ++) {
		carte = carte->suiv;
	}
	
	return carte;
}
	
/* *************************************************************
void EchangerCartes(int i, int j, Tas *T)
echange les cartes i et j du tas T
Precondition : les deux cartes existent i,j <= LaHauteur(T)
**************************************************************** */
void EchangerCartes(int i, int j, Tas *T) {
	struct adCarte  *carte_i = retrouver_adCarte(i,*T),
			*carte_j = retrouver_adCarte(j,*T),
			*tmp;
	
	tmp = carte_j->suiv;
	carte_j->suiv = carte_i->suiv;
	carte_i->suiv = tmp;

	tmp = carte_j->prec;
	carte_j->prec = carte_i->prec;
	carte_i->prec = tmp;
}


/* *************************************************************
void BattreTas(Tas *T)
bas le tas T
**************************************************************** */
void BattreTas(Tas *T) {
	InitAlea();
	int i;  
	for(i=1; i<=LaHauteur(*T); i++) {    /*i fait un parcours de chaque carte du tas */
		int nbr_aleatoire = UnEntier(LaHauteur(*T));
		EchangerCartes(i, nbr_aleatoire, T);
	}

}



/* ******************************************************************************
void RetournerTas(Tas *T)
retourne le tas T : la premiere devient la derniere et la visibilite est inversee
********************************************************************************* */
void RetournerTas(Tas *T) {
	Localisation loc_temp;
	Tas *tas_temp = NULL; 
	CreerTasVide(loc_temp, LaHauteur(*T), tas_temp);
	int num_carte;
	for(num_carte=1;num_carte<=LaHauteur(*T);num_carte++) {
		DeplacerHautSur(T, tas_temp);
		RetournerCarteSur(tas_temp);
	}
	PoserTasSurTas(tas_temp, T); 
	SupprimerTasVide(tas_temp); 
}


	/* Deplacements de cartes d'un tas sur un autre */


/* ******************************************************************************
void AjouterCarteSurTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sur le tas T
********************************************************************************* */
void AjouterCarteSurTas (struct adCarte *ac, Tas *T) {
	 ac->suiv = T->queue->suiv;
	T->queue->suiv = ac;
	ac->prec =T->queue;
}

/* ******************************************************************************
void AjouterCarteSousTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sous le tas T
********************************************************************************* */
void AjouterCarteSousTas (struct adCarte *ac, Tas *T) {
	ac->suiv = T->tete->suiv;
	T->tete->suiv = ac;
	ac->prec =T->tete;
}


/* ******************************************************************************
void DeplacerHautSur(Tas *T1, Tas *T2)
enlève la carte située au dessus de T1 et la place au dessus de T2
Pré-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSur(Tas *T1, Tas *T2) {
	struct adCarte *carte_tas_1, *carte_tas_2;
	carte_tas_1 = T1->queue;
	carte_tas_2 = T2->queue;

	carte_tas_1->suiv = NULL;
	(carte_tas_1->prec)->suiv = NULL;
	carte_tas_2->suiv = carte_tas_1;
	carte_tas_1->prec = carte_tas_2;
}

/* ******************************************************************************
void DeplacerHautSous(Tas *T1, Tas *T2)
enlève la carte située au dessus de T1 et la place au dessous de T2.
Pré-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSous(Tas *T1, Tas *T2) {
	struct adCarte * AQ1, * AT2;

	AQ1 = T1->queue;
	AT2 = T2->tete;

	AQ1->prec = T1->queue;
	AQ1->prec->suiv = NULL;
	*(AT2->prec) = *AQ1;
	*(AQ1->suiv) = *AT2;
	AQ1 = T2->tete;
	T2->tete->prec = NULL;
}

/* ******************************************************************************
void DeplacerBasSur(Tas *T1, Tas *T2)
enlève la carte située au dessous de T1 et la place au dessus de T2.
Pré-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSur(Tas *T1, Tas *T2) {
	struct adCarte * AT1, * AQ2;
	AT1 = T1->tete;
	AQ2 = T2->queue;

	AT1->suiv = (*T1).tete;
	(*(*T1).tete).prec = NULL;
	*(*AQ2).suiv = *AT1;
	*(*AT1).prec = *AQ2;
	AT1 = (*T2).queue;
	(*(*T2).queue).suiv = NULL;
}


/* ******************************************************************************
void DeplacerBasSous(Tas *T1, Tas *T2) {
enlève la carte située au dessous de T1 et la place au dessous de T2.
Pré-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSous(Tas *T1, Tas *T2) {
	struct adCarte * AT1, * AT2;
	AT1 = (*T1).tete;
	AT2 = (*T2).tete;

	(*AT1).suiv = (*T1).tete;
	(*(*T1).tete).prec = NULL;
	*(*AT2).prec = *AT1;
	*(*AT1).suiv = *AT2;
	AT1 = (*T2).tete;
}

/* ******************************************************************************
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2)
enlève du tas T1, la carte de couleur C et de rang R et la place au dessus de T2.
Pré-condition : T1 contient la carte et T2 est actif.
********************************************************************************* */
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2) {
	struct adCarte *carte_courante = T1->queue;

	while (  carte_courante != NULL &&
		 (carte_courante->elt.CC != C && carte_courante->elt.RC != R)
		) {
		carte_courante = carte_courante->suiv;
	}

	if (carte_courante != NULL){
		carte_courante->prec->suiv = carte_courante->suiv;
		carte_courante->suiv->prec = carte_courante->prec;

		carte_courante->suiv = T2->queue;
		carte_courante->prec = NULL;
		T2->queue = carte_courante;
	}
}


/* ******************************************************************************
void PoserTasSurTas(Tas *T1, Tas *T2)
pose le tas T1 sur le tas T2.
Les deux tas doivent avoir le même mode d'étalement.
A l'état final, le tas T1 est vide mais toujours actif, et le tas T2 comporte (de bas en
haut) toutes les cartes qu'il avait au départ puis toutes les cartes de T1 dans l'ordre
qu'elles avaient au départ dans chacun des tas.
Cette opération ne modifie ni la visibilité des cartes, ni la localisation des tas T1 et T2,
ni leur mode d'étalement.
********************************************************************************* */
void PoserTasSurTas(Tas *T1, Tas *T2) {
	if ((*T1).MT != (*T2).MT) return;
	while ((*T1).HT != 0) {
		DeplacerBasSous(T1, T2);
	}
}


