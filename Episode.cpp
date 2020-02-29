/****************************************************************************
* Fichier: Episode.cpp
* Auteur : Aldric Lopez et Juliette Morin
* Date :  12 févr. 2020
* Mise a jour : 29 févr. 2020
* Description : Implémentation de la classe Episode
* ***************************************************************************/

#include "Episode.h"

//! Constructeur par défault de la classe Épisode
//! \param numEpisode           Numero de l'épisode
//! \param nom					Nom de l'épisode
//! \param dure					Durée de l'épisode
Episode::Episode() :
	numEpisode_(0),
	nom_("Unknown"),
	duree_("Unknown")
{
}

//! Constructeur par paramètre de la classe Épisode
//! \param numEpisode           Numero de l'épisode
//! \param nom					Nom de l'épisode
//! \param duree				Durée de l'épisode
Episode::Episode(unsigned int numEpisode, const std::string& nom, const std::string& duree) :
	numEpisode_(numEpisode),
	nom_(nom),
	duree_(duree)
{
}

//! Opérateur qui compare le numéro d'épisode avec un épisode
//! \param numEpisode		Le numéro d'épisode
//! \return					Un Bool représentant s'ils sont identiques ou non
bool Episode::operator==(unsigned int numEpisode)
{
	return (numEpisode_ == numEpisode);
}

//! Opérateur qui affiche tous les attributs de l'épisode
//! \param numEpisode		Le numéro d'épisode
//! \return					Un Bool representant s'ils sont identiques
std::ostream& operator<<(std::ostream& os, const Episode& episode)
{
	os << "\t\tEpisode " << std::setfill('0') << std::setw(2) << episode.numEpisode_ << ": " << episode.nom_ << " | Duree: "
		<< episode.duree_ << "\n";

	return os;
}

//! Opérateur qui initialise tous les attributs de l'épisode
//! \param is			Le stream où se trouve les attributs
//! \param episode		L'épisode que l'on désire initialiser
std::istream& operator>>(std::istream& is, Episode& episode)
{
	return is >> episode.numEpisode_ >> quoted(episode.nom_ )>> quoted(episode.duree_);
}

//! Méthode qui retourne le numéro d'épisodes
//! \return				Le numéro d'épisodes
unsigned int Episode::getNumEpisode() const
{
	return numEpisode_;
}