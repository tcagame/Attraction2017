#include "Office.h"
#include "Application.h"
#include "NPCObaba.h"
#include "NPCMiko.h"
#include "NPCOtohime.h"
#include "NPCAngel.h"
#include "NPCMermaid.h"
#include "NPCShaker.h"
#include "NPC.h"
#include "World.h"

OfficePtr Office::getTask( ) {
	return std::dynamic_pointer_cast< Office >( Application::getInstance( )->getTask( getTag( ) ) );
}


Office::Office( ) {
}


Office::~Office( ) {
}

void Office::update( ) {
	WorldPtr world = World::getTask( );
	std::list< NPCPtr >::iterator ite = _npc.begin( );
	while( ite != _npc.end( ) ) {
		NPCPtr npc = (*ite);
		if ( !npc ) {
			ite++;
			continue;
		}
		npc->update( );
		npc->setSynchronousData( );
		ite++;
	}
}

void Office::popUpNPC( EVENT type ) {
	switch ( type ) {
	case EVENT_SHOP:
		addEventNPC( NPCPtr( new NPCObaba( Vector( 800, 225 ) ) ) );
		break;
	case EVENT_LAKE:
		addEventNPC( NPCPtr( new NPCMiko( Vector( 200, 225 ) ) ) );
		break;
	case EVENT_RYUGU:
		//ìVèó
		addEventNPC( NPCPtr( new NPCAngel( Vector( 325, 225 ) ) ) );
		addEventNPC( NPCPtr( new NPCAngel( Vector( 700, 225 ) ) ) );
		//â≥ïP
		addEventNPC( NPCPtr( new NPCOtohime( Vector( 510, 150 ) ) ) );
		//êlãõ
		addEventNPC( NPCPtr( new NPCMermaid( Vector( 225, 250 ) ) ) );
		addEventNPC( NPCPtr( new NPCMermaid( Vector( 864, 250 ) ) ) );
		break;
	case EVENT_GAMBLE:
		//ÉcÉ{êUÇË
		addEventNPC( NPCPtr( new NPCShaker( Vector( 650, 225 ) ) ) );
		//íÜñ~
		break;
	}
}

std::list< NPCPtr > Office::getNPC( ) const {
	return _npc;
}

void Office::eraseEventNPC( ) {
	std::list< NPCPtr >::iterator ite = _npc.begin( );
	while( ite != _npc.end( ) ) {
		NPCPtr npc = (*ite);
		if ( !npc ) {
			ite++;
			continue;
		}
		if ( npc->getArea( ) == AREA_EVENT ) {
			ite = _npc.erase( ite );
			continue;
		}
		ite++;
	}
}

void Office::addEventNPC( NPCPtr npc ) {
	npc->setArea( AREA_EVENT );
	_npc.push_back( npc );
}

void Office::shiftPos( ) {
	std::list< NPCPtr >::iterator ite = _npc.begin( );
	while( ite != _npc.end( ) ) {
		NPCPtr npc = (*ite);
		if ( !npc ) {
			ite++;
			continue;
		}
		npc->shiftPos( );
		ite++;
	}
}
