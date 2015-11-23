
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_game_singleton.cpp
// Description : les methodes pour realiser la pattern singleton sur la classe Game

#include "cl_game.hpp"


// constructeurs
Game::Game()
{
	m_pData_sfml = Data_sfml::GetSingleton();
	m_pGraph = Graph::GetSingleton();
	m_pJoueur = Joueur::GetSingleton();
	m_pSound = Sound::GetSingleton();
	m_pMenu = Menu::GetSingleton();
	m_pNiveau = Niveau::GetSingleton();

	m_GameState = e_Menu;
}


// destructeurs
Game::~Game()
{}


// singleton
Game* Game::GetSingleton()
{
	static Game oGame;
	return &oGame;
}


// accesseurs
int Game::GetGamestate() const
{
	return m_GameState;
}


// mustateurs
void Game::SetGamestate(int _Gamestate)
{
	m_GameState = _Gamestate;
}


// chargement de toutes les donnees du jeu
void Game::Initialiser()
{
	// active les scores par defaut
	//Faux_Scores();

	// Direction le menu !
	m_pMenu->Traiter_Menu();
}


// permet de reset le tableau des high scores avec des faux scores
void Game::Faux_Scores()
{
	FILE* pFlux = fopen("../Files/high_scores.bin", "wb");

	for (int i = 0; i < 10; ++i)
	{
		struct JOUEUR stJoueur;
		sprintf(stJoueur.s_Nom, "Pilote_%d", i);
		stJoueur.s_Score = 95000 - i*8000;
		stJoueur.s_Temps_max = 24*(10-i);

		fwrite(&stJoueur, 1, sizeof(struct JOUEUR), pFlux);
	}

	fclose(pFlux);
}


// permet d'enregistrer le joueur a la fin de sa partie
// si il a eu un assez bon score par rapport aux 10 autres
void Game::Enregistrer_Joueur()
{
	FILE* pFlux = NULL;
	struct JOUEUR stTabJoueurs[11];
	struct JOUEUR stJTemp;

	pFlux = fopen("../Files/high_scores.bin", "rb");

	// on recupère les 10 joueurs du tableau des high scores
	fread(&stTabJoueurs, 10, sizeof(struct JOUEUR), pFlux);

	// on rajoute un 11 eme : soi-même
	for(int i = 0; i < 20; ++i)
		stTabJoueurs[10].s_Nom[i] = m_pJoueur->GetNom()[i];

	stTabJoueurs[10].s_Score = m_pJoueur->GetScore();
	stTabJoueurs[10].s_Temps_max = m_pJoueur->GetTemps_max();

	// on trie le tout
	for (int j = 0; j < 10; ++j)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (stTabJoueurs[i + 1].s_Score > stTabJoueurs[i].s_Score)
			{
				stJTemp = stTabJoueurs[i + 1];
				stTabJoueurs[i + 1] = stTabJoueurs[i];
				stTabJoueurs[i] = stJTemp;
			}
		}
	}

	// on réouvre le fichier en ecriture seule
	freopen("../Files/high_scores.bin", "wb", pFlux);

	// on écrase son ancien contenu avec seulement les 10 premiers sur 11 !
	fwrite(&stTabJoueurs, 10, sizeof(struct JOUEUR), pFlux);

	fclose(pFlux);
}


// liberation de toutes les donnees du jeu
void Game::Desinitialiser()
{
	
}