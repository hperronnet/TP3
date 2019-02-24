/*
* Titre : PlatCustom.cpp - Travail Pratique #3
* Date : 24 F�vrier 2019
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
* Calcul le supplement du prix en fonction du nombre d'ingr�dients rajout�s et des frais par ingr�dient
*/
double PlatCustom::calculerSupplement() const
{
	return nbIngredients_*FRAIS_CUSTOMISATION;
}

/*
* Op�rateur d'affichage
* \param le plat � afficher et l'os
* \return os (ce qui est � afficher)
*/
ostream & operator<<(ostream & os, const PlatCustom & plat)
{
	os << static_cast<Plat>(plat) <<  "Contient " << plat.getNbIngredients() << " elements modifies pour un total de " << plat.getSupplement() << " $." << endl;
	return os;
}
