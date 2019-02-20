/*
* Titre : Restaurant.cpp - Travail Pratique #2
* Date : 11 F�vrier 2019
* Auteur : Fatou S. MOUNZEO
*/

#include "Restaurant.h"

//constructeurs 
Restaurant::Restaurant() {
	nom_ = new string("Inconnu"); 

	chiffreAffaire_ = 0; 
	
	momentJournee_ = Matin; 

	menuMatin_ = new Menu("menu.txt", Matin);
	menuMidi_ = new Menu("menu.txt", Midi);
	menuSoir_ = new Menu("menu.txt",  Soir);

}

Restaurant::Restaurant(const string& fichier,  const string& nom, TypeMenu moment) {
	nom_ = new string(nom); 

	chiffreAffaire_ = 0; 

	momentJournee_ = moment; 

	menuMatin_ = new Menu(fichier, Matin);
	menuMidi_ = new Menu(fichier,  Midi);
	menuSoir_ = new Menu(fichier,  Soir);

	lireTable(fichier); 
	lireAdresses(fichier);
}
Restaurant::Restaurant(const Restaurant & restau) : nom_(new string(*restau.nom_)),
chiffreAffaire_(restau.chiffreAffaire_),
momentJournee_(restau.momentJournee_),
menuMatin_(new Menu(*restau.menuMatin_)),
menuMidi_(new Menu(*restau.menuMidi_)),
menuSoir_(new Menu(*restau.menuSoir_))
{
	tables_.clear();
	for (unsigned i = 0; i < restau.tables_.size(); ++i)
		tables_.push_back(new Table(*restau.tables_[i]));
	for (unsigned i = 0; i < NB_ZONES_LIVR; i++) 
		fraisTransport_[i] = restau.getFraisTransports(i);


}
//destructeur 
Restaurant::~Restaurant() {
	delete nom_; 
	delete menuMatin_; 
	delete menuMidi_; 
	delete menuSoir_; 
	for (unsigned i = 0; i < tables_.size(); ++i)
		delete tables_[i];

}

//setter 
void Restaurant::setMoment(TypeMenu moment) {
	momentJournee_ = moment; 
}
void Restaurant::setNom(const string & nom)
{
	nom_ = new string(nom);
}

//getters 
string Restaurant::getNom() const {
	return *nom_; 
}

TypeMenu Restaurant::getMoment() const {
	return momentJournee_; 
}

double Restaurant::getFraisTransports(int index) const
{
	return fraisTransport_[index];
}

/*
*  libererTable : libere une table. calcul la r�duction du client si il y est �ligible.
* \param l'id de la table
*/
void Restaurant::libererTable(int id) 
{
	for (unsigned i = 0; i < tables_.size(); ++i) {
		if (id == tables_[i]->getId()) {
			double prixTable = tables_[i]->getChiffreAffaire();
			Client *client = tables_[i]->getClientPrincipal();
			double reduction = 0.0;
			if (id == INDEX_TABLE_LIVRAISON+1) {
				reduction = calculerReduction(client, prixTable, true);
			}
			else {
				reduction = calculerReduction(client, prixTable, false);
			}

			chiffreAffaire_ += tables_[i]->getChiffreAffaire() + reduction; 
			tables_[i]->libererTable(); 
			break;
		}
	}
}



/*
* Op�rateur d'affichage
* \param le restaurant � afficher et l'os
* \return os (ce qui est � afficher)
*/
ostream& operator<<(ostream& os, const Restaurant& restau)
{
	os << "Le restaurant " << *restau.nom_;
	if (restau.chiffreAffaire_ != 0)
		os << " a fait un chiffre d'affaire de : " << restau.chiffreAffaire_ << "$" << endl;
	else
		os << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;

	os << "-Voici les tables : " << endl;

	for (unsigned i = 0; i < restau.tables_.size(); i++) {
		os  << *restau.tables_[i] << endl;
	}
	os << endl;


	os << "-Voici son menu : " << endl;
	os << "Matin : " << endl
		<<*restau.menuMatin_<<endl << "Le plat le moins cher est : " << *restau.menuMatin_->trouverPlatMoinsCher() << endl;

	os << "Midi : " << endl
		<< *restau.menuMidi_<<endl << "Le plat le moins cher est : " << *restau.menuMidi_->trouverPlatMoinsCher() << endl;
	os << "Soir : " << endl
		<< *restau.menuSoir_<<endl << "Le plat le moins cher est : " << *restau.menuSoir_->trouverPlatMoinsCher() <<endl;


	return os;
}


