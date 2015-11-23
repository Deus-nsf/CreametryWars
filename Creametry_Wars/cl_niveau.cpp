
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_niveau.cpp
// Description : les methodes de la classe Niveau

#include "cl_game.hpp"


// constructeurs
Niveau::Niveau()
{
	m_pData_sfml = Data_sfml::GetSingleton();
	m_pGraph = Graph::GetSingleton();
	m_pSound = Sound::GetSingleton();
	m_pJoueur = Joueur::GetSingleton();

	TempsNiveau.restart();
	TempsPourUneVie.restart();
	TempsSpawn.restart();
	TempsSpawn_2.restart();

	TempsPourSpawn = 0.5f;
	TempsPourSpawn_2 = 0.2f;

	bool_BOMB = 0;

	fDeltaCalcul = 15.0f;	// temporisation des calculs
	iTempsPourUneVie = 30;
	iTailleMapX = 2400;
	iTailleMapY = 1800;
}


// destructeurs
Niveau::~Niveau()
{}


// singleton
Niveau* Niveau::GetSingleton()
{
	static Niveau oNiveau;
	return &oNiveau;
}







// boucle de gestion de tous les elements du niveau
void Niveau::Boucle_Niveau()
{
	TempsPourUneVie.restart();
	m_pData_sfml->GetHorloge()->restart();
	m_pSound->GetMusiques()->at(e_ThemeJeu)->play();

	m_pGraph->GetTextes()->at(e_NomEtScore).setPosition(10, 10);
	
	m_pGraph->GetTextes()->at(e_TempsEcoule).setPosition(580, 10);	


	while (Game::GetSingleton()->GetGamestate() == e_Jeu)
	{
		// petite temporisation pour les calculs et l'affichage
		if (TempsNiveau.getElapsedTime().asMilliseconds() > fDeltaCalcul)
		{
			Avancer_Temps();

			Affichage_Niveau();

			Actions_Joueur();

			Mouvements_Joueur();

			Bouger_Tirs();

			Gestion_Ennemis();

			Collisions_Map();

			Collisions_Tir_Ennemis();

			Collisions_Joueur_Ennemis();

			TempsNiveau.restart();
		}


		switch (Game::GetSingleton()->GetGamestate())
		{
		case e_Jeu:
			Affichage_Niveau();
			break;
		case e_Quitter:

			Game::GetSingleton()->Desinitialiser();
			break;
		}
	}

	m_pSound->GetMusiques()->at(e_ThemeJeu)->stop();
	m_pSound->GetMusiques()->at(e_ThemeMenu)->play();
}









// fait avancer le temps max et donne des vies
void Niveau::Avancer_Temps()
{
	m_pJoueur->SetTemps_max( (int)m_pData_sfml->GetHorloge()->getElapsedTime().asSeconds() );

	if(TempsPourUneVie.getElapsedTime().asSeconds() > iTempsPourUneVie)
	{
		m_pJoueur->SetVies( m_pJoueur->GetVies() + 1);
		TempsPourUneVie.restart();
	}
}



// liste des actions du joueur dans le niveau
void Niveau::Actions_Joueur()
{
	while ( m_pData_sfml->GetFenetre()->pollEvent(*m_pData_sfml->GetEvenements()) )
	{
		// on regarde le type de l'évènement...
		switch (m_pData_sfml->GetEvenements()->type)
		{
			// fenêtre fermée
		case sf::Event::Closed:
			m_pData_sfml->GetFenetre()->close();
			Game::GetSingleton()->SetGamestate(e_Quitter);
			break;

			// touche pressée
		case sf::Event::KeyPressed:
			{
				switch(m_pData_sfml->GetEvenements()->key.code)
				{
				case sf::Keyboard::Escape:
					Game::GetSingleton()->SetGamestate(e_MenuGS);
					break;

				case sf::Keyboard::Space:
					{
						if((m_pJoueur->GetBombes() > 0) && (bool_BOMB == 0))
						{
							m_pJoueur->SetBombes(m_pJoueur->GetBombes() - 1);
							m_pJoueur->GetJCsBOMB()->setPosition(m_pJoueur->GetPosX(), m_pJoueur->GetPosY());
							bool_BOMB = 1;

							for(int i = 0; i < (signed int)ListeEnnemis.size(); ++i)
							{
								ListeEnnemis[i].SetPtsDeVie(0);
							}

							for(int i = 0; i < (signed int)ListeEnnemis_2.size(); ++i)
							{
								ListeEnnemis_2[i].SetPtsDeVie(0);
							}
						}
					}
					break;

				case sf::Keyboard::K:
					{
						Mort_Joueur();
					}
				}
			}
			break;
		}
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		m_pJoueur->Tirer();
}



// liste des mouvements que peut effectuer le joueur dans le niveau
void Niveau::Mouvements_Joueur()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pJoueur->MoveRight();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_pJoueur->MoveLeft();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		m_pJoueur->MoveUp();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pJoueur->MoveDown();
}



