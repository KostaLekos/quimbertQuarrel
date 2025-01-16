
#include <raylib.h>


#include <string>
#include <random>
#include <vector>

static std::mt19937_64::result_type randInt( int min, int max ) {
    std::random_device randomDev;
    std::mt19937_64 rng( randomDev() );
    std::uniform_int_distribution< std::mt19937::result_type > dist( min, max );

    return dist( rng );
}

int main( int argc, char** argv, char** envv ) {
    std::string choice;
    int quimbertQuantity;
    int looks;
    int smell;
    std::string color;
    int personality;
    int gumption;
    int length;
    std::string name;
    std::string owner;




    while(!WindowShouldClose()) {

    }

}