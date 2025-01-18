
#include "../include/quimbert.hpp"

#include <raylib.h>


#include <string>
#include <random>

std::mt19937_64::result_type randInt( int min, int max ) {
    std::random_device randomDev;
    std::mt19937_64 rng( randomDev() );
    std::uniform_int_distribution< std::mt19937::result_type > dist( min, max );

    return dist( rng );
}


/*
** Makes a button with text
** Source code is not well documented because i forget how it works
*/
bool makeButtonText( int pos_x, int pos_y, int size_x, int size_y,
    std::string text, int fontSize, bool isDisabled ) {
    
    Rectangle main( pos_x, pos_y, size_x, size_y );

    if ( !isDisabled ) {
        /*
        ** Mouse isn't in button
        */
        if ( !CheckCollisionPointRec( GetMousePosition(), main ) ) {
            /*
            ** Background / buttom bounding box / outline
            */
            DrawRectangleRec( main, BLACK );
            // Inside color
            DrawRectangle( pos_x + 10, pos_y + 10,
                size_x - 10, size_y - 10, LIGHTGRAY);

            // Drop shadow
            DrawRectangle( pos_x + size_x, pos_y + 5, 5,
                size_y, DARKGRAY);
            DrawRectangle( pos_x + 5, pos_y + size_y,
                size_x, 5, DARKGRAY );
            
            DrawText( text.c_str(), pos_x + 20, pos_y, fontSize, BLACK);

            return false;
        /*
        ** Mouse is in button
        */
        } else {
            if ( IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) ) {
                DrawRectangle( pos_x + 5, pos_y + 5, size_x, size_y, BLACK );
                DrawRectangle( pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, GRAY );
                DrawText( text.c_str(), pos_x + 25, pos_y + 25 - 20, fontSize, BLACK );
                return true;

            }

            if ( !IsMouseButtonDown( MOUSE_BUTTON_LEFT ) ) {
                // same except dark interior
                DrawRectangleRec( main, BLACK );
                DrawRectangle( pos_x + 10, pos_y + 10, size_x - 20, size_y - 20, GRAY );
                DrawRectangle( pos_x + size_x, pos_y + 5, 5, size_y, DARKGRAY );
                DrawRectangle( pos_x + 5, pos_y + size_y, size_x, 5, DARKGRAY );
                DrawText( text.c_str(), pos_x + 20, pos_y + 20 - 20, fontSize, BLACK );
                return false;
            } else {
                DrawRectangle( pos_x + 5, pos_y + 5, size_x, size_y, BLACK );
                DrawRectangle( pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, GRAY );
                DrawText( text.c_str(), pos_x + 25, pos_y + 25 - 20, fontSize, BLACK );
                return false;
            }
        }
    } else {
        DrawRectangle( pos_x + 5, pos_y + 5, size_x, size_y, BLACK );
        DrawRectangle( pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, GRAY );
        DrawText( text.c_str(), pos_x + 25, pos_y + 25 - 20, fontSize, BLACK );
        return false;
    }
}


/*
** Copy-pasted from Java verson
*/
bool makeButtonColor( int pos_x, int pos_y, int size_x, int size_y, Color color1, Color color2, bool isDisabled ) {
    bool result = false;
    // background rectangle / collision rectangle
    Rectangle main = Rectangle( pos_x, pos_y, size_x, size_y );
    if ( !isDisabled ) {
        if ( !CheckCollisionPointRec( GetMousePosition(), main ) ) {
            // background / button bounding box / outline
            DrawRectangleRec( main, BLACK );
            // inner body color
            DrawRectangle( pos_x + 10, pos_y + 10, size_x - 20, size_y - 20, color1 );
            // drop shadow
            DrawRectangle( pos_x + size_x, pos_y + 5, 5, size_y, DARKGRAY );
            DrawRectangle( pos_x + 5, pos_y + size_y, size_x, 5, DARKGRAY );
        } else {
            if ( IsMouseButtonReleased( 0 ) ) {
                result = true;
            }

            if ( !IsMouseButtonDown( 0 ) && !result ) {
                // same except dark interior
                DrawRectangleRec( main, BLACK );
                DrawRectangle( pos_x + 10, pos_y + 10, size_x - 20, size_y - 20, color2 );
                DrawRectangle( pos_x + size_x, pos_y + 5, 5, size_y, DARKGRAY );
                DrawRectangle( pos_x + 5, pos_y + size_y, size_x, 5, DARKGRAY );
            } else {

                DrawRectangle( pos_x + 5, pos_y + 5, size_x, size_y, BLACK );
                DrawRectangle( pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, color2 );
            }
        }
    } else {
        DrawRectangle( pos_x + 5, pos_y + 5, size_x, size_y, BLACK );
        DrawRectangle( pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, color2 );
    }
    return result;
}


/*
** Copy-pasted again
*/
bool makeButtonImage(int pos_x, int pos_y, int size_x, int size_y, std::string path, bool isDisabled) {
    // load image
    Image img = LoadImage( path.c_str() );
    ImageCrop( &img , Rectangle(pos_x + 10, pos_y + 10, size_x - 20, size_y - 20) );
    Texture tex = LoadTextureFromImage(img);
    UnloadImage(img);
    bool result = false;

    // background rectangle / collision rectangle
    Rectangle main = Rectangle(pos_x, pos_y, size_x, size_y);
    if (!isDisabled) {
        if (!CheckCollisionPointRec(GetMousePosition(), main)) {
            // background / button bounding box / outline
            DrawRectangleRec(main, BLACK);
            // inner body color
            DrawRectangle(pos_x + 10, pos_y + 10, size_x - 20, size_y - 20, LIGHTGRAY);
            // drop shadow
            DrawRectangle(pos_x + size_x, pos_y + 5, 5, size_y, DARKGRAY);
            DrawRectangle(pos_x + 5, pos_y + size_y, size_x, 5, DARKGRAY);

            DrawTexture(tex, pos_x + 10, pos_y + 10, WHITE);
        } else {
            if (IsMouseButtonReleased(0)) {
                result = true;
            }

            if (!IsMouseButtonDown(0) && !result) {
                // same except dark interior
                DrawRectangleRec(main, BLACK);
                DrawRectangle(pos_x + 10, pos_y + 10, size_x - 20, size_y - 20, GRAY);
                DrawRectangle(pos_x + size_x, pos_y + 5, 5, size_y, DARKGRAY);
                DrawRectangle(pos_x + 5, pos_y + size_y, size_x, 5, DARKGRAY);

                DrawTexture(tex, pos_x + 10, pos_y + 10, WHITE);

            } else {

                DrawRectangle(pos_x + 5, pos_y + 5, size_x, size_y, BLACK);
                DrawRectangle(pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, GRAY);
                DrawTexture(tex, pos_x + 15, pos_y + 15, WHITE);

            }
        }
    } else {
        DrawRectangle(pos_x + 5, pos_y + 5, size_x, size_y, BLACK);
        DrawRectangle(pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, GRAY);
    }
    return result;
}


/*
** Checks if any printable characters are pressed
*/
bool isAnyKeyPressed() {
    int key = GetKeyPressed();
    if ( key >= 32 && key <= 126 ) {
        return true;
    }
    return false;
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





}