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
    */
    std::string sniff();

    /*
    ** Block attack?
    */
    void block();

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
    */
    void useItem( std::string item );

    /*
    ** Get a string with your current stats
    */
    std::string getStatsString();

    /*
    ** Return individual stat value
    */
    std::string getStat( std::string stat );

    /*
    ** Returns a random integer min <= x <= max
    */
    static std::mt19937_64::result_type randInt( int min, int max );

private:

    /*
    ** Point affected stats
    */
    int looks;
    int smell;
    std::string color;
    int personality;
    int gumption;
    int length;
    std::string name;
    std::string owner;


    /*
    ** Non point affected things
    */
    int health;
    int turns;
    int toDeal;
    int blocks;
    int lives = 1;
    int yellowFlowers;
    int greenFlowers;
    int purpleFlowers;
    int orangeFlowers;
    int redFlowers;
    std::vector< std::string > Inventory;

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