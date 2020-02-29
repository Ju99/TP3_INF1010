/****************************************************************************
* Fichier: Librairie.cpp
* Auteur : Aldric Lopez et Juliette Morin
* Date :  12 févr. 2020
* Mise a jour : 29 févr. 2020
* Description : Implémentation de la classe Librairie
* ***************************************************************************/

#include "Librairie.h"

//! Constructeur de copie de la classe Librairie
Librairie::Librairie(const Librairie& librairie)
{
	*this = librairie;
}

//! Operateur qui affecte une librairie à une autre
//! /param Librairie	La librairie à affecter
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

//! Méthode qui retourne un film comportant le même nom que celui envoyé en paramètre
//! \param nomFilm Le nom du film à chercher
//! \return        Un pointeur vers le film. Nullptr si le film n'existe pas
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
	Media* media = chercherMedia(nomFilm, Media::TypeMedia::Film);
	if (!media)
		return nullptr;
	return dynamic_cast<Film*>(media);
}

//! Méthode qui cherche une série comportant le même nom que celui envoyé en paramètre
//! \param nomSerie		Le nom de la série à chercher
//! \return				Un pointeur vers la série. Nullptr si la série n'existe pas
Serie* Librairie::chercherSerie(const std::string& nomSerie)
{
	Media* media = chercherMedia(nomSerie, Media::TypeMedia::Serie);
	if (media == nullptr)
		return nullptr;
	return dynamic_cast<Serie*>(media);
}

