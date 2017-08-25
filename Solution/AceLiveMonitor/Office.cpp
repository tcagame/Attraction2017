#include "Office.h"
#include "Application.h"
#include "MapEvent.h"
#include "NPCObaba.h"
#include "NPCMiko.h"
#include "NPCOtohime.h"
#include "NPCAngel.h"
#include "NPCMermaid.h"
#include "NPC.h"

OfficePtr Office::getTask( ) {
	return std::dynamic_pointer_cast< Office >( Application::getInstance( )->getTask( getTag( ) ) );
}


Office::Office( ) {
}


Office::~Office( ) {
}

void Office::update( ) {
	MapEvent::TYPE type = MapEvent::getTask( )->getType( );
	std::list< NPCPtr >::iterator ite = _npc.begin( );
	while( ite != _npc.end( ) ) {
		NPCPtr npc = (*ite);
		if ( !npc ) {
			ite++;
			continue;
		}
		npc->update( );
		npc->setSynchronousData( );
		if( type == MapEvent::TYPE_TITLE ) {
			ite = _npc.erase( ite );
			continue;
		}
		ite++;
	}
}

void Office::popUpNPC( ) {
	MapEvent::TYPE type = MapEvent::getTask( )->getType( );
	_npc.clear( );
	switch ( type ) {
	case MapEvent::TYPE_SHOP:
		_npc.push_back( NPCPtr( new NPCObaba( Vector( 800, 225 ) ) ) );
		break;
	case MapEvent::TYPE_LAKE:
		_npc.push_back( NPCPtr( new NPCMiko( Vector( 200, 225 ) ) ) );
		break;
	case MapEvent::TYPE_RYUGU:
		//ìVèó
		_npc.push_back( NPCPtr( new NPCAngel( Vector( 325, 225 ) ) ) );
		_npc.push_back( NPCPtr( new NPCAngel( Vector( 700, 225 ) ) ) );
		//â≥ïP
		_npc.push_back( NPCPtr( new NPCOtohime( Vector( 510, 150 ) ) ) );
		//êlãõ
		_npc.push_back( NPCPtr( new NPCMermaid( Vector( 225, 250 ) ) ) );
		_npc.push_back( NPCPtr( new NPCMermaid( Vector( 864, 250 ) ) ) );
		break;
	}
}

std::list< NPCPtr > Office::getNPC( ) const {
	return _npc;
}
