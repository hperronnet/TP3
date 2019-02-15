#include "PlatBio.h"

PlatBio::PlatBio(string nom, double prix, double cout, double ecotaxe) : ecoTaxe_(ecotaxe)
{
	//nom_ = nom;
	//prix_ = prix;
	//cout_ = cout;
	ecoTaxe_ = ecotaxe;
}

double PlatBio::getEcoTaxe() const
{
	return ecoTaxe_;
}

void PlatBio::setEcoTaxe(double ecoTaxe)
{
	ecoTaxe_ = ecoTaxe;
}

ostream & operator<<(ostream & os, const PlatBio & plat)
{
	// TODO: insérer une instruction return ici
	os << plat << endl  << "Comprend une taxe écologique de :" << plat.getEcoTaxe();
}
