/*
* Titre : PPlatBio.cpp - Travail Pratique #3
* Date : 24 Février 2019
* Auteurs : Hugo Perronnet 1885263 - Philippe Maisonneuve 1959052
*/


#include "PlatBio.h"

//Constructeur
PlatBio::PlatBio(string nom, double prix, double cout, double ecotaxe) : Plat(nom,prix,cout), ecoTaxe_(ecotaxe)
{
	type_ = Bio;
}

//gettrer
double PlatBio::getEcoTaxe() const
{
	return ecoTaxe_;
}

//setter
void PlatBio::setEcoTaxe(double ecoTaxe)
{
	ecoTaxe_ = ecoTaxe;
}

/*
* Opérateur d'affichage
* \param le platBio à afficher et l'os
* \return os (ce qui est à afficher)
*/
ostream & operator<<(ostream & os, const PlatBio & plat)
{
	// TODO: insérer une instruction return ici
	os << static_cast<Plat>(plat) << "Comprend une taxe ecologique de : " << plat.ecoTaxe_ << " $."<< endl;
	return os;
}
