#pragma once

#include <random>
#include <string>
#include <vector>

class Quimbert {
public:
    Quimbert( int looks, int smell, std::string color, 
        int personality, int gumption, int length, 
        std::string name, std::string owner );
    
    /*
    ** Sniff gets an item and adds it to your inventory, or fails and does nothing
    ** Hint, if you need to know how many items, get the inventory size, then call sniff, then get the size again.
    ** If you need the items, then they are always the back one (or two) elements of the inventory vec
    */
    void sniff();

    /*
    ** Gains a block or 2 or none
    ** If you need the number, see Sniff() comments above
    */
    void gainBlock();

    /*
    ** Return inventory
    */
    std::vector< std::string > getInventory();

    /*
    ** Returns current health
    */
    int getHealth();

    /*
    ** Get info on item
    */
    static std::string infoOfItem( std::string item );

    /*
    ** Use an item from your inventory
    ** Returns true if succeeded, false if failed
    */
    bool useItem( std::string item );

    /*
    ** Get a string with your current stats
    */
    std::string getStatsString();

    /*
    ** Return individual stat value
    */
    std::string getStrStat( std::string stat );
    int getIntStat( std::string stat );

    /*
    ** Returns a random integer min <= x <= max
    */
    static std::mt19937_64::result_type randInt( int min, int max );

private:

    /*
    ** Point affected stats
    */
    int _looks;
    int _smell;
    std::string _color;
    int _personality;
    int _gumption;
    int _length;
    std::string _name;
    std::string _owner;


    /*
    ** Non point affected things
    */
    int _health;
    int _turns;
    int _toDeal;
    int _blocks;
    int _lives = 1;
    int _yellowFlowers;
    int _greenFlowers;
    int _purpleFlowers;
    int _orangeFlowers;
    int _redFlowers;
    std::vector< std::string > _inventory;

    /*
    ** List of all possible items, there are redundant items because they are more commom than others
    */
    static inline const std::string items[] = {
        "black truffle", "mushroom", "twig", "rock", "white truffle", 
        "unidentified piece of flesh", "carrot", "knife", "ak47", "bazooka",
        "turnip", "yellow flower", "green flower", "purple flower", 
        "orange flower", "red flower", "black truffle", "mushroom",
        "twig", "rock", "unidentified piece of flesh", "carrot", "knife",
        "turnip", "yellow flower", "green flower", "purple flower", 
        "orange flower", "red flower", "twig", "rock",
        "unidentified piece of flesh", "carrot", "turnip", "yellow flower",
        "green flower", "purple flower", "orange flower", "red flower"
    };

    /*
    ** Number of items
    */
    static inline const std::size_t itemCount = std::size( items );

};