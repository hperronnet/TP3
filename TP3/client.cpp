#include "Client.h"

Client::Client()
{
	nom_ = "inconnu";
	prenom_ = "inconnu";
	statut_ = Occasionnel;
	tailleGroupe_ = 1;
}

Client::Client(string nom, string prenom, int tailleGroupe) : nom_(nom), prenom_(prenom), tailleGroupe_(tailleGroupe)
{
	statut_ = Occasionnel;
}

Client::~Client()
{
}

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

ostream & operator<<(ostream & os, const Client & client)
{
	os << " - " << client.nom_ << " " << client.prenom_ << ". Statut : " << client.convertirStatutString() << "." << endl;
	return os;
}
