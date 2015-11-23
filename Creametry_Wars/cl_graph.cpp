
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_graph.cpp
// Description : les methodes de la classe Graph

#include "cl_game.hpp"


// constructeurs
Graph::Graph()
{
	// attention a bien regler ceci en fonction des donnees de la spritesheet
	TailleSprite = 64;
	NbrLigneSS = 2;
	NbrColonneSS = 2;

	Charger_Sprites();
	Charger_Shapes();
	Charger_Textes();
}


// destructeurs
Graph::~Graph()
{
	while (Sprites.size() > 0)
	{
		delete Sprites.back();
		Sprites.pop_back();
	}

	while (Textures.size() > 0)
	{
		delete Textures.back();
		Textures.pop_back();
	}
}


// singleton
Graph* Graph::GetSingleton()
{
	static Graph oGraph;
	return &oGraph;
}



// chargement des textures et des sprites <!> l'ordre doit imperativement correspondre a l'ordre des enums TEXTURES_E et SPRITES_E
void Graph::Charger_Sprites()
{
	Textures.push_back(new sf::Texture());
	Textures.back()->loadFromFile("../Textures/menu.png");
	Sprites.push_back(new sf::Sprite());
	Sprites.back()->setTexture(*Textures[e_MenuSp]);

	Textures.push_back(new sf::Texture());
	Textures.back()->loadFromFile("../Textures/high_scores.png");
	Sprites.push_back(new sf::Sprite());
	Sprites.back()->setTexture(*Textures[e_HighScoresSp]);
	
	Textures.push_back(new sf::Texture());
	Textures.back()->loadFromFile("../Textures/fond_jeu.png");
	Sprites.push_back(new sf::Sprite());
	Sprites.back()->setTexture(*Textures[e_FondJeuSp]);

	Textures.push_back(new sf::Texture());
	Textures.back()->loadFromFile("../Textures/sprite_sheet.png");
	// création des sprites en fonction de la spritesheet
	for (int y = 0; y < NbrLigneSS; ++y)
	{
		for (int x = 0; x < NbrColonneSS; ++x)
		{
			Sprites.push_back(new sf::Sprite());
			Sprites.back()->setTexture(*Textures[e_SpriteSheet]);
			Sprites.back()->setTextureRect(sf::IntRect((x*TailleSprite) + x, (y*TailleSprite) + y, TailleSprite, TailleSprite));
			Sprites.back()->setOrigin(32.0f, 32.0f);
		}
	}

	Joueur::GetSingleton()->SetSprite(Graph::GetSingleton()->GetSprites()->at(e_VaisseauHeros));
}


// chargement des shapes <!> l'ordre doit imperativement correspondre a l'ordre de l'enum SHAPES_E
void Graph::Charger_Shapes()
{
	Rectangles.push_back(sf::RectangleShape(sf::Vector2f(350, 60)));
	Rectangles[e_CurseurMenu].setFillColor(sf::Color::Transparent);
	Rectangles[e_CurseurMenu].setOutlineColor(sf::Color::Red);
	Rectangles[e_CurseurMenu].setOutlineThickness(2);
	Rectangles[e_CurseurMenu].setPosition(210, 325);

	Rectangles.push_back(sf::RectangleShape(sf::Vector2f(2400, 1800)));
	Rectangles[e_LimitesMap].setFillColor(sf::Color(0, 255, 255, 15));
	Rectangles[e_LimitesMap].setOutlineColor(sf::Color(0, 255, 255, 255));
	Rectangles[e_LimitesMap].setOutlineThickness(5);
	Rectangles[e_LimitesMap].setPosition(0, 0);

	Rectangles.push_back(sf::RectangleShape(sf::Vector2f(2400, 0)));
	Rectangles[e_GridLineHor].setFillColor(sf::Color::Transparent);
	Rectangles[e_GridLineHor].setOutlineColor(sf::Color(0, 255, 255, 63));
	Rectangles[e_GridLineHor].setOutlineThickness(1);
	Rectangles[e_GridLineHor].setPosition(0, 0);

	Rectangles.push_back(sf::RectangleShape(sf::Vector2f(0, 1800)));
	Rectangles[e_GridLineVer].setFillColor(sf::Color::Transparent);
	Rectangles[e_GridLineVer].setOutlineColor(sf::Color(0, 255, 255, 63));
	Rectangles[e_GridLineVer].setOutlineThickness(1);
	Rectangles[e_GridLineVer].setPosition(0, 0);

	Rectangles.push_back(sf::RectangleShape(sf::Vector2f(700, 460)));
	Rectangles[e_Fond_HighScores].setFillColor(sf::Color(0, 0, 0, 191));
	Rectangles[e_Fond_HighScores].setOutlineColor(sf::Color(0, 255, 255, 127));
	Rectangles[e_Fond_HighScores].setOutlineThickness(2);
	Rectangles[e_Fond_HighScores].setPosition(50, 100);
}


// chargement des shapes <!> l'ordre doit imperativement correspondre a l'ordre de l'enum TEXTES_E
void Graph::Charger_Textes()
{
	Police.loadFromFile("../Fonts/OBLIVIOUSFONT.TTF");

	for(int i = 0; i < e_LIMIT; ++i)
	{
		Textes.push_back(sf::Text());
		Textes.back().setFont(Police);
		Textes.back().setCharacterSize(22);
		Textes.back().setColor(sf::Color::Yellow);
	}

	Textes[e_NomEtScore].setPosition(10, 10);	// va varier
	Textes[e_TempsEcoule].setPosition(580, 10);	// va varier
	Textes[e_NbrBombes].setPosition(10, 570);
	Textes[e_NbrVies].setPosition(650, 570);
}


// accesseurs
std::vector<sf::Sprite*>* Graph::GetSprites()
{
	return &Sprites;
}


std::vector<sf::RectangleShape>* Graph::GetRectangles()
{
	return &Rectangles;
}


std::vector<sf::Text>* Graph::GetTextes()
{
	return &Textes;
}


sf::Font* Graph::GetPolice()
{
	return &Police;
}