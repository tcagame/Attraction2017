#include "Game.h"
#include "Application.h"
#include "Viewer.h"
#include "Family.h"

GamePtr Game::getTask( ) {
	return std::dynamic_pointer_cast< Game >( Application::getInstance( )->getTask( getTag( ) ) );
}


Game::Game( ) {
}


Game::~Game( ) {
}

void Game::initialize( ) {
	_family = FamilyPtr( new Family );
	_viewer = ViewerPtr( new Viewer( _family ) );
}

void Game::update( ) {
	_family->update( );
	_viewer->update( );
}