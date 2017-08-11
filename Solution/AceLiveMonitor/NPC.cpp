#include "NPC.h"
#include "Application.h"
#include "MapEvent.h"
#include "NPCObaba.h"
#include "NPCMiko.h"
#include "NPCOtohime.h"
#include "NPCAngel.h"
#include "NPCMermaid.h"

NPCPtr NPC::getTask( ) {
	return std::dynamic_pointer_cast< NPC >( Application::getInstance( )->getTask( getTag( ) ) );
}


NPC::NPC( ) {
}


NPC::~NPC( ) {
}

void NPC::update( ) {
	MapEvent::TYPE type = MapEvent::getTask( )->getType( );
	std::list< CharacterPtr >::iterator ite = _npc_chara.begin( );
	while( ite != _npc_chara.end( ) ) {
		if ( !( *ite ) ) {
			ite++;
			continue;
		}
		if( type == MapEvent::TYPE_TITLE ) {
			ite = _npc_chara.erase( ite );
			continue;
		}
		( *ite )->update( );
		ite++;
	}
}

void NPC::popUpNPC( ) {
	MapEvent::TYPE type = MapEvent::getTask( )->getType( );
	_npc_chara.clear( );
	switch ( type ) {
	case MapEvent::TYPE_SHOP:
		_npc_chara.push_back( CharacterPtr( new NPCObaba( Vector( 800, 225 ) ) ) );
		break;
	case MapEvent::TYPE_LAKE:
		_npc_chara.push_back( CharacterPtr( new NPCMiko( Vector( 200, 225 ) ) ) );
		break;
	case MapEvent::TYPE_RYUGU:
		_npc_chara.push_back( CharacterPtr( new NPCAngel( Vector( 325, 225 ) ) ) );
		_npc_chara.push_back( CharacterPtr( new NPCAngel( Vector( 700, 225 ) ) ) );
		_npc_chara.push_back( CharacterPtr( new NPCOtohime( Vector( 510, 150 ) ) ) );
		_npc_chara.push_back( CharacterPtr( new NPCMermaid( Vector( 225, 250 ) ) ) );
		_npc_chara.push_back( CharacterPtr( new NPCMermaid( Vector( 864, 250 ) ) ) );
		break;
	}
}

std::list< CharacterPtr > NPC::getNPCChara( ) const {
	return _npc_chara;
}
