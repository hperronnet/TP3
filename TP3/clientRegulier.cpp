#include "ClientRegulier.h"
using namespace std;

ClientRegulier::ClientRegulier()
{
	nom_ = "inconnu";
	prenom_ = "inconnu";
	statut_ = Occasionnel;
	tailleGroupe_ = 0;
	nbPoints_ = 0;

}

ClientRegulier::ClientRegulier(string nom, string prenom, int tailleGroupe, int nbPoints)
{
	nom_ = nom;
	prenom_ = prenom;
	statut_ = Occasionnel;
	tailleGroupe_ = tailleGroupe;
	nbPoints_ = nbPoints;
}

int ClientRegulier::getNbPoints()
{
	return nbPoints_;
}

void ClientRegulier::augmenterNbPoints(int bonus)
{
	nbPoints_ += bonus;
}

ostream & operator<<(ostream & os, const ClientRegulier & client)
{
	os << client.getNom  << " " << client.getPrenom << " statut :"<< client.getStatut << "Possede " << client.getNbPoints << "Points."<< endl;
}
