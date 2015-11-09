/**
This file defines each character that composes a map and what it is supposed to
represent.
*/

#pragma once

#include <vector>

struct TranslationList {
    char WALL;
    char GROUND;
    char GRASS;
    char TREE;
};

const TranslationList Components = {.WALL = 'w', .GROUND = 'g', .GRASS = ';', .TREE = 't'};

const std::vector<char> ALLOWED_CHARS = { Components.WALL,
                                          Components.GROUND,
                                          Components.GRASS,
                                          Components.TREE };
