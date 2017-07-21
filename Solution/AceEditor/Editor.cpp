#include "Editor.h"
#include "Drawer.h"
#include "Application.h"
#include "ChipPreview.h"
#include "ChipGuide.h"
#include "Data.h"
#include "Information.h"
#include "ChipCursor.h"
#include "ChipEditor.h"
#include "Exporter.h"
#include "ChipMenu.h"
#include "ObjectGuide.h"
#include "ObjectPreview.h"
#include "ObjectCursor.h"
#include "ObjectEditor.h"
#include "ObjectMenu.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Ground.h"
#include "Structure.h"

EditorPtr Editor::getTask( ) {
	ApplicationPtr app = Application::getInstance( );
	return std::dynamic_pointer_cast< Editor >( app->getTask( getTag( ) ) );
}


Editor::Editor( ) :
_phase( PHASE_EDIT_BG ),
_mode( MODE_CHIP ) {
}

Editor::~Editor( ) {
}

void Editor::initialize( ) {
	// drawer初期化後
	ImagePtr menu_image = Drawer::getTask( )->createImage( "Menu/menu.png" );
	GroundPtr ground = GroundPtr( new Ground );
	StructurePtr structure = StructurePtr( new Structure );

	DataPtr data    = DataPtr		  ( new Data );
	_chip_cursor    = ChipCursorPtr	  ( new ChipCursor   ( data ) );
	_chip_editor    = ChipEditorPtr	  ( new ChipEditor   ( data, _chip_cursor ) );
	_chip_guide     = ChipGuidePtr	  ( new ChipGuide	 ( data, _chip_cursor, _chip_editor ) );
	_chip_preview   = ChipPreviewPtr  ( new ChipPreview  ( data, _chip_cursor, _chip_editor, ground, structure ) );
	_chip_menu	    = ChipMenuPtr	  ( new ChipMenu	 ( menu_image, _chip_editor, ground, structure ) );
	_object_cursor  = ObjectCursorPtr ( new ObjectCursor ( data ) );
	_object_editor  = ObjectEditorPtr ( new ObjectEditor ( data, _object_cursor ) );
	_object_guide   = ObjectGuidePtr  ( new ObjectGuide  ( data, _object_cursor ) );
	_object_preview = ObjectPreviewPtr( new ObjectPreview( data, _object_cursor ) );
	_object_menu    = ObjectMenuPtr   ( new ObjectMenu   ( menu_image ) );
	_information    = InformationPtr  ( new Information  ( data, _chip_cursor, _object_cursor, _chip_editor ) );
	_exporter       = ExporterPtr	  ( new Exporter     ( data ) );
}


void Editor::update( ) {
	updateMode( );
	drawMode( );
}

void Editor::updateMode( ) {
	switch ( _mode ) {
	case MODE_CHIP:
		updateChipMode( );
		break;
	case MODE_OBJECT:
		updateObjectMode( );
		break;
	case MODE_SAVEALL:
		_chip_editor->save( );
		_mode = MODE_CHIP;
		break;
	case MODE_LOADALL:
		_chip_editor->load( );
		_mode = MODE_CHIP;
		break;
	case MODE_SAVEPAGE:
		_chip_editor->savePage( );
		_mode = MODE_CHIP;
		break;
	case MODE_LOADPAGE:
		_chip_editor->loadPage( );
		_mode = MODE_CHIP;
		break;
	case MODE_EXPORT:
		if ( !_exporter->update( ) ) {
			_mode = MODE_CHIP;
		}
		break;
	}

	if ( _mode != MODE_EXPORT ) {
		KeyboardPtr keyboard( Keyboard::getTask( ) );
		if ( keyboard->isPushKey( "F1" ) ) {
			_mode = MODE_SAVEALL;
		}
		if ( keyboard->isPushKey( "F2" ) ) {
			_mode = MODE_LOADALL;
		}
		if ( keyboard->isPushKey( "F3" ) ) {
			_mode = MODE_SAVEPAGE;
		}
		if ( keyboard->isPushKey( "F4" ) ) {
			_mode = MODE_LOADPAGE;
		}
		if ( keyboard->isPushKey( "F5" ) ) {
			_mode = MODE_CHIP;
			_phase = PHASE_EDIT_BG;
			_chip_cursor->setScrollX( _object_cursor->getScrollX( ) );
		}
		if ( keyboard->isPushKey( "F6" ) ) {	
			_mode = MODE_OBJECT;
			_phase = PHASE_EDIT_BG;
			_object_cursor->setScrollX( _chip_cursor->getScrollX( ) );
		}
		if ( keyboard->isPushKey( "F9" ) ) {
			_mode = MODE_EXPORT;
			_exporter->start( );
		}
	}
}

