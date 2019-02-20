/*
* Titre : Menu.cpp - Travail Pratique #3
* Date : 11 Février 2019
* Auteur : Fatou S Mounzeo
*/

#include "Menu.h"

//constructeurs 
Menu::Menu() {
	type_ = Matin; 
}

Menu::Menu(string fichier, TypeMenu type) {
	type_ = type; 

	//lecture du fichier -- creation du menu
	lireMenu(fichier); 
}

//Constructeur par copie
Menu::Menu(const Menu & menu): type_(menu.type_)
{
	for (unsigned i = 0; i < menu.listePlats_.size(); ++i)
	{
		if (menu.listePlats_[i]->getType() == Regulier) {
			listePlats_.push_back(new Plat(*menu.listePlats_[i]));
		}

		else {
			PlatBio* platBio = static_cast<PlatBio*>(menu.listePlats_[i]);
			listePlats_.push_back(new PlatBio(*platBio));
		}


	}

}

//Destructeur
Menu::~Menu() {
	for (unsigned i = 0; i < listePlats_.size(); i++)
		delete listePlats_[i];
}

//getters
vector<Plat*> Menu::getListePlats() const
{
	return listePlats_;
}

//autres methodes 

/*
* Opérateur d'affichage
* \param le menu à afficher et l'os
* \return os (ce qui est à afficher)
*/
ostream& operator<<(ostream& os, const Menu& menu)
{
	for (unsigned i = 0; i < menu.listePlats_.size(); ++i) {
		
		if (menu.listePlats_[i]->getType() == Regulier)
			os << "\t" << *menu.listePlats_[i];

		else if (menu.listePlats_[i]->getType() == Bio) {
			PlatBio* platBio = static_cast<PlatBio*>(menu.listePlats_[i]);
			os << "\t" << *platBio;
		}
		else if (menu.listePlats_[i]->getType() == Custom) {
			PlatCustom* platCustom = static_cast<PlatCustom*>(menu.listePlats_[i]);
			os << "\t" << *platCustom;
		}

	}
	return os;
}

/*
* operateur += : Ajoute un plat à la liste de plats du menu
* \param le plat à ajouter
* \return La liste de plat (le menu)
*/
Menu& Menu::operator+=(const Plat& plat) {
	listePlats_.push_back(new Plat(plat));
	return *this;
}

/*
* operateur += : Ajoute un plat BIO à la liste de plats du menu à l'aide d'un static_cast
* \param le platBio à ajouter
* \return La liste de plat (le menu)
*/
Menu& Menu::operator+=(const PlatBio& plat) {
	listePlats_.push_back(new PlatBio(plat));
	return *this;
}


/*
* operateur = : écrase les attributs du menu par les attributs du menu passé en paramètre
* \param le nouveau menu
* \return une référence au menu.
*/
Menu & Menu::operator=(const Menu & menu)
{
	if (this != &menu)
	{
		this->type_ = menu.type_;
		listePlats_.clear();

		for (unsigned i = 0; i < menu.listePlats_.size(); ++i) {

			if (menu.listePlats_[i]->getType() == Regulier) {
				listePlats_.push_back(new Plat(*menu.listePlats_[i]));

			}
			else {
				PlatBio* platBio = static_cast<PlatBio*>(menu.listePlats_[i]);
				listePlats_.push_back(new Plat(*platBio));
			}
		}
	}
	return *this;
}

/*
* lisreMenu : Lit dans le fichier polyfood.txt et ajoute chacun des plat du menu dans le menu en fonction de sont type (Matin, Midin Soir)
* \param le fichier contenu les menu, les prix, les tables
*/
void Menu::lireMenu(const string& fichier) {
	ifstream file(fichier, ios::in); 

	if (!file) {
		cout << "ERREUR : le fichier n'a pas pu etre ouvert" << endl; 
	}
	else {
		string type; 
		switch (type_) {
		case Matin :
			type = "-MATIN"; 
			break; 
		case Midi : 
			type = "-MIDI";
			break;
		case Soir : 
			type = "-SOIR"; 
			break;
		}
		string ligne; 

		string nom; 
		
		string prixString;
		double prix; 

		string coutString; 
		double cout;

		string typeString;
		int typePlat;

		string ecotaxeString;
		double ecoTaxe;
		// lecture
		while (!file.eof()) {
			std::getline(file, ligne); 
			//trouver le bon type de menu (section)
			if (ligne == type){ 
				//commencer a lire -- s'arrete si fin du fichier ou encore si on arrive a une nouvelle section du menu 
				std::getline(file, ligne);
				int curseur = 0;;
				while (ligne[0] != '-' && !file.eof()) {
					//trouver le nom 
					for (int i = 0; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						nom += ligne[i]; 
					}

					//trouver le type 
					for (int i = curseur + 1; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						typeString += ligne[i];

					}

					typePlat = stoi(typeString);

					//trouver le prix 

					for (int i = curseur + 1; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i; 
							break; 
						}
						prixString += ligne[i]; 
						
					}
					//passer le prixString en double --- indice dans l'enonce 
					prix = stof(prixString.c_str()); 

					for (int i = curseur + 1; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							if (typePlat == Bio)
								curseur = i;
							break;

						}

						coutString += ligne[i]; 
					}

					cout = stod(coutString.c_str()); 

					//lire le taux si plat bio

					if (typePlat == TypePlat::Bio) {

						for (int i = curseur + 1; i < int(ligne.size()); i++) {
							if (ligne[i] == ' ')
								break;
							ecotaxeString += ligne[i];
						}
						ecoTaxe = stod(ecotaxeString);
						*this += PlatBio(nom, prix, cout, ecoTaxe);
					}
					else {
						*this += Plat(nom, prix, cout);
					}

					nom = ""; 
					prixString = ""; 
					coutString = ""; 
					typeString = "";
					ecotaxeString ="";

					std::getline(file, ligne);
				}
			}
		}

		file.close(); 
	}
}

/*
* trouverPlatMoinsCher : parcours le menu et trouve le plat le moins cher pour chaque type de menu (Matin, Midi, Soir)
/ \return le plat le moins cher
*/
Plat * Menu::trouverPlatMoinsCher() const
{
	Plat minimum(*listePlats_[0]);
	int found = -1;

	for (unsigned i = 0; i < listePlats_.size(); ++i)
	{
		if (*listePlats_[i] <= minimum)
		{
			minimum = *listePlats_[i];
			found = i;
		}
	}

	return listePlats_[found];

}

/*
* trouverPlat : trouve un plat dans le menu à partir de son nom
* \param le nom du plat
* \return le plat trouvé, ou nullptr si il n'existe pas ou n'est pas trouvé
*/
Plat* Menu::trouverPlat(const string& nom) const {
	for (int i = 0; i < listePlats_.size(); ++i) {
		if (listePlats_[i]->getNom() == nom)
			return listePlats_[i]; 
	}
	return nullptr; 
}