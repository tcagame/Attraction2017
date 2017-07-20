#include "Application.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Drawer.h"
#include "Editor.h"
#include "Task.h"
#include "ace_define.h"
#include "Editor.h"

void main( ) {
	TaskPtr keyboard = TaskPtr( new Keyboard( ) );
	TaskPtr mouse = TaskPtr( new Mouse( ) );
	TaskPtr drawer = TaskPtr( new Drawer( "../Resource/Ace/Editor" ) );
	TaskPtr editor = TaskPtr( new Editor( ) );

	ApplicationPtr app = Application::getInstance( );
	app->addTask( Keyboard::getTag( ), keyboard );
	app->addTask( Mouse::getTag( ), mouse );
	app->addTask( Drawer::getTag( ), drawer );
	app->addTask( Editor::getTag( ), editor );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
}