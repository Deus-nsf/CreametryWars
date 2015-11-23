
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_joueur.hpp
// Description : c'est la classe des donnees du joueur

// SINGLETON

#pragma once

#include "header_libs.hpp"
#include "cl_tir.hpp"


class Joueur
{
protected:

	Joueur();
	~Joueur();

	char Nom[100];
	long int Score;
	int Temps_max;
	int Vies;
	int Bombes;

	sf::CircleShape JCsBOMB;

	float BOMB_radius;
	float BOMB_opacity;

	float MoveFactor;
	float PosX, PosY;
	sf::Vector2f VecteurOrientation;
	float AngleRad;

	std::vector<Tir> ListeTirs;

	sf::Clock* m_pHorlogeNiveau;
	sf::Clock m_pHorlogeBombes;
	sf::Sprite* m_pSpriteJoueur;

public:

	static Joueur* GetSingleton();

	void SetNom(char *);
	void SetSprite(sf::Sprite*);

	const char* GetNom() const;
	int GetScore() const;
	int GetTemps_max() const;
	int GetVies() const;
	int GetBombes() const;

	sf::Sprite* GetSprite();
	float GetPosX();
	float GetPosY();
	float GetAngleRad();
	std::vector<Tir>* GetListeTirs();
	sf::CircleShape* GetJCsBOMB();

	void Calculer_Orientation();

	void SetPosX(float);
	void SetPosY(float);

	void SetScore(long int);
	void SetTemps_max(int);
	void SetVies(int);
	void SetBombes(int);

	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();

	void Tirer();
	void A_BOMB();
};