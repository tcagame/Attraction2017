#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "Application.h"

PTR( Controller );
PTR( Command );
PTR( StatusDrawer );

class Controller : public Task {
public:
	static std::string getTag( ) { return "CONTROLLER"; };
	static ControllerPtr getTask( ) {
		ApplicationPtr app = Application::getInstance( );
		return std::dynamic_pointer_cast< Controller >( app->getTask( getTag( ) ) );
	};
public:
	Controller( );
	virtual ~Controller( );
public:
	void initialize( );
private:
	void update( );
	void drawFlame( ) const;
private:
	CommandPtr _command;
	StatusDrawerPtr _status_drawer;
};

