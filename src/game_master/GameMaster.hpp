/**

*/

#pragma once

#include <map>
#include <vector>
#include <list>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Map.hpp"
#include "system.hpp"

class GameMaster {

private:
    std::map<char,char> _mapchars;
    std::vector<std::string> _valid_maps;
    std::list<Enemy> _enemies;

public:
    GameMaster(std::map<char,char> mapchars);

    //selectMap();
    //playMap();

    /**
    Checks the sanity of all found maps.
    */
    bool checkSanityAll();

    /**
    Creates a player and play untill it dies or the map ends.
    */
    void playGame(bool sanity_check = true);

private:
    /**
    Removes dead enemies from the list.
    */
    void _cleanEnemies();

    /**
    Moves the player on the map.
    */
    void _movePlayer(Player& p, Map& current_map);

    /**
    Moves all living enemies on the map. Remember to call _cleanEnemies() before
    this.
    */
    void _moveEnemies(Map& current_map);

    /**
    Fight enemies, if possible.
    */
    void _checkForFights(Player& p);
};
