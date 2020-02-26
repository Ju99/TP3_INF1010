#ifndef GESTIONNAIRESAISONS_H
#define GESTIONNAIRESAISONS_H

#include <limits>
#include "Saison.h"

class GestionnaireSaisons
{
public:
    static constexpr size_t SAISON_INEXSISTANTE = std::numeric_limits<std::size_t>::max();

    GestionnaireSaisons() = default;
    ~GestionnaireSaisons();

    GestionnaireSaisons& operator+=(std::unique_ptr<Saison> saison);
    GestionnaireSaisons& operator-=(unsigned int numSaison);

    void ajouterEpisode(unsigned int numSaison, std::unique_ptr<Episode> episode);
    void retirerEpisode(unsigned int numSaison, unsigned int numEpisode);

    virtual std::ostream& afficher(std::ostream& os) const = 0;

    Saison* getSaison(unsigned int numSaison) const;
    size_t getNbSaisons() const;

protected:
    size_t trouverIndexSaison(const unsigned int numSaison) const;

    // Attribute
    std::vector<std::unique_ptr<Saison>> saisons_;
};
#endif // GESTIONNAIRESAISONS_H