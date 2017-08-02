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
	_dolls[ DOLL_GHOST ]->load( "Resource/Rock/enemy/enm05_yurei/enm05_a01.mv1" );
	_dolls[ DOLL_REDBARD ]->load( "Resource/Rock/enemy/enm02_bird/enm02_a01.mv1" );
	_dolls[ DOLL_WATERGHOST ]->load( "Resource/Rock/enemy/enm17_mizunoyokai/enm17_a01.mv1" );
}

ModelMV1Ptr RockDollHouse::getModel( DOLL id ) const {
	return _dolls[ id ];
}

void RockDollHouse::update( ) {
}
