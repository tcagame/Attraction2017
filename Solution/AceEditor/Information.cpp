#include "Information.h"
#include "Drawer.h"
#include "ace_define.h"
#include "ChipCursor.h"
#include "ObjectCursor.h"
#include "Data.h"
#include "ChipEditor.h"
#include "Editor.h"

const int VIEW_CHIP_POS_X = 0;
const int VIEW_CHIP_POS_Y = 0;
const int VIEW_PAGE_POS_X = 0;
const int VIEW_PAGE_POS_Y = 20;
const int VIEW_GUIDE_POS_X = 0;
const int VIEW_GUIDE_POS_Y = 40;
const int VIEW_MODE_POS_X = SCREEN_WIDTH - 200;
const int VIEW_MODE_POS_Y = 20;
const int VIEW_CHIP_MODE_POS_X = SCREEN_WIDTH - 200;
const int VIEW_CHIP_MODE_POS_Y = 40;

Information::Information( DataConstPtr data, ChipCursorConstPtr chip_cursor, ObjectCursorConstPtr object_cursor, ChipEditorConstPtr chip_editor ) :
_chip_cursor( chip_cursor ),
_object_cursor( object_cursor ),
_data( data ),
_chip_editor( chip_editor ) {
}

Information::~Information( ) {
}

void Information::draw( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->drawString( VIEW_CHIP_POS_X, VIEW_CHIP_POS_Y, "チップ座標:%d", _chip_cursor->getScrollX( ) );
	

	Editor::MODE edit_mode = Editor::getTask( )->getMode( );
	switch ( edit_mode ) {
	case Editor::MODE_CHIP:
		drawer->drawString( VIEW_MODE_POS_X, VIEW_MODE_POS_Y, "チップモード" );
		drawChipMode( );
		break;
	case Editor::MODE_OBJECT:
		drawer->drawString( VIEW_MODE_POS_X, VIEW_MODE_POS_Y, "オブジェクトモード" );
		drawObjectMode( );
		break;
	}
}

void Information::drawChipMode( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	ChipEditor::MODE chip_mode;
	int number;
	_chip_editor->getMode( chip_mode, number );
	switch ( chip_mode ) {
		case ChipEditor::MODE_HEIGHT:
			drawer->drawString( VIEW_CHIP_MODE_POS_X, VIEW_CHIP_MODE_POS_Y, "高さ編集：%d", number );
			break;
		case ChipEditor::MODE_STRUCTURE:
			drawer->drawString( VIEW_CHIP_MODE_POS_X, VIEW_CHIP_MODE_POS_Y, "ストラクチャー編集：%d", number );
			break;
		case ChipEditor::MODE_GROUND:
			drawer->drawString( VIEW_CHIP_MODE_POS_X, VIEW_CHIP_MODE_POS_Y, "グラウンド編集：%d", number );
			break;
		case ChipEditor::MODE_COPY:
			drawer->drawString( VIEW_CHIP_MODE_POS_X, VIEW_CHIP_MODE_POS_Y, "コピー中" );
			break;
	}

	if ( _chip_cursor->isOnChip( ) ) {
		drawer->drawString( VIEW_PAGE_POS_X, VIEW_PAGE_POS_Y, "ページ座標:%d", ( ( _chip_cursor->getScrollX( ) + _chip_cursor->getGX( ) ) * CHIP_WIDTH / GRAPH_SIZE ) % _data->getPageNum( ) );
		drawer->drawString( VIEW_GUIDE_POS_X, VIEW_GUIDE_POS_Y, "ガイド座標:%d,%d", _chip_cursor->getGX( ), _chip_cursor->getGY( ) );
	}
}

void Information::drawObjectMode( ) const {
	DrawerPtr drawer( Drawer::getTask( ) );
	if ( _object_cursor->isOnChip( ) ) {
		drawer->drawString( VIEW_GUIDE_POS_X, VIEW_GUIDE_POS_Y, "ガイド座標:%d,%d", _object_cursor->getGX( ), _object_cursor->getGY( ) );
	}
}