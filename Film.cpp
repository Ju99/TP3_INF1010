#include "Film.h"

// To do
Film::Film(Auteur* auteur) :
	Media(auteur, Media::TypeMedia::Film),
	duree_("0")
{
}

// To do
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
           bool estRestreintParAge, Auteur* auteur, const std::string& duree):
    Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, Media::TypeMedia::Film),
	duree_(duree)
{
}

// To do 
std::ostream& Film::afficher(std::ostream& os) const
{
	Media::afficher(os);
	os << "\tDuree: " << duree_ << '\n';
	return os;
}

// To do
std::istream& Film::lire(std::istream& is)
{
	Media::lire(is);
	return is >> std::quoted(duree_);
}

// To do
std::unique_ptr<Media> Film::clone() const
{
	return std::make_unique<Film>(*this);
}
