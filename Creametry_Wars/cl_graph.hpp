
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_graph.hpp
// Description : c'est la classe des elements graphiques du jeu

// SINGLETON

#pragma once

#include "header_libs.hpp"


enum TEXTURES_E
{
	e_Menu,
	e_HighScores,
	e_FondJeu,
	e_SpriteSheet,
};

enum SPRITES_E
{
	e_MenuSp,
	e_HighScoresSp,
	e_FondJeuSp,
	e_VaisseauHeros,
	e_Ennemi_1,
	e_Ennemi_2,
	e_Explosion,
};

enum SHAPES_E
{
	e_CurseurMenu,
	e_LimitesMap,
	e_GridLineHor,
	e_GridLineVer,
	e_Fond_HighScores,
};

enum TEXTES_E
{
	e_NomEtScore,
	e_TempsEcoule,
	e_NbrBombes,
	e_NbrVies,

	e_LIMIT,
};


class Graph
{
protected:

	Graph();
	~Graph();

	std::vector<sf::Texture*> Textures;
	std::vector<sf::Sprite*> Sprites;
	std::vector<sf::RectangleShape> Rectangles;
	std::vector<sf::Text> Textes;

	sf::Font Police;
	

	int TailleSprite;
	int NbrLigneSS;
	int NbrColonneSS;

public:
	
	static Graph* GetSingleton();

	void Charger_Sprites();
	void Charger_Shapes();
	void Charger_Textes();

	std::vector<sf::Sprite*>* GetSprites();
	std::vector<sf::RectangleShape>* GetRectangles();
	std::vector<sf::Text>* GetTextes();
	sf::Font* GetPolice();
};