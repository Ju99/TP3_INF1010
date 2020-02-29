/****************************************************************************
* Fichier: Episode.cpp
* Auteur : Aldric Lopez et Juliette Morin
* Date :  12 f�vr. 2020
* Mise a jour : 29 f�vr. 2020
* Description : Impl�mentation de la classe Episode
* ***************************************************************************/

#include "Episode.h"

//! Constructeur par d�fault de la classe �pisode
//! \param numEpisode           Numero de l'�pisode
//! \param nom					Nom de l'�pisode
//! \param dure					Dur�e de l'�pisode
Episode::Episode() :
	numEpisode_(0),
	nom_("Unknown"),
	duree_("Unknown")
{
}

//! Constructeur par param�tre de la classe �pisode
//! \param numEpisode           Numero de l'�pisode
//! \param nom					Nom de l'�pisode
//! \param duree				Dur�e de l'�pisode
Episode::Episode(unsigned int numEpisode, const std::string& nom, const std::string& duree) :
	numEpisode_(numEpisode),
	nom_(nom),
	duree_(duree)
{
}

//! Op�rateur qui compare le num�ro d'�pisode avec un �pisode
//! \param numEpisode		Le num�ro d'�pisode
//! \return					Un Bool repr�sentant s'ils sont identiques ou non
bool Episode::operator==(unsigned int numEpisode)
{
	return (numEpisode_ == numEpisode);
}

//! Op�rateur qui affiche tous les attributs de l'�pisode
//! \param numEpisode		Le num�ro d'�pisode
//! \return					Un Bool representant s'ils sont identiques
std::ostream& operator<<(std::ostream& os, const Episode& episode)
{
	os << "\t\tEpisode " << std::setfill('0') << std::setw(2) << episode.numEpisode_ << ": " << episode.nom_ << " | Duree: "
		<< episode.duree_ << "\n";

	return os;
}

//! Op�rateur qui initialise tous les attributs de l'�pisode
//! \param is			Le stream o� se trouve les attributs
//! \param episode		L'�pisode que l'on d�sire initialiser
std::istream& operator>>(std::istream& is, Episode& episode)
{
	return is >> episode.numEpisode_ >> quoted(episode.nom_ )>> quoted(episode.duree_);
}

//! M�thode qui retourne le num�ro d'�pisodes
//! \return				Le num�ro d'�pisodes
unsigned int Episode::getNumEpisode() const
{
	return numEpisode_;
}