#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
const  char typejoueur1[] = "humain";
const char typejoueur2[] = "IA";
const int nombrejoueur = 4;
const int nombrecartepaquet = 32;
const int carteparjoueur = 8;
const int taillecartedutourjouer = 4;

const char* TabValeur[] = { "7", "8", "9", "10", "valet", "dame", "roi", "As" };
const char* TabCouleur[] = { "trefle", "pique", "coeur", "carreau" };

typedef struct _CARTE_ {
	int valeur;
	int couleur;

} CARTE;

CARTE* InitialiserTableau(CARTE* Jeuxdecarte, int nb)
{
	for (int i = 0; i < nb; i++)
	{
		Jeuxdecarte[i].valeur = 0;
		Jeuxdecarte[i].couleur = 0;
	}
	return Jeuxdecarte;
}

CARTE JouerIA(CARTE* carteIA, int compteurtour)
{
	int i;
	CARTE cartejouerIA = { 0,0 };
	CARTE max = { 0,0 };
	for (i = 0; i < carteparjoueur - compteurtour; i++)
	{
		if (carteIA[i].valeur > max.valeur)
		{
			max.valeur = carteIA[i].valeur;

		}
	}
	printf("L'IA a choisie de jouer la carte %s de %s\n", TabValeur[max.valeur], TabCouleur[max.couleur]);
	for (int i = 0; i < carteparjoueur - compteurtour; i++)
	{
		if (carteIA[i].valeur == max.valeur && carteIA[i].couleur == max.couleur)
		{
			while (i < carteparjoueur - compteurtour)
			{
				carteIA[i] = carteIA[i + 1];
				i++;
			}
			break;
		}
	}
	
	return max;
}




// La fonction Initialiser prend un tableau vide pour le remplir de carte. La fonction retourne le tableau de carte, alias le jeux de carte,  initialisée.
void InitialiserJeux(CARTE* jeuxdecarte)
{
	int val, coul, i;;
	i = 0;
	for (coul = 0; coul < nombrejoueur; coul++)
	{
		for (val = 0; val < carteparjoueur; val++)
		{
			jeuxdecarte[i].valeur = val;
			jeuxdecarte[i].couleur = coul;
			printf(" %d -- %s de %s \n", i, TabValeur[jeuxdecarte[i].valeur], TabCouleur[jeuxdecarte[i].couleur]);
			i++;

		}
	}
}

// La fonction melanger prend un jeu de carte ordonné de manière croissante (pCarte) et renvoie un paquet qui est une permutation aleatoire du paquet en entré  
void Melanger(CARTE* pCarte)
{
	for (int iCarte = (nombrecartepaquet - 1); iCarte >= 0; --iCarte)
	{
		int jCarte = rand() % (iCarte + 1);
		CARTE temp = pCarte[iCarte];
		pCarte[iCarte] = pCarte[jCarte];
		pCarte[jCarte] = temp;

	}
}

CARTE** allouerJeuDeCarteParjoueur() {
	CARTE** jeuJoueurs = malloc(nombrejoueur * sizeof(CARTE*));
	for (int i = 0; i < nombrejoueur; i++) {
		jeuJoueurs[i] = (CARTE*)malloc(carteparjoueur * sizeof(CARTE));
	}
	return jeuJoueurs;
}

// La fonction DistribuerCarteParJoueur prend un jeux de carte mélangé (jeux) et un tableau de carte par joueur vide (Cartejoueur) et renvoie le tableau de carte par joueur remplie avec les élément du jeux de carte mélangée (jeux).
CARTE** DistribuerCarteParJoueur(CARTE* jeux, CARTE** Cartejoueur)
{
	int i, j, m;
	m = 0;
	for (i = 0; i < nombrejoueur; i++)
	{
		for (j = 0; j < carteparjoueur; j++)
		{
			Cartejoueur[i][j] = jeux[m];
			//(Cartejoueur[i][j]).valeur = (jeux[m]).valeur;
			//(Cartejoueur[i][j]).couleur = (jeux[m]).couleur;
			printf("joueur %d carte numero %d = %s de %s \n", i, j, TabValeur[(Cartejoueur[i][j]).valeur], TabCouleur[(Cartejoueur[i][j]).couleur]);
			m++;
		}
	}
	return Cartejoueur;
}