//! Méthode qui ajoute une saison comportant le même nom que celui envoyé en paramètre
//! \param nomSerie		Le nom de la série à chercher
//! \param saison		Pointeur unique d'une saison
void Librairie::ajouterSaison(const std::string& nomSerie, std::unique_ptr<Saison> saison)
{
	size_t index = trouverIndexMedia(nomSerie);

	if (index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
		*dynamic_cast<Serie*>(medias_[index].get()) += move(saison);
}

//! Méthode qui retire une saison comportant le même nom que celui envoyé en paramètre
//! \param nomSerie		Le nom de la série à chercher
//! \param numSaison	Le numéro de la saison
void Librairie::retirerSaison(const std::string& nomSerie, unsigned int numSaison)
{
	size_t index = trouverIndexMedia(nomSerie);

	if (index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
		*dynamic_cast<Serie*>(medias_[index].get()) -= numSaison;
}

//! Méthode qui ajoute un épisode comportant le même nom que celui envoyé en paramètre
//! \param nomSerie		Le nom de la série à chercher
//! \param numSaison	Le numéro de la saison
//! \param episode		Pointeur unique d'un épisode
void Librairie::ajouterEpisode(const std::string& nomSerie, unsigned int numSaison,
                               std::unique_ptr<Episode> episode)
{
	size_t index = trouverIndexMedia(nomSerie);

	if (index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
		dynamic_cast<Serie*>(medias_[index].get())->ajouterEpisode(numSaison, move(episode));
}

//! Méthode qui retire un épisode comportant le même nom que celui envoyé en paramètre
//! \param nomSerie		Le nom de la série à chercher
//! \param numSaison	Le numéro de la saison
//! \param numEpisode	Le numéro d'épisode
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

//! Méthode qui retourne le nombre de medias
//! \return		Le nombre de medias
size_t Librairie::getNbMedias() const
{
	return medias_.size();
}

//! Opérateur qui affiche tous les attributs de la librairie
//! \param os			Le stream dans lequel afficher
//! \param saison		La librairie à afficher
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

//! Méthode qui retourne l'index du média recherché
//! \param nomMedia		Le nom du média à chercher
//! \return				L'index du média recherché s'il existe, sinon MEDIA_INEXSISTANT
size_t Librairie::trouverIndexMedia(const std::string& nomMedia) const
{
	for (size_t i = 0; i < medias_.size(); i++)
	{
		if (medias_[i]->getNom() == nomMedia)
			return i;
	}
	
	return MEDIA_INEXSISTANT;
}

//! Opérateur qui ajoute un média
//! \param media			Un pointeur de média à ajouter
//! \return					La librairie avec le média ajouté
Librairie& Librairie::operator+=(std::unique_ptr<Media> media)
{
	if (media == nullptr)
	{
		return *this;
	}
	medias_.push_back(move(media));
	return *this;
}

//! Opérateur qui retire un média
//! \param nomMedia			Le nom du média à retirer
//! \return					La librairie avec le média retiré
Librairie& Librairie::operator-=(const std::string& nomMedia)
{
	size_t indexFilm = trouverIndexMedia(nomMedia);
	if (indexFilm == MEDIA_INEXSISTANT)
	{
		return *this;
	}

	medias_[indexFilm] = std::move(medias_[medias_.size() - 1]);
	medias_.pop_back();

	return *this;
}

//! Méthode qui retourne l'index du média recherché
//! \param nomMedia		Le nom du média à chercher
//! \param typeMedia	Le type de média à chercher
//! \return				L'index du média recherché s'il existe, sinon nullptr
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

//! Méthode qui lit une ligne
//! \param ligne		Le string comportant les restrictions
//! \return				Un Bool représentant si la lecture est un succès ou non
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

//! Méthode qui lit une ligne
//! \param ligne				Le string comportant les attributs d'un média
//! \param gestionnaireAuteurs	Le gestionnaire des auteurs qui associe le média à un auteur
//! \return						Un Bool représentant si la lecture est un succès ou non
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

//! Méthode qui retourne un vecteur de pointeur unique de medias
//! \return		Le vecteur de medias
const std::vector<std::unique_ptr<Media>>& Librairie::getMedias() const
{
	return medias_;
}

//! Méthode qui lit une ligne
//! \param ligne				Le string comportant les attributs d'un épisode
//! \param gestionnaireAuteurs	Le gestionnaire des auteurs qui associe l'épisode à un auteur
//! \return						Un Bool représentant si la lecture est un succès ou non
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

//! Méthode qui lit une ligne
//! \param ligne				Le string comportant les attributs d'une saison
//! \param gestionnaireAuteurs	Le gestionnaire des auteurs qui associe une saison à un auteur
//! \return						Un Bool représentant si la lecture est un succès ou non
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

//! Méthode qui lit une ligne
//! \param ligne				Le string comportant les attributs d'une série
//! \param gestionnaireAuteurs	Le gestionnaire des auteurs qui associe une série à un auteur
//! \return						Un Bool représentant si la lecture est un succès ou non
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

//! Méthode qui lit une ligne
//! \param ligne				Le string comportant les attributs d'un film
//! \param gestionnaireAuteurs	Le gestionnaire des auteurs qui associe le film à un auteur
//! \return						Un Bool représentant si la lecture est un succès ou non
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

//! Méthode qui retourne le nombre de films de la librairie
//! \return		Le nombre de films
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

//! Méthode qui retourne le nombre de série de la librairie
//! \return		Le nombre de série
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

//! Méthode qui retourne le nombre de saisons de la librairie
//! \return		Le nombre de saisons
size_t Librairie::getNbSaisons(const std::string& nomSerie) const
{
	size_t index = trouverIndexMedia(nomSerie);
	if (index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
		return dynamic_cast<Serie*>(medias_[index].get())->getNbSaisons();
	else
		return 0;
}

//! Méthode qui retourne le nombre d'épisode de la librairie
//! \return		Le nombre d'épisode
size_t Librairie::getNbEpisodes(const std::string& nomSerie, const unsigned int numSaison) const
{
	size_t index = trouverIndexMedia(nomSerie);
	if (index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Serie)
		return dynamic_cast<Serie*>(medias_[index].get())->getSaison(numSaison)->getNbEpisodes();
	else
		return 0;
}