/*
* commanderPlat : cherche le plat command� avec les ingr�dients en plus ou le type si il y en a puis l'ajoute � la commande
* \param le nom du plat, l'id de la table et (facultatif) le type et le nombre d'ingr�dients en plas
*/
void Restaurant::commanderPlat(const string& nom, int idTable,TypePlat type, int nbIngredients) {

	///TODO
	/// Modifier la fonction pour ajouter des plats customis�s aux commandes
	Plat* plat = nullptr; 
	int index = 0; 
	for (unsigned i = 0; i < tables_.size(); i++) {
		if (idTable == tables_[i]->getId()) {
			index = i; 
			switch (momentJournee_) {
			case Matin :
				plat = menuMatin_->trouverPlat(nom); 
				break; 
			case Midi : 
				plat = menuMidi_->trouverPlat(nom); 
				break; 
			case Soir :
				plat = menuSoir_->trouverPlat(nom); 
				break; 
			}

			break;
		}
	}
	//cout << "debogage:: " << tables_[index]->getClientPrincipal()->getTailleGroupe();
	
	if (plat == nullptr || !tables_[index]->estOccupee()) {

		cout << "Erreur : table vide ou plat introuvable" << endl << endl;
	}
	else
	{
		if (type == Custom) {
			PlatCustom* custom = new PlatCustom(plat->getNom(), plat->getPrix(), plat->getCout(), nbIngredients);
			//PlatCustom* custom = static_cast<PlatCustom*>(plat);
			tables_[index]->commander(custom);
		}
		else {
			tables_[index]->commander(plat);
		}

	}

 
}


/*
* operateur = : �crase les attributs du restaurant par les attributs du restaurant pass� en param�tre
* \param le nouveau menu
* \return une r�f�rence au menu.
*/
bool Restaurant::operator<(const Restaurant & restau) const 
{
	return this->chiffreAffaire_ < restau.chiffreAffaire_;
}

/*
* operateur = :
* \param le restaurant � comparer au celui actuel
* \return Vrai si le chiffre d'affaire du restaurant est inf�rieur � celui du restaurant pass� en param�rte
*/
Restaurant & Restaurant::operator=(const Restaurant & restau)
{
	if (this != &restau)
	{
		chiffreAffaire_ = restau.chiffreAffaire_;
		momentJournee_ = restau.momentJournee_;
		menuMatin_ = new Menu(*restau.menuMatin_);
		menuMidi_ = new Menu(*restau.menuMidi_);
		menuSoir_ = new Menu(*restau.menuSoir_);
		for (unsigned i = 0; i < tables_.size(); ++i)
			delete tables_[i];

		tables_.clear();
		for (unsigned i = 0; i < restau.tables_.size(); ++i)
			tables_.push_back(new Table(*restau.tables_[i]));
		for (unsigned i = 0; i < NB_ZONES_LIVR; i++)
			fraisTransport_[i] = restau.getFraisTransports(i);

	}

	return *this;
}

/*
* lireTable : Ouvre le fichier entr� en param�tre pour lire les tables du restaurant (id, capacit�)
* \param le fichier a ouvrir
*/
void Restaurant::lireTable(const string& fichier) {
	ifstream file(fichier, ios::in); 

	if (file) {
		string ligne; 
		
		string idString; 
		int id; 

		string nbPersonnesString; 
		int nbPersonnes; 

		int curseur = 0; 
		while ( !file.eof()) {
			getline(file, ligne); 
			if (ligne == "-TABLES") {
					getline(file, ligne); 
				do {
					for (unsigned i = 0; i < ligne.size(); i++) {
						if (ligne[i] == ' ') {
							curseur = i; 
							break; 
						}
						idString += ligne[i]; 
					}

					id = stoi(idString); 

					nbPersonnesString = ligne.substr(curseur + 1); 
					nbPersonnes = stoi(nbPersonnesString); 

					*this+= new Table(id, nbPersonnes); 
					nbPersonnesString = ""; 
					idString = ""; 					
					getline(file, ligne);

				} while (ligne[0] != '-' && !file.eof());
			}
		}
		file.close(); 
	}
}

/*
* Op�rateur += : Ajoute une table � la lsite de tables du restaurant
* \param un pointeur vers une table
* \return le restaurant modifi�
*/
Restaurant& Restaurant::operator+=(Table* table) {
	tables_.push_back(new Table(*table)); 
	return *this;
}