CARTE** Distribuer()
{
	CARTE* Jeuxdecarte = (CARTE*)malloc(nombrecartepaquet * sizeof(CARTE));
	InitialiserJeux(Jeuxdecarte);
	Melanger(Jeuxdecarte);
	CARTE** JeuxJoueur = allouerJeuDeCarteParjoueur();
	DistribuerCarteParJoueur(Jeuxdecarte, JeuxJoueur);
	return JeuxJoueur;
}

// LA fonction TranformationCarteparjoueurEnCartedunjoueur prend les jeux de cartes des joueurs regroupées dans un tableau pour retournée un jeux de carte individuelle.
CARTE* TranformationCarteparjoueurEnCartedunjoueur(CARTE** Carteparjoueur, int numerojoueur)
{
	CARTE* Jeuxdunjoueur = malloc(carteparjoueur * sizeof(CARTE*));
	Jeuxdunjoueur = InitialiserTableau(Jeuxdunjoueur, carteparjoueur);
	for (int i = 0; i < carteparjoueur; i++)
	{
		Jeuxdunjoueur[i] = Carteparjoueur[numerojoueur][i];
	}
	return Jeuxdunjoueur;
}

CARTE JouerUneCarte(CARTE* cartedujoueur, CARTE cartechoisie, int compteurtour)
{
	printf("Vous jouez la carte qui a pour valeur %s de %s\n", TabValeur[cartechoisie.valeur], TabCouleur[cartechoisie.couleur]);
	printf("Il vous reste maintenant les carte suivant\n");
	for (int i = 0; i < carteparjoueur-compteurtour; i++)
	{
		if (cartedujoueur[i].valeur == cartechoisie.valeur && cartedujoueur[i].couleur == cartechoisie.couleur)
		{
			while (i < carteparjoueur - compteurtour)
			{
				cartedujoueur[i] = cartedujoueur[i + 1];
				i++;
			}
			break;
		}
	}

	for (int i = 0; i < carteparjoueur - compteurtour - 1; i++)
		printf(" %d -- %s de %s \n", i, TabValeur[cartedujoueur[i].valeur], TabCouleur[cartedujoueur[i].couleur]);
	CARTE cartejouer = cartechoisie;
	return cartejouer;


}
CARTE ChoisirUneCarte(CARTE* cartedujoueur, int compteurtour)
{
	CARTE cartechoisi = { 0,0 };
	int i;
	printf("Choisissez la carte que vous voulez jouer en tapant le numero de la carte:\n");
	for (i = 0; i < carteparjoueur - compteurtour; i++)
	{

		printf("Voici la carte %d qui a pour valeur %s de %s\n", i, TabValeur[cartedujoueur[i].valeur], TabCouleur[cartedujoueur[i].couleur]);

	}
	scanf("%d", &i);
	while (i < 0 || i >= carteparjoueur - compteurtour)
	{
		printf("Cette carte n'existe pas, choisissez un autre numero :\n");
		scanf("%d", &i);
	}

	printf("Vous avez choisi la carte numero %d qui a pour valeur %s de %s\n", i, TabValeur[cartedujoueur[i].valeur], TabCouleur[cartedujoueur[i].couleur]);
	cartechoisi = cartedujoueur[i];
	return cartechoisi;
}

CARTE JouerHumain(CARTE* cartedujoueur, int compteurtour)
{
	CARTE cartechoisi = { 0,0 };
	CARTE cartejouer;
	cartechoisi = ChoisirUneCarte(cartedujoueur, compteurtour);
	cartejouer = JouerUneCarte(cartedujoueur, cartechoisi, compteurtour);
	return cartejouer;
}

const char* TesterTypeJoueur()
{
	const char* typedujoueur;
	int reponse;
	printf("Es-tu un humain ? (1 pour oui 0 pour non)\n");
	scanf("%d", &reponse);
	if (reponse == 1)
	{
		typedujoueur = typejoueur1;
	}
	else
	{
		typedujoueur = typejoueur2;
	}
	printf("Vous etes donc du type %s\n", typedujoueur);
	return typedujoueur;
}


