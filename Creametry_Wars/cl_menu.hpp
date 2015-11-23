
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_menu.hpp
// Description : c'est la classe du menu

// SINGLETON

#pragma once

#include "header_libs.hpp"


class Menu
{
protected:

	Menu();
	~Menu();

	Data_sfml* m_pData_sfml;
	Graph* m_pGraph;
	Joueur* m_pJoueur;
	Sound* m_pSound;
	Niveau* m_pNiveau;

	int m_iEtatMenu;

public:

	static Menu* GetSingleton();

	void Traiter_Menu();
	void Afficher_Menu();
	void Afficher_High_Scores();
	void Saisir_Nom();
};