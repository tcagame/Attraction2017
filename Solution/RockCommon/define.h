#pragma once

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = ( SCREEN_WIDTH * 9 ) / 16;

const int MESSAGE_COUNT = 10;

const unsigned int STATE_NONE		= 0b00000000;
const unsigned int STATE_ENTRY		= 0b00000001;
const unsigned int STATE_STREET_1	= 0b00000010;
const unsigned int STATE_STREET_2	= 0b00000100;
const unsigned int STATE_STREET_3	= 0b00001000;
const unsigned int STATE_BOSS		= 0b00010000;
const unsigned int STATE_RESULT		= 0b00100000;
