#include "Office.h"
#include "Application.h"
#include "MapEvent.h"
#include "NPCObaba.h"
#include "NPCMiko.h"
#include "NPCOtohime.h"
#include "NPCAngel.h"
#include "NPCMermaid.h"
#include "NPCShaker.h"
#include "NPC.h"

OfficePtr Office::getTask( ) {
	return std::dynamic_pointer_cast< Office >( Application::getInstance( )->getTask( getTag( ) ) );
}


Office::Office( ) {
}


Office::~Office( ) {
}

void Office::update( ) {
	EVENT event = MapEvent::getTask( )->getEvent( );
	std::list< NPCPtr >::iterator ite = _npc.begin( );
	while( ite != _npc.end( ) ) {
		NPCPtr npc = (*ite);
		if ( !npc ) {
			ite++;
			continue;
		}
		npc->update( );
		npc->setSynchronousData( );
		if( event == EVENT_NONE ) {
			ite = _npc.erase( ite );
			continue;
		}
		ite++;
	}
}

void Office::popUpNPC( ) {
	EVENT event = MapEvent::getTask( )->getEvent( );
	_npc.clear( );
	switch ( event ) {
	case EVENT_SHOP:
		_npc.push_back( NPCPtr( new NPCObaba( Vector( 800, 225 ) ) ) );
		break;
	case EVENT_LAKE:
		_npc.push_back( NPCPtr( new NPCMiko( Vector( 200, 225 ) ) ) );
		break;
	case EVENT_RYUGU:
		//ìVèó
		_npc.push_back( NPCPtr( new NPCAngel( Vector( 325, 225 ) ) ) );
		_npc.push_back( NPCPtr( new NPCAngel( Vector( 700, 225 ) ) ) );
		//â≥ïP
		_npc.push_back( NPCPtr( new NPCOtohime( Vector( 510, 150 ) ) ) );
		//êlãõ
		_npc.push_back( NPCPtr( new NPCMermaid( Vector( 225, 250 ) ) ) );
		_npc.push_back( NPCPtr( new NPCMermaid( Vector( 864, 250 ) ) ) );
		break;
	case EVENT_GAMBLE:
		//ÉcÉ{êUÇË
		_npc.push_back( NPCPtr( new NPCShaker( Vector( 650, 225 ) ) ) );
		//íÜñ~
		break;
	}
}

std::list< NPCPtr > Office::getNPC( ) const {
	return _npc;
}
