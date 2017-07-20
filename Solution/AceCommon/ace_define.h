#pragma once

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Editor用
const int GRAPH_SIZE = 256;
const int CHIP_WIDTH = 64;
const int CHIP_HEIGHT = 16;
const int OBJECT_GUIDE_SIZE = 16;
const int DISP_WIDTH = SCREEN_WIDTH - CHIP_WIDTH - CHIP_WIDTH / 2;
const int PREVIEW_HEIGHT = GRAPH_SIZE;
const int DISP_CHIP_WIDTH = 19;
const int DISP_CHIP_HEIGHT = 40;
const int PAGE_CHIP_WIDTH_NUM = GRAPH_SIZE / CHIP_WIDTH;
const int MAP_HEIGHT = 40;
const int GUIDE_X = 0;
const int GUIDE_Y = 450 - CHIP_HEIGHT * MAP_HEIGHT / 2 - CHIP_HEIGHT;
const int PREVIEW_X = GUIDE_X + CHIP_WIDTH / 2;
const int PREVIEW_Y = SCREEN_HEIGHT - PREVIEW_HEIGHT;
const int MAP_COVER_HEIGHT = 31;//たろすけライン

const int STRUCTURE_LIST_NUM = 100;
const int GROUND_LIST_NUM = 100;