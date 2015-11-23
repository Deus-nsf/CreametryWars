
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_data_sfml.hpp
// Description : c'est la classe des donnees de la SFML

// SINGLETON

#pragma once

#include "header_libs.hpp"


class Data_sfml
{
protected:

	Data_sfml();
	~Data_sfml();

	sf::RenderWindow Fenetre;
	sf::Clock Horloge;
	sf::Event Evenements;
	sf::View CameraJeu;
	sf::View CameraHud;

public:

	static Data_sfml* GetSingleton();

	sf::RenderWindow* GetFenetre();
	sf::Event* GetEvenements();
	sf::Clock* GetHorloge();
	sf::View* GetCameraJeu();
	sf::View* GetCameraHud();

	void SetCameraJeu();
};