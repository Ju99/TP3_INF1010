#include "Serie.h"

// To do              
//!param    Pointeur vers l'auteur du serie
Serie::Serie(Auteur* auteur):
    Media(auteur, Media::TypeMedia::Serie)
{
}

// To do
Serie::Serie(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
	bool estRestreintParAge, Auteur* auteur) :
	Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, Media::TypeMedia::Serie)
{
}

// To do
Serie::Serie(const Serie& serie):
    Serie(serie.nom_, serie.anneeDeSortie_, serie.genre_, serie.pays_, 
		serie.estRestreintParAge_, serie.auteur_)
{
	for (unsigned int i = 0; i < serie.paysRestreints_.size(); i++)
		paysRestreints_.push_back(serie.paysRestreints_[i]);
	
	for (unsigned int i = 0; i < serie.saisons_.size(); i++)
		saisons_.push_back(std::make_unique<Saison>(*serie.saisons_[i]));
}

// To do
std::ostream& Serie::afficher(std::ostream& os) const
{
	Media::afficher(os);
	for (size_t i = 0; i < saisons_.size(); i++)
		os << *saisons_[i];
	return os;
}

// To do
std::unique_ptr<Media> Serie::clone() const
{
    return std::make_unique<Serie>(*this);
}