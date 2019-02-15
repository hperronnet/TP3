#include "Client.h"

Client::Client()
{
	nom_ = "inconnu";
	prenom_ = "inconnu";
	statut_ = Occasionnel;
	tailleGroupe_ = 0;
}

Client::Client(string nom, string prenom, int tailleGroupe) : nom_(nom), prenom_(prenom), tailleGroupe_(tailleGroupe)
{
}

Client::~Client()
{
}

StatutClient Client::getStatut()
{
	return statut_;
}

int Client::getTailleGroupe()
{
	return tailleGroupe_;
}

string Client::getNom()
{
	return nom_;
}

string Client::getPrenom()
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
		break;
	}
}

ostream & operator<<(ostream & os, const Client & client)
{
	os << " - " << client.nom_ << " " << client.prenom_ << ". Statut : " << client.convertirStatutString();
	return os;
}