void Editor::drawMode( ) {
	// 常に描画
	_information->draw( );
	_chip_preview->draw( );
	DrawerPtr drawer = Drawer::getTask( );
	switch ( _mode ) {
	case MODE_CHIP:
		drawChipMode( );
		break;
	case MODE_OBJECT:
		drawObjectMode( );
		break;
	case MODE_EXPORT:
		_exporter->draw( );
		break;
	}
	
	drawer->flip( );

	switch ( _mode ) {
	case MODE_SAVEALL:
		drawer->drawString( 0, 0, "セーブ" );
		break;
	case MODE_LOADALL:
		drawer->drawString( 0, 0, "ロード" );
		break;
	case MODE_SAVEPAGE:
		drawer->drawString( 0, 0, "ページセーブ" );
		break;
	case MODE_LOADPAGE:
		drawer->drawString( 0, 0, "ページロード" );
		break;
	}
}

void Editor::updateChipMode( ) {
	switch( _phase ) {
	case PHASE_EDIT_BG:
		_chip_preview->update( );
		_chip_cursor->update( );
		_object_cursor->setScrollX( _chip_cursor->getScrollX( ) );
		_chip_editor->update( );
		break;
	case PHASE_MENU:
		_chip_menu->update( );
		break;
	}

	checkPhase( );
}

void Editor::updateObjectMode( ) {
	switch( _phase ) {
	case PHASE_EDIT_BG:
		_object_cursor->update( );
		_chip_cursor->setScrollX( _object_cursor->getScrollX( ) );
		_object_editor->update( );
		break;
	case PHASE_MENU:
		_object_menu->update( );
		break;
	}

	checkPhase( );
}

void Editor::checkPhase( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->isPushRightButton( ) ) {
		PHASE phase = _phase;
		if ( _phase == PHASE_EDIT_BG ) {
			phase = PHASE_MENU;
			switch( _mode ) {
			case MODE_CHIP:
				_chip_menu->setPos( mouse->getPos( ) );
				break;
			case MODE_OBJECT:
				_object_menu->setPos( mouse->getPos( ) );
				break;
			}
		}
		if ( _phase == PHASE_MENU ) {
			phase = PHASE_EDIT_BG;
		}
		_phase = phase;
	}
	bool active = false;
	if ( !_chip_menu->getActive( ) && _mode == MODE_CHIP ) {
		active = true;
	}
	if ( !_object_menu->getActive( ) && _mode == MODE_OBJECT ) {
		active = true;
	}
	if ( _phase == PHASE_MENU && mouse->isPushLeftButton( ) && active ) {
		_phase = PHASE_EDIT_BG;
	}
}

void Editor::drawChipMode( ) const {
	_chip_guide->draw( );
	if ( _phase == PHASE_MENU ) {
		_chip_menu->draw( );
	}
}

void Editor::drawObjectMode( ) const {
	_object_guide->draw( );
	_object_preview->draw( );
	if ( _phase == PHASE_MENU ) {
		_object_menu->draw( );
	}
}

Editor::MODE Editor::getMode( ) const {
	return _mode;
}