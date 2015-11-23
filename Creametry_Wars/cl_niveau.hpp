
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_niveau.hpp
// Description : c'est la classe du niveau du jeu

// SINGLETON

#pragma once

#include "header_libs.hpp"
#include "cl_ennemi_base.hpp"
#include "cl_ennemi_fantome.hpp"


class Niveau
{
protected:

	Niveau();
	~Niveau();

	Data_sfml* m_pData_sfml;
	Graph* m_pGraph;
	Sound* m_pSound;
	Joueur* m_pJoueur;

	std::vector<Ennemi_Base> ListeEnnemis;
	std::vector<Ennemi_Fantome> ListeEnnemis_2;

	float TempsPourSpawn;
	float TempsPourSpawn_2;

	sf::Clock TempsNiveau;
	sf::Clock TempsPourUneVie;
	sf::Clock TempsSpawn;
	sf::Clock TempsSpawn_2;

	int bool_BOMB;

	float fDeltaCalcul;
	int iTempsPourUneVie;
	int iTailleMapX;
	int iTailleMapY;

public:

	static Niveau* GetSingleton();

	void Boucle_Niveau();

	void Avancer_Temps();

	void Affichage_Niveau();	// liste d'appels
	void Afficher_Map();
	void Afficher_Sprites();
	void Afficher_HUD();

	void Actions_Joueur();
	void Mouvements_Joueur();
	void Bouger_Tirs();

	void Gestion_Ennemis();
	void Collisions_Map();
	void Collisions_Tir_Ennemis();
	void Collisions_Joueur_Ennemis();

	void Mort_Joueur();

	int GetTailleMapX() const;
	int GetTailleMapY() const;

	void Setbool_BOMB(int);

	void Safe_Desinit();
};