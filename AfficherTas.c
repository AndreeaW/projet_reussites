/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005, 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#include "AfficherTas.h"
#include "graphlib_w.h"

#include "cards.bm"
#include "back.bm"
#include "vide.bm"

/* Tableau de correspondance ;
   indice dans le tableau card_bits <-> indice dans le tableau CodeCarte */
int CodeCarte[52] = 	{
                        /* Trefle */
			27,28,29,30,31,32,33,34,35,36,37,38,26,
			/* Carreau */
			14,15,16,17,18,19,20,21,22,23,24,25,13,
			/* Coeur */
			1,2,3,4,5,6,7,8,9,10,11,12,0,
			/* Pique */
			40,41,42,43,44,45,46,47,48,49,50,51,39
							};

#define EspX 50
#define EspY 70
#define DecY 20

Fenetre FenetreParDefaut;

void CreerImage(int width, int height, char *data, XImage *ximage)
{
  ximage->height = height;
  ximage->width = width;
  ximage->xoffset = 0;
  ximage->format = XYBitmap;
  ximage->data = (char *)data;
  ximage->byte_order = LSBFirst;
  ximage->bitmap_unit = 16;
  ximage->bitmap_bit_order = LSBFirst;
  ximage->bitmap_pad = 16;
  ximage->bytes_per_line = (width+7)/8;
  ximage->depth = 1;
}

void OuvrirGraphique(char nom[])
{
  gr_inits_w(&FenetreParDefaut, 10,10, 640, 400, nom);
}

void FermerGraphique()
{  
  cliquer(FenetreParDefaut);
  gr_close(&FenetreParDefaut);
}

void EffacerGraphique()
{
  clear_screen(FenetreParDefaut);
}


void AttendreCliquer()
{
  cliquer(FenetreParDefaut);
}

void AfficherCarte(Carte C, int x, int y)
{
  int Code;
  XImage ImCarte;

  if (EstCachee(C))
    {
      CreerImage(back_width, back_height, back_bits, &ImCarte);
      ajout_image_noire(FenetreParDefaut, ImCarte, x, y, back_width, back_height);
    }
  else /* La carte est découverte */
    {
      Code = (C.CC - 1)*13 + C.RC - 2;
      if ((C.CC == Trefle)||(C.CC == Pique))
	{
	  CreerImage(card_width, card_height, card_bits[CodeCarte[Code]], &ImCarte);
	  ajout_image_noire(FenetreParDefaut, ImCarte, x, y, card_width, card_height);
	}
      else
	{
	  CreerImage(card_width, card_height, card_bits[CodeCarte[Code]], &ImCarte);
	  ajout_image_rouge(FenetreParDefaut, ImCarte, x, y, card_width, card_height);
	}
    }
}

void AfficherTasVide(Localisation L)
{
  XImage ImCarte;

  CreerImage(vide_width, vide_height, vide_bits, &ImCarte);
  ajout_image_noire(FenetreParDefaut, ImCarte, EspX*(L.NC-1), EspY*(L.NL-1), vide_width, vide_height);
}

void AfficherTas(Tas T, char message[])
{
  int i;
  Localisation L;
  int H;
  
  L.NC = (LaPlace(T)).NC;
  L.NL = (LaPlace(T)).NL;
  
  if (TasVide(T)) {
      AfficherTasVide(L);
      overwrite_gr(FenetreParDefaut, EspX*(L.NC-1), EspY*L.NL+ DecY/2, message);
  } else
    if (TasEmpile(T)) {
      AfficherCarte(CarteSur(T), EspX*(L.NC-1), EspY*(L.NL-1));
      overwrite_gr(FenetreParDefaut,EspX*(L.NC-1), EspY*L.NL+ DecY/2, message);
    } else	/* tas étalé */ {
    	H = LaHauteur(T);
    	for (i = 1; i <= H; i++)
	      AfficherCarte(IemeCarte(T, i), EspX*(L.NC-1), EspY*(L.NL-1) + DecY*(i-1));
    	overwrite_gr(FenetreParDefaut,EspX*(L.NC-1), 350, message);	
   }
}
