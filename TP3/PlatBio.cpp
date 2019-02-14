#include "PlatBio.h"

PlatBio::PlatBio(string nom, double prix, double cout, double ecotaxe)
{
	nom_ = nom;

}

double PlatBio::getEcoTaxe() const
{
	return 0.0;
}

void PlatBio::setEcoTaxe(double ecoTaxe)
{
}

ostream & operator<<(ostream & os, const PlatBio & plat)
{
	// TODO: insérer une instruction return ici
}
