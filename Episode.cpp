#include "Episode.h"

// To do
Episode::Episode() :
	numEpisode_(0),
	nom_("Unknown"),
	duree_("Unknown")
{
}

// To do
Episode::Episode(unsigned int numEpisode, const std::string& nom, const std::string& duree) :
	numEpisode_(numEpisode),
	nom_(nom),
	duree_(duree)
{
}

// To do
bool Episode::operator==(unsigned int numEpisode)
{
	return (numEpisode_ == numEpisode);
}

// To do
std::ostream& operator<<(std::ostream& os, const Episode& episode)
{
	os << "\t\tEpisode " << std::setfill('0') << std::setw(2) << episode.numEpisode_ << ": " << episode.nom_ << " | Duree: "
		<< episode.duree_ << "\n";

	//allignement des durees

	return os;
}

// To do
std::istream& operator>>(std::istream& is, Episode& episode)
{
	return is >> episode.numEpisode_ >> quoted(episode.nom_ )>> quoted(episode.duree_);
}

// To do
unsigned int Episode::getNumEpisode() const
{
	return numEpisode_;
}