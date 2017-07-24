#include "Game.h"
#include "Application.h"
#include "Viewer.h"
#include "Family.h"
#include "Armoury.h"

GamePtr Game::getTask( ) {
	return std::dynamic_pointer_cast< Game >( Application::getInstance( )->getTask( getTag( ) ) );
}


Game::Game( ) {
}


Game::~Game( ) {
}

void Game::initialize( ) {
}

void Game::update( ) {
}