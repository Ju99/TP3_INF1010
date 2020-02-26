#include "Media.h"

namespace
{
    //! Fonction qui convertit le enum Media::Genre en string
    //! \param genre    Le genre à convertir
    //! \return         Le string qui représente le enum
    const std::string& getGenreString(Media::Genre genre)
    {
        static const std::string NOMS_GENRES[] = {"Action",
                                                  "Aventure",
                                                  "Comedie",
                                                  "Horreur",
                                                  "Romance"};

        auto index = enum_value(genre);
        assert(valid_as_enum<Media::Genre>(index));
        return NOMS_GENRES[index];
    }

    //! Fonction qui convertit le enum Pays en string
    //! \param pays     Le pays à convertir
    //! \return         Le string qui représente le enum
    const std::string& getPaysString(Pays pays)
    {
        static const std::string NOMS_PAYS[] = {"Bresil",
                                                "Canada",
                                                "Chine",
                                                "EtatsUnis",
                                                "France",
                                                "Japon",
                                                "RoyaumeUni",
                                                "Russie",
                                                "Mexique"};
        auto index = enum_value(pays);
        assert(valid_as_enum<Pays>(index));
        return NOMS_PAYS[index];
    }
} // namespace

// To do
Media::Media(Auteur* auteur, Media::TypeMedia typeMedia) :
	nom_("Unkwown"),
	anneeDeSortie_(0),
	genre_(),
	pays_(),
	estRestreintParAge_(false),
	auteur_(auteur),
	typeMedia_(typeMedia)
{
}

// To do
Media::Media(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur, Media::TypeMedia typeMedia) :
	nom_(nom),
	anneeDeSortie_(anneeDeSortie),
	genre_(genre),
	pays_(pays),
	estRestreintParAge_(estRestreintParAge),
	auteur_(auteur),
	typeMedia_(typeMedia)
{
}

// To do
Media::Media(const Media& media) :
	Media (media.nom_, media.anneeDeSortie_, media.genre_, media.pays_, media.estRestreintParAge_,
		media.auteur_, media.typeMedia_)
{
	for (unsigned int i = 0; i < media.paysRestreints_.size(); i++)
		paysRestreints_.push_back(media.paysRestreints_[i]);
}


//! Destructeur virtuel
Media::~Media()
{
	paysRestreints_.clear();
}

//! Méthode qui ajoute un pays à liste des pays restreints du media
//! \param pays Pays à ajouter à la liste
void Media::ajouterPaysRestreint(Pays pays)
{
	paysRestreints_.push_back(pays);
}

//! Méthode qui supprime les pays restreints
void Media::supprimerPaysRestreints()
{
	paysRestreints_.clear();
}

//! Méthode qui retourne si un pays est dans la liste des pays restreints du media
//! \param pays Le pays à chercher dans la liste des pays restreints
//! \return     Un bool représentant si le pays se trouve dans la liste des pays restreints
bool Media::estRestreintDansPays(Pays pays) const
{
	for (std::size_t i = 0; i < paysRestreints_.size(); i++)
	{
		if (paysRestreints_[i] == pays)
		{
			return true;
		}
	}
	return false;
}

// Méthode qui retourne si le media est restreint aux moins de 16 ans
// \return Un bool représentant si le film est restreint aux moins de 16 ans
bool Media::estRestreintParAge() const
{
	return estRestreintParAge_;
}

//! opérateur qui affiche le film
//! \param os Le stream dans lequel afficher
//! \param Film le film que l'on veut afficher
std::ostream& Media::afficher(std::ostream& os) const
{
	os << nom_ << "\n\tDate de sortie: " << anneeDeSortie_
		<< "\n\tGenre: " << getGenreString(genre_) << "\n\tAuteur: " << auteur_->getNom()
		<< "\n\tPays: " << getPaysString(pays_)
		<< (paysRestreints_.size() == 0 ? "\n\tAucun pays restreint." : "\n\tPays restreints:");

	for (std::size_t i = 0; i < paysRestreints_.size(); i++)
	{
		os << "\n\t\t" << getPaysString(paysRestreints_[i]);
	}
	os << '\n';

	return os;
    }

// to do
std::ostream& operator<<(std::ostream& os, const Media& media)
{
	return media.afficher(os);
}

// Méthode qui retourne le genre du media
// \return Le genre du media
Media::Genre Media::getGenre() const
{
	return genre_;
}

// Méthode qui retourne le nom du media
// \return Le nom du media
const std::string& Media::getNom() const
{
	return nom_;
}

// Méthode qui retourne l'auteur
// \return L'auteur du media
const Auteur* Media::getAuteur() const
{
	return auteur_;
}

// To do
Media::TypeMedia Media::getTypeMedia() const
{
	return typeMedia_;
}

// To do
std::istream& Media::lire(std::istream& is)
{
	int genreValeurEnum;
	int paysValeurEnum;
	
	if (is >> std::quoted(nom_) >> anneeDeSortie_
		>> genreValeurEnum >> paysValeurEnum >> estRestreintParAge_)
	{
		genre_ = to_enum<Media::Genre>(genreValeurEnum);
		pays_ = to_enum<Pays>(paysValeurEnum);
	}
	
	return is;
}

// To do
std::istream& operator>>(std::istream& is, Media& media)
{
	return media.lire(is);
}

// To do
std::unique_ptr<Media> Media::clone() const
{
	return std::make_unique<Media>(*this);
}