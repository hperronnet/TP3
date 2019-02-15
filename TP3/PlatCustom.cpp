#include "PlatCustom.h"

PlatCustom::PlatCustom(string nom, double prix, double cout, int nbIngredients) : nbIngredients_(nbIngredients)
{
	nom_ = nom;
	prix_ = prix;
	cout_ = cout;
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
	os << "Contient " << plat.getNbIngredients() << " éléments modifiés pour un total de " << plat.getSupplement << " $." << endl;
	return os;
}
