#include "RockDollHouse.h"
#include "Application.h"

RockDollHousePtr RockDollHouse::getTask( ) {
	return std::dynamic_pointer_cast< RockDollHouse >( Application::getInstance( )->getTask( getTag( ) ) );
}

RockDollHouse::RockDollHouse( ) {
}

RockDollHouse::~RockDollHouse( ) {
}

void RockDollHouse::initialize( ) {
	for ( int i = 0; i < MAX_DOLL; i++ ) {
		_dolls[ i ] = ModelMV1Ptr( new ModelMV1 );
	}
	//player
	_dolls[ DOLL_TAROSUKE_WAIT		]->load( "Resource/Rock/player/tarosuke_wait.mv1" );
	_dolls[ DOLL_TAROSUKE_JUMP		]->load( "Resource/Rock/player/tarosuke_jump.mv1" );
	_dolls[ DOLL_TAROSUKE_WALK		]->load( "Resource/Rock/player/tarosuke_walk.mv1" );
	_dolls[ DOLL_TAROSUKE_DEAD		]->load( "Resource/Rock/player/tarosuke_dead.mv1" );
	_dolls[ DOLL_TAROSUKE_CHARGE	]->load( "Resource/Rock/player/tarosuke_charge.mv1" );

	_dolls[ DOLL_GARISUKE_WAIT		]->load( "Resource/Rock/player/garisuke_wait.mv1" );
	_dolls[ DOLL_GARISUKE_JUMP		]->load( "Resource/Rock/player/garisuke_jump.mv1" );
	_dolls[ DOLL_GARISUKE_WALK		]->load( "Resource/Rock/player/garisuke_walk.mv1" );
	_dolls[ DOLL_GARISUKE_DEAD		]->load( "Resource/Rock/player/garisuke_dead.mv1" );
	_dolls[ DOLL_GARISUKE_CHARGE	]->load( "Resource/Rock/player/garisuke_charge.mv1" );

	_dolls[ DOLL_TAROJIRO_WAIT		]->load( "Resource/Rock/player/tarojiro_wait.mv1" );
	_dolls[ DOLL_TAROJIRO_JUMP		]->load( "Resource/Rock/player/tarojiro_jump.mv1" );
	_dolls[ DOLL_TAROJIRO_WALK		]->load( "Resource/Rock/player/tarojiro_walk.mv1" );
	_dolls[ DOLL_TAROJIRO_DEAD		]->load( "Resource/Rock/player/tarojiro_dead.mv1" );
	_dolls[ DOLL_TAROJIRO_CHARGE	]->load( "Resource/Rock/player/tarojiro_charge.mv1" );

	_dolls[ DOLL_TAROMI_WAIT		]->load( "Resource/Rock/player/taromi_wait.mv1" );
	_dolls[ DOLL_TAROMI_JUMP		]->load( "Resource/Rock/player/taromi_jump.mv1" );
	_dolls[ DOLL_TAROMI_WALK		]->load( "Resource/Rock/player/taromi_walk.mv1" );
	_dolls[ DOLL_TAROMI_DEAD		]->load( "Resource/Rock/player/taromi_dead.mv1" );
	_dolls[ DOLL_TAROMI_CHARGE		]->load( "Resource/Rock/player/taromi_charge.mv1" );
	//enemy
	_dolls[ DOLL_GHOST		]->load( "Resource/Rock/enemy/enm05_yurei/enm05_a01.mv1" );
	_dolls[ DOLL_REDBARD	]->load( "Resource/Rock/enemy/enm02_bird/enm02_a01.mv1" );
	_dolls[ DOLL_WATERGHOST ]->load( "Resource/Rock/enemy/enm17_mizunoyokai/enm17_a01.mv1" );
}

ModelMV1Ptr RockDollHouse::getModel( DOLL id ) const {
	return _dolls[ id ];
}

void RockDollHouse::update( ) {
}
