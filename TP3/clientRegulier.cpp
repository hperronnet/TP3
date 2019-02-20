#include "ClientRegulier.h"
using namespace std;

//Constructeur par d�faut
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
* augmenterNbPoints : augmente le nombre de points d'un client r�gulier/fidele
* \param le nombre de points � ajouter au client
*/
void ClientRegulier::augmenterNbPoints(int bonus)
{
	nbPoints_ += bonus;
}

/*
* Op�rateur d'affichage
* \param le clientRegulier � afficher et l'os
* \return os (ce qui est � afficher)
*/
ostream & operator<<(ostream & os, const ClientRegulier & client)
{
	os << client.getNom() << "  " << client.getPrenom() << " - Statut : Regulier." << " Possede " << client.getNbPoints() << " points."<< endl;
	return os;
}
