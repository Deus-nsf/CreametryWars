
// Auteur : Alfiguigui Mehdi
// Date : 15/01/2013
// Nom du fichier : main.cpp
// Description : c'est le point d'entree du programme


#include "header_classes.hpp"


int main(int argc, char* argv[])
{
	Game* oGame = Game::GetSingleton();
	srand((unsigned int) time(NULL));

	oGame->Initialiser();

	return EXIT_SUCCESS;
}