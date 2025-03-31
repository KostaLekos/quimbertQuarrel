#include "../include/quimbert.hpp"


#include <random>
#include <stdexcept>
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
    std::string name, std::string owner )
    : _looks( looks ),
      _smell( smell ),
      _color( color ),
      _personality( personality ),
      _gumption( gumption ),
      _length( length ),
      _name( name ),
      _owner( owner ),
      _health( ( looks > 0 ) ? randInt( 3, 5 ) * looks / 2 : 1 ),
      _startingHealth( ( looks > 0 ) ? randInt( 3, 5 ) * looks / 2 : 1 )
    {
    }

/*
** Sniffs, returns true on success, and false otherwise
*/
void Quimbert::sniff() {
    if ( _smell == 10 ) {
        if ( 0 < _smell + randInt( -10, 10 ) ) {
            _inventory.push_back( items[ randInt( 0, itemCount - 1 ) ] );
        }
    }
    if ( 0 < _smell + randInt( -10, 10 ) ) {
        _inventory.push_back( items[ randInt( 0, itemCount - 1 ) ] );
    }
}

void Quimbert::gainBlock() {
    if ( ( _personality + randInt( -7, 10 ) ) >= 10 ) {
        _blocks++;
        
        // Special for personality
        if ( _personality == 10 && randInt( 1, 4 ) == 4 ) {
            if ( ( _personality + randInt( -7, 10 ) ) >= 10 ) {
                _blocks++;
            }
        }
    }
}

// std::vector< std::string > Quimbert::getInventory() {
//     return _inventory;
// }

// int Quimbert::getHealth() {
//     return _health;
// }

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
    for ( size_t i = 0; i < _inventory.size(); i++ ) {
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

// std::string Quimbert::getStrStat( std::string stat ) {
//     if ( stat == "color") return _color;
//     else if ( stat == "name") return _name;
//     else if ( stat == "owner") return _owner;

//     throw std::runtime_error( "Invalid Stat" );
// }

// void Quimbert::setStrStat( std::string stat, std::string newValue ) {
//     if ( stat == "color") _color = newValue;
//     else if ( stat == "name") _name = newValue;
//     else if ( stat == "owner") _owner = newValue;

//     throw std::runtime_error( "Invalid Stat" );
// }

// int Quimbert::getIntStat( std::string stat ) {
//     if ( stat == "looks") return _looks;
//     else if ( stat == "smell") return _smell;
//     else if ( stat == "personality") return _personality;
//     else if ( stat == "gumption") return _gumption;
//     else if ( stat == "length") return _length;

//     throw std::runtime_error( "Invalid Stat" );
// }

// void Quimbert::setIntStat( std::string stat, int newValue ) {
//     if ( stat == "looks") _looks = newValue;
//     else if ( stat == "smell") _smell = newValue;
//     else if ( stat == "personality") _personality = newValue;
//     else if ( stat == "gumption") _gumption = newValue;
//     else if ( stat == "length") _length = newValue;

//     throw std::runtime_error( "Invalid Stat" );
// }



/*
** Get the stats
*/

int Quimbert::getLooks() {
    return _looks;
}

int Quimbert::getSmell() {
    return _smell;
}

std::string Quimbert::getColor() {
    return _color;
}

int Quimbert::getPersonality() {
    return _personality;
}

int Quimbert::getGumption() {
    return _gumption;
}

int Quimbert::getLength() {
    return _length;
}

std::string Quimbert::getName() {
    return _name;
}

std::string Quimbert::getOwner() {
    return _owner;
}


/*
** Set stats
*/

void Quimbert::setLooks( int newVal ) {
    _looks = newVal;
}

void Quimbert::setSmell( int newVal ) {
    _smell = newVal;
}

void Quimbert::setColor( std::string newVal ) {
    _color = newVal;
}

void Quimbert::setPersonality( int newVal ) {
    _personality = newVal;
}

void Quimbert::setGumption( int newVal ) {
    _gumption = newVal;
}

void Quimbert::setLength( int newVal ) {
    _length = newVal;
}

void Quimbert::setName( std::string newVal ) {
    _name = newVal;
}

void Quimbert::setOwner( std::string newVal ) {
    _owner = newVal;
}


/*
** Get other stats
*/

int Quimbert::getHealth() {
    return _health;
}

int Quimbert::getTurns() {
    return _turns;
}

int Quimbert::getToDeal() {
    return _toDeal;
}

int Quimbert::getBlocks() {
    return _blocks;
}

int Quimbert::getLives() {
    return _lives;
}

int Quimbert::getYellowFlowers() {
    return _yellowFlowers;
}

int Quimbert::getGreenFlowers() {
    return _greenFlowers;
}

int Quimbert::getPurpleFlowers() {
    return _purpleFlowers;
}

int Quimbert::getOrangeFlowers() {
    return _orangeFlowers;
}

int Quimbert::getRedFlowers() {
    return _redFlowers;
}

std::vector< std::string > Quimbert::getInventory() {
    return _inventory;
}


void Quimbert::setHealth( int newVal ) {
    _health = newVal;
}

void Quimbert::setTurns( int newVal ) {
    _turns = newVal;
}

void Quimbert::setToDeal( int newVal ) {
    _toDeal = newVal;
}

void Quimbert::setBlocks( int newVal ) {
    _blocks = newVal;
}

void Quimbert::setLives( int newVal ) {
    _lives = newVal;
}

void Quimbert::setYellowFlowers( int newVal ) {
    _yellowFlowers = newVal;
}

void Quimbert::setGreenFlowers( int newVal ) {
    _greenFlowers = newVal;
}

void Quimbert::setPurpleFlowers( int newVal ) {
    _purpleFlowers = newVal;
}

void Quimbert::setOrangeFlowers( int newVal ) {
    _orangeFlowers = newVal;
}

void Quimbert::setRedFlowers( int newVal ) {
    _redFlowers = newVal;
}

void Quimbert::setInventory( std::vector< std::string > newVal ) {
    _inventory = newVal;
}

std::vector< std::string > *Quimbert::getInventoryDangerous() {
    return &_inventory;
}
