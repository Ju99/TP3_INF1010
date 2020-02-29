/****************************************************************************
* Fichier: GestionnaireSaisons.cpp
* Auteur : Aldric Lopez et Juliette Morin
* Date :  12 f�vr. 2020
* Mise a jour : 29 f�vr. 2020
* Description : Impl�mentation de la classe GestionnaireSaisons
* ***************************************************************************/

#include "GestionnaireSaisons.h"

//! Destructeur de la classe GestionnaireSaisons
GestionnaireSaisons::~GestionnaireSaisons()
{
	saisons_.clear();
}

//! Op�rateur qui ajoute une saison
//! \param saison			La saison � ajouter
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

//! Op�rateur qui retire un �pisode
//! \param numSaison		Le num�ro de saison � retirer
//! \return	Saison			Le gestionnaire de saison avec la saison enlev�e
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

//! M�thode qui ajouter un �pisode � la saison dont le num�ro est pass� en param�tre	
void GestionnaireSaisons::ajouterEpisode(const unsigned int numSaison,
                                         std::unique_ptr<Episode> episode)
{
	unsigned int indexSaison = trouverIndexSaison(numSaison);
	if (indexSaison != SAISON_INEXSISTANTE)
		*saisons_[indexSaison] += std::move(episode);
}

//! M�thode qui retire un �pisode � la saison dont le num�ro est pass� en param�tre		
void GestionnaireSaisons::retirerEpisode(const unsigned int numSaison,
                                         const unsigned int numEpisode)
{
	unsigned int indexSaison = trouverIndexSaison(numSaison);
	if (indexSaison != SAISON_INEXSISTANTE)
		*saisons_[indexSaison] -= numEpisode;
}

//! M�thode qui cherche une saison comportant le num�ro envoy� en param�tre
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

//! M�thode qui retourne une saison
//! \return				Le pointeur d'une saison si la saison existe, sinon nullptr
Saison* GestionnaireSaisons::getSaison(const unsigned int numSaison) const
{
	unsigned int indexSaison = trouverIndexSaison(numSaison);
	if (indexSaison != SAISON_INEXSISTANTE)
		return saisons_[indexSaison].get();
	return nullptr;
}

//! M�thode qui retourne le nombre de saisons
//! \return				Le nombre de saisons
size_t GestionnaireSaisons::getNbSaisons() const
{
	return saisons_.size();
}