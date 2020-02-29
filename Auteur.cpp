/****************************************************************************
* Fichier: Auteur.cpp
* Auteur : Aldric Lopez et Juliette Morin
* Date :  12 févr. 2020
* Mise a jour : 29 févr. 2020
* Description : Implémentation de la classe Auteur
* ***************************************************************************/

#include "Auteur.h"
#include <iostream>

//! Constructeur de la classe Auteur
//! \param nom              Nom de l'auteur
//! \param anneeDeNaissance Année de naissance de l'auteur
Auteur::Auteur(const std::string& nom, unsigned int anneeDeNaissance)
    : nom_(nom)
    , anneeDeNaissance_(anneeDeNaissance)
    , nbMedias_(0)
{
}

//! Méthode qui retourne le nom de l'auteur
//! \return		Le nom de l'auteur
const std::string& Auteur::getNom() const
{
    return nom_;
}

//! Méthode qui retourne l'année de naissance de l'auteur
//! \return		L'année de naissance de l'auteur
unsigned int Auteur::getAnneeDeNaissance() const
{
    return anneeDeNaissance_;
}

//! Méthode qui retourne le nombre de films de l'auteur
//! \return		Le nombre de films de l'auteur
unsigned int Auteur::getNbMedias() const
{
    return nbMedias_;
}

//! Méthode qui set le nombre de films de l'auteur
//! \param nbFilms  Le nombre de films de l'auteur
void Auteur::setNbMedias(unsigned int nbMedias)
{
    nbMedias_ = nbMedias;
}

//! Opérateur qui compare un string avec le nom de l'auteur avec auteur comme opérande de gauche
//! \param nom		Le nom avec le quel on veut comparé l'auteur
//! \return			Vrai si les noms sont identique, faux sinon
bool Auteur::operator==(const std::string& nom) const
{
	return (nom_ == nom);
}

//! Opérateur qui compare un string avec le nom de l'auteur avec le nom comme opérande de gauche.
//! \param nom			Le nom avec le quel on veut comparé l'auteur
//! \param auteur		L'auteur avec lequel on compare le nom.
bool operator==(const std::string& nom, const Auteur& auteur)
{
	return (nom == auteur.nom_);
}

//! Opérateur qui affiche un auteur
//! \param os		Le stream dans lequel afficher
//! \param auteur	L'auteur a afficher
std::ostream& operator<<(std::ostream& os, const Auteur& auteur)
{
	os << "\nNom: " << auteur.nom_ << " | Date de naissance: " << auteur.anneeDeNaissance_
		<< " | Nombre de Film/Serie: " << auteur.nbMedias_;

	return os;
}

//! Opérateur qui initialise tous les attributs d'un auteur
//! \param is		Le stream où se trouve les attributs
//! \param auteur	L'auteur que l'on désire initialiser
std::istream& operator>>(std::istream& is, Auteur& auteur)
{
	auteur.nbMedias_ = 0;
	return is >> quoted(auteur.nom_) >> auteur.anneeDeNaissance_;
}
