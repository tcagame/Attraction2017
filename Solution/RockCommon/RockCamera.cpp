#include "RockCamera.h"
#include "Application.h"
#include "Drawer.h"

RockCameraPtr RockCamera::getTask( ) {
	return std::dynamic_pointer_cast< RockCamera >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockCamera::RockCamera( const Vector& pos, const Vector& target ) :
_pos( pos ),
_target( target ) {
}


RockCamera::~RockCamera( ) {
}

void RockCamera::initialize( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->setCameraUp( Vector( 0, 1, 0 ) );
	drawer->setCamera( _pos, _target );
}


Vector RockCamera::getPos( ) const {
	return _pos;
}

Vector RockCamera::getTarget( ) const {
	return _target;
}

void RockCamera::setPos( const Vector& pos ) {
	_pos = pos;
}

void RockCamera::setTarget( const Vector& target ) {
	_target = target;
}