#include "../include/quimbert.hpp"


#include <random>
#include <vector>
#include <string>
#include <algorithm>

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
    for ( int i = 0; i < _inventory.size(); i++ ) {
        if ( _inventory[ i ] == item ) {

            /*
            ** Item implementations with if-else's
            */

            if ( item == "black truffle" ) {
                _inventory.erase( _inventory.begin() + i );
                if ( ( _gumption + randInt( -2, 10 ) ) >= 10 ) {
                    _turns += 2;
                    return true;
                } else {
                    return false;
                }
            } else if ( item == "mushroom" ) {
                _inventory.erase( _inventory.begin() + i );
                if ( _gumption + randInt( -1, 10 ) >= 10 ) {
                    _health += randInt( 2, 4 );
                    return true;
                } else {
                    return false;
                }
            } else if ( item == "twig" ) {
                _inventory.erase( _inventory.begin() + i );
                if ( _gumption + randInt( 0, 10 ) >= 10 ) {
                    _toDeal = 2;
                    return true;
                } else {
                    return false;
                }
            } else if ( item == "rock" ) {
                _inventory.erase( _inventory.begin() + i );
                if ( _gumption + randInt( -1, 10 ) >= 10 ) {
                    _toDeal = randInt( 2, 3 );
                    return true;
                } else {
                    return false;
                }
            } else if ( item == "white truffle" ) {
                _inventory.erase( _inventory.begin() + i );
                if ( _gumption + randInt( -3, 10) >= 10 ) {
                    _turns += 3;
                    return true;
                } else {
                    return false;
                }
            } else if ( item == "unidentified piece of flesh" ) {
                _inventory.erase( _inventory.begin() + i );
                if ( _gumption + randInt( 1, 10 ) >= 10 ) {
                    _health += randInt( -5, 5 );
                    return true;
                } else {
                    return false;
                }
            } else if ( item == "carrot" ) {
                _inventory.erase( _inventory.begin() + i );
                if ( _gumption + randInt( 0, 10 ) >= 10 ) {
                    _health += 2;
                    return true;
                } else {
                    return false;
                }
            } else if ( item == "knife" ) {
                _inventory.erase( _inventory.begin() + i );
                if ( _gumption + randInt( -3, 10 ) >= 10 ) {
                    _toDeal = 5;
                    return true;
                } else {
                    return false;
                }
            } else if ( item == "ak47" ) {
                _inventory.erase( _inventory.begin() + i );
                if ( _gumption + randInt( -6, 10 ) >= 10 ) {
                    _toDeal = randInt( 5, 10 );
                    return true;
                } else {
                    return false;
                }
            } else if ( item == "bazooka" ) {
                _inventory.erase( _inventory.begin() + i );
                if ( _gumption + randInt( -10, 10 ) >= 10 ) {
                    _toDeal = randInt( 8, 14 );
                    return true;
                } else {
                    return false;
                }
            } else if ( item == "turnip" ) {
                _inventory.erase( _inventory.begin() + i );
                if ( _gumption + randInt( -1, 10 ) >= 10 ) {
                    _health += randInt( 1, 3 );
                    return true;
                } else {
                    return false;
                }
            } else if ( item == "yellow flower" || item == "green flower" || item == "purple flower" || 
                item == "red flower" || item == "orange flower" ) {
                _inventory.erase( _inventory.begin() + i );

                if ( _gumption + randInt( 4, 10 ) >= 10 ) {
                    if ( _yellowFlowers > 0 && _greenFlowers > 0 && 
                        _purpleFlowers > 0 && _orangeFlowers > 0 && _redFlowers > 0 ) {

                        _lives++;

                        _yellowFlowers--;
                        _greenFlowers--;
                        _orangeFlowers--;
                        _redFlowers--;
                        _purpleFlowers--;

                        return true;
                    } else {
                        return false;
                    }
                }
            }

        }
    }
    /*
    ** Invalid item
    */
    return false;
}


std::string Quimbert::getStatsString() {
    return _name + " stats: \nLooks: " + std::to_string( _looks ) + "/10\nSmell: " +
        std::to_string( _smell ) + "/10\nColor: " + _color + "\nPersonality: " +
        std::to_string( _personality ) + "/10\nGumption: " + std::to_string( _gumption ) +
        "/10\nLength: " + std::to_string( _length ) + "/10\nOwner: " + _owner + "\n";
}

std::string Quimbert::getStat( std::string stat ) {
    if ( stat == "looks") return std::to_string( _looks );
    else if ( stat == "smell") return std::to_string( _smell );
    else if ( stat == "personality") return std::to_string( _personality );
    else if ( stat == "gumption") return std::to_string( _gumption );
    else if ( stat == "length") return std::to_string( _length );
    else if ( stat == "color") return _color;
    else if ( stat == "name") return _name;
    else if ( stat == "owner") return _owner;

    return "Invalid Stat";
}