/*
* placerClient : Place un client sur une table en fonction de son nombre de places et le nombre de clients
* \param un pointeur vers un client
*/
void Restaurant::placerClients(Client* client) 
{
	int indexTable = -1;
	int minimum = 100;

	for (unsigned i = 0; i < tables_.size(); i++) {
		if (tables_[i]->getNbPlaces() >= client->getTailleGroupe() && !tables_[i]->estOccupee() && tables_[i]->getNbPlaces() < minimum && tables_[i]->getId() != 5) {
			indexTable = i;
			minimum = tables_[i]->getNbPlaces();
		}
	}
	if (indexTable == -1) {
		cout << "Erreur : il n'y a plus/pas de table disponible pour les clients. " << endl;
	}
	else {
		tables_[indexTable]->placerClients(client->getTailleGroupe());
		tables_[indexTable]->setClientPrincipal(client);
	}
}

/*
* livrerClient : Similaire a la fonction placerClient. Le client qui se fait livr� est virtuellement plac� sur un table d�di�
* V�rifie d'abord si le client � le statut ad�quat pour se faire livrer (Prestige)
* \param un pointeur vers un client ainsi que sa commande
*/
void Restaurant::livrerClient(Client * client, vector<string> commande)
{
	cout << "Livraison en cours... " << endl;

	if (client->getStatut() == Prestige) {

		ClientPrestige* clientPrestige = static_cast<ClientPrestige*>(client);
		tables_[INDEX_TABLE_LIVRAISON]->setClientPrincipal(clientPrestige);
		tables_[INDEX_TABLE_LIVRAISON]->placerClients(1);

		for (int i = 0; i < commande.size(); i++) {
			commanderPlat(commande[i], INDEX_TABLE_LIVRAISON+1);
		}

		cout << "Statut de la table de livraison : (table numero " << tables_[INDEX_TABLE_LIVRAISON]->getId() << ")." <<endl;
		cout << *tables_[INDEX_TABLE_LIVRAISON] << endl;
		cout << "Livraison terminee !" << endl;
		libererTable(INDEX_TABLE_LIVRAISON+1);

	}
	else {
		cout << "Le client " << client->getNom() << " " << client->getPrenom() << " n'est pas admisible a la livraison." << endl;
	}
	
	///TODO
	///se r�ferer � l'�nonc� 
	///v�rifier que le client a droit aux livraisons
	///Si oui lui assigner la table des livraisons 
	///Effectuer la commande


}

/*
* calculerReduction : Calcule la r�duaction du prix de la commande d'un client en fonction de son statut.
* Si le client se fait livrer, calcul le montant de la livraison
* \param un pointeur vers un client, le montant de la facture et un bool qui indique si le client se fait livrer ou non
* \return le montant de la r�duction du client
*/
double Restaurant::calculerReduction(Client * client, double montant, bool livraison)
{
	double reduction = 0.0;			//La r�duction doit etre un chiffre n�gatif : 
									//Ex : si reduc = -5 --> r�duction de 5$
	if (client->getStatut() == Fidele) {
		ClientRegulier* clientRegulier = static_cast<ClientRegulier*>(client);
		if (clientRegulier->getNbPoints() > SEUIL_DEBUT_REDUCTION) {
			reduction = (-montant) * TAUX_REDUC_REGULIER;
		}
	}
	else if (client->getStatut() == Prestige) {
		ClientPrestige* clientPrestige = static_cast<ClientPrestige*>(client);
		reduction = (-montant) * TAUX_REDUC_PRESTIGE;
		if (livraison & (clientPrestige->getNbPoints() < SEUIL_LIVRAISON_GRATUITE)) {
			switch (clientPrestige->getAddresseCode())
			{
			case Zone1 :
				reduction += getFraisTransports(0); //La r�duction r�duit du montant des frais de transport
				break;
			case Zone2 :
				reduction += getFraisTransports(1);
				break;
			case Zone3 :
				reduction += getFraisTransports(2);
				break;
			default:
				break;
			}
		}
	}
	return reduction;
}

/*
* lireAdresse : lit dans le fichier donn� en param�tre les adresses disponible ainsi que le prix de livraison associ�
* \param le fichier � lire
*/
void Restaurant::lireAdresses(const string & fichier)
{
	ifstream file(fichier, ios::in);

		if (file) {
			string ligne;

			string addresseCodeStr;
			int addressCode = 0;

			string fraisStrg;
			double frais;

			int curseur = 0;
			while (!file.eof()) {
				getline(file, ligne);
				if (ligne == "-ADDRESSES") {
					while (!file.eof()) {
						getline(file, ligne);
						for (unsigned i = 0; i < ligne.size(); i++) {
							if (ligne[i] == ' ') {
								curseur = i;
								break;
							}
							addresseCodeStr += ligne[i];
							addressCode = stoi(addresseCodeStr);

						}


						fraisStrg = ligne.substr(curseur + 1);
						frais = stod(fraisStrg);
						fraisTransport_[addressCode] = frais;

						addresseCodeStr = "";
						fraisStrg = "";



					}

					
				}
			}
			file.close();
		}
	}


