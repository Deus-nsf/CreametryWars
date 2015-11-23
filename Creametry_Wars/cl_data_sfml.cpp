
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_data_sfml.cpp
// Description : les methodes de la classe Data_sfml

#include "cl_game.hpp"


// constructeurs
Data_sfml::Data_sfml()
{
	Fenetre.create(sf::VideoMode(800, 600, 32), "Creametry Wars", sf::Style::Close);
	Fenetre.setKeyRepeatEnabled(false);
	Fenetre.setVerticalSyncEnabled(false);
	Horloge.restart();
	CameraHud = Fenetre.getDefaultView();
}


// destructeurs
Data_sfml::~Data_sfml()
{}


// singleton
Data_sfml* Data_sfml::GetSingleton()
{
	static Data_sfml oData_sfml;
	return &oData_sfml;
}


// accesseurs
sf::RenderWindow* Data_sfml::GetFenetre()
{
	return &Fenetre;
}

sf::Event* Data_sfml::GetEvenements()
{
	return &Evenements;
}

sf::Clock* Data_sfml::GetHorloge()
{
	return &Horloge;
}

sf::View* Data_sfml::GetCameraHud()
{
	return &CameraHud;
}

sf::View* Data_sfml::GetCameraJeu()
{
	return &CameraJeu;
}


// mutateurs
void Data_sfml::SetCameraJeu()
{
	Joueur* m_pJoueur = Joueur::GetSingleton();

	CameraJeu.setCenter( sf::Vector2f( m_pJoueur->GetPosX(), m_pJoueur->GetPosY() ));
	CameraJeu.setSize(800, 600);
}