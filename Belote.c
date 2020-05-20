#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
const  char typejoueur1[] = "humain";
const char typejoueur2[] = "IA";
const int nombrejoueur = 4;
const int nombrecartepaquet = 32;
const int carteparjoueur = 8;


const char* TabValeur[] = { "6", "7", "8", "9", "10", "valet", "dame", "roi" };
const char* TabCouleur[] = { "trefle", "carreau", "coeur", "pique" };

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

CARTE JouerUneCarte(CARTE* cartedujoueur, CARTE cartechoisie)
{
	printf("Vous jouez la carte qui a pour valeur %s de %s\n", TabValeur[cartechoisie.valeur], TabCouleur[cartechoisie.couleur]);
	printf("Il vous reste maintenant les carte suivant\n");
	for (int i = 0; i < carteparjoueur; i++)
	{
		if (cartedujoueur[i].valeur == cartechoisie.valeur && cartedujoueur[i].couleur == cartechoisie.couleur)
		{
			for (int j = i; j < carteparjoueur; j++)
			{
				if (j < carteparjoueur - 1)
				{
					cartedujoueur[j] = cartedujoueur[j + 1];
				}

			}
		}
	}

	for (int i = 0; i < carteparjoueur - 1; i++)
		printf(" %d -- %s de %s \n", i, TabValeur[cartedujoueur[i].valeur], TabCouleur[cartedujoueur[i].couleur]);
	CARTE cartejouer = cartechoisie;
	return cartejouer;


}
CARTE ChoisirUneCarte(CARTE* cartedujoueur)
{
	CARTE cartechoisi = { 0,0 };
	int i;
	printf("Choisissez la carte que vous voulez jouer en tapant le numero de la carte:\n");
	for (i = 0; i < carteparjoueur; i++)
	{

		printf("Voici la carte %d qui a pour valeur %s de %s\n", i, TabValeur[cartedujoueur[i].valeur], TabCouleur[cartedujoueur[i].couleur]);

	}
	scanf("%d", &i);
	while (i < 0 || i >= carteparjoueur)
	{
		printf("Cette carte n'existe pas, choisissez un autre numero :\n");
		scanf("%d", &i);
	}

	printf("Vous avez choisi la carte numero %d qui a pour valeur %s de %s\n", i, TabValeur[cartedujoueur[i].valeur], TabCouleur[cartedujoueur[i].couleur]);
	cartechoisi = cartedujoueur[i];
	return cartechoisi;
}

CARTE JouerHumain(CARTE* cartedujoueur)
{
	CARTE cartechoisi = { 0,0 };
	CARTE cartejouer;
	cartechoisi = ChoisirUneCarte(cartedujoueur);
	cartejouer = JouerUneCarte(cartedujoueur, cartechoisi);
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


int AjouterCarteAuTourCourant(CARTE cartejouer, CARTE* cartedutourjouer, int nombrecartejouer)
{
	cartedutourjouer[nombrecartejouer].valeur = cartejouer.valeur;
	cartedutourjouer[nombrecartejouer].couleur = cartejouer.couleur;
	nombrecartejouer = nombrecartejouer + 1;
	return nombrecartejouer;
}

int CompterResultatDuTour(int* cartedutourjouer, int nombrecartejouer, int* compteurjoueur)
{
	int gagnant = 1;
	int max = 0;
	int i;
	for (i = 0; i < nombrecartejouer; i++)
	{
		if (cartedutourjouer[i] > max)
		{
			max = cartedutourjouer[i];

		}
	}
	printf(" max = %d\n", max);
	for (int i = 0; i < nombrecartejouer; i++)
	{
		for (int j = i + 1; j < nombrecartejouer; j++)
		{
			if (cartedutourjouer[i] == cartedutourjouer[j++] && max <= cartedutourjouer[i])
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
		if (max == cartedutourjouer[0])
		{
			compteurjoueur[0]++;
			printf("Le joueur 1 a pour scores : %d\n", compteurjoueur[0]);

		}
		else if (max == cartedutourjouer[1])
		{
			compteurjoueur[1]++;
			printf("Le joueur 2 a pour scores : %d\n", compteurjoueur[1]);

		}
		else if (max == cartedutourjouer[2])
		{
			compteurjoueur[2]++;
			printf("Le joueur 3 a pour scores : %d\n", compteurjoueur[2]);

		}
		else if (max == cartedutourjouer[3])
		{
			compteurjoueur[3]++;
			printf("Le joueur 4 a pour scores : %d\n", compteurjoueur[3]);

		}
		return 0;
		break;
	}
	return 0;

}

// La fonction JouerUnJoueur prend les carte d'un joueur et retourne la carte jouée.
void JouerUnJoueur(CARTE* Cartedujoueur, CARTE* cartedutourjouer, int nombrecartejouer)
{
	CARTE cartejouer = { 0,0 };
	const char* naturejoueur = TesterTypeJoueur();
	if (naturejoueur == typejoueur1)
	{
		cartejouer = JouerHumain(Cartedujoueur);
		nombrecartejouer = AjouterCarteAuTourCourant(cartejouer, cartedutourjouer, nombrecartejouer);


	}

}



int main()
{
	CARTE** Jeuxjoueur;
	Jeuxjoueur = Distribuer();
	CARTE* Joueur0 = malloc(carteparjoueur * sizeof(CARTE*));
	int joueurnumero0 = 0;
	Joueur0 = TranformationCarteparjoueurEnCartedunjoueur(Jeuxjoueur, joueurnumero0);
	
	int nombrecartejouer = 0;
	CARTE* cartedutourjouer = malloc(nombrecartejouer * sizeof(CARTE*));
	cartedutourjouer = InitialiserTableau(cartedutourjouer, nombrecartejouer);
	JouerUnJoueur(Joueur0, cartedutourjouer, nombrecartejouer);




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
