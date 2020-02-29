/****************************************************************************
* Fichier: Saison.cpp
* Auteur : Aldric Lopez et Juliette Morin
* Date :  12 févr. 2020
* Mise a jour : 29 févr. 2020
* Description : Implémentation de la classe Saison
* ***************************************************************************/

#include "Saison.h"

//! Constructeur par défault de la classe Saison
//! \param numSaison			Numéro de la saison
//! \param nbEpisodesmax		Nombre d'épisode max
Saison::Saison() :
    numSaison_(0),
	nbEpisodesmax_(0)
{
}

//! Constructeur par paramètre de la classe Saison
//! \param numSaison			Numéro de la saison
//! \param nbEpisodesmax		Nombre d'épisode max
Saison::Saison(unsigned int numSaison, unsigned int nbEpisodemax) :
    numSaison_(numSaison),
	nbEpisodesmax_(nbEpisodemax)
{
}

//! Constructeur par copie de la classe Saison
//! \param numSaison			Numéro de la saison
//! \param nbEpisodesmax		Nombre d'épisode max
Saison::Saison(const Saison& saison):
	Saison (saison.numSaison_, saison.nbEpisodesmax_)
{
	for (size_t i = 0; i < saison.episodes_.size(); i++)
		episodes_.push_back(std::make_unique<Episode>(*saison.episodes_[i]));
}

//! Destructeur de la classe Saison
Saison::~Saison()
{
	episodes_.clear();
}

//! Opérateur qui ajoute un épisode
//! \param episode			Un pointeur unique d'un épisode
//! \return					La saison avec un épisode ajouté
Saison& Saison::operator+=(std::unique_ptr<Episode> episode)
{
	size_t indexEpisode = trouverIndexEpisode(episode->getNumEpisode());
	if (indexEpisode != EPISODE_INEXSISTANTE && episodes_[indexEpisode]->operator==(episode->getNumEpisode()))
		*this -= episode->getNumEpisode();
	
	episodes_.push_back(move(episode));
	sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
	return *this;
}

//! Opérateur qui retire un épisode
//! \param numEpisode		Le numéro de l'épisode à retirer
//! \return	Saison			La saison avec l'épisode enlevé
Saison& Saison::operator-=(unsigned int numEpisode)
{
	unsigned int indexEpisode = trouverIndexEpisode(numEpisode);
	if (indexEpisode == EPISODE_INEXSISTANTE)
		return *this;
	episodes_[indexEpisode] = std::move(episodes_[episodes_.size() - 1]);
	episodes_.pop_back();
	sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
	return *this;
}

//! Opérateur qui compare le numéro de saison avec une saison
//! \param numSaison		Le numéro de la saison à comparer
//! \return					Un bool représentant s'ils sont égaux ou non
bool Saison::operator==(unsigned int numSaison)
{
	return (numSaison_ == numSaison);
}


//! Opérateur qui affiche tous les attributs de la saison
//! \param os			Le stream dans lequel afficher
//! \param saison		La saison à afficher
std::ostream& operator<<(std::ostream& os, const Saison& saison)
{
	os << "\tSaison " << std::setfill('0') << std::setw(2) <<saison.numSaison_ << ": " << saison.getNbEpisodes() << "/" 
		<< saison.nbEpisodesmax_;
	if (saison.getNbEpisodes() == saison.nbEpisodesmax_)
		os << "(Terminee)";
	else
		os << "(En cours)";
	os << "\n";
	for (unsigned int i = 0; i < saison.getNbEpisodes(); i++)
		os << *saison.episodes_[i];
	os << "\n";
	
	return os;
}

//! Opérateur qui initialise tous les attributs d'une saison
//! \param is			Le stream où se trouve les attributs
//! \param episode		La saison que l'on désire initialiser
std::istream& operator>>(std::istream& is, Saison& saison)
{
	return is >> saison.numSaison_ >> saison.nbEpisodesmax_;
}

//! Méthode qui retourne le numéro de saison
//! \return				Le numéro de saison
unsigned int Saison::getNumSaison() const
{
	return numSaison_;
}

//! Méthode qui retourne le nombre d'épisodes
//! \return				Le nombre d'épisodes
size_t Saison::getNbEpisodes() const
{
	return episodes_.size();
}

//! Méthode qui retourne l'index de l'épisode recherché
//! \return		L'index de l'épisodes recherché s'il existe, sinon EPISODE_INEXSISTANTE
size_t Saison::trouverIndexEpisode(unsigned int numEpisode)
{
	for (unsigned int i = 0; i < getNbEpisodes(); i++)
	{
		if (episodes_[i]->getNumEpisode() == numEpisode)
			return i;
	}
	return EPISODE_INEXSISTANTE;
}