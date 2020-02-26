#include "Saison.h"

// To do
Saison::Saison() :
    numSaison_(0),
	nbEpisodesmax_(0)
{
}

// To do
Saison::Saison(unsigned int numSaison, unsigned int nbEpisodemax) :
    numSaison_(numSaison),
	nbEpisodesmax_(nbEpisodemax)
{
}

// To do
Saison::Saison(const Saison& saison):
	Saison (saison.numSaison_, saison.nbEpisodesmax_)
{
	for (size_t i = 0; i < saison.episodes_.size(); i++)
		episodes_.push_back(std::make_unique<Episode>(*saison.episodes_[i]));
}

// To do
Saison::~Saison()
{
	episodes_.clear();
}

// To do
Saison& Saison::operator+=(std::unique_ptr<Episode> episode)
{
	size_t indexEpisode = trouverIndexEpisode(episode->getNumEpisode());
	if (indexEpisode != EPISODE_INEXSISTANTE && episodes_[indexEpisode]->operator==(episode->getNumEpisode()))
		*this -= episode->getNumEpisode();
	
	episodes_.push_back(move(episode));
	sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
	return *this;
}

// To do
Saison& Saison::operator-=(unsigned int numEpisode)
{
	unsigned int indexEpisode = trouverIndexEpisode(numEpisode);
	if (indexEpisode == EPISODE_INEXSISTANTE)
		return *this;
	episodes_[indexEpisode] = std::move(episodes_[episodes_.size() - 1]);
	episodes_.pop_back();
	sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
	return *this;
}

// To do
bool Saison::operator==(unsigned int numSaison)
{
	return (numSaison_ == numSaison);
}

// To do
std::ostream& operator<<(std::ostream& os, const Saison& saison)
{
	os << "\tSaison " << std::setfill('0') << std::setw(2) <<saison.numSaison_ << ": " << saison.getNbEpisodes() << "/" 
		<< saison.nbEpisodesmax_;
	if (saison.getNbEpisodes() == saison.nbEpisodesmax_)
		os << "(Terminee)";
	else
		os << "(En cours)";
	os << "\n";
	for (unsigned int i = 0; i < saison.getNbEpisodes(); i++)
		os << *saison.episodes_[i];
	os << "\n";
	
	return os;
}

// To do
std::istream& operator>>(std::istream& is, Saison& saison)
{
	return is >> saison.numSaison_ >> saison.nbEpisodesmax_;
}

// To do
unsigned int Saison::getNumSaison() const
{
	return numSaison_;
}

// To do
size_t Saison::getNbEpisodes() const
{
	return episodes_.size();
}

// To do
size_t Saison::trouverIndexEpisode(unsigned int numEpisode)
{
	for (unsigned int i = 0; i < getNbEpisodes(); i++)
	{
		if (episodes_[i]->getNumEpisode() == numEpisode)
			return i;
	}
	return EPISODE_INEXSISTANTE;
}