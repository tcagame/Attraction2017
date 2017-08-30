#include "World.h"
#include "SynchronousData.h"
#include "Application.h"

WorldPtr World::getTask( ) {
	return std::dynamic_pointer_cast< World >( Application::getInstance( )->getTask( getTag( ) ) );
}

World::World( ) :
_event( EVENT_NONE ) {
}

World::~World( ) {
}

void World::update( ) {
	// �����f�[�^�ɃC�x���g����ݒ�
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->setEvent( _event );
}

void World::setEvent( EVENT event ) {
	_event = event;
}
