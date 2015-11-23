
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_game.hpp
// Description : c'est la classe generale du programme

// SINGLETON & FACADE

#pragma once

#include "cl_data_sfml.hpp"
#include "cl_graph.hpp"
#include "cl_joueur.hpp"
#include "cl_sound.hpp"
#include "cl_niveau.hpp"
#include "cl_menu.hpp"
#include "cl_ennemi.hpp"
#include "cl_ennemi_base.hpp"
#include "cl_ennemi_fantome.hpp"


enum GAMESTATES_E
{
	e_MenuGS,
	e_HighScoresGS,
	e_Jeu,
	e_Quitter,
};


struct JOUEUR
{
	char s_Nom[100];
	long int s_Score;
	int s_Temps_max;
};


class Game
{
protected:

	Game();
	~Game();

	Data_sfml* m_pData_sfml;
	Graph* m_pGraph;
	Sound* m_pSound;
	Joueur* m_pJoueur;
	Menu* m_pMenu;
	Niveau* m_pNiveau;

	int m_GameState;

public:

	static Game* GetSingleton();

	int GetGamestate() const;

	void SetGamestate(int _Gamestate);
                                      
	void Initialiser();
	void Faux_Scores();
	void Enregistrer_Joueur();
	void Desinitialiser();
};