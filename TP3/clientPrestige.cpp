#include "ClientPrestige.h"

//Constructeur par défaut
ClientPrestige::ClientPrestige() : ClientRegulier()
{
	addresse_ = Zone3;
	statut_ = Prestige;
}

//Constructeur
ClientPrestige::ClientPrestige(string nom, string prenom, int tailleGroupe, int nbPoints, AddressCode addresse) : ClientRegulier(nom, prenom, tailleGroupe, nbPoints)
{
	addresse_ = addresse;
	statut_ = Prestige;
}

//Getters
AddressCode ClientPrestige::getAddresseCode() const
{
	return addresse_;
}

/*
* getAdressCodeString : convertit l'adressCode d'un client (enum) en string associé pour faciliter l'affichage
* \return le l'adressCode convertit en string
*/
string ClientPrestige::getAddressCodeString()
{
	switch (addresse_)
	{
	case Zone1:
		return "Zone 1";
	case Zone2:
		return "Zone 2";
	case Zone3:
		return "Zone 3";
	default:
		return "";
	}
}

/*
* Opérateur d'affichage
* \param le clientPrestige à afficher et l'os
* \return os (ce qui est à afficher)
*/
ostream & operator<<(ostream & os, ClientPrestige client)
{
	os << client.getNom() << " " << client.getPrenom() << " - Satut : Prestige." << " Possede " << client.getNbPoints() << " points." << endl;
	os << "Habite dans la " << client.getAddressCodeString() << endl;
	return os;
}
