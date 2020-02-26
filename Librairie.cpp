#include "Librairie.h"


// To do
Librairie::Librairie(const Librairie& librairie)
{
	*this = librairie;
		
}

// To do
Librairie& Librairie::operator=(const Librairie& librairie)
{
	if (&librairie == this)
		return *this;

	medias_.clear();

	for (unsigned int i = 0; i < librairie.medias_.size(); i++)
	{
		medias_.push_back(librairie.medias_[i]->clone());
	}

	return *this;
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
    medias_.clear();
}

// To do
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
	Media* media = chercherMedia(nomFilm, Media::TypeMedia::Film);
	if (!media)
		return nullptr;
	return dynamic_cast<Film*>(media);
}

// To do
Serie* Librairie::chercherSerie(const std::string& nomSerie)
{
	Media* media = chercherMedia(nomSerie, Media::TypeMedia::Serie);
	if (media == nullptr)
		return nullptr;
	return dynamic_cast<Serie*>(media);
}

// To do
void Librairie::ajouterSaison(const std::string& nomSerie, std::unique_ptr<Saison> saison)
{
	size_t index = trouverIndexMedia(nomSerie);

	if (index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
		*dynamic_cast<Serie*>(medias_[index].get()) += move(saison);
}

// To do
void Librairie::retirerSaison(const std::string& nomSerie, unsigned int numSaison)
{
	size_t index = trouverIndexMedia(nomSerie);

	if (index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
		*dynamic_cast<Serie*>(medias_[index].get()) -= numSaison;
}

// To do
void Librairie::ajouterEpisode(const std::string& nomSerie, unsigned int numSaison,
                               std::unique_ptr<Episode> episode)
{
	size_t index = trouverIndexMedia(nomSerie);

	if (index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
		dynamic_cast<Serie*>(medias_[index].get())->ajouterEpisode(numSaison, move(episode));
}


void Librairie::retirerEpisode(const std::string& nomSerie, unsigned int numSaison,
                               unsigned int numEpisode)
{
	size_t index = trouverIndexMedia(nomSerie);

	if (index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
		dynamic_cast<Serie*>(medias_[index].get())->retirerEpisode(numSaison, numEpisode);
}

//! Méthode qui charge les series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un serie à un
//! auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerMediasDepuisFichier(const std::string& nomFichier,
                                           GestionnaireAuteurs& gestionnaireAuteurs)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		for (size_t i = 0; i < medias_.size(); i++)
		{
			std::string nomAuteur = medias_[i]->getAuteur()->getNom();
			gestionnaireAuteurs.chercherAuteur(nomAuteur)->setNbMedias(0);
		}
		
		
		medias_.clear();

		std::string ligne;
		while (std::getline(fichier, ligne))
		{
			if (lireLigneMedia(ligne, gestionnaireAuteurs) == false)
			{
				return false;
			}
		}
		return true;
	}
	std::cerr << "Le fichier " << nomFichier
		<< " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
	return false;
}

//! Méthode qui charge les restrictions des series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (size_t i = 0; i < medias_.size(); i++)
            medias_[i]->supprimerPaysRestreints();

        std::string ligne;
        while (getline(fichier, ligne))
            if (!lireLigneRestrictions(ligne))
                return false;

        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

// To do
size_t Librairie::getNbMedias() const
{
	return medias_.size();
}

// To do
std::ostream& operator<<(std::ostream& os, const Librairie& librairie)
{
	for (const auto& media : librairie.medias_)
	{
		if (media->getTypeMedia() == Media::TypeMedia::Film)
			media->afficher(os);
	}
	for (const auto& media : librairie.medias_)
	{
		if (media->getTypeMedia() == Media::TypeMedia::Serie)
			media->afficher(os);
	}
	return os;
}

// To do
size_t Librairie::trouverIndexMedia(const std::string& nomMedia) const
{
	for (size_t i = 0; i < medias_.size(); i++)
	{
		if (medias_[i]->getNom() == nomMedia)
			return i;
	}
	
	return MEDIA_INEXSISTANT;
}

// To do
Librairie& Librairie::operator+=(std::unique_ptr<Media> media)
{
	if (media == nullptr)
	{
		return *this;
	}
	medias_.push_back(move(media));
	return *this;
}

// To do
Librairie& Librairie::operator-=(const std::string& nomMedia)
{
	size_t indexFilm = trouverIndexMedia(nomMedia);
	if (indexFilm == MEDIA_INEXSISTANT)
	{
		return *this;
	}

	medias_[indexFilm] = std::move(medias_[medias_.size() - 1]);
	medias_.pop_back();
	/*const Auteur* auteur = medias_[indexFilm]->getAuteur();
	auteur->setNbMedias(auteur->getNbMedias() - 1);*/

	return *this;
}

// To do
Media* Librairie::chercherMedia(const std::string& nomMedia, Media::TypeMedia typeMedia)
{
	size_t index = trouverIndexMedia(nomMedia);

	if (index != MEDIA_INEXSISTANT)
	{
		Media* media = medias_[index].get();
		if (medias_[index]->getTypeMedia() == typeMedia)
			return media;
	}
	
	return nullptr;
}

// To do
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomMedia;
	int typeMedia;
	
	if (stream >> typeMedia >> std::quoted(nomMedia))
	{
		Media* media = chercherMedia(nomMedia, to_enum<Media::TypeMedia>(typeMedia));
		if (media == nullptr)
		{
			return false;
		}

		int paysValeurEnum;
		while (stream >> paysValeurEnum)
		{
			media->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));
		}
		return true;
	}
	return false;
}

