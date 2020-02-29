/****************************************************************************
* Fichier: Film.cpp
* Auteur : Aldric Lopez et Juliette Morin
* Date :  12 févr. 2020
* Mise a jour : 29 févr. 2020
* Description : Implémentation de la classe Film
* ***************************************************************************/

#include "Film.h"

//! Constructeur de la classe Film
Film::Film(Auteur* auteur) :
	Media(auteur, Media::TypeMedia::Film),
	duree_("0")
{
}

//! Constructeur de la classe Film
//! \param nom                  Nom du film
//! \param anneeDeSortie        Année de sortie du film
//! \param genre                Le genre du film
//! \param pays                 Le pays d'origine du film
//! \param estRestreintParAge   Bool qui représente si le film est interdit aux moins de 16 ans
//! \param auteur               Pointeur vers l'auteur du film
//! \param auteur               Duree du film
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
           bool estRestreintParAge, Auteur* auteur, const std::string& duree):
    Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, Media::TypeMedia::Film),
	duree_(duree)
{
}

//! Méthode qui affiche tous les attributs du film
//! \param os			Le stream dans lequel afficher
//! \param saison		Le film à afficher
std::ostream& Film::afficher(std::ostream& os) const
{
	Media::afficher(os);
	os << "\tDuree: " << duree_ << '\n';
	return os;
}

//! Méthode qui initialise tous les attributs de la classe Film
std::istream& Film::lire(std::istream& is)
{
	Media::lire(is);
	return is >> std::quoted(duree_);
}

//! Méthode qui retourne une copie de média
//! \return				Un pointeur unique du film
std::unique_ptr<Media> Film::clone() const
{
	return std::make_unique<Film>(*this);
}
