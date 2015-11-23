
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_ennemi.hpp
// Description : les methodes de la classe Ennemi

#include "cl_game.hpp"

int Ennemi::PointsAccumules = 0;

// constructeurs
Ennemi::Ennemi()
{
	PosX = (rand() % 2000) + 100.0f;
	PosY = (rand() % 1500) + 100.0f;
	PointsPourBombe = 100000;
}


// destructeurs
Ennemi::~Ennemi()
{}


// quand un ennemi se fait toucher
void Ennemi::Touche()
{
	if(PtsDeVie >= 0)
	{
		--PtsDeVie;
	}
}


// calcule l'orientation de l'ennemi en fonction de la position du joueur
void Ennemi::Calculer_Orientation()
{
	VecteurOrientation.x = Joueur::GetSingleton()->GetPosX();
	VecteurOrientation.y = Joueur::GetSingleton()->GetPosY();

	VecteurOrientation.x -= PosX;
	VecteurOrientation.y -= PosY;

	// normalisation
	float fTemp = VecteurOrientation.x;

	VecteurOrientation.x = fTemp / (sqrt(fTemp * fTemp + VecteurOrientation.y * VecteurOrientation.y));
	VecteurOrientation.y = VecteurOrientation.y / (sqrt(fTemp * fTemp + VecteurOrientation.y * VecteurOrientation.y));

	AngleRad = atan2(VecteurOrientation.x, VecteurOrientation.y);
}



// verifie si l'ennemi est en vie ou non
void Ennemi::VerifieEtat()
{
	if(PtsDeVie == 0)
	{
		PtsDeVie = -1;
		ImageEnnemi = Graph::GetSingleton()->GetSprites()->at(e_Explosion);
		TimerExplosion.restart();
	}

	if((PtsDeVie == -1) && (TimerExplosion.getElapsedTime().asSeconds() >= 0.5f))
	{
		Meurt();
	}
}


// regarde si un ennemi est mort
void Ennemi::Meurt()
{
	EstEnVie = 0;
	Joueur::GetSingleton()->SetScore(Joueur::GetSingleton()->GetScore() + 500);
	PointsAccumules += 500;

	if(PointsAccumules >= PointsPourBombe)
	{
		Joueur::GetSingleton()->SetBombes(Joueur::GetSingleton()->GetBombes() + 1);
		PointsAccumules = 0;
	}
}


// regle la position initiale d'un ennemi
void Ennemi::SetPosition(float _PosX, float _PosY)
{
	PosX = _PosX;
	PosY = _PosY;
}



// test temporaire bombe
void Ennemi::SetPtsDeVie(int _PtsDeVie)
{
	PtsDeVie = _PtsDeVie;
}



// accesseurs
int Ennemi::GetEstEnVie()
{
	return EstEnVie;
}



sf::Sprite* Ennemi::GetImage()
{
	return ImageEnnemi;
}



float Ennemi::GetAngleRad()
{
	return AngleRad;
}



float Ennemi::GetPosX()
{
	return PosX;
}


float Ennemi::GetPosY()
{
	return PosY;
}