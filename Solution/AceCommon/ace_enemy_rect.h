#pragma once

const int SMALL_CHIP_SIZE = 32; // SMALL_CHAR_GRAPH_SIZEÇ∆ìØÇ∂Ç…Ç∑ÇÈ
const int CHIP_SIZE = 64; // NORMAL_CHAR_GRAPH_SIZEÇ∆ìØÇ∂Ç…Ç∑ÇÈ
const int BIG_CHIP_SIZE = 128; // BIG_CHAR_GRAPH_SIZEÇ∆ìØÇ∂Ç…Ç∑ÇÈ

struct Rect {
	int tx;
	int ty;
	Rect( ) {
		tx = 0;
		ty = 0;
	}
	Rect( int tx_, int ty_ ) {
		tx = tx_;
		ty = ty_;
	}
};

// âÊëúÇÃç∑Çµë÷Ç¶Ç…ÇÊÇËïœçXóLÇË
const Rect RECT_PUPLE_ZOMBIE	( 0 * CHIP_SIZE, 3 * CHIP_SIZE );
const Rect RECT_FACE_AND_HAND	( 2 * CHIP_SIZE, 9 * CHIP_SIZE );
const Rect RECT_NO_FACE			( 0 * CHIP_SIZE, 11 * CHIP_SIZE );
const Rect RECT_LANCER			( 0 * CHIP_SIZE, 7 * CHIP_SIZE );
const Rect RECT_CROCO_SNAKE		( 0 * CHIP_SIZE, 8 * CHIP_SIZE );
const Rect RECT_GHOUL			( 0 * CHIP_SIZE, 1 * CHIP_SIZE );
const Rect RECT_GHOST			( 16 * CHIP_SIZE, 11 * CHIP_SIZE );
const Rect RECT_ONE_EYE_SNAKE	( 0 * CHIP_SIZE, 0 * CHIP_SIZE );
const Rect RECT_WHITE_MIST		( 5 * CHIP_SIZE, 7 * CHIP_SIZE );
const Rect RECT_GRAY_MIST		( 11 * CHIP_SIZE, 7 * CHIP_SIZE );
const Rect RECT_STONE_FACE		( 12 * CHIP_SIZE, 1 * CHIP_SIZE );
const Rect RECT_NO_NECK_GHOST	( 0 * CHIP_SIZE, 10 * CHIP_SIZE );
const Rect RECT_SHISHIMAI_DAEMON	( 8 * CHIP_SIZE, 12 * CHIP_SIZE );
const Rect RECT_SHISHIMAI		( 0 * CHIP_SIZE, 12 * CHIP_SIZE );
const Rect RECT_ARCHER			( 0 * CHIP_SIZE, 13 * CHIP_SIZE );
const Rect RECT_HAND			( 8 * CHIP_SIZE, 2 * CHIP_SIZE );
const Rect RECT_RED_BIRD		( 0 * CHIP_SIZE, 14 * CHIP_SIZE );
const Rect RECT_BLUE_MONK		( 6 * CHIP_SIZE, 9 * CHIP_SIZE );
//const Rect RECT_RED_DAEMON_JR	( 1 * CHIP_SIZE, 9 * CHIP_SIZE );EditorÇ≈èûä“Ç∑ÇÈÇ©ïsñæ
const Rect RECT_GREEN_ZOMBIE	( 6 * CHIP_SIZE, 3 * CHIP_SIZE );
const Rect RECT_HUG_DAEMON		( 13 * CHIP_SIZE, 9 * CHIP_SIZE );
const Rect RECT_SWAMP_ZOMBIE_A	( 0 * CHIP_SIZE, 6 * CHIP_SIZE );
const Rect RECT_SWAMP_ZOMBIE_B	( 0 * CHIP_SIZE, 4 * CHIP_SIZE );
const Rect RECT_SWAMP_ZOMBIE_C	( 6 * CHIP_SIZE, 5 * CHIP_SIZE );
const Rect RECT_SKELETON		( 0 * CHIP_SIZE, 2 * CHIP_SIZE );
const Rect RECT_LADY			( 0 * CHIP_SIZE, 1 * CHIP_SIZE );
const Rect RECT_WIND			( 4 * BIG_CHIP_SIZE, 3 * BIG_CHIP_SIZE );
const Rect RECT_ONYUDO			( 0 * BIG_CHIP_SIZE, 1 * BIG_CHIP_SIZE );
const Rect RECT_JIZO			( 7 * BIG_CHIP_SIZE, 0 * BIG_CHIP_SIZE );
const Rect RECT_TREE			( 0 * BIG_CHIP_SIZE, 4 * BIG_CHIP_SIZE );
const Rect RECT_GAMA			( 0 * BIG_CHIP_SIZE, 5 * BIG_CHIP_SIZE );
const Rect RECT_FLOG			( 0 * SMALL_CHIP_SIZE, 1 * SMALL_CHIP_SIZE );
const Rect RECT_BAT				( 5 * SMALL_CHIP_SIZE, 0 * SMALL_CHIP_SIZE );
const Rect RECT_STONE			( 0 * SMALL_CHIP_SIZE, 6 * SMALL_CHIP_SIZE );
const Rect RECT_MOTH			( 0 * SMALL_CHIP_SIZE, 5 * SMALL_CHIP_SIZE );
const Rect RECT_EYE_DAEMON		( 3 * SMALL_CHIP_SIZE, 5 * SMALL_CHIP_SIZE );
