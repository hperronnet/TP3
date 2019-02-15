#include "ClientRegulier.h"
using namespace std;

ClientRegulier::ClientRegulier() : Client()
{
	//nom_ = "inconnu";
	//prenom_ = "inconnu";
	//statut_ = Occasionnel;
	//tailleGroupe_ = 0;
	nbPoints_ = 0;
}

ClientRegulier::ClientRegulier(string nom, string prenom, int tailleGroupe, int nbPoints) : Client(nom, prenom,tailleGroupe)
{
	//nom_ = nom;
	//prenom_ = prenom;
	//tailleGroupe_ = tailleGroupe;
	statut_ = Occasionnel;
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
	os << client.getNom() << " " << client.getPrenom() << " statut :"<< client.getStatut() << "Possede " << client.getNbPoints() << "Points."<< endl;
	return os;
}
