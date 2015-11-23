
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_sound.cpp
// Description : les methodes de la classe Sound

#include "cl_sound.hpp"


// constructeurs
Sound::Sound()
{
	Charger_Musiques();
	Charger_Sons();
}


// destructeurs
Sound::~Sound()
{
	while (Musiques.size() > 0)
	{
		delete Musiques.back();
		Musiques.pop_back();
	}

	while (Sons.size() > 0)
	{
		delete Sons.back();
		Sons.pop_back();
	}
}


// singleton
Sound* Sound::GetSingleton()
{
	static Sound oSound;
	return &oSound;
}


// charge les musiques du jeu <!> l'ordre doit imperativement correspondre a MUSIQUES_E
void Sound::Charger_Musiques()
{
	Musiques.push_back(new sf::Music());
	Musiques[e_ThemeMenu]->openFromFile("../Sounds/Music/menu_theme.ogg");
	Musiques[e_ThemeMenu]->setVolume(50.0f);
	Musiques[e_ThemeMenu]->setLoop(true);

	Musiques.push_back(new sf::Music());
	Musiques[e_ThemeJeu]->openFromFile("../Sounds/Music/game_theme.ogg");
	Musiques[e_ThemeJeu]->setVolume(50.0f);
	Musiques[e_ThemeJeu]->setLoop(true);
}


// charge les sons du jeu <!> l'ordre doit imperativement correspondre a SONS_E
void Sound::Charger_Sons()
{
	BuffersSons.push_back(new sf::SoundBuffer());
	BuffersSons[e_Bip]->loadFromFile("../Sounds/Sound/bip.ogg");

	BuffersSons.push_back(new sf::SoundBuffer());
	BuffersSons[e_Door]->loadFromFile("../Sounds/Sound/door.ogg");


	Sons.push_back(new sf::Sound());
	Sons[e_Bip]->setBuffer(*BuffersSons[e_Bip]);
	Sons[e_Bip]->setVolume(20.0f);

	Sons.push_back(new sf::Sound());
	Sons[e_Door]->setBuffer(*BuffersSons[e_Door]);
	Sons[e_Door]->setVolume(40.0f);
}


// accesseurs
std::vector<sf::Music*>* Sound::GetMusiques()
{
	return &Musiques;
}


std::vector<sf::Sound*>* Sound::GetSons()
{
	return &Sons;
}