#include "../include/quimbert.hpp"


#include <random>

std::mt19937_64::result_type Quimbert::randInt( int min, int max ) {
    std::random_device randomDev;
    std::mt19937_64 rng( randomDev() );
    std::uniform_int_distribution< std::mt19937::result_type > dist( min, max );

    return dist( rng );
}


Quimbert::Quimbert( int looks, int smell, std::string color, 
    int personality, int gumption, int length, 
    std::string name, std::string owner ) {
        this->looks = looks;
        this->smell = smell;
        this->color = color;
        this->personality = personality;
        this->gumption = gumption;
        this->length = length;
        this->name = name;
        this->owner = owner;
    }