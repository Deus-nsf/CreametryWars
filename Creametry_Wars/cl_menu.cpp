
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_menu.cpp
// Description : les methodes de la classe Menu

#include "cl_game.hpp"


// constructeurs
Menu::Menu()
{
	m_pData_sfml = Data_sfml::GetSingleton();
	m_pGraph = Graph::GetSingleton();
	m_pJoueur = Joueur::GetSingleton();
	m_pSound = Sound::GetSingleton();
	m_pNiveau = Niveau::GetSingleton();

	m_iEtatMenu = 0;
}



// destructeurs
Menu::~Menu()
{}



// singleton
Menu* Menu::GetSingleton()
{
	static Menu oMenu;
	return &oMenu;
}



// permet d'effectuer des operations sur le menu
void Menu::Traiter_Menu()
{
	m_pSound->GetMusiques()->at(e_ThemeMenu)->play();

	while (Game::GetSingleton()->GetGamestate() == e_MenuGS)
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
					if (m_pData_sfml->GetEvenements()->key.code == sf::Keyboard::Return)
					{
						m_pSound->GetSons()->at(e_Door)->play();

						switch(m_iEtatMenu)
						{
							case 0:
								Game::GetSingleton()->SetGamestate(e_Jeu);
								break;

							case 1:
								Game::GetSingleton()->SetGamestate(e_HighScoresGS); 
								break;

							case 2:
								Game::GetSingleton()->SetGamestate(e_Quitter);
								break;

							default:
								break;
						}
					}

					if (m_pData_sfml->GetEvenements()->key.code == sf::Keyboard::Up)
					{
						m_pSound->GetSons()->at(e_Bip)->play();

						if (m_iEtatMenu == 0)
						{
							m_pGraph->GetRectangles()->at(e_CurseurMenu).setPosition(210, 465);
							m_iEtatMenu = 2;
						}
						else
						{
							m_pGraph->GetRectangles()->at(e_CurseurMenu).setPosition(
								210, m_pGraph->GetRectangles()->at(e_CurseurMenu).getPosition().y - 70);
							--m_iEtatMenu;
						}
					}

					if (m_pData_sfml->GetEvenements()->key.code == sf::Keyboard::Down)
					{
						m_pSound->GetSons()->at(e_Bip)->play();

						if (m_iEtatMenu == 2)
						{
							m_pGraph->GetRectangles()->at(e_CurseurMenu).setPosition(210, 325);
							m_iEtatMenu = 0;

						}
						else
						{
							m_pGraph->GetRectangles()->at(e_CurseurMenu).setPosition(
								210, m_pGraph->GetRectangles()->at(e_CurseurMenu).getPosition().y + 70);
							++m_iEtatMenu;
						}
					}
				}
				break;

				// on ne traite pas les autres types d'évènements
			default:
				break;
			}
		}

		// appels des différentes fonctions selon le gamestate :

		
		switch (Game::GetSingleton()->GetGamestate())
		{
		case e_MenuGS:
			Afficher_Menu();
			break;
		case e_HighScoresGS :
			Afficher_High_Scores();
			break;
		case e_Jeu:
			Saisir_Nom();
			break;
		case e_Quitter:
			Game::GetSingleton()->Desinitialiser();
			break;
		}
	}
}



// affiche les donnees graphiques du menu
void Menu::Afficher_Menu()
{
	m_pData_sfml->GetFenetre()->clear();

	m_pData_sfml->GetFenetre()->draw( *m_pGraph->GetSprites()->at(0) );
	m_pData_sfml->GetFenetre()->draw( m_pGraph->GetRectangles()->at(e_CurseurMenu) );

	m_pData_sfml->GetFenetre()->display();
}



