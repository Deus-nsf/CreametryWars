
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : cl_sound.hpp
// Description : c'est la classe des elements sonores du jeu

// SINGLETON

#pragma once

#include "header_libs.hpp"


enum MUSIQUES_E
{
	e_ThemeMenu,
	e_ThemeJeu,
};

enum SONS_E
{
	e_Bip,
	e_Door,
};


class Sound
{
protected:

	Sound();
	~Sound();

	std::vector<sf::SoundBuffer*> BuffersSons;
	std::vector<sf::Sound*> Sons;
	std::vector<sf::Music*> Musiques;

public:

	static Sound* GetSingleton();
	
	void Charger_Sons();
	void Charger_Musiques();

	std::vector<sf::Music*>* GetMusiques();
	std::vector<sf::Sound*>* GetSons();
};