void AjouterCarteAuTourCourant(CARTE cartejouer, CARTE* cartedutourjouer, int nombrecartejouer)
{
	cartedutourjouer[nombrecartejouer].valeur = cartejouer.valeur;
	cartedutourjouer[nombrecartejouer].couleur = cartejouer.couleur;
}

int CompterResultatDuTour(CARTE* cartedutourjouer, int nombrecartejouer, int* compteurjoueur)
{
	int gagnant = 1;
	CARTE max = { 0,0 };
	int i;
	for (i = 0; i < nombrecartejouer; i++)
	{
		if (cartedutourjouer[i].valeur > max.valeur && cartedutourjouer[i].couleur > max.couleur)
		{
			max.valeur = cartedutourjouer[i].valeur;
			max.couleur = cartedutourjouer[i].couleur;

		}
	}
	printf(" max = %s de %s\n", TabValeur[max.valeur], TabCouleur[max.couleur]);
	for (int i = 0; i < nombrecartejouer; i++)
	{
		for (int j = i + 1; j < nombrecartejouer; j++)
		{
			if (cartedutourjouer[i].valeur == cartedutourjouer[j++].valeur && cartedutourjouer[i].couleur == cartedutourjouer[j++].couleur && max.valeur <= cartedutourjouer[i].valeur && max.couleur == cartedutourjouer[i].couleur)
			{
				gagnant = 0;
				break;
			}
		}
	}
	switch (gagnant)
	{
	case 0:
		printf("Il n'y a pas de gagnant pour le moment le jeux continue jusqu'a ce qu'il y en ai un\n");
		return gagnant;
		break;
	case 1:
		if (max.valeur == cartedutourjouer[0].valeur && max.couleur == cartedutourjouer[0].couleur)
		{
			compteurjoueur[0]++;
			printf("Le joueur humain a pour scores : %d\n", compteurjoueur[0]);

		}
		else if (max.valeur == cartedutourjouer[1].valeur && max.couleur == cartedutourjouer[1].couleur)
		{
			compteurjoueur[1]++;
			printf("Le joueur IA1 a pour scores : %d\n", compteurjoueur[1]);

		}
		else if (max.valeur == cartedutourjouer[2].valeur && max.couleur == cartedutourjouer[2].couleur)
		{
			compteurjoueur[2]++;
			printf("Le joueur IA2 a pour scores : %d\n", compteurjoueur[2]);

		}
		else if (max.valeur == cartedutourjouer[3].valeur && max.couleur == cartedutourjouer[3].couleur)
		{
			compteurjoueur[3]++;
			printf("Le joueur IA3 a pour scores : %d\n", compteurjoueur[3]);

		}
		return 0;
		break;
	}
	return gagnant;

}


// La fonction JouerUnJoueur prend les carte d'un joueur et retourne la carte jouée.
void JouerUnJoueurHumain(CARTE* Cartehumain, CARTE* cartedutourjouer, int nombrecartejouer, int compteurtour)
{
	CARTE cartejouer = { 0,0 };
	cartejouer = JouerHumain(Cartehumain, compteurtour);
	AjouterCarteAuTourCourant(cartejouer, cartedutourjouer, nombrecartejouer);
	
}

void JouerUnJoueurIA(CARTE* CarteIA, CARTE* cartedutourjouer, int compteurtour, int nombrecartejouer)
{
	CARTE cartejouerIA = { 0,0 };
	cartejouerIA = JouerIA(CarteIA, compteurtour);
	AjouterCarteAuTourCourant(cartejouerIA, cartedutourjouer, nombrecartejouer);
}


