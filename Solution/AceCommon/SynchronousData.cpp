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

EVENT SynchronousData::getEvent( ) const {
	return _data.event;
}

void SynchronousData::setEvent( EVENT event ) {
	_data.event = event;
}

int SynchronousData::getCameraX( ) const {
	return _data.camera_x;
}

void SynchronousData::setCameraX( int x ) {
	_data.camera_x = x; 
}

int SynchronousData::getStatusX( PLAYER player ) const {
	return _data.status[ player ].x;
}

int SynchronousData::getStatusPower( PLAYER player ) const {
	return _data.status[ player ].power;
}

int SynchronousData::getStatusMoney( PLAYER player ) const {
	return _data.status[ player ].money;
}

bool SynchronousData::isInProssessionOfStatusItem( PLAYER player, unsigned char item ) const {
	return ( _data.status[ player ].items & item ) != 0;
}

int SynchronousData::getStatusVirtue( PLAYER player ) const {
	return _data.status[ player ].virtue;
}

int SynchronousData::getStatusRedo( PLAYER player ) const {
	return _data.status[ player ].redo;
}

unsigned char SynchronousData::getStatusState( PLAYER player ) const {
	return _data.status[ player ].state;
}

void SynchronousData::setStatusX( PLAYER player, int x ) {
	_data.status[ player ].x = ( long )x;
}

void SynchronousData::setStatusPower( PLAYER player, int power ) {
	assert( power >= 0 );
	_data.status[ player ].power = ( unsigned char )power;
}

void SynchronousData::setStatusMoney( PLAYER player, int money ) {
	assert( money >= 0 );
	_data.status[ player ].money = ( unsigned char )money;
}

void SynchronousData::setInProssessionOfStatusItem( PLAYER player, unsigned char item, bool possession ) {
	if ( possession ) {
		_data.status[ player ].items |= item;
	} else {
		_data.status[ player ].items &= ~item;
	}
}

void SynchronousData::setStatusVirtue( PLAYER player, int virtue ) {
	assert( virtue >= 0 );
	_data.status[ player ].virtue = ( unsigned char )virtue;
}

void SynchronousData::setStatusRedo( PLAYER player, int redo ) {
	assert( redo >= 0 );
	_data.status[ player ].redo = ( unsigned char )redo;
}

void SynchronousData::setStatusState( PLAYER player, unsigned char area ) {
	_data.status[ player ].state = ( unsigned char )area;
}


void SynchronousData::resetObject( ) {
	_data.idx[ AREA_STREET ] = 0;
	_data.idx[ AREA_EVENT ] = OBJECT_NUM - 1;
}

int SynchronousData::getObjectNum( AREA area ) const {
	int num = _data.idx[ area ];
	if ( area == AREA_EVENT ) {
		num = OBJECT_NUM - 1 - num;
	}
	return num;
}

int SynchronousData::getIdx( AREA area, int relative_idx ) const {
	int index = 0;
	if ( area == AREA_STREET ) {
		index = relative_idx;
		assert( index < _data.idx[ AREA_STREET ] );
	} else {
		index = OBJECT_NUM - 1 - relative_idx;
		assert( index > _data.idx[ AREA_EVENT ] );
	}
	return index;
}

int SynchronousData::getObjectAX( int idx ) const {
	return _data.object[ idx ].ax;
}

int SynchronousData::getObjectAY( int idx ) const {
	return _data.object[ idx ].ay;
}

unsigned char SynchronousData::getObjectType( int idx ) const {
	return _data.object[ idx ].type;
}

unsigned char SynchronousData::getObjectAttribute( int idx ) const {
	return _data.object[ idx ].attribute;
}

int SynchronousData::getObjectPattern( int idx ) const {
	return _data.object[ idx ].pattern;
}

int SynchronousData::getObjectSize( int idx ) const {
	return _data.object[ idx ].size;
}

void SynchronousData::addObject( AREA area, unsigned char type, int pattern, unsigned char attribute, int ax, int ay, int size ) {
	if ( _data.idx[ AREA_STREET ] >= _data.idx[ AREA_EVENT ] ) {
		return;
	}
	assert( pattern >= 0 );

	int index = _data.idx[ area ];
	if ( area == AREA_STREET ) {
		_data.idx[ AREA_STREET ]++;
	} else {
		_data.idx[ AREA_EVENT ]--;
	}

	_data.object[ index ].type      = type;
	_data.object[ index ].pattern   = pattern;
	_data.object[ index ].attribute = attribute;
	_data.object[ index ].ax        = ( long )ax;
	_data.object[ index ].ay        = ( long )ay;
	_data.object[ index ].size      = size;
}
