#include "Client.h"

//Constructeur par d�faut
Client::Client()
{
	nom_ = "inconnu";
	prenom_ = "inconnu";
	statut_ = Occasionnel;
	tailleGroupe_ = 1;
}

//Constructeur par copie
Client::Client(string nom, string prenom, int tailleGroupe) : nom_(nom), prenom_(prenom), tailleGroupe_(tailleGroupe)
{
	statut_ = Occasionnel;
}

//destructeur
Client::~Client()
{
}

//Getters
StatutClient Client::getStatut() const
{
	return statut_;
}

int Client::getTailleGroupe() const
{
	return tailleGroupe_;
}

string Client::getNom() const
{
	return nom_;
}

string Client::getPrenom() const
{
	return prenom_;
}

/*
* convertirStatutString : convertit le statut d'un client (enum) en string associ� pour faciliter l'affichage
* \return le statut convertit en string
*/
string Client::convertirStatutString() const
{
	switch (statut_)
	{
	case Occasionnel:
		return "Occasionnel";
	case Fidele:
		return "Fidele";
	case Prestige:
		return "Prestige";
	default:
		return "";
	}
}

/*
* Op�rateur d'affichage
* \param le client � afficher et l'os
* \return os (ce qui est � afficher)
*/
ostream & operator<<(ostream & os, const Client & client)
{
	os << " - " << client.nom_ << " " << client.prenom_ << ". Statut : " << client.convertirStatutString() << "." << endl;
	return os;
}
