#include "SynchronousData.h"
#include "Application.h"
#include <assert.h>

SynchronousDataPtr SynchronousData::getTask( ) {
	return std::dynamic_pointer_cast< SynchronousData >( Application::getInstance( )->getTask( getTag( ) ) );
}

SynchronousData::SynchronousData( ) {
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

int SynchronousData::getStatusPower( int idx ) {
	assert( idx < ACE_PLAYER_NUM );
	return _data.status[ idx ].power;
}

int SynchronousData::getStatusMoney( int idx ) {
	assert( idx < ACE_PLAYER_NUM );
	return _data.status[ idx ].money;
}

bool SynchronousData::isInProssessionOfStatusItem( int idx, unsigned char item ) {
	assert( idx < ACE_PLAYER_NUM );
	return ( _data.status[ idx ].items & item) != 0;
}

int SynchronousData::getStatusVirtue( int idx ) {
	return _data.status[ idx ].virtue;
}

int SynchronousData::getStatusRedo( int idx ) {
	return _data.status[ idx ].redo;
}

unsigned char SynchronousData::getStatusState( int idx ) {
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
	_object_num = 0;
}

int SynchronousData::getObjectNum( ) {
	return _object_num;
}

int SynchronousData::getObjectX( int idx ) {
	assert( idx < _object_num );
	return _data.object[ idx ].x;
}

int SynchronousData::getObjectY( int idx ) {
	assert( idx < _object_num );
	return _data.object[ idx ].y;
}

unsigned char SynchronousData::getObjectType( int idx ) {
	assert( idx < _object_num );
	return _data.object[ idx ].type;
}

int SynchronousData::getObjectPattern( int idx ) {
	assert( idx < _object_num );
	return _data.object[ idx ].pattern;
}

void SynchronousData::addObject( unsigned char type, int pattern, unsigned char attribute, int x, int y ) {
	if ( _object_num >= OBJECT_NUM ) {
		return;
	}
	assert( x >= 0 );
	assert( y >= 0 );
	assert( pattern >= 0 );
	_data.object[ _object_num ].type      = type;
	_data.object[ _object_num ].pattern   = ( unsigned char )pattern;
	_data.object[ _object_num ].attribute = attribute;
	_data.object[ _object_num ].x         = ( unsigned long )x;
	_data.object[ _object_num ].y         = ( unsigned long )y;
	_object_num++;
}

