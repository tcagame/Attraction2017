#include "Game.h"
#include "Application.h"
#include "Viewer.h"
#include "Family.h"
#include "PsychicManager.h"

GamePtr Game::getTask( ) {
	return std::dynamic_pointer_cast< Game >( Application::getInstance( )->getTask( getTag( ) ) );
}


Game::Game( ) {
}


Game::~Game( ) {
}

void Game::initialize( ) {
	_family = FamilyPtr( new Family );
	_psychic_manager = PsychicManagerPtr( new PsychicManager );
	_viewer = ViewerPtr( new Viewer( _family, _psychic_manager ) );
}

void Game::update( ) {
	_family->update( );
	_psychic_manager->update( );
	_viewer->update( );
}

PsychicManagerPtr Game::getPsychicManager( ) {
	return _psychic_manager;
}