// cette fonction affiche les high-scores
void Menu::Afficher_High_Scores()
{
	FILE* pFlux = NULL;

	pFlux = fopen("../Files/high_scores.bin", "rb");

	while ( Game::GetSingleton()->GetGamestate() == e_HighScoresGS )
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
				if ( (m_pData_sfml->GetEvenements()->key.code == sf::Keyboard::Return) ||
					(m_pData_sfml->GetEvenements()->key.code == sf::Keyboard::Escape))
				{
					m_pSound->GetSons()->at(e_Door)->play();
					Game::GetSingleton()->SetGamestate(e_MenuGS);
				}
				break;
			}
		}
		
		m_pData_sfml->GetFenetre()->clear();
		m_pData_sfml->GetFenetre()->draw( *m_pGraph->GetSprites()->at(e_HighScoresSp) );
		m_pData_sfml->GetFenetre()->draw( m_pGraph->GetRectangles()->at(e_Fond_HighScores) );

		m_pGraph->GetTextes()->at(e_NomEtScore).setPosition(100, 100);

		// affichage des scores
		for (int i = 0; i < 10; ++i)
		{
			struct JOUEUR stJoueur;
			static std::stringstream szChaine;
			int iCouleur;

			fread(&stJoueur, 1, sizeof(struct JOUEUR), pFlux);

			szChaine.str("");
			szChaine << stJoueur.s_Nom << "\t\t" << stJoueur.s_Score << " Points\t\t" << stJoueur.s_Temps_max << " Secondes";
			iCouleur = 255 - (i*28);

			m_pGraph->GetTextes()->at(e_NomEtScore).setString(szChaine.str());
			m_pGraph->GetTextes()->at(e_NomEtScore).setColor(sf::Color(255, iCouleur, 0, 255));
			
			m_pGraph->GetTextes()->at(e_NomEtScore).setPosition(100, m_pGraph->GetTextes()->at(e_NomEtScore).getPosition().y + 40);
			m_pData_sfml->GetFenetre()->draw(m_pGraph->GetTextes()->at(e_NomEtScore));
		}

		rewind(pFlux);
		m_pGraph->GetTextes()->at(e_NomEtScore).setPosition(100, 100);

		m_pData_sfml->GetFenetre()->display();
	}

	fclose(pFlux);
}



// permet de saisir son nom au lancement d'une partie
void Menu::Saisir_Nom()
{
	int iContinuer = 1;
	int iCompteurLettres = 0;
	sf::Text Blabla_Nom_Joueur;
	char szNomTemp[100] = "";
	char szChaine[200] = "";

	m_pData_sfml->GetFenetre()->setKeyRepeatEnabled(true);
	m_pJoueur->SetNom("\0");

	Blabla_Nom_Joueur.setFont( *m_pGraph->GetPolice() );
	Blabla_Nom_Joueur.setCharacterSize(22);
	Blabla_Nom_Joueur.setPosition( 150.0f, 200.0f );

	while(iContinuer == 1)
	{
		while ( m_pData_sfml->GetFenetre()->pollEvent( *m_pData_sfml->GetEvenements() ) )
		{
			switch ( m_pData_sfml->GetEvenements()->type )
			{
				// fenêtre fermée
			case sf::Event::Closed:
				m_pData_sfml->GetFenetre()->close();
				Game::GetSingleton()->SetGamestate(e_Quitter);
				iContinuer = 0;
				break;

			case sf::Event::TextEntered:
				// saisie clavier complexe (les caracteres de la table ASCII standard)
				if ( (m_pData_sfml->GetEvenements()->text.unicode > 31) &&
					(m_pData_sfml->GetEvenements()->text.unicode < 128) &&
					(iCompteurLettres < 20) )
				{
					m_pSound->GetSons()->at(e_Bip)->play();
					szNomTemp[iCompteurLettres] = (char)(m_pData_sfml->GetEvenements()->text.unicode);
					szNomTemp[iCompteurLettres + 1] = '\0';
					++iCompteurLettres;
				}
				break;

				// touche pressée
			case sf::Event::KeyPressed:
				if ( m_pData_sfml->GetEvenements()->key.code == sf::Keyboard::Return )
				{
					iContinuer = 0;
				}

				if ( (m_pData_sfml->GetEvenements()->key.code == sf::Keyboard::Back) && (iCompteurLettres > 0) )
				{
					m_pSound->GetSons()->at(e_Bip)->play();
					--iCompteurLettres;
					szNomTemp[iCompteurLettres] = '\0';
				}
				break;
			}
		}

		sprintf(szChaine, "Saisissez votre nom, entree pour valider : \n\n%s", szNomTemp);

		Blabla_Nom_Joueur.setString(szChaine);

		m_pData_sfml->GetFenetre()->clear(sf::Color::Black);
		m_pData_sfml->GetFenetre()->draw(Blabla_Nom_Joueur);
		m_pData_sfml->GetFenetre()->display();
	}

	m_pJoueur->SetNom(szNomTemp);
	m_pData_sfml->GetFenetre()->setKeyRepeatEnabled(false);

	m_pSound->GetMusiques()->at(e_ThemeMenu)->stop();
	m_pSound->GetSons()->at(e_Door)->play();
	m_pNiveau->Boucle_Niveau();
}