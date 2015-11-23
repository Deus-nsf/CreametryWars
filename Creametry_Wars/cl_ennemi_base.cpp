
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_ennemi_base.hpp
// Description : les methodes de la classe Ennemi_Base

#include "cl_game.hpp"


// constructeurs
Ennemi_Base::Ennemi_Base() : Ennemi()
{
	ImageEnnemi = Graph::GetSingleton()->GetSprites()->at(e_Ennemi_1);
	SpeedFactor = 3.0f;
	PtsDeVie = 8;
	EstEnVie = 1;
}


// destructeurs
Ennemi_Base::~Ennemi_Base()
{}


Ennemi* Ennemi_Base::clone()
{
	return new Ennemi_Base(*this);
}


// comportement de l'ennemi de base
void Ennemi_Base::Comportement()
{
	if(PtsDeVie > 0)
	{
		PosX += VecteurOrientation.x * SpeedFactor;
		PosY += VecteurOrientation.y * SpeedFactor;
	}
}