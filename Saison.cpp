/****************************************************************************
* Fichier: Saison.cpp
* Auteur : Aldric Lopez et Juliette Morin
* Date :  12 f�vr. 2020
* Mise a jour : 29 f�vr. 2020
* Description : Impl�mentation de la classe Saison
* ***************************************************************************/

#include "Saison.h"

//! Constructeur par d�fault de la classe Saison
//! \param numSaison			Num�ro de la saison
//! \param nbEpisodesmax		Nombre d'�pisode max
Saison::Saison() :
    numSaison_(0),
	nbEpisodesmax_(0)
{
}

//! Constructeur par param�tre de la classe Saison
//! \param numSaison			Num�ro de la saison
//! \param nbEpisodesmax		Nombre d'�pisode max
Saison::Saison(unsigned int numSaison, unsigned int nbEpisodemax) :
    numSaison_(numSaison),
	nbEpisodesmax_(nbEpisodemax)
{
}

//! Constructeur par copie de la classe Saison
//! \param numSaison			Num�ro de la saison
//! \param nbEpisodesmax		Nombre d'�pisode max
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

//! Op�rateur qui ajoute un �pisode
//! \param episode			Un pointeur unique d'un �pisode
//! \return					La saison avec un �pisode ajout�
Saison& Saison::operator+=(std::unique_ptr<Episode> episode)
{
	size_t indexEpisode = trouverIndexEpisode(episode->getNumEpisode());
	if (indexEpisode != EPISODE_INEXSISTANTE && episodes_[indexEpisode]->operator==(episode->getNumEpisode()))
		*this -= episode->getNumEpisode();
	
	episodes_.push_back(move(episode));
	sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
	return *this;
}

//! Op�rateur qui retire un �pisode
//! \param numEpisode		Le num�ro de l'�pisode � retirer
//! \return	Saison			La saison avec l'�pisode enlev�
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

//! Op�rateur qui compare le num�ro de saison avec une saison
//! \param numSaison		Le num�ro de la saison � comparer
//! \return					Un bool repr�sentant s'ils sont �gaux ou non
bool Saison::operator==(unsigned int numSaison)
{
	return (numSaison_ == numSaison);
}


//! Op�rateur qui affiche tous les attributs de la saison
//! \param os			Le stream dans lequel afficher
//! \param saison		La saison � afficher
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

//! Op�rateur qui initialise tous les attributs d'une saison
//! \param is			Le stream o� se trouve les attributs
//! \param episode		La saison que l'on d�sire initialiser
std::istream& operator>>(std::istream& is, Saison& saison)
{
	return is >> saison.numSaison_ >> saison.nbEpisodesmax_;
}

//! M�thode qui retourne le num�ro de saison
//! \return				Le num�ro de saison
unsigned int Saison::getNumSaison() const
{
	return numSaison_;
}

//! M�thode qui retourne le nombre d'�pisodes
//! \return				Le nombre d'�pisodes
size_t Saison::getNbEpisodes() const
{
	return episodes_.size();
}

//! M�thode qui retourne l'index de l'�pisode recherch�
//! \return		L'index de l'�pisodes recherch� s'il existe, sinon EPISODE_INEXSISTANTE
size_t Saison::trouverIndexEpisode(unsigned int numEpisode)
{
	for (unsigned int i = 0; i < getNbEpisodes(); i++)
	{
		if (episodes_[i]->getNumEpisode() == numEpisode)
			return i;
	}
	return EPISODE_INEXSISTANTE;
}