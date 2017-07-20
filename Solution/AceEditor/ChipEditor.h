#pragma once
#include "smart_ptr.h"
#include <vector>

PTR( Data );
PTR( ChipCursor );

class ChipEditor {
public:
	enum MODE {
		MODE_GROUND,
		MODE_STRUCTURE,
		MODE_HEIGHT,
		MODE_COPY,
		MODE_SAVE,
	};
public:
	ChipEditor( DataPtr data, ChipCursorConstPtr chip_cursor );
	virtual ~ChipEditor( );
public:
	void update( );
	void setMode( MODE mode, int number );
	void getMode( MODE& mode, int& number ) const;
	int getRange( ) const;
	void getReplacePos( std::vector< int >& x, std::vector< int >& y, bool mx_my = false ) const;
	void save( ) const;
	void load( );
	void savePage( ) const;
	void loadPage( );
private:
	void edit( );
	void updateMode( );
	void editWidth( );
	void editChip( );
	void changeRange( );
private:
	DataPtr _data;
	ChipCursorConstPtr _chip_cursor;
	MODE _mode;
	MODE _before_mode;
	int _number;
	int _range;
	bool _click_active;//メニューを閉じたときにクリック判定が出るのを防ぐ
};

