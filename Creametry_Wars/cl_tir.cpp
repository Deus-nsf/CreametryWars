
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_tir.cpp
// Description : les methodes pour gerer les tirs

#include "cl_game.hpp"


// constructeurs
Tir::Tir()
{
	int R, G, B;

	R = 255;
	G = rand() % 256;
	B = 0;

	SpeedFactor = 15.0f;

	m_pData_sfml = Data_sfml::GetSingleton();

	SetDirection();
	SetPosition();

	CercleTir.setRadius(4);
	CercleTir.setOutlineThickness(2);
	CercleTir.setFillColor(sf::Color(R, G, B, 255));
	CercleTir.setOutlineColor(sf::Color(R, G, B, 127));
}


// destructeurs
Tir::~Tir()
{}



// accesseurs
sf::CircleShape* Tir::GetCircle()
{
	return &CercleTir;
}


float Tir::GetPosX()
{
	return PosX;
}


float Tir::GetPosY()
{
	return PosY;
}



// permet de regler la direction de deplacement d'un tir
void Tir::SetDirection()
{
	DirectionTir.x =
		(float)sf::Mouse::getPosition(*Data_sfml::GetSingleton()->GetFenetre()).x - 400;
		

	DirectionTir.y =
		(float)sf::Mouse::getPosition(*Data_sfml::GetSingleton()->GetFenetre()).y - 300;

	// normalisation
	float fTemp = DirectionTir.x;

	DirectionTir.x = fTemp / (sqrt(fTemp * fTemp + DirectionTir.y * DirectionTir.y));
	DirectionTir.y = DirectionTir.y / (sqrt(fTemp * fTemp + DirectionTir.y * DirectionTir.y));
}


// SET POSITIOOON !!! QUI M'EMMENNE 10 GLACOOOOONS !!!
void Tir::SetPosition()
{
	PosX = Joueur::GetSingleton()->GetSprite()->getPosition().x + (32 * DirectionTir.x);
	PosY = Joueur::GetSingleton()->GetSprite()->getPosition().y + (32 * DirectionTir.y);

	CercleTir.setPosition(PosX, PosY);
}


// permet de regler la direction de deplacement d'un tir
void Tir::Avancer()
{
	PosX += DirectionTir.x * SpeedFactor;
	PosY += DirectionTir.y * SpeedFactor;

	CercleTir.setPosition(PosX, PosY);
}