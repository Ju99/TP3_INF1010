/****************************************************************************
* Fichier: Serie.cpp
* Auteur : Aldric Lopez et Juliette Morin
* Date :  12 f�vr. 2020
* Mise a jour : 29 f�vr. 2020
* Description : Impl�mentation de la classe Serie
* ***************************************************************************/

#include "Serie.h"

//! Constructeur de la classe s�rie
Serie::Serie(Auteur* auteur):
    Media(auteur, Media::TypeMedia::Serie)
{
}

//! Constructeur de la classe Serie
//! \param nom                  Nom de la s�rie
//! \param anneeDeSortie        Ann�e de sortie de la s�rie
//! \param genre                Le genre de la s�rie
//! \param pays                 Le pays d'origine de la s�rie
//! \param estRestreintParAge   Bool qui repr�sente si la s�rie est interdite aux moins de 16 ans
//! \param auteur               Pointeur vers l'auteur de la s�rie
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

//! M�thode qui affiche la s�rie
//! \param os		Le stream dans lequel afficher
std::ostream& Serie::afficher(std::ostream& os) const
{
	Media::afficher(os);
	for (size_t i = 0; i < saisons_.size(); i++)
		os << *saisons_[i];
	return os;
}

//! M�thode qui retourne une copie de la s�rie
//! \return				Un pointeur unique d'une s�rie
std::unique_ptr<Media> Serie::clone() const
{
    return std::make_unique<Serie>(*this);
}