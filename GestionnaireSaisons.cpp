#include "GestionnaireSaisons.h"

// To do
GestionnaireSaisons::~GestionnaireSaisons()
{
	saisons_.clear();
}

// To do
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

// To do
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

// To do
void GestionnaireSaisons::ajouterEpisode(const unsigned int numSaison,
                                         std::unique_ptr<Episode> episode)
{
	unsigned int indexSaison = trouverIndexSaison(numSaison);
	if (indexSaison != SAISON_INEXSISTANTE)
		*saisons_[indexSaison] += std::move(episode);
}

// To do
void GestionnaireSaisons::retirerEpisode(const unsigned int numSaison,
                                         const unsigned int numEpisode)
{
	unsigned int indexSaison = trouverIndexSaison(numSaison);
	if (indexSaison != SAISON_INEXSISTANTE)
		*saisons_[indexSaison] -= numEpisode;
}

/// To do
size_t GestionnaireSaisons::trouverIndexSaison(const unsigned int numSaison) const
{
	for (unsigned int i = 0; i < saisons_.size(); i++)
	{
		if (saisons_[i]->getNumSaison() == numSaison)
			return i;
	}
	return SAISON_INEXSISTANTE;
}

// To do
Saison* GestionnaireSaisons::getSaison(const unsigned int numSaison) const
{
	unsigned int indexSaison = trouverIndexSaison(numSaison);
	if (indexSaison != SAISON_INEXSISTANTE)
		return saisons_[indexSaison].get();
	return nullptr;
}

// To do
size_t GestionnaireSaisons::getNbSaisons() const
{
	return saisons_.size();
}