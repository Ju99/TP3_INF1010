/****************************************************************************
* Fichier: Serie.cpp
* Auteur : Aldric Lopez et Juliette Morin
* Date :  12 févr. 2020
* Mise a jour : 29 févr. 2020
* Description : Implémentation de la classe Serie
* ***************************************************************************/

#include "Serie.h"

//! Constructeur de la classe série
Serie::Serie(Auteur* auteur):
    Media(auteur, Media::TypeMedia::Serie)
{
}

//! Constructeur de la classe Serie
//! \param nom                  Nom de la série
//! \param anneeDeSortie        Année de sortie de la série
//! \param genre                Le genre de la série
//! \param pays                 Le pays d'origine de la série
//! \param estRestreintParAge   Bool qui représente si la série est interdite aux moins de 16 ans
//! \param auteur               Pointeur vers l'auteur de la série
Serie::Serie(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
	bool estRestreintParAge, Auteur* auteur) :
	Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, Media::TypeMedia::Serie)
{
}

//! Constructeur par copie de la classe Serie
Serie::Serie(const Serie& serie):
    Serie(serie.nom_, serie.anneeDeSortie_, serie.genre_, serie.pays_, 
		serie.estRestreintParAge_, serie.auteur_)
{
	for (unsigned int i = 0; i < serie.paysRestreints_.size(); i++)
		paysRestreints_.push_back(serie.paysRestreints_[i]);
	
	for (unsigned int i = 0; i < serie.saisons_.size(); i++)
		saisons_.push_back(std::make_unique<Saison>(*serie.saisons_[i]));
}

//! Méthode qui affiche la série
//! \param os		Le stream dans lequel afficher
std::ostream& Serie::afficher(std::ostream& os) const
{
	Media::afficher(os);
	for (size_t i = 0; i < saisons_.size(); i++)
		os << *saisons_[i];
	return os;
}

//! Méthode qui retourne une copie de la série
//! \return				Un pointeur unique d'une série
std::unique_ptr<Media> Serie::clone() const
{
    return std::make_unique<Serie>(*this);
}