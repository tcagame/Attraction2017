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
	assert( idx < MAX_PLAYER );
	return _data.status[ idx ].power;
}

int SynchronousData::getStatusMoney( int idx ) const {
	assert( idx < MAX_PLAYER );
	return _data.status[ idx ].money;
}

bool SynchronousData::isInProssessionOfStatusItem( int idx, unsigned char item ) const {
	assert( idx < MAX_PLAYER );
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
	assert( idx < MAX_PLAYER );
	assert( power >= 0 );
	_data.status[ idx ].power = ( unsigned char )power;
}

void SynchronousData::setStatusMoney( int idx, int money ) {
	assert( idx < MAX_PLAYER );
	assert( money >= 0 );
	_data.status[ idx ].power = ( unsigned char )money;
}

void SynchronousData::setInProssessionOfStatusItem( int idx, unsigned char item, bool possession ) {
	assert( idx < MAX_PLAYER );
	if ( possession ) {
		_data.status[ idx ].items |= item;
	} else {
		_data.status[ idx ].items &= ~item;
	}
}

void SynchronousData::setStatusVirtue( int idx, int virtue ) {
	assert( idx < MAX_PLAYER );
	assert( virtue >= 0 );
	_data.status[ idx ].power = ( unsigned char )virtue;
}

void SynchronousData::setStatusRedo( int idx, int redo ) {
	assert( idx < MAX_PLAYER );
	assert( redo >= 0 );
	_data.status[ idx ].power = ( unsigned char )redo;
}

void SynchronousData::setStatusState( int idx, unsigned char state ) {
	assert( idx < MAX_PLAYER );
	_data.status[ idx ].power = ( unsigned char )state;
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
