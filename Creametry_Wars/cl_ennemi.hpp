
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_ennemi.hpp
// Description : c'est la classe mere des ennemis

// MERE

#pragma once

#include "header_libs.hpp"


class Ennemi
{
protected:

	sf::Sprite * ImageEnnemi;
	float PosX;
	float PosY;
	sf::Vector2f VecteurOrientation;
	sf::Clock TimerExplosion;
	float SpeedFactor;
	float AngleRad;
	int PtsDeVie;
	int EstEnVie;
	int PointsPourBombe;
	static int PointsAccumules;

public:

	Ennemi();
	virtual ~Ennemi();

	virtual Ennemi* clone() = 0;
	virtual void Comportement() = 0;
	void Touche();
	void Calculer_Orientation();
	void Meurt();
	void VerifieEtat();
	
	void SetPosition(float, float);
	void SetPtsDeVie(int);

	sf::Sprite* GetImage();
	int GetEstEnVie();
	float GetAngleRad();
	float GetPosX();
	float GetPosY();
};