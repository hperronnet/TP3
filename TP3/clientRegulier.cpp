#include "ClientRegulier.h"
using namespace std;

ClientRegulier::ClientRegulier() : Client()
{
	statut_ = Fidele;
	nbPoints_ = 0;
}

ClientRegulier::ClientRegulier(string nom, string prenom, int tailleGroupe, int nbPoints) : Client(nom, prenom,tailleGroupe)
{
	//nom_ = nom;
	//prenom_ = prenom;
	//tailleGroupe_ = tailleGroupe;
	statut_ = Fidele;
	nbPoints_ = nbPoints;
}

int ClientRegulier::getNbPoints() const
{
	return nbPoints_;
}

void ClientRegulier::augmenterNbPoints(int bonus)
{
	nbPoints_ += bonus;
}

ostream & operator<<(ostream & os, const ClientRegulier & client)
{
	os << client.getNom() << "  " << client.getPrenom() << " - Statut : Regulier." << " Possede " << client.getNbPoints() << " points."<< endl;
	return os;
}