// methode pour updater la position des tirs
void Niveau::Bouger_Tirs()
{
	for(int i = 0; i < (signed int)m_pJoueur->GetListeTirs()->size(); ++i)
	{
		m_pJoueur->GetListeTirs()->at(i).Avancer();
	}

	for(int i = 0; i < (signed int)m_pJoueur->GetListeTirs()->size(); ++i)
	{
		if ((m_pJoueur->GetListeTirs()->at(i).GetPosX() < 0) ||
			(m_pJoueur->GetListeTirs()->at(i).GetPosX() > iTailleMapX) ||
			(m_pJoueur->GetListeTirs()->at(i).GetPosY() < 0) ||
			(m_pJoueur->GetListeTirs()->at(i).GetPosY() > iTailleMapY) )
		{
			m_pGraph->GetRectangles()->at(e_LimitesMap).setOutlineColor(
				m_pJoueur->GetListeTirs()->at(i).GetCircle()->getFillColor());

			m_pGraph->GetRectangles()->at(e_GridLineHor).setFillColor(
				m_pJoueur->GetListeTirs()->at(i).GetCircle()->getFillColor());

			m_pGraph->GetRectangles()->at(e_GridLineVer).setFillColor(
				m_pJoueur->GetListeTirs()->at(i).GetCircle()->getFillColor());

			m_pJoueur->GetListeTirs()->erase( m_pJoueur->GetListeTirs()->begin() + i );
			
			--i;
		}
	}
}



// tout ce qui va gerer les ennemis (sauf les collisions et l'affichage)
void Niveau::Gestion_Ennemis()
{
	if(TempsSpawn.getElapsedTime().asSeconds() > TempsPourSpawn)
	{
		ListeEnnemis.push_back( Ennemi_Base() );
		TempsSpawn.restart();
	}

	if(TempsSpawn_2.getElapsedTime().asSeconds() > TempsPourSpawn_2)
	{
		ListeEnnemis_2.push_back( Ennemi_Fantome() );
		TempsSpawn_2.restart();
	}

	for(int i = 0; i < (signed int)ListeEnnemis.size(); ++i)
	{
		ListeEnnemis[i].Calculer_Orientation();
		ListeEnnemis[i].VerifieEtat();
		ListeEnnemis[i].Comportement();

		if(ListeEnnemis[i].GetEstEnVie() == 0)
		{
			ListeEnnemis.erase(ListeEnnemis.begin() + i);
			--i;
		}
	}

	for(int i = 0; i < (signed int)ListeEnnemis_2.size(); ++i)
	{
		
		ListeEnnemis_2[i].VerifieEtat();
		ListeEnnemis_2[i].Comportement();
		ListeEnnemis_2[i].Calculer_Orientation();

		if(ListeEnnemis_2[i].GetEstEnVie() == 0)
		{
			ListeEnnemis_2.erase(ListeEnnemis_2.begin() + i);
			--i;
		}
	}
}



// affichage de tout les elements du niveau
void Niveau::Affichage_Niveau()
{
	m_pData_sfml->GetFenetre()->clear();

	m_pData_sfml->SetCameraJeu();

	Afficher_Map();
	Afficher_Sprites();
	Afficher_HUD();

	//m_pGraph->GetTextes()->at(e_NomEtScore).setColor(sf::Color(255, 255, 0, 255));
	//m_pGraph->GetTextes()->at(e_NomEtScore).setColor(sf::Color(255, 255, 0, 255));

	m_pData_sfml->GetFenetre()->display();
}


// affichage de la map
void Niveau::Afficher_Map()
{
	m_pData_sfml->GetFenetre()->setView( *m_pData_sfml->GetCameraJeu() );

	// image de fond
	for(int y = -1; y < 3; ++y)
	{
		for(int x = -1; x < 3; ++x)
		{
			m_pGraph->GetSprites()->at(e_FondJeu)->setPosition((800.0f * x) + m_pJoueur->GetPosX()/2, (600.0f * y) + m_pJoueur->GetPosY()/2);
			m_pData_sfml->GetFenetre()->draw( *m_pGraph->GetSprites()->at(e_FondJeu) );
		}
	}

	// limites map
	m_pData_sfml->GetFenetre()->draw( m_pGraph->GetRectangles()->at(e_LimitesMap) );
	
	// grid
	for(int x = 0; x < 120; ++x)
	{
		m_pGraph->GetRectangles()->at(e_GridLineVer).setPosition(20.0f * x, 0.0f);
		m_pData_sfml->GetFenetre()->draw( m_pGraph->GetRectangles()->at(e_GridLineVer) );
	}

	for(int x = 0; x < 90; ++x)
	{
		m_pGraph->GetRectangles()->at(e_GridLineHor).setPosition(0.0f, 20.0f * x);
		m_pData_sfml->GetFenetre()->draw( m_pGraph->GetRectangles()->at(e_GridLineHor) );
	}
}