void JouerUnTour(CARTE* Joueurhumain, CARTE* JoueurIA1, CARTE* JoueurIA2, CARTE* JoueurIA3, int* compteurjoueur, int compteurtour)
{
	int gagnanttour = 0;
	CARTE* cartedutourjouer = malloc(taillecartedutourjouer * sizeof(CARTE));
	cartedutourjouer = InitialiserTableau(cartedutourjouer, taillecartedutourjouer);
	int nombrecartejouer = 0;
	JouerUnJoueurHumain(Joueurhumain, cartedutourjouer, nombrecartejouer, compteurtour);
	nombrecartejouer++;
	printf("\n");
	JouerUnJoueurIA(JoueurIA1, cartedutourjouer, nombrecartejouer, compteurtour);
	nombrecartejouer++;
	printf("\n");
	JouerUnJoueurIA(JoueurIA2, cartedutourjouer, nombrecartejouer, compteurtour);
	nombrecartejouer++;
	printf("\n");
	JouerUnJoueurIA(JoueurIA3, cartedutourjouer, nombrecartejouer, compteurtour);
	nombrecartejouer++;
	printf("\n");
	gagnanttour = CompterResultatDuTour(cartedutourjouer, nombrecartejouer, compteurjoueur);
}

void JouerUnePartie()
{
	int compteurjoueur[4] = { 0 };
	CARTE** Jeuxjoueur;
	Jeuxjoueur = Distribuer();
	CARTE* Joueurhumain0 = malloc(carteparjoueur * sizeof(CARTE*));
	CARTE* JoueurIA1 = malloc(carteparjoueur * sizeof(CARTE*));
	CARTE* JoueurIA2 = malloc(carteparjoueur * sizeof(CARTE*));
	CARTE* JoueurIA3 = malloc(carteparjoueur * sizeof(CARTE*));
	int joueurhumain = 0;
	int joueurIA1 = 1;
	int joueurIA2 = 2;
	int joueurIA3 = 3;
	Joueurhumain0 = TranformationCarteparjoueurEnCartedunjoueur(Jeuxjoueur, joueurhumain);
	JoueurIA1 = TranformationCarteparjoueurEnCartedunjoueur(Jeuxjoueur, joueurIA1);
	for (int i = 0; i < carteparjoueur; i++)
	{
		printf("IA1 %d -- %s de %s \n", i, TabValeur[JoueurIA1[i].valeur], TabCouleur[JoueurIA1[i].couleur]);
	}
	printf("\n");
	JoueurIA2 = TranformationCarteparjoueurEnCartedunjoueur(Jeuxjoueur, joueurIA2);
	for (int i = 0; i < carteparjoueur; i++)
	{
		printf("IA2 %d -- %s de %s \n", i, TabValeur[JoueurIA2[i].valeur], TabCouleur[JoueurIA2[i].couleur]);
	}
	printf("\n");
	JoueurIA3 = TranformationCarteparjoueurEnCartedunjoueur(Jeuxjoueur, joueurIA3);
	for (int i = 0; i < carteparjoueur; i++)
	{
		printf("IA3 %d -- %s de %s \n", i, TabValeur[JoueurIA3[i].valeur], TabCouleur[JoueurIA3[i].couleur]);
	}
	int compteurtour = 0;
	for (int i = 0; i < carteparjoueur; i++)
	{
		JouerUnTour(Joueurhumain0, JoueurIA1, JoueurIA2, JoueurIA3, compteurjoueur, compteurtour);
		compteurtour++;
	}
	
}




int main()
{
	JouerUnePartie();

	




	//	int compteurjoueur[4] = { 0 };
	//	for (int i = 0; i < 4; i++)
	//	{
	//		printf("%d\n", compteurjoueur[i]);
	//	}
	//	int cartedutourjouer[4] = { 2,2,3,4 };
	//	for (int i = 0; i < 4; i++)
	//	{
	//		printf("%d\n", cartedutourjouer[i]);
	//	}
	//	 //int nombrecartejouer = 0;
	//	// initialisertour(cartedutourjouer);
	//	 //testertypejoueur();
	//	/*int mescarte[4]={1,2,3,4};
	//	int cartejouer;
	//	cartejouer=jouerhumain(mescarte, nombrecarte);*/
	//	/*nombrecartejouer=AjouterCarteAuTourCourant(cartejouer, cartedutourjouer, nombrecartejouer);*/
	//	int nombrecarte = 4;
	//    CompterResultatDuTour(cartedutourjouer, nombrecarte, compteurjoueur);
	//	for (int i = 0; i < 4; i++)
	//    {
	//	    printf("%d\n", compteurjoueur[i]);
	//	}
	//
}
