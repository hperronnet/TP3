/*
* Titre : Table.cpp - Travail Pratique #3
* Date : 11 Février 2019
* Auteur :Fatou S. MOUNZEO
*/

#include "Table.h"

//constructeurs
Table::Table() {
	id_ = -1;
	nbPlaces_ = 1;
	nbClientsATable_ = 0;
}

Table::Table(int id, int nbPlaces) {
	id_ = id;
	nbPlaces_ = nbPlaces;
	nbClientsATable_ = 0;
}

//getters
int Table::getId() const {
	return id_;
}

int Table::getNbPlaces() const {
	return nbPlaces_;
}

bool Table::estOccupee() const
{
	return nbClientsATable_!=0;
}

bool Table::estPleine() const {
	return nbPlaces_ == 0;
}

int Table::getNbClientsATable() const
{
	return nbClientsATable_;
}

vector<Plat*> Table::getCommande() const
{
	return commande_;
}

Client * Table::getClientPrincipal() const
{
	return clientPrincipal_;
}

//setters
void Table::setId(int id) {
	id_ = id;
}

/*
* setClientPrincipal : set le client principal d'une table en prenant en compte son statut
*\param le client principal
*/
void Table::setClientPrincipal(Client * clientPrincipal)
{	
	if (clientPrincipal->getStatut() == Fidele) {
		ClientRegulier* regulier = static_cast<ClientRegulier*>(clientPrincipal);
		clientPrincipal_ = regulier;
	}
	if (clientPrincipal->getStatut() == Prestige) {
		ClientPrestige* prestige = static_cast<ClientPrestige*>(clientPrincipal);
		clientPrincipal_ = prestige;
	}
	else {
		clientPrincipal_ = clientPrincipal;
	}
}

/*
* libererTable : réinitialise le nombre de clients à table, le nombre de places et vide la commande du/des client(s)
*/
void Table::libererTable() {
	nbPlaces_ += nbClientsATable_;
	nbClientsATable_ = 0;
	commande_.clear();
}

/*
* placerClient : ajoute un/des client(s) à une table
* \param le nombre de clients
*/
void Table::placerClients(int nbClient) {
	nbPlaces_ -= nbClient;
	nbClientsATable_ = nbClient;
}

/*
* commander : Ajoute un plat à la commande du/des client(s)
* \param un pointeur vers un plat
*/
void Table::commander(Plat* plat) {
	commande_.push_back(plat);
}

/*
* getChiffreAffaire : calcul le chiffre d'affaire créé par la table lorsque celle-ci est libérée en prenant 
* en compte le type du plat (donc ecoTaxe ou nb d'ingrédients en plus)
* \return le chiffre d'affaire
*/
double Table::getChiffreAffaire() const {
	///TODO
	///Modifier pour que le chiffre d'Affaire prenne en compte le type de plat
	///voir Énoncé
	double chiffre = 0;
	for (unsigned i = 0; i < commande_.size(); ++i) {
		if (commande_[i]->getType() == Bio) {
			chiffre += commande_[i]->getPrix() + static_cast<PlatBio*>(commande_[i])->getEcoTaxe() - commande_[i]->getCout();
		}
		else if (commande_[i]->getType() == Custom) {
			chiffre += commande_[i]->getPrix() + static_cast<PlatCustom*>(commande_[i])->getSupplement() - commande_[i]->getCout();
		}
		else {
			chiffre += commande_[i]->getPrix() - commande_[i]->getCout();
		}
	}

	return chiffre;
}

/*
* Opérateur d'affichage
* \param la table à afficher et l'os
* \return os (ce qui est à afficher)
*/
ostream& operator<<(ostream& os, const Table& table)
{
	os << "La table numero " << table.id_;
	if (table.estOccupee())
	{
		os << " est occupee. " << endl;
		if (table.clientPrincipal_->getStatut() == Prestige) {
			ClientPrestige* prestige = static_cast<ClientPrestige*>(table.clientPrincipal_);
			os << "Le client principal est : " << *prestige << endl;
		}
		else if (table.clientPrincipal_->getStatut() == Fidele) {
			ClientRegulier* regulier = static_cast<ClientRegulier*>(table.clientPrincipal_);
			os << "Le client principal est : " << *regulier << endl;
		}
		else {
			os << "Le client principal est : " << *table.clientPrincipal_ << endl;
		}


		//switch (table.getClientPrincipal()->getStatut())
		//{
		//case Prestige : 
		//	os << static_cast<ClientPrestige*>(table.getClientPrincipal());
		//  break;
		//case Fidele :
		//	os << table.getClientPrincipal();
		//  break;
		//default:
		//	break;
		//}
		if (!table.commande_.empty())
		{
			os << "Voici la commande passee par les clients : " << endl;
			for (unsigned i = 0; i < table.commande_.size(); ++i)
			{
				if (table.commande_[i]->getType() == Regulier)
					os << "\t" << *table.commande_[i];
				else if (table.commande_[i]->getType() == Bio) {
					PlatBio* platBio = static_cast<PlatBio*>(table.commande_[i]);
					os << "\t" << *platBio;
				}
				else if (table.commande_[i]->getType() == Custom) {
					PlatCustom* platCustom = static_cast<PlatCustom*>(table.commande_[i]);
					os << "\t" << *platCustom;
				}
			}
		}
		else
			os << "Mais ils n'ont rien commande pour l'instant. " << endl;
	}
	else
		os << " est vide. " << endl;

	return os;
}
