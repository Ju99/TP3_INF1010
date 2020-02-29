/****************************************************************************
* Fichier: GestionnaireSaisons.cpp
* Auteur : Aldric Lopez et Juliette Morin
* Date :  12 févr. 2020
* Mise a jour : 29 févr. 2020
* Description : Implémentation de la classe GestionnaireSaisons
* ***************************************************************************/

#include "GestionnaireSaisons.h"

//! Destructeur de la classe GestionnaireSaisons
GestionnaireSaisons::~GestionnaireSaisons()
{
	saisons_.clear();
}

//! Opérateur qui ajoute une saison
//! \param saison			La saison à ajouter
//! \return					Le gestionnaire de saison avec une nouvelle saison
GestionnaireSaisons& GestionnaireSaisons::operator+=(std::unique_ptr<Saison> saison)
{
	size_t indexSaison = trouverIndexSaison(saison->getNumSaison());
	if (indexSaison != SAISON_INEXSISTANTE)
	{
		if (*saisons_[indexSaison] == saison->getNumSaison())
			*this -= saison->getNumSaison();
	}
	saisons_.push_back(move(saison));
	sort(saisons_.begin(), saisons_.end(), Saison::SortByNumSaison());
	return *this;
}

//! Opérateur qui retire un épisode
//! \param numSaison		Le numéro de saison à retirer
//! \return	Saison			Le gestionnaire de saison avec la saison enlevée
GestionnaireSaisons& GestionnaireSaisons::operator-=(const unsigned int numSaison)
{
	unsigned int indexSaison = trouverIndexSaison(numSaison);
	if (indexSaison == SAISON_INEXSISTANTE)
		return *this;

	saisons_[indexSaison] = std::move(saisons_[saisons_.size() - 1]);
	saisons_.pop_back();
	sort(saisons_.begin(), saisons_.end(), Saison::SortByNumSaison());
	return *this;
}

//! Méthode qui ajouter un épisode à la saison dont le numéro est passé en paramètre	
void GestionnaireSaisons::ajouterEpisode(const unsigned int numSaison,
                                         std::unique_ptr<Episode> episode)
{
	unsigned int indexSaison = trouverIndexSaison(numSaison);
	if (indexSaison != SAISON_INEXSISTANTE)
		*saisons_[indexSaison] += std::move(episode);
}

//! Méthode qui retire un épisode à la saison dont le numéro est passé en paramètre		
void GestionnaireSaisons::retirerEpisode(const unsigned int numSaison,
                                         const unsigned int numEpisode)
{
	unsigned int indexSaison = trouverIndexSaison(numSaison);
	if (indexSaison != SAISON_INEXSISTANTE)
		*saisons_[indexSaison] -= numEpisode;
}

//! Méthode qui cherche une saison comportant le numéro envoyé en paramètre
//! \return				L'index d'une saison si la saison existe, sinon SAISON_INEXSISTANTE
size_t GestionnaireSaisons::trouverIndexSaison(const unsigned int numSaison) const
{
	for (unsigned int i = 0; i < saisons_.size(); i++)
	{
		if (saisons_[i]->getNumSaison() == numSaison)
			return i;
	}
	return SAISON_INEXSISTANTE;
}

//! Méthode qui retourne une saison
//! \return				Le pointeur d'une saison si la saison existe, sinon nullptr
Saison* GestionnaireSaisons::getSaison(const unsigned int numSaison) const
{
	unsigned int indexSaison = trouverIndexSaison(numSaison);
	if (indexSaison != SAISON_INEXSISTANTE)
		return saisons_[indexSaison].get();
	return nullptr;
}

//! Méthode qui retourne le nombre de saisons
//! \return				Le nombre de saisons
size_t GestionnaireSaisons::getNbSaisons() const
{
	return saisons_.size();
}