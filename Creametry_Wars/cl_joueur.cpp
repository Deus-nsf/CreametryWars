
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_joueur.cpp
// Description : les methodes de la classe Joueur

#include "cl_game.hpp"


// constructeurs
Joueur::Joueur()
{
	Score = 0;
	Temps_max = 0;
	Vies = 30;
	Bombes = 3;

	MoveFactor = 6.0f;
	PosX = 50.0f;
	PosY = 50.0f;
	VecteurOrientation.x = 0.0f;
	VecteurOrientation.y = 0.0f;
	AngleRad = 0.0f;

	BOMB_radius = 0;
	BOMB_opacity = 255;

	JCsBOMB.setOutlineThickness(5);

	m_pHorlogeNiveau = Data_sfml::GetSingleton()->GetHorloge();
	m_pHorlogeNiveau->restart();
}


// destructeurs
Joueur::~Joueur()
{
	while (ListeTirs.size() > 0)
	{
		ListeTirs.pop_back();
	}
}


// singleton
Joueur* Joueur::GetSingleton()
{
	static Joueur oJoueur;
	return &oJoueur;
}


// mutateurs
void Joueur::SetNom(char* _Nom)
{
	strcpy(Nom, _Nom);
}


void Joueur::SetSprite(sf::Sprite* _pSprite)
{
	m_pSpriteJoueur = _pSprite;
}


// accesseurs
const char* Joueur::GetNom() const
{
	return Nom;
}


int Joueur::GetScore() const
{
	return Score;
}


int Joueur::GetTemps_max() const
{
	return Temps_max;
}


int Joueur::GetVies() const
{
	return Vies;
}


int Joueur::GetBombes() const
{
	return Bombes;
}


sf::Sprite* Joueur::GetSprite()
{
	return m_pSpriteJoueur;
}


float Joueur::GetPosX()
{
	return PosX;
}


float Joueur::GetPosY()
{
	return PosY;
}



float Joueur::GetAngleRad()
{
	return AngleRad;
}



std::vector<Tir>* Joueur::GetListeTirs()
{
	return &ListeTirs;
}


sf::CircleShape* Joueur::GetJCsBOMB()
{
	return &JCsBOMB;
}



// permet de calculer la rotation du sprite en radiants
void Joueur::Calculer_Orientation()
{
	VecteurOrientation.x = (float)sf::Mouse::getPosition(*Data_sfml::GetSingleton()->GetFenetre()).x;
	VecteurOrientation.y = (float)sf::Mouse::getPosition(*Data_sfml::GetSingleton()->GetFenetre()).y;

	VecteurOrientation.x -= 400;
	VecteurOrientation.y -= 300;

	AngleRad = atan2(VecteurOrientation.x, VecteurOrientation.y);
}



// mutateurs
void Joueur::SetPosX(float _PosX)
{
	PosX = _PosX;
}

void Joueur::SetPosY(float _PosY)
{
	PosY = _PosY;
}

void Joueur::SetScore(long int _Score)
{
	Score = _Score;
}


void Joueur::SetTemps_max(int _Temps_max)
{
	Temps_max = _Temps_max;
}


void Joueur::SetVies(int _Vies)
{
	Vies = _Vies;
}


void Joueur::SetBombes(int _Bombes)
{
	Bombes = _Bombes;
}





//  methodes de deplacement
void Joueur::MoveRight()
{
	PosX += MoveFactor;
}

void Joueur::MoveLeft()
{
	PosX -= MoveFactor;
}

void Joueur::MoveUp()
{
	PosY -= MoveFactor;
}

void Joueur::MoveDown()
{
	PosY += MoveFactor;
}


void Joueur::Tirer()
{
	ListeTirs.push_back( Tir() );
}


// OH MY GOD JC IT'S A BOMB !
void Joueur::A_BOMB()
{
	if(m_pHorlogeBombes.getElapsedTime().asMilliseconds() > 60)
	{
		BOMB_radius += 0.4f;
		BOMB_opacity -= 0.08f;
	}

	JCsBOMB.setRadius(BOMB_radius);
	JCsBOMB.setOrigin(BOMB_radius, BOMB_radius);
	JCsBOMB.setOutlineColor(sf::Color(255, 0, 0, (int)BOMB_opacity));
	JCsBOMB.setFillColor(sf::Color(255, 0, 0, (int)(BOMB_opacity/1.5f)));

	Data_sfml::GetSingleton()->GetFenetre()->draw(JCsBOMB);

	if(BOMB_radius > 1200)
	{
		Niveau::GetSingleton()->Setbool_BOMB(0);
		BOMB_radius = 0;
		BOMB_opacity = 255;
	}
}
// A BOMB !