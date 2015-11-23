
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_tir.hpp
// Description : c'est la classe de gestion des tirs


#pragma once

#include "header_libs.hpp"


class Tir
{
protected:

	sf::CircleShape CercleTir;
	sf::Vector2f DirectionTir;

	float PosX;
	float PosY;
	float SpeedFactor;

	Data_sfml* m_pData_sfml;

public:

	Tir();
	~Tir();

	sf::CircleShape* GetCircle();

	float GetPosX();
	float GetPosY();

	void SetDirection();
	void SetPosition();
	void Avancer();
};