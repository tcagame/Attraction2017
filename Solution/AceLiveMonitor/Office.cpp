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
		npc->update( );
		npc->setSynchronousData( );
		ite++;
	}
}

NPCPtr Office::popUpNPC( EVENT type ) {
	NPCPtr npc;
	switch ( type ) {
	case EVENT_SHOP:
		npc = NPCPtr(new NPCObaba(Vector(800, 225)));
		addEventNPC( npc );
		break;
	case EVENT_LAKE:
		npc = NPCPtr(new NPCMiko(Vector(200, 225)));
		addEventNPC( npc );
		break;
	case EVENT_RYUGU:
		//ìVèó
		addEventNPC( NPCPtr( new NPCAngel( Vector( 325, 225 ) ) ) );
		addEventNPC( NPCPtr( new NPCAngel( Vector( 700, 225 ) ) ) );
		//â≥ïP
		npc = NPCPtr(new NPCOtohime(Vector(510, 150)));
		addEventNPC( npc );
		//êlãõ
		addEventNPC( NPCPtr( new NPCMermaid( Vector( 225, 250 ) ) ) );
		addEventNPC( NPCPtr( new NPCMermaid( Vector( 864, 250 ) ) ) );
		break;
	case EVENT_GAMBLE:
		npc = NPCPtr(new NPCShaker(Vector(650, 225)));
		//ÉcÉ{êUÇË
		addEventNPC( npc );
		//íÜñ~
		break;
	}
	return npc;
}

std::list< NPCPtr > Office::getNPC( ) const {
	return _npc;
}

void Office::eraseEventNPC( ) {
	std::list< NPCPtr >::iterator ite = _npc.begin( );
	while( ite != _npc.end( ) ) {
		NPCPtr npc = (*ite);
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

void Office::shiftPos( int map_width ) {
	std::list< NPCPtr >::iterator ite = _npc.begin( );
	while( ite != _npc.end( ) ) {
		NPCPtr npc = (*ite);
		npc->shiftPos( map_width );
		ite++;
	}
}

void Office::setSynchronousData( ) {
	std::list< NPCPtr >::iterator ite = _npc.begin();
	while ( ite != _npc.end( ) ) {
		NPCPtr npc = (*ite);
		npc->setSynchronousData( );
		ite++;
	}
}