// affichage des vaisseaux, tirs, etc...
void Niveau::Afficher_Sprites()
{
	// affichage du heros
	m_pJoueur->GetSprite()->setPosition(m_pJoueur->GetPosX(), m_pJoueur->GetPosY());
	m_pJoueur->Calculer_Orientation();
	m_pJoueur->GetSprite()->setRotation( -(m_pJoueur->GetAngleRad() * (180/3.14f)) - 180);
	m_pData_sfml->GetFenetre()->draw( *m_pJoueur->GetSprite() );

	// affichage des tirs
	for(int i = 0; i < (signed int)m_pJoueur->GetListeTirs()->size(); ++i)
	{
		m_pData_sfml->GetFenetre()->draw( *m_pJoueur->GetListeTirs()->at(i).GetCircle() );
	}

	// affichage des ennemis
	for(int i = 0; i < (signed int)ListeEnnemis.size(); ++i)
	{
		ListeEnnemis[i].GetImage()->setRotation( -ListeEnnemis[i].GetAngleRad() * (180/3.14f) - 180) ;
		ListeEnnemis[i].GetImage()->setPosition( ListeEnnemis[i].GetPosX(), ListeEnnemis[i].GetPosY() );
		m_pData_sfml->GetFenetre()->draw( *ListeEnnemis[i].GetImage() );
	}

	for(int i = 0; i < (signed int)ListeEnnemis_2.size(); ++i)
	{
		ListeEnnemis_2[i].GetImage()->setRotation( -ListeEnnemis_2[i].GetAngleRad() * (180/3.14f) - 180) ;
		ListeEnnemis_2[i].GetImage()->setPosition( ListeEnnemis_2[i].GetPosX(), ListeEnnemis_2[i].GetPosY() );
		m_pData_sfml->GetFenetre()->draw( *ListeEnnemis_2[i].GetImage() );
	}

	if(bool_BOMB == 1)
		m_pJoueur->A_BOMB();
}


// affichage du score, nbr bombes, nbr vies...
void Niveau::Afficher_HUD()
{
	static std::stringstream Chaine;
	Chaine.str("");
	
	m_pData_sfml->GetFenetre()->setView( *m_pData_sfml->GetCameraHud() );

	Chaine << m_pJoueur->GetNom() << " : " << m_pJoueur->GetScore();
	m_pGraph->GetTextes()->at(e_NomEtScore).setString( Chaine.str() );
	Chaine.str("");

	Chaine << " Secondes : " << m_pJoueur->GetTemps_max();
	m_pGraph->GetTextes()->at(e_TempsEcoule).setString( Chaine.str() );
	Chaine.str("");

	Chaine << " Bombes : " << m_pJoueur->GetBombes();
	m_pGraph->GetTextes()->at(e_NbrBombes).setString( Chaine.str() );
	Chaine.str("");

	Chaine << " Vies : " << m_pJoueur->GetVies();
	m_pGraph->GetTextes()->at(e_NbrVies).setString( Chaine.str() );

	m_pData_sfml->GetFenetre()->draw( m_pGraph->GetTextes()->at(e_NomEtScore) );
	m_pData_sfml->GetFenetre()->draw( m_pGraph->GetTextes()->at(e_TempsEcoule) );
	m_pData_sfml->GetFenetre()->draw( m_pGraph->GetTextes()->at(e_NbrBombes) );
	m_pData_sfml->GetFenetre()->draw( m_pGraph->GetTextes()->at(e_NbrVies) );
}



// Permet de tester la collision avec la map pour le joueur et les ennemis
void Niveau::Collisions_Map()
{
	if (m_pJoueur->GetPosX() < 32)
		m_pJoueur->SetPosX(32.0f);

	if (m_pJoueur->GetPosX() > (iTailleMapX - 32))
		m_pJoueur->SetPosX(iTailleMapX - 32.0f);

	if (m_pJoueur->GetPosY() < 32)
		m_pJoueur->SetPosY(32.0f);

	if (m_pJoueur->GetPosY() > (iTailleMapY - 32))
		m_pJoueur->SetPosY(iTailleMapY - 32.0f);
}



