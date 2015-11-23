
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_ennemi_fantome.hpp
// Description : les methodes de la classe Ennemi_Fantome

#include "cl_game.hpp"


// constructeurs
Ennemi_Fantome::Ennemi_Fantome() : Ennemi()
{
	ImageEnnemi = Graph::GetSingleton()->GetSprites()->at(e_Ennemi_2);
	SpeedFactor = 6.5f;
	PtsDeVie = 4;
	EstEnVie = 1;
}


// destructeurs
Ennemi_Fantome::~Ennemi_Fantome()
{}


Ennemi* Ennemi_Fantome::clone()
{
	return new Ennemi_Fantome(*this);
}


// comportement de l'ennemi de base
void Ennemi_Fantome::Comportement()
{
	if(PtsDeVie > 0)
	{
		if( ((AngleRad - Joueur::GetSingleton()->GetAngleRad()) < 1.5f) && 
			((AngleRad - Joueur::GetSingleton()->GetAngleRad()) > -1.5f) )
		{
			PosX += VecteurOrientation.x * SpeedFactor;
			PosY += VecteurOrientation.y * SpeedFactor;
		}
	}
}