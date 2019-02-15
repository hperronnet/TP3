#include "PlatCustom.h"

PlatCustom::PlatCustom(string nom, double prix, double cout, int nbIngredients)
{
	nom_ = nom;
	prix_ = prix;
	cout_ = cout;
	nbIngredients_ = nbIngredients;
}

int PlatCustom::getNbIngredients() const
{
	return nbIngredients_;
}

double PlatCustom::getSupplement() const
{
	return supplement_;
}

void PlatCustom::setNbIngredients(int nIngredients)
{
	nbIngredients_ = nIngredients;
}

double PlatCustom::calculerSupplement() const
{
	return supplement_;
}

ostream & operator<<(ostream & os, const PlatCustom & plat)
{
	os << plat.nom_ << " - " << plat.prix_ << "$ (" << plat.cout_ << "$ pour le restaurant)." <<endl;
	return os;
}
