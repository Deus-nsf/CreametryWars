
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_ennemi_base.hpp
// Description : c'est la classe fille d'un ennemi de base

// FILLE -> Ennemi

#pragma once

#include "header_libs.hpp"
#include "cl_ennemi.hpp"


class Ennemi_Base : public Ennemi
{
protected:

	// membres herites : 

	/*
	sf::Sprite * ImageEnnemi;
	float PosX;
	float PosY;
	sf::Vector2f VecteurOrientation;
	sf::Clock TimerExplosion;
	float SpeedFactor;
	float AngleRad;
	int PtsDeVie;
	int EstEnVie;
	*/

public:

	Ennemi_Base();
	virtual ~Ennemi_Base();

	virtual Ennemi* clone();
	virtual void Comportement();

	// methodes herites :

	/*
	void Touche();
	void Calculer_Orientation();
	void Meurt();
	void VerifieEtat();
	
	void SetPosition(float, float);

	float GetPosX();
	float GetPosY();
	*/
};