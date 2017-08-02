#pragma once

const int CHIP_SIZE = 64; // NORMAL_CHAR_GRAPH_SIZEのサイズと同じにする

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

// 画像の差し替えにより変更有り
const Rect RECT_PUPLE_ZOMBIE	( 0 * CHIP_SIZE, 1 * CHIP_SIZE );
const Rect RECT_FACE_AND_HAND	( 3 * CHIP_SIZE, 7 * CHIP_SIZE );
const Rect RECT_NO_FACE			( 12 * CHIP_SIZE, 5 * CHIP_SIZE );
const Rect RECT_LANCER			( 5 * CHIP_SIZE, 11 * CHIP_SIZE );
const Rect RECT_CROCO_SNAKE		( 4 * CHIP_SIZE, 7 * CHIP_SIZE );
const Rect RECT_GHOUL			( 7 * CHIP_SIZE, 8 * CHIP_SIZE );
const Rect RECT_GHOST			( 2 * CHIP_SIZE, 3 * CHIP_SIZE );
const Rect RECT_ONE_EYE_SNAKE	( 0 * CHIP_SIZE, 12 * CHIP_SIZE );
const Rect RECT_WHITE_MIST		( 1 * CHIP_SIZE, 5 * CHIP_SIZE );
const Rect RECT_STONE_FACE		( 1 * CHIP_SIZE, 9 * CHIP_SIZE );

const Rect RECT_NO_NECK_GHOST	( 6 * CHIP_SIZE, 1 * CHIP_SIZE );
const Rect RECT_SHISHIMAI_DEMON	( 8 * CHIP_SIZE, 5 * CHIP_SIZE );
const Rect RECT_SHISHIMAI		( 4 * CHIP_SIZE, 5 * CHIP_SIZE );
const Rect RECT_ARCHER			( 7 * CHIP_SIZE, 4 * CHIP_SIZE );
const Rect RECT_HAND			( 8 * CHIP_SIZE, 0 * CHIP_SIZE );
const Rect RECT_RED_BIRD		( 0 * CHIP_SIZE, 4 * CHIP_SIZE );
const Rect RECT_BLUE_MONK		( 11 * CHIP_SIZE, 8 * CHIP_SIZE );
//const Rect RECT_RED_DEMON_JR	( 1 * CHIP_SIZE, 9 * CHIP_SIZE );Editorで償還するか不明
const Rect RECT_GREEN_ZOMBIE	( 3 * CHIP_SIZE, 1 * CHIP_SIZE );
const Rect RECT_HUG_DEMON		( 4 * CHIP_SIZE, 6 * CHIP_SIZE );
const Rect RECT_SWAMP_ZOMBIE_A	( 0 * CHIP_SIZE, 10 * CHIP_SIZE );
const Rect RECT_SWAMP_ZOMBIE_B	( 5 * CHIP_SIZE, 10 * CHIP_SIZE );
const Rect RECT_SWAMP_ZOMBIE_C	( 4 * CHIP_SIZE, 11 * CHIP_SIZE );
