#include "SynchronousData.h"
#include "Application.h"
#include <assert.h>

SynchronousDataPtr SynchronousData::getTask( ) {
	return std::dynamic_pointer_cast< SynchronousData >( Application::getInstance( )->getTask( getTag( ) ) );
}

SynchronousData::SynchronousData( ) {
	resetObject( );
}


SynchronousData::~SynchronousData( ) {
}

void SynchronousData::update( ) {

}

void * SynchronousData::getPtr( ) {
	return ( void * )&_data;
}

int SynchronousData::getSize( ) {
	return sizeof( _data );
}

int SynchronousData::getStatusPower( int idx ) const {
	assert( idx < ACE_PLAYER_NUM );
	return _data.status[ idx ].power;
}

int SynchronousData::getStatusMoney( int idx ) const {
	assert( idx < ACE_PLAYER_NUM );
	return _data.status[ idx ].money;
}

bool SynchronousData::isInProssessionOfStatusItem( int idx, unsigned char item ) const {
	assert( idx < ACE_PLAYER_NUM );
	return ( _data.status[ idx ].items & item) != 0;
}

int SynchronousData::getStatusVirtue( int idx ) const {
	return _data.status[ idx ].virtue;
}

int SynchronousData::getStatusRedo( int idx ) const {
	return _data.status[ idx ].redo;
}

unsigned char SynchronousData::getStatusState( int idx ) const {
	return _data.status[ idx ].state;
}

void SynchronousData::setStatusPower( int idx, int power ) {
	assert( idx < ACE_PLAYER_NUM );
	assert( power >= 0 );
	_data.status[ idx ].power = ( unsigned char )power;
}

void SynchronousData::setStatusMoney( int idx, int money ) {
	assert( idx < ACE_PLAYER_NUM );
	assert( money >= 0 );
	_data.status[ idx ].power = ( unsigned char )money;
}

void SynchronousData::setInProssessionOfStatusItem( int idx, unsigned char item, bool possession ) {
	assert( idx < ACE_PLAYER_NUM );
	if ( possession ) {
		_data.status[ idx ].items |= item;
	} else {
		_data.status[ idx ].items &= ~item;
	}
}

void SynchronousData::setStatusVirtue( int idx, int virtue ) {
	assert( idx < ACE_PLAYER_NUM );
	assert( virtue >= 0 );
	_data.status[ idx ].power = ( unsigned char )virtue;
}

void SynchronousData::setStatusRedo( int idx, int redo ) {
	assert( idx < ACE_PLAYER_NUM );
	assert( redo >= 0 );
	_data.status[ idx ].power = ( unsigned char )redo;
}

void SynchronousData::setStatusState( int idx, unsigned char state ) {
	assert( idx < ACE_PLAYER_NUM );
	_data.status[ idx ].power = ( unsigned char )state;
}


void SynchronousData::resetObject( ) {
	_object_idx[ AREA_MAIN ] = 0;
	_object_idx[ AREA_EVENT ] = OBJECT_NUM - 1;
}

int SynchronousData::getObjectNum( AREA area ) const {
	int num = _object_idx[ area ];
	if ( area == AREA_EVENT ) {
		num = OBJECT_NUM - 1 - num;
	}
	return num;
}

int SynchronousData::getIdx( AREA area, int relative_idx ) const {
	int idx = 0;
	if ( area == AREA_MAIN ) {
		idx = relative_idx;
		assert( idx < _object_idx[ AREA_MAIN ] );
	} else {
		idx = OBJECT_NUM - 1 - relative_idx;
		assert( idx > _object_idx[ AREA_EVENT ] );
	}
	return idx;
}

int SynchronousData::getObjectX( int idx ) const {
	return _data.object[ idx ].x;
}

int SynchronousData::getObjectY( int idx ) const {
	return _data.object[ idx ].y;
}

unsigned char SynchronousData::getObjectType( int idx ) const {
	return _data.object[ idx ].type;
}

int SynchronousData::getObjectPattern( int idx ) const {
	return _data.object[ idx ].pattern;
}

void SynchronousData::addObject( AREA area, unsigned char type, int pattern, unsigned char attribute, int x, int y ) {
	if ( _object_idx[ AREA_MAIN ] >= _object_idx[ AREA_EVENT ] ) {
		return;
	}
	assert( x >= 0 );
	assert( y >= 0 );
	assert( pattern >= 0 );

	int idx = _object_idx[ area ];
	if ( area == AREA_MAIN ) {
		_object_idx[ AREA_MAIN ]++;
	} else {
		_object_idx[ AREA_EVENT ]--;
	}

	_data.object[ idx ].type      = type;
	_data.object[ idx ].pattern   = ( unsigned char )pattern;
	_data.object[ idx ].attribute = attribute;
	_data.object[ idx ].x         = ( unsigned long )x;
	_data.object[ idx ].y         = ( unsigned long )y;
}

