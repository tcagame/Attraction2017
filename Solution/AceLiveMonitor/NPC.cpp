#include "NPC.h"
#include "Application.h"
#include "MapEvent.h"
#include "NPCObaba.h"

NPCPtr NPC::getTask( ) {
	return std::dynamic_pointer_cast< NPC >( Application::getInstance( )->getTask( getTag( ) ) );
}


NPC::NPC( ) {
}


NPC::~NPC( ) {
}

void NPC::update( ) {
	std::list< CharacterPtr >::iterator ite = _npc_chara.begin( );
	while( ite != _npc_chara.end( ) ) {
		if ( !( *ite ) ) {
			ite++;
			continue;
		}
		( *ite )->update( );
		ite++;
	}
}

void NPC::popUpNPC( ) {
	MapEvent::TYPE type = MapEvent::getTask( )->getType( );
	switch ( type ) {
	case MapEvent::TYPE_SHOP:
		_npc_chara.push_back( CharacterPtr( new NPCObaba( Vector( 800, 225 ) ) ) );
		break;
	}
}

std::list< CharacterPtr > NPC::getNPCChara( ) const {
	return _npc_chara;
}
