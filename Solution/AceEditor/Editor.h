#pragma once
#include "ace_define.h"
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( Editor );
PTR( Preview );
PTR( ChipGuide );
PTR( Information );
PTR( ChipCursor );
PTR( ChipEditor );
PTR( ChipMenu );
PTR( ObjectGuide );
PTR( ObjectCursor );
PTR( ObjectMenu );
PTR( Exporter );
PTR( Ground );
PTR( Structure );

class Editor : public Task {
public:
	static std::string getTag( ) { return "EDITOR"; };
	static EditorPtr getTask( );
public:
	enum MODE {
		MODE_OBJECT,
		MODE_CHIP,
		MODE_SAVEALL,
		MODE_LOADALL,
		MODE_SAVEPAGE,
		MODE_LOADPAGE,
		MODE_EXPORT,
	};
public:
	Editor( );
	virtual ~Editor( );
public:
	void update( );
	MODE getMode( ) const;
private:
	enum PHASE {
		PHASE_EDIT_BG,
		PHASE_MENU
	};
private:
	void initialize( );
	void updateMode( );
	void drawMode( );
	void updateChipMode( );
	void updateObjectMode( );
	void drawChipMode( ) const;
	void drawObjectMode( ) const;
	void checkPhase( );
private:
	InformationPtr _information;
	ChipGuidePtr _chip_guide;
	PreviewPtr _preview;
	ChipCursorPtr _chip_cursor;
	ChipEditorPtr _chip_editor;
	ChipMenuPtr _chip_menu;
	ObjectGuidePtr _object_guide;
	ObjectCursorPtr _object_cursor;
	ObjectMenuPtr _object_menu;
	ExporterPtr _exporter;
	PHASE _phase;
	MODE _mode;
};