// To do
bool Librairie::lireLigneMedia(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    lireLigneMediaFunction fonctionLireligne[] = {&Librairie::lireLigneFilm,
                                                  &Librairie::lireLigneSerie,
                                                  &Librairie::lireLigneSaison,
                                                  &Librairie::lireLigneEpisode};
    std::istringstream stream(ligne);
    int typeMediaValeurEnum;

    if (stream >> typeMediaValeurEnum)
        return invoke(fonctionLireligne[typeMediaValeurEnum], *this, stream, gestionnaireAuteurs);

    return false;
}

// To do
const std::vector<std::unique_ptr<Media>>& Librairie::getMedias() const
{
	return medias_;
}

// To do
bool Librairie::lireLigneEpisode(std::istream& is, GestionnaireAuteurs&)
{
	int numero;
	std::string nom;
	std::string duree;
	std::string nomSerie;
	int numSaison;

	if (is >> numero >> std::quoted(nom) >> std::quoted(duree) >> std::quoted(nomSerie) >> numSaison)
	{
		Episode episode(numero, nom, duree);
		ajouterEpisode(nomSerie, numSaison, std::make_unique<Episode>(episode));
		return true;
	}
	return false;
}

// To do
bool Librairie::lireLigneSaison(std::istream& is, GestionnaireAuteurs&)
{
	int numeroSaison;
	int nbEpParSaisons;
	std::string nomSerie;
	
	if (is >> numeroSaison >> nbEpParSaisons >> std::quoted(nomSerie))
	{
		Saison saison(numeroSaison, nbEpParSaisons);
		ajouterSaison(nomSerie, std::make_unique<Saison>(saison));
		return true;
	}
	return false;
}

// To do
bool Librairie::lireLigneSerie(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
	std::string nomAuteur;
	is >> std::quoted(nomAuteur);
	Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);

	Serie serie(auteur);

	if (serie.lire(is))
	{
		auteur->setNbMedias(auteur->getNbMedias() + 1);

		*this +=  std::make_unique<Serie>(serie);

		return true;
	}
	return false;
}

// To do
bool Librairie::lireLigneFilm(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
	std::string nomAuteur;
	is >> std::quoted(nomAuteur);
	Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);

	Film film(auteur);
	
	if (film.lire(is))
	{
		auteur->setNbMedias(auteur->getNbMedias() + 1);

		*this += std::make_unique<Film>(film);
		
		return true;
	}
	return false;
}

// To do
size_t Librairie::getNbFilms() const
{
	unsigned nbFilms = 0;
	for (size_t i = 0; i < medias_.size(); i++)
	{
		if (medias_[i]->getTypeMedia() == Media::TypeMedia::Film)
			++nbFilms;
	}

	return nbFilms;
}

// To do
size_t Librairie::getNbSeries() const
{
	unsigned nbSeries = 0;
	for (size_t i = 0; i < medias_.size(); i++)
	{
		if (medias_[i]->getTypeMedia() == Media::TypeMedia::Serie)
			++nbSeries;
	}

	return nbSeries;
}

// To do
size_t Librairie::getNbSaisons(const std::string& nomSerie) const
{
	size_t index = trouverIndexMedia(nomSerie);
	if (index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
		return dynamic_cast<Serie*>(medias_[index].get())->getNbSaisons();
	else
		return 0;
}

// To do
size_t Librairie::getNbEpisodes(const std::string& nomSerie, const unsigned int numSaison) const
{
	size_t index = trouverIndexMedia(nomSerie);
	if (index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
		return dynamic_cast<Serie*>(medias_[index].get())->getSaison(numSaison)->getNbEpisodes();
	else
		return 0;
}
