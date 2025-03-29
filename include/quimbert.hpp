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
    ** Returns a random integer min <= x <= max
    */
    static std::mt19937_64::result_type randInt( int min, int max );

    /*
    ** Returns a pointer to the inventory, which is dangerous because you have raw access to the _inventory object
    */
    std::vector< std::string > *getInventoryDangerous();

    
    /*
    ** Get the stats
    */

    int getLooks();
    int getSmell();
    std::string getColor();
    int getPersonality();
    int getGumption();
    int getLength();
    std::string getName();
    std::string getOwner();

    /*
    ** Set stats
    */

    void setLooks( int newVal );
    void setSmell( int newVal );
    void setColor( std::string newVal );
    void setPersonality( int newVal );
    void setGumption( int newVal );
    void setLength( int newVal );
    void setName( std::string newVal );
    void setOwner( std::string newVal );

    /*
    ** Get other stats
    */

    int getHealth();
    int getTurns();
    int getToDeal();
    int getBlocks();
    int getLives();
    int getYellowFlowers();
    int getGreenFlowers();
    int getPurpleFlowers();
    int getOrangeFlowers();
    int getRedFlowers();
    std::vector< std::string > getInventory();

    void setHealth( int newVal );
    void setTurns( int newVal );
    void setToDeal( int newVal );
    void setBlocks( int newVal );
    void setLives( int newVal );
    void setYellowFlowers( int newVal );
    void setGreenFlowers( int newVal );
    void setPurpleFlowers( int newVal );
    void setOrangeFlowers( int newVal );
    void setRedFlowers( int newVal );
    void setInventory( std::vector< std::string > newVal );



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