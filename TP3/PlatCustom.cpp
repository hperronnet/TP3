/*
* Titre : PlatCustom.cpp - Travail Pratique #3
* Date : 24 Février 2019
* Auteurs : Hugo Perronnet 1885263 - Philippe Maisonneuve 1959052
*/


#include "PlatCustom.h"

//Constructeur
PlatCustom::PlatCustom(string nom, double prix, double cout, int nbIngredients) : Plat(nom,prix,cout), nbIngredients_(nbIngredients)
{
	supplement_ = calculerSupplement();
	type_ = Custom;
}

//getters
int PlatCustom::getNbIngredients() const
{
	return nbIngredients_;
}

double PlatCustom::getSupplement() const
{
	return supplement_;
}

//setters
void PlatCustom::setNbIngredients(int nIngredients)
{
	nbIngredients_ = nIngredients;
}

/*
* CalculerSupplement()
* Calcul le supplement du prix en fonction du nombre d'ingrédients rajoutés et des frais par ingrédient
*/
double PlatCustom::calculerSupplement() const
{
	return nbIngredients_*FRAIS_CUSTOMISATION;
}

/*
* Opérateur d'affichage
* \param le plat à afficher et l'os
* \return os (ce qui est à afficher)
*/
ostream & operator<<(ostream & os, const PlatCustom & plat)
{
	os << static_cast<Plat>(plat) <<  "Contient " << plat.getNbIngredients() << " elements modifies pour un total de " << plat.getSupplement() << " $." << endl;
	return os;
}