// Permet de tester la collision entre les tirs et les ennemis
void Niveau::Collisions_Tir_Ennemis()
{
	float fLength = 0.0f;

	for(int i = 0; i < (signed int)ListeEnnemis.size(); ++i)
	{
		for(int j = 0; j < (signed int)m_pJoueur->GetListeTirs()->size(); ++j)
		{
			fLength = sqrt((ListeEnnemis[i].GetPosX() - m_pJoueur->GetListeTirs()->at(j).GetPosX()) * 
				(ListeEnnemis[i].GetPosX() - m_pJoueur->GetListeTirs()->at(j).GetPosX()) + 
				(ListeEnnemis[i].GetPosY() - m_pJoueur->GetListeTirs()->at(j).GetPosY()) * 
				(ListeEnnemis[i].GetPosY() - m_pJoueur->GetListeTirs()->at(j).GetPosY()));

			if(fLength < 36)
			{
				ListeEnnemis[i].Touche();
				m_pJoueur->GetListeTirs()->erase( m_pJoueur->GetListeTirs()->begin() + j);
				--j;
			}
		}
	}

	for(int i = 0; i < (signed int)ListeEnnemis_2.size(); ++i)
	{
		for(int j = 0; j < (signed int)m_pJoueur->GetListeTirs()->size(); ++j)
		{
			fLength = sqrt((ListeEnnemis_2[i].GetPosX() - m_pJoueur->GetListeTirs()->at(j).GetPosX()) * 
				(ListeEnnemis_2[i].GetPosX() - m_pJoueur->GetListeTirs()->at(j).GetPosX()) + 
				(ListeEnnemis_2[i].GetPosY() - m_pJoueur->GetListeTirs()->at(j).GetPosY()) * 
				(ListeEnnemis_2[i].GetPosY() - m_pJoueur->GetListeTirs()->at(j).GetPosY()));

			if(fLength < 36)
			{
				ListeEnnemis_2[i].Touche();
				m_pJoueur->GetListeTirs()->erase( m_pJoueur->GetListeTirs()->begin() + j);
				--j;
			}
		}
	}
}



// collisions entre le joueur et les ennemis
void Niveau::Collisions_Joueur_Ennemis()
{
	float fLength = 0.0f;

	for(int i = 0; i < (signed int)ListeEnnemis.size(); ++i)
	{
		fLength = sqrt((ListeEnnemis[i].GetPosX() - m_pJoueur->GetPosX()) * 
			(ListeEnnemis[i].GetPosX() - m_pJoueur->GetPosX()) + 
			(ListeEnnemis[i].GetPosY() - m_pJoueur->GetPosY()) * 
			(ListeEnnemis[i].GetPosY() - m_pJoueur->GetPosY()));

		if(fLength < 64)
		{
			m_pJoueur->SetVies(m_pJoueur->GetVies() - 1);
			ListeEnnemis.erase( ListeEnnemis.begin() + i );
			--i;
		}
	}

	for(int i = 0; i < (signed int)ListeEnnemis_2.size(); ++i)
	{
		fLength = sqrt((ListeEnnemis_2[i].GetPosX() - m_pJoueur->GetPosX()) * 
			(ListeEnnemis_2[i].GetPosX() - m_pJoueur->GetPosX()) + 
			(ListeEnnemis_2[i].GetPosY() - m_pJoueur->GetPosY()) * 
			(ListeEnnemis_2[i].GetPosY() - m_pJoueur->GetPosY()));

		if(fLength < 64)
		{
			m_pJoueur->SetVies(m_pJoueur->GetVies() - 1);
			ListeEnnemis_2.erase( ListeEnnemis_2.begin() + i );
			--i;
		}
	}

	if(m_pJoueur->GetVies() <= 0)
	{
		Mort_Joueur();
	}
}



// ce qu'il va se passer quand le joueur va mourrir
void Niveau::Mort_Joueur()
{
	Game::GetSingleton()->Enregistrer_Joueur();

	m_pJoueur->SetScore(0);
	m_pJoueur->SetTemps_max(0);
	m_pJoueur->SetVies(3);
	m_pJoueur->SetBombes(10);

	Game::GetSingleton()->SetGamestate(e_MenuGS);
}



//accesseurs
int Niveau::GetTailleMapX() const
{
	return iTailleMapX;
}


int Niveau::GetTailleMapY() const
{
	return iTailleMapY;
}



// mutateurs
void Niveau::Setbool_BOMB(int _bool_BOMB)
{
	bool_BOMB = _bool_BOMB;
}



// desinitialisation securisee du programme
void Niveau::Safe_Desinit()
{

}