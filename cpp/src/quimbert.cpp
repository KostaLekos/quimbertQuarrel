#include "../include/quimbert.hpp"


#include <random>
#include <vector>
#include <string>

std::mt19937_64::result_type Quimbert::randInt( int min, int max ) {
    std::random_device randomDev;
    std::mt19937_64 rng( randomDev() );
    std::uniform_int_distribution< std::mt19937::result_type > dist( min, max );

    return dist( rng );
}

/*
** Simple variable assignment
*/
Quimbert::Quimbert( int looks, int smell, std::string color, 
    int personality, int gumption, int length, 
    std::string name, std::string owner ) {
        this->_looks = looks;
        this->_smell = smell;
        this->_color = color;
        this->_personality = personality;
        this->_gumption = gumption;
        this->_length = length;
        this->_name = name;
        this->_owner = owner;
}

/*
** Sniffs, returns true on success, and false otherwise
*/
bool Quimbert::sniff() {
    if ( 0 < _smell + randInt( -10, 10 ) ) {
        _inventory.push_back( items[ randInt( 0, itemCount - 1 ) ] );
        return true;
    } else {
        return false;
    }
}

int Quimbert::gainBlock() {
    if ( ( _personality + randInt( -7, 10 ) ) >= 10 ) {
        _blocks++;

        if ( _personality == 10 && randInt( 1, 4 ) == 4 ) {
            if ( ( _personality + randInt( -7, 10 ) ) >= 10 ) {
                _blocks++;
                return 2;
            }
        }
        return 1;
    }
    return 0;
}

std::vector< std::string > Quimbert::getInventory() {
    return _inventory;
}

int Quimbert::getHealth() {
    return _health;
}

std::string Quimbert::infoOfItem( std::string item ) {
    /*
    ** Conver `item` to lower case
    */
    std::transform( item.begin(), item.end(), item.begin(), 
        []( unsigned char c ){ return std::tolower( c ); });

    /*
    ** Check against each item and return that items help text
    */
    if ( item == "black truffle" ) {
        return "Take an extra turn.";
    } else if ( item == "mushroom" ) {
        return "Heal 2-4 hp.";
    } else if ( item == "twig" ) {
        return "Deal 2 damage.";
    }else if ( item == "rock" ) {
        return "Deal 2-3 damage.";
    } else if ( item == "white truffle" ) {
        return "Take two extra turns.";
    } else if ( item == "unidentified piece of flesh" ) {
        return "Heal 1-5 hp or take 1-5 damage (or do nothing).";
    } else if ( item == "carrot" ) {
        return "Heal 2 hp.";
    } else if ( item == "knife" ) {
        return "One time use. Deal 5 damage.";
    } else if ( item == "ak47" ) {
        return "One time use. Deal 5-10 damage.";
    } else if ( item == "bazooka" ) {
        return "One time use. Deal 8-14 damage.";
    } else if ( item == "turnip" ) {
        return "Heal 1-3 hp.";
    } else if ( item == "yellow flower" ) {
        return "Useless alone.";
    } else if ( item == "green flower" ) {
        return "Useless alone.";
    } else if ( item == "purple flower" ) {
        return "Useless alone.";
    } else if ( item == "orange flower" ) {
        return "Useless alone.";
    } else if ( item == "red flower" ) {
        return "Useless alone.";
    }
    return "Item does not exist.";
}

bool Quimbert::useItem( std::string item ) {
    for ( std::string invItem : _inventory) {
        if ( invItem == item ) { 
            /*
            ** Item implementations with if-else's
            */




            return true;
        }
    }
    return false;
}