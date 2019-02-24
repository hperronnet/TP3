/*
* Titre : clientRegulier.cpp - Travail Pratique #3
* Date : 24 Février 2019
* Auteurs : Hugo Perronnet 1885263 - Philippe Maisonneuve 1959052
*/



#include "ClientRegulier.h"
using namespace std;

//Constructeur par défaut
ClientRegulier::ClientRegulier() : Client()
{
	statut_ = Fidele;
	nbPoints_ = 0;
}

//Constructeur
ClientRegulier::ClientRegulier(string nom, string prenom, int tailleGroupe, int nbPoints) : Client(nom, prenom,tailleGroupe)
{
	statut_ = Fidele;
	nbPoints_ = nbPoints;
}

//Getter
int ClientRegulier::getNbPoints() const
{
	return nbPoints_;
}

/*
* augmenterNbPoints : augmente le nombre de points d'un client régulier/fidele
* \param le nombre de points à ajouter au client
*/
void ClientRegulier::augmenterNbPoints(int bonus)
{
	nbPoints_ += bonus;
}

/*
* Opérateur d'affichage
* \param le clientRegulier à afficher et l'os
* \return os (ce qui est à afficher)
*/
ostream & operator<<(ostream & os, const ClientRegulier & client)
{
	os << client.getNom() << "  " << client.getPrenom() << " - Statut : Regulier." << " Possede " << client.getNbPoints() << " points."<< endl;
	return os;
}
