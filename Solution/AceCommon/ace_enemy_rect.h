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
const Rect RECT_PUPLE_ZOMBIE( 0 * CHIP_SIZE, 1 * CHIP_SIZE );
const Rect RECT_FACE_AND_HAND( 3 * CHIP_SIZE, 7 * CHIP_SIZE );