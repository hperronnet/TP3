#include "ClientPrestige.h"

ClientPrestige::ClientPrestige() : ClientRegulier()
{
	addresse_ = Zone3;
}

ClientPrestige::ClientPrestige(string nom, string prenom, int tailleGroupe, int nbPoints, AddressCode addresse) : ClientRegulier(nom, prenom, tailleGroupe, nbPoints)
{
	addresse_ = addresse;
}

AddressCode ClientPrestige::getAddresseCode()
{
	return addresse_;
}

string ClientPrestige::getAddressCodeString()
{
	switch (addresse_)
	{
	case Zone1:
		return "Zone1";
	case Zone2:
		return "Zone 2";
	case Zone3:
		return "Zone 3";
	default:
		break;
	}
}

ostream & operator<<(ostream & os, ClientPrestige client)
{
	os << client.getNom() << " " << client.getPrenom() << " - Satut : Prestige." << "Possède " << client.getNbPoints() << " points." << endl;
	return os;
}
