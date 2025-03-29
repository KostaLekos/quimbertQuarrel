
#include "../include/quimbert.hpp"
#include "../include/textbox.hpp"

#include "../third/raylib/src/raylib.h"

#include <raylib.h>
#include <stdexcept>
#include <string>
#include <iostream>
#include <random>

#define Q_RAYWHITE Color{245, 245, 245, 255}
#define Q_OFFWHITE Color{230, 230, 230, 255}
#define Q_WHITE Color{255, 255, 255, 255}
#define Q_RED Color{230, 41, 55, 255}
#define Q_MAROON Color{190, 33, 55, 255}
#define Q_ORANGE Color{255, 161, 0, 255}
#define Q_DARKORANGE Color{215, 135, 0, 255}
#define Q_YELLOW Color{253, 249, 0, 255}
#define Q_GOLD Color{255, 203, 0, 255}
#define Q_LIME Color{0, 158, 47, 255}
#define Q_GREEN Color{0, 228, 48, 255}
#define Q_LIGHTBLUE Color{102, 191, 255, 255}
#define Q_DARKLIGHTBLUE Color{0, 148, 255, 255}
#define Q_BLUE Color{0, 121, 241, 255}
#define Q_DARKBLUE Color{0, 82, 172, 255}
#define Q_VIOLET Color{135, 60, 190, 255}
#define Q_PURPLE Color{200, 122, 255, 255}
#define Q_DARKPURPLE Color{112, 31, 126, 255}
#define Q_DARKGRAY Color{80, 80, 80, 255}
#define Q_LIGHTBLACK Color{39, 39, 39, 255}
#define Q_BLACK Color{0, 0, 0, 255}
#define Q_LIGHTGRAY Color{200, 200, 200, 255}
#define Q_GRAY Color{130, 130, 130, 255}
#define Q_PINK Color{255, 109, 194, 255}
#define Q_MAGENTA Color{255, 82, 183, 255}

std::mt19937_64::result_type randInt( int min, int max ) {
    std::random_device randomDev;
    std::mt19937_64 rng( randomDev() );
    std::uniform_int_distribution< std::mt19937::result_type > dist( min, max );

    return dist( rng );
}//kokk

// Colors: Red, Orange, Yellow, Green, Blue, DarkBlue, Purple, Q_BLACK, Q_GRAY, Pink
Color stoc( std::string color ) {
    if ( color == "red") {
        return Q_RED;
    } else if ( color == "orange" ) {
        return Q_ORANGE;
    } else if ( color == "yellow" ) {
        return Q_YELLOW;
    } else if ( color == "green" ) {
        return Q_GREEN;
    } else if ( color == "lightblue" ) {
        return Q_LIGHTBLUE;
    } else if ( color == "blue" ) {
        return Q_BLUE;
    } else if ( color == "purple" ) {
        return Q_PURPLE;
    } else if ( color == "black" ) {
        return Q_DARKGRAY;
    } else if ( color == "gray" ) {
        return Q_LIGHTGRAY;
    } else if ( color == "pink" ) {
        return Q_PINK;
    } else {
        throw std::runtime_error( color + " is not a recognized color");
    }
}

Color stocDark( std::string color ) {
    if ( color == "red") {
        return Q_MAROON;
    } else if ( color == "orange" ) {
        return Q_DARKORANGE;
    } else if ( color == "yellow" ) {
        return Q_GOLD;
    } else if ( color == "green" ) {
        return Q_LIME;
    } else if ( color == "lightblue" ) {
        return Q_DARKLIGHTBLUE;
    } else if ( color == "blue" ) {
        return Q_DARKBLUE;
    } else if ( color == "purple" ) {
        return Q_VIOLET;
    } else if ( color == "black" ) {
        return Q_LIGHTBLACK;
    } else if ( color == "gray" ) {
        return Q_GRAY;
    } else if ( color == "pink" ) {
        return Q_MAGENTA;
    } else {
        throw std::runtime_error( color + " is not a recognized color");
    }
}

/*
** Rewrote makeButtonText, give position of top-left corner, text, fontsize, and whether or not to ignore input
** Made better than the previous one!
*/
bool makeButtonText( int pos_x, int pos_y, std::string text, int fontSize, bool isDisabled = false ) {

    Rectangle main = { ( float ) pos_x, ( float ) pos_y,
        ( float ) MeasureText( text.c_str(), fontSize ) + 40, 
        ( float ) MeasureTextEx( GetFontDefault(), text.c_str(), fontSize, ( float ) fontSize / 10 ).y + 40 };
    Rectangle coll = main;
    coll.width += 5; coll.height += 5;

        bool buttonDown = isDisabled || CheckCollisionPointRec( GetMousePosition(), coll ) && IsMouseButtonDown( MOUSE_LEFT_BUTTON );
    if ( buttonDown ) {
        main.x += 5; main.y += 5;
    }

    Rectangle inside = { main.x + 10, main.y + 10, main.width - 20, main.height - 20 };



    DrawRectangleRec( main, Q_BLACK ); // Draw Q_BLACK boarder
    DrawRectangleRec( inside, CheckCollisionPointRec( GetMousePosition(), coll ) ? DARKGRAY : Q_GRAY ); // inside color

    // Drop shaddow
    if ( !buttonDown ) {
        DrawRectangleRec( { main.x + main.width, main.y + 5, 5, main.height }, DARKGRAY );
        DrawRectangleRec( { main.x + 5, main.y + main.height, main.width, 5 }, Q_DARKGRAY );
    }
    DrawText( text.c_str(), main.x + 10 + 10, main.y + 10 + 10, fontSize, Q_BLACK );

    return IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec( GetMousePosition(), coll );

}


/*
** Makes a button, but with the center at the coordinates listed
*/
bool makeButtonTextCenter( int pos_x, int pos_y, std::string text, int fontSize, bool isDisabled = false ) {
    return makeButtonText( pos_x - 10 - 10 - MeasureText( text.c_str(), fontSize ) / 2,
                               pos_y - 10 - 10 - MeasureTextEx( GetFontDefault(), text.c_str(), fontSize, ( float ) fontSize / 10 ).y,
                               text, fontSize, isDisabled );
}

/*
** DEPRECATED, DO NOT USE
**
** Makes a button with text
** Source code is not well documented because i forget how it works
*/
bool makeButtonText_DEPRECATED( int pos_x, int pos_y, int size_x, int size_y,
    std::string text, int fontSize, bool isDisabled = false ) {
    
    Rectangle main{ ( float ) pos_x, ( float ) pos_y, ( float ) size_x, ( float ) size_y };

    if ( !isDisabled ) {
        /*
        ** Mouse isn't in button
        */
        if ( !CheckCollisionPointRec( GetMousePosition(), main ) ) {
            /*
            ** Background / buttom bounding box / outline
            */
            DrawRectangleRec( main, Q_BLACK );
            // Inside color
            DrawRectangle( pos_x + 10, pos_y + 10,
                size_x - 20, size_y - 20, Q_LIGHTGRAY);

            // Drop shadow
            DrawRectangle( pos_x + size_x, pos_y + 5, 5,
                size_y, Q_DARKGRAY);
            DrawRectangle( pos_x + 5, pos_y + size_y,
                size_x, 5, Q_DARKGRAY );
            
            DrawText( text.c_str(), pos_x + 20, pos_y, fontSize, Q_BLACK);

            return false;
        /*
        ** Mouse is in button
        */
        } else {
            if ( IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) ) {
                DrawRectangle( pos_x + 5, pos_y + 5, size_x, size_y, Q_BLACK );
                DrawRectangle( pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, Q_GRAY );
                DrawText( text.c_str(), pos_x + 25, pos_y + 25 - 20, fontSize, Q_BLACK );
                return true;

            }

            if ( !IsMouseButtonDown( MOUSE_BUTTON_LEFT ) ) {
                // same except dark interior
                DrawRectangleRec( main, Q_BLACK );
                DrawRectangle( pos_x + 10, pos_y + 10, size_x - 20, size_y - 20, Q_GRAY );
                DrawRectangle( pos_x + size_x, pos_y + 5, 5, size_y, Q_DARKGRAY );
                DrawRectangle( pos_x + 5, pos_y + size_y, size_x, 5, Q_DARKGRAY );
                DrawText( text.c_str(), pos_x + 20, pos_y + 20 - 20, fontSize, Q_BLACK );
                return false;
            } else {
                DrawRectangle( pos_x + 5, pos_y + 5, size_x, size_y, Q_BLACK );
                DrawRectangle( pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, Q_GRAY );
                DrawText( text.c_str(), pos_x + 25, pos_y + 25 - 20, fontSize, Q_BLACK );
                return false;
            }
        }
    } else {
        DrawRectangle( pos_x + 5, pos_y + 5, size_x, size_y, Q_BLACK );
        DrawRectangle( pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, Q_GRAY );
        DrawText( text.c_str(), pos_x + 25, pos_y + 25 - 20, fontSize, Q_BLACK );
        return false;
    }
}

bool makeButtonColor( int pos_x, int pos_y, int size_x, int size_y, Color color1, Color color2, bool isDisabled = false ) {
    Rectangle main = { ( float ) pos_x, ( float ) pos_y, ( float ) size_x, ( float ) size_y };
    Rectangle coll = main;
    coll.width += 5; coll.height += 5;

    bool buttonDown = isDisabled || CheckCollisionPointRec( GetMousePosition(), coll ) && IsMouseButtonDown( MOUSE_LEFT_BUTTON );
    if ( buttonDown ) {
        main.x += 5; main.y += 5;
    }

    Rectangle inside = { main.x + 10, main.y + 10, main.width - 20, main.height - 20 };



    DrawRectangleRec( main, Q_BLACK ); // Draw Q_BLACK boarder
    DrawRectangleRec( inside, CheckCollisionPointRec( GetMousePosition(), coll ) ? color2 : color1 ); // inside color

    // Drop shaddow
    if ( !buttonDown ) {
        DrawRectangleRec( { main.x + main.width, main.y + 5, 5, main.height }, Q_DARKGRAY );
        DrawRectangleRec( { main.x + 5, main.y + main.height, main.width, 5 }, Q_DARKGRAY );
    }


    return IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec( GetMousePosition(), coll );

}

bool makeButtonColorCenter( int pos_x, int pos_y, int size_x, int size_y, Color color1, Color color2, bool isDisabled = false ) {
    return makeButtonColor( pos_x - size_x / 2, pos_y - size_y / 2, size_x, size_y, color1, color2, isDisabled );
}
/*
** Copy-pasted from Java verson
*/
bool makeButtonColor_DEPRECATED( int pos_x, int pos_y, int size_x, int size_y, Color color1, Color color2, bool isDisabled = false ) {
    bool result = false;
    // background rectangle / collision rectangle
    Rectangle main{ ( float ) pos_x, ( float ) pos_y, ( float ) size_x, ( float ) size_y };
    if ( !isDisabled ) {
        if ( !CheckCollisionPointRec( GetMousePosition(), main ) ) {
            // background / button bounding box / outline
            DrawRectangleRec( main, Q_BLACK );
            // inner body color
            DrawRectangle( pos_x + 10, pos_y + 10, size_x - 20, size_y - 20, color1 );
            // drop shadow
            DrawRectangle( pos_x + size_x, pos_y + 5, 5, size_y, Q_DARKGRAY );
            DrawRectangle( pos_x + 5, pos_y + size_y, size_x, 5, Q_DARKGRAY );
        } else {
            if ( IsMouseButtonReleased( 0 ) ) {
                result = true;
            }

            if ( !IsMouseButtonDown( 0 ) && !result ) {
                // same except dark interior
                DrawRectangleRec( main, Q_BLACK );
                DrawRectangle( pos_x + 10, pos_y + 10, size_x - 20, size_y - 20, color2 );
                DrawRectangle( pos_x + size_x, pos_y + 5, 5, size_y, Q_DARKGRAY );
                DrawRectangle( pos_x + 5, pos_y + size_y, size_x, 5, Q_DARKGRAY );
            } else {

                DrawRectangle( pos_x + 5, pos_y + 5, size_x, size_y, Q_BLACK );
                DrawRectangle( pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, color2 );
            }
        }
    } else {
        DrawRectangle( pos_x + 5, pos_y + 5, size_x, size_y, Q_BLACK );
        DrawRectangle( pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, color2 );
    }
    return result;
}

/*
** NOTE: Call with the "image" part as &someImg, and unload it after ( if desired )
*/
bool makeButtonImage( int pos_x, int pos_y, Texture2D tex, Color background = Q_GRAY, bool isDisabled = false ) {

    Rectangle main = { ( float ) pos_x, ( float ) pos_y, ( float ) tex.width + 20, ( float ) tex.height + 20 };
    Rectangle coll = main;
    coll.width += 5; coll.height += 5;
    
    bool buttonDown = isDisabled || CheckCollisionPointRec( GetMousePosition(), coll ) && IsMouseButtonDown( MOUSE_LEFT_BUTTON );
    if ( buttonDown ) {
        main.x += 5; main.y += 5;
    }
    
    Rectangle inside = { main.x + 10, main.y + 10, main.width - 20, main.height - 20 };
    
    DrawRectangleRec( main, Q_BLACK ); // Draw Q_BLACK boarder
    DrawRectangleRec( inside, background ); // Draw Q_GRAY inside
    
    DrawTexture( tex, inside.x, inside.y, Q_WHITE );


    // Drop shaddow
    if ( !buttonDown ) {
        DrawRectangleRec( { main.x + main.width, main.y + 5, 5, main.height }, Q_DARKGRAY );
        DrawRectangleRec( { main.x + 5, main.y + main.height, main.width, 5 }, Q_DARKGRAY );
    }


    return IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec( GetMousePosition(), coll );

}

bool makeButtonImageCenter( int pos_x, int pos_y, Texture2D tex, Color background = Q_GRAY, bool isDisabled = false ) {
    return makeButtonImage( pos_x - ( tex.width + 40 ) / 2, pos_y - ( tex.height + 40 ) / 2, tex, background, isDisabled );
}

/*
** Copy-pasted again
** NOTE: Call with the "image" part as &someImg, and unload it after ( if desired )
*/
bool makeButtonImage_DEPRACATED(int pos_x, int pos_y, int size_x, int size_y, Image* image, bool isDisabled = false ) {
    // load image
    ImageCrop( image , { ( float ) pos_x + 10, ( float ) pos_y + 10, ( float ) size_x - 20, ( float ) size_y - 20 } );
    Texture tex = LoadTextureFromImage( *image );
    bool result = false;

    // background rectangle / collision rectangle
    Rectangle main{ ( float ) pos_x, ( float ) pos_y, ( float ) size_x, ( float ) size_y };
    if (!isDisabled) {
        if (!CheckCollisionPointRec(GetMousePosition(), main)) {
            // background / button bounding box / outline
            DrawRectangleRec(main, Q_BLACK);
            // inner body color
            DrawRectangle(pos_x + 10, pos_y + 10, size_x - 20, size_y - 20, Q_LIGHTGRAY);
            // drop shadow
            DrawRectangle(pos_x + size_x, pos_y + 5, 5, size_y, Q_DARKGRAY);
            DrawRectangle(pos_x + 5, pos_y + size_y, size_x, 5, Q_DARKGRAY);

            DrawTexture(tex, pos_x + 10, pos_y + 10, Q_WHITE);
        } else {
            if (IsMouseButtonReleased(0)) {
                result = true;
            }

            if (!IsMouseButtonDown(0) && !result) {
                // same except dark interior
                DrawRectangleRec(main, Q_BLACK);
                DrawRectangle(pos_x + 10, pos_y + 10, size_x - 20, size_y - 20, Q_GRAY);
                DrawRectangle(pos_x + size_x, pos_y + 5, 5, size_y, Q_DARKGRAY);
                DrawRectangle(pos_x + 5, pos_y + size_y, size_x, 5, Q_DARKGRAY);

                DrawTexture(tex, pos_x + 10, pos_y + 10, Q_WHITE);

            } else {

                DrawRectangle(pos_x + 5, pos_y + 5, size_x, size_y, Q_BLACK);
                DrawRectangle(pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, Q_GRAY);
                DrawTexture(tex, pos_x + 15, pos_y + 15, Q_WHITE);

            }
        }
    } else {
        DrawRectangle(pos_x + 5, pos_y + 5, size_x, size_y, Q_BLACK);
        DrawRectangle(pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, Q_GRAY);
    }
    UnloadTexture( tex );
    return result;
}



int drawPlus( int pos_x, int pos_y, bool canNotBePressed, int startNum, int maxOrMinVal, bool isMinus = false ) {
    Rectangle main = { ( float ) pos_x, ( float ) pos_y, 100, 100 }; /* Main body (Q_BLACK outline) */
    Rectangle coll = main; /* Collision hitbox */
    coll.width += 5; coll.height += 5; /* Update collision hitbox to include Q_GRAY area, to prevent jankyness */
    
    canNotBePressed |= isMinus ? ( startNum <= maxOrMinVal ) : ( startNum >= maxOrMinVal ); /* update canBePressed if it is outside the bounds */

    /* check if the button should be down, down if cant be pressed or mouse is down inside box */
    /* button release added to prevent jankyness with the button flickering */
    bool isDown = canNotBePressed || ( CheckCollisionPointRec( GetMousePosition(), coll ) && ( IsMouseButtonDown( MOUSE_LEFT_BUTTON ) || IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) ) );

    if ( isDown ) {
        main.x += 5; main.y += 5;
    }

    /* Q_GRAY / darkgray area inside the box */
    Rectangle inside = { main.x + 10, main.y + 10, main.width - 20, main.height - 20 };

    /* vert and hori bars of the plus or minus*/
    Rectangle hBar = { main.x + 20, main.y + 45 , 60, 10 };
    Rectangle vBar = { main.x + 45, main.y + 20, 10, 60 };

    DrawRectangleRec( main, Q_BLACK ); // draw Q_BLACK outling
    DrawRectangleRec( inside, CheckCollisionPointRec( GetMousePosition(), coll ) ? Q_DARKGRAY : Q_GRAY ); // draw Q_GRAY inside
    DrawRectangleRec( hBar, Q_BLACK ); // draw the minus sign
    if ( !isMinus ) {
        DrawRectangleRec( vBar, Q_BLACK ); // turn into a plus if not a minus
    }
    if ( !isDown ) {
        DrawRectangleRec( { main.x + main.width, main.y + 5, 5, main.height }, Q_DARKGRAY ); // drop shadow if not down
        DrawRectangleRec( { main.x + 5, main.y + main.height, main.width, 5 }, Q_DARKGRAY );
    }

    if ( !canNotBePressed && CheckCollisionPointRec( GetMousePosition(), coll ) && IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) ) { // can i haz increment??????
        return startNum + ( isMinus ? -1 : 1 ); // yes
    }
    return startNum;
}

int drawPlusCenter( int pos_x, int pos_y, bool canNotBePressed, int startNum, int maxOrMinVal, bool isMinus = false ) {
    return drawPlus( pos_x - 50, pos_y - 50, canNotBePressed, startNum, maxOrMinVal, isMinus );
}

/*
** You guessed it! Copy-pasted
*/
int drawPlus_DEPRECATED(int posx, int posy, bool isGrayedOut, int numToIncrement, int maxMinVal, bool isMinus) {
    Rectangle rec = { (float) posx, (float) posy, 100, 100 };
    if (!isGrayedOut) {
        if(!CheckCollisionPointRec(GetMousePosition(), rec)) {
            DrawRectangleRec(rec, Q_BLACK);
            DrawRectangle(80 + posx, 50 + posy, 80, 80, Q_LIGHTGRAY);
            if (!isMinus) {
                DrawRectangle(115 + posx, 65 + posy, 10, 50, Q_BLACK);
            }
            DrawRectangle(95 + posx, 85 + posy, 50, 10, Q_BLACK);
            DrawRectangle(75 + posx, 140 + posy, 95, 5, Q_DARKGRAY);
            DrawRectangle(170 + posx, 45 + posy, 5, 100, Q_DARKGRAY); 
        } else {
            if (IsMouseButtonReleased(0)) {
                if (!isMinus) {
                    numToIncrement++;
                } else {
                    numToIncrement--;
                }

                if ((!isMinus) ? (numToIncrement <= maxMinVal) : (numToIncrement >= maxMinVal)) {
                    DrawRectangle(75 + posx, 45 + posy, 100, 100, Q_BLACK);
                    DrawRectangle(85 + posx, 55 + posy, 80, 80, Q_DARKGRAY);
                    if (!isMinus) {
                        DrawRectangle(120 + posx, 70 + posy, 10, 50, Q_BLACK);
                    }
                    DrawRectangle(100 + posx, 90 + posy, 50, 10, Q_BLACK);
                }
            }

            if (IsMouseButtonDown(0)) {
                DrawRectangle(75 + posx, 45 + posy, 100, 100, Q_BLACK);
                DrawRectangle(85 + posx, 55 + posy, 80, 80, Q_GRAY);
                if (!isMinus) {
                    DrawRectangle(120 + posx, 70 + posy, 10, 50, Q_BLACK);
                }
                DrawRectangle(100 + posx, 90 + posy, 50, 10, Q_BLACK);
            } else if ((!isMinus) ? (numToIncrement < maxMinVal) : (numToIncrement > maxMinVal)) {
                DrawRectangle(70 + posx, 40 + posy, 100, 100, Q_BLACK);
                DrawRectangle(80 + posx, 50 + posy, 80, 80, Q_GRAY);
                if (!isMinus) {
                    DrawRectangle(115 + posx, 65 + posy, 10, 50, Q_BLACK); //correct
                }
                DrawRectangle(95 + posx, 85 + posy, 50, 10, Q_BLACK);
                DrawRectangle(75 + posx, 140 + posy, 95, 5, Q_DARKGRAY);
                DrawRectangle(170 + posx, 45 + posy, 5, 100, Q_DARKGRAY);
            }
        }
    } else {
        DrawRectangle(75 + posx, 45 + posy, 100, 100, Q_BLACK);
        DrawRectangle(85 + posx, 55 + posy, 80, 80, Q_DARKGRAY);
        if (!isMinus) {
            DrawRectangle(120 + posx, 70 + posy, 10, 50, Q_BLACK);
        }
        DrawRectangle(100 + posx, 90 + posy, 50, 10, Q_BLACK);
    }
    return numToIncrement;
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

    /*
    ** IDK
    */
    std::string choice;
    int quimbertQuantity = 2;

    /*
    ** Temp quimbert stats
    */
    int looks;
    int smell;
    std::string color = "red";
    int personality;
    int gumption;
    int length;
    std::string name;
    std::string owner;
    
    int startingPoints = randInt( 25, 35 );
    std::vector< Quimbert > quimbertArr;
    bool gameDone;
    bool isMusicMuted = false;
    std::string gameLayout = "start";
    
    bool madeQuimbert = false;
    int currentQuimbert = 0;
    
    int monitorWidth = GetMonitorWidth( 0 ), monitorHeight = GetMonitorHeight( 0 );
    
    bool showColorSelectionPanel = false;
    Color currentColor = stoc( color );
    
    


    // Image info1 = LoadImage( "./resources/textures/UI/infoButton1.png" );
    // Image info2 = LoadImage( "./resources/textures/UI/infoButton2.png" );
    // Image info3 = LoadImage( "./resources/textures/UI/infoButton3.png" );
    // Texture2D infoButton1 = LoadTexture( "./resources/textures/UI/infoButton1.png" );
    // Texture2D infoButton2 = LoadTexture( "./resources/textures/UI/infoButton2.png" );
    // Texture2D infoButton3 = LoadTexture( "./resources/textures/UI/infoButton3.png" );
    // UnloadImage( info1 );
    // UnloadImage( info2 );
    // UnloadImage( info3 );

    SetConfigFlags( FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED );

    InitWindow(1840, 1000, "Quimbert Quarrel");
    //InitWindow(1366, 768, "Quimbert Quarrel");
    SetWindowMinSize(600, 500); 
    SetWindowMaxSize(monitorWidth, monitorHeight);
    SetWindowPosition(40, 70);
    MaximizeWindow();
    SetTargetFPS(60);
    InitAudioDevice();

    Music blippy = LoadMusicStream("./resources/soundtrack/BlippyBounce.mp3");
    Music ambient = LoadMusicStream("./resources/soundtrack/ambient.mp3");
    Music mania = LoadMusicStream("./resources/soundtrack/MenuMania.mp3");
    Music quimbertcall = LoadMusicStream("./resources/soundtrack/Quimbert's Call (Main Menu Theme).mp3");

    PlayMusicStream(blippy);
    SetMusicVolume(blippy, 0.25f);
    SetMusicVolume(ambient, 0.25f);
    SetMusicVolume(mania, 0.25f);
    SetMusicVolume(quimbertcall, 0.25f);

    QuimbertTextBox textBoxName( Rectangle{
        ( float ) GetScreenWidth() / 2 + 20, 250, 375, 75 } );
    textBoxName.setCharLength( 25 );

    QuimbertTextBox textBoxOwner( Rectangle{
        ( float ) GetScreenWidth() / 2 + 20, 350, 375, 75 } );
    textBoxOwner.setCharLength( 25 );

    Image exitImage = LoadImage( "./resources/textures/UI/exit.png" );
    Texture2D exitTex = LoadTextureFromImage( exitImage );
    UnloadImage( exitImage );

    Image mutedImage = LoadImage( "./resources/textures/UI/muted.png");
    ImageResize( &mutedImage, 70, 70 );
    Texture2D mutedTex = LoadTextureFromImage( mutedImage );
    UnloadImage( mutedImage );

    Image unmutedImage = LoadImage( "./resources/textures/UI/unmuted.png");
    ImageResize( &unmutedImage, 70, 70 );
    Texture2D unmutedTex = LoadTextureFromImage( unmutedImage );
    UnloadImage( unmutedImage );



    while ( !WindowShouldClose() ) {

        if ( !isMusicMuted ) {
            UpdateMusicStream( blippy );
        }

        if ( gameLayout == "start" ) {
            BeginDrawing();
            ClearBackground( Q_RAYWHITE );

            DrawText("Quimbert Quarrel", (GetScreenWidth() / 2) - (MeasureText("Quimbert Quarrel", 96) / 2), (GetScreenHeight() / 4), 96, Q_BLACK);
            DrawText("A Green Apple Game", (GetScreenWidth() / 2) - (MeasureText("A Green Apple Game", 36) / 2), (GetScreenHeight() / 4 + 100), 36, Q_BLACK);

            Rectangle localButton{ ( float ) GetScreenWidth() / 2 - 155, ( float ) GetScreenHeight() / 2, 300, 150 };


            if ( makeButtonTextCenter( GetScreenWidth() / 2, GetScreenHeight() / 2, "Local", 80, false ) ) {
                gameLayout = "howManyQuimberts";
            }

            if ( makeButtonImage( GetScreenWidth() - 170, 10, ( isMusicMuted ? mutedTex : unmutedTex ), Q_GRAY, false ) ) {
                isMusicMuted = !isMusicMuted;
            }

            if ( makeButtonImage( 40, 40, exitTex ) ) {
                /* Break out of the main game loop and stop execution */
                break; 
            }

            DrawFPS( 20, 20 );
            EndDrawing();
        } else if ( gameLayout == "howManyQuimberts" ) {
            BeginDrawing();
            ClearBackground( Q_RAYWHITE );
            
            Rectangle backButton = {20, 20, 120, 80};
            
            // Back button
            if (!CheckCollisionPointRec(GetMousePosition(), backButton)) {
                DrawRectangleRec(backButton, Q_BLACK);
                DrawRectangle(30, 30, 100, 60, Q_LIGHTGRAY);
                DrawLineEx( { 115, 60 }, { 60, 60 }, 15, Q_BLACK);
                DrawTriangle({ 45, 60 }, { 70, 80 }, { 70, 40 }, Q_BLACK);
                DrawRectangle(140, 25, 5, 80, Q_DARKGRAY);
                DrawRectangle(25, 100, 115, 5, Q_DARKGRAY);
            } else {
                if (!IsMouseButtonDown( MOUSE_LEFT_BUTTON )) {
                    DrawRectangle(20, 20, 120, 80, Q_BLACK);
                    DrawRectangle(30, 30, 100, 60, Q_GRAY);
                    DrawLineEx( { 115, 60 }, { 60, 60 }, 15, Q_BLACK);
                    DrawTriangle( { 45, 60 }, { 70, 80 }, { 70, 40 }, Q_BLACK);
                    DrawRectangle(140, 25, 5, 80, Q_DARKGRAY);
                    DrawRectangle(25, 100, 115, 5, Q_DARKGRAY);
                } else {
                    DrawRectangle(25, 25, 120, 80, Q_BLACK);
                    DrawRectangle(35, 35, 100, 60, Q_GRAY);
                    DrawLineEx( { 120, 65 }, { 65, 65 }, 15, Q_BLACK);
                    DrawTriangle( { 50, 65 }, { 75, 85 }, { 75, 45 }, Q_BLACK);
                }

                if (IsMouseButtonReleased(0)) {
                    gameLayout = "start";
                }
            }
            
            
            DrawText( "How many Quimberts?", GetScreenWidth() / 2 - MeasureText("How many Quimberts?", 80) / 2, 140, 80, Q_BLACK);
            
            /* Draw the current numbers box */
            DrawRectangle((GetScreenWidth() / 2) - 60, GetScreenHeight() / 2 - 70, 120, 150, Q_BLACK);
            DrawRectangle((GetScreenWidth() / 2) - 50, GetScreenHeight() / 2 + 10 - 70, 100, 130, Q_LIGHTGRAY);
            /* Actually draw the number */
            DrawText(std::to_string(quimbertQuantity).c_str(), (GetScreenWidth() / 2) - MeasureText(std::to_string(quimbertQuantity).c_str(), 108) / 2, GetScreenHeight() / 2 + 25 - 70, 108, Q_BLACK);

            quimbertQuantity = drawPlusCenter( GetScreenWidth() / 2 + 130, GetScreenHeight() / 2 + 80 - 70, false, quimbertQuantity, 8, false);
            quimbertQuantity = drawPlusCenter( GetScreenWidth() / 2 - 130, GetScreenHeight() / 2 + 80 - 70, false, quimbertQuantity, 2, true);

            if ( makeButtonTextCenter( GetScreenWidth() / 2, GetScreenHeight() / 2 + 260 - 70, "Next", 60, false) ) {
                gameLayout = "createQuimbertDetails";
            }
            
            EndDrawing();
        } else if ( gameLayout == "createQuimbertDetails" ) {
            BeginDrawing();
            ClearBackground( Q_RAYWHITE );

            Rectangle backButton = {20, 20, 120, 80};

            // Back button
            if (!CheckCollisionPointRec(GetMousePosition(), backButton)) {
                DrawRectangleRec(backButton, Q_BLACK);
                DrawRectangle(30, 30, 100, 60, Q_LIGHTGRAY);
                DrawLineEx( { 115, 60 }, { 60, 60 }, 15, Q_BLACK);
                DrawTriangle({ 45, 60 }, { 70, 80 }, { 70, 40 }, Q_BLACK);
                DrawRectangle(140, 25, 5, 80, Q_DARKGRAY);
                DrawRectangle(25, 100, 115, 5, Q_DARKGRAY);
            } else {
                if (!IsMouseButtonDown( MOUSE_LEFT_BUTTON )) {
                    DrawRectangle(20, 20, 120, 80, Q_BLACK);
                    DrawRectangle(30, 30, 100, 60, Q_GRAY);
                    DrawLineEx( { 115, 60 }, { 60, 60 }, 15, Q_BLACK);
                    DrawTriangle( { 45, 60 }, { 70, 80 }, { 70, 40 }, Q_BLACK);
                    DrawRectangle(140, 25, 5, 80, Q_DARKGRAY);
                    DrawRectangle(25, 100, 115, 5, Q_DARKGRAY);
                } else {
                    DrawRectangle(25, 25, 120, 80, Q_BLACK);
                    DrawRectangle(35, 35, 100, 60, Q_GRAY);
                    DrawLineEx( { 120, 65 }, { 65, 65 }, 15, Q_BLACK);
                    DrawTriangle( { 50, 65 }, { 75, 85 }, { 75, 45 }, Q_BLACK);
                }

                if (IsMouseButtonReleased(0)) {
                    gameLayout = "howManyQuimberts";
                }
            }

            textBoxName.processTextInput();
            textBoxName.render();

            textBoxOwner.processTextInput();
            textBoxOwner.render();

            DrawText( ( ( std::string( "Quimbert #" ) + std::to_string( currentQuimbert + 1 ) ).c_str() ), (GetScreenWidth() / 2) - (MeasureText("Quimbert #1", 96) / 2), 20, 96, Q_BLACK);
            DrawText(("Make your Quimbert"), (GetScreenWidth() / 2) - (MeasureText("Make your Quimbert", 96) / 2), 120, 96, Q_BLACK);

            DrawText("Name:", ((GetScreenWidth() / 2) - MeasureText("Name:", 72)) - 30, 250, 72, Q_BLACK);
            DrawText("Owner:", ((GetScreenWidth() / 2) - MeasureText("Owner:", 72)) - 30, 350, 72, Q_BLACK);
            DrawText("Color:", ((GetScreenWidth() / 2) - MeasureText("Color:", 72)) - 30, 450, 72, Q_BLACK);

            textBoxName.setBox( { ( float ) GetScreenWidth() / 2 + 20, 250, 375, 75 } );
            textBoxOwner.setBox( { ( float ) GetScreenWidth() / 2 + 20, 350, 375, 75 } );

            if ( makeButtonColor( GetScreenWidth() / 2 + 20, 450, 60, 60, currentColor, stocDark(color), false ) ) {
                showColorSelectionPanel = true;
            }


            
            if ( showColorSelectionPanel ) {                
                /*
                ** The box that the color buttons are in
                */
                Rectangle colorSelectionPanelMain = { ( float ) GetScreenWidth() / 2 + 60 + 20 + 10, 450, 80 * 5 + 20 * 2, 80 * 2 + 20 * 2 };
                Rectangle colorSelectionPanelInside = colorSelectionPanelMain;
                colorSelectionPanelInside.x += 10; colorSelectionPanelInside.y += 10; 
                colorSelectionPanelInside.width -= 20; colorSelectionPanelInside.height -= 20;

                /*
                ** Draw the box that the selector buttons are in
                */
                DrawRectangleRec( colorSelectionPanelMain, Q_BLACK );
                DrawRectangleRec( colorSelectionPanelInside, Q_GRAY );

                /*
                ** Draw the selector buttons
                */
                // Colors: Red, Orange, Yellow, Green, Blue, DarkBlue, Purple, Black, Gray, Pink

                //COLOR DARKENING GUIDE
                /*
                Q_RED --> Q_MAROON
                Q_ORANGE --> Q_DARKORANGE
                Q_YELLOW --> Q_GOLD
                Q_GREEN --> Q_LIME
                Q_LIGHTBLUE --> Q_DARKLIGHTBLUE
                Q_BLUE --> Q_DARKBLUE
                Q_PURPLE --> Q_VIOLET
                Q_DARKGRAY --> Q_LIGHTBLACK
                Q_LIGHTGRAY --> Q_GRAY
                Q_PINK --> Q_MAGENTA
                */

                if ( makeButtonColor( colorSelectionPanelInside.x + 80 * 0 + 10, colorSelectionPanelInside.y + 80 * 0 + 10, 60, 60, Q_RED, Q_MAROON, false) ) {
                    color = "red";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( colorSelectionPanelInside.x + 80 * 1 + 10, colorSelectionPanelInside.y + 80 * 0 + 10, 60, 60, Q_ORANGE, Q_DARKORANGE, false) ) {
                    color = "orange";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( colorSelectionPanelInside.x + 80 * 2 + 10, colorSelectionPanelInside.y + 80 * 0 + 10, 60, 60, Q_YELLOW, Q_GOLD, false) ) {
                    color = "yellow";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( colorSelectionPanelInside.x + 80 * 3 + 10, colorSelectionPanelInside.y + 80 * 0 + 10, 60, 60, Q_GREEN, Q_LIME, false) ) {
                    color = "green";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( colorSelectionPanelInside.x + 80 * 4 + 10, colorSelectionPanelInside.y + 80 * 0 + 10, 60, 60, Q_LIGHTBLUE, Q_DARKLIGHTBLUE, false) ) {
                    color = "lightblue";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( colorSelectionPanelInside.x + 80 * 0 + 10, colorSelectionPanelInside.y + 80 * 1 + 10, 60, 60, Q_BLUE, Q_DARKBLUE, false) ) {
                    color = "blue";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( colorSelectionPanelInside.x + 80 * 1 + 10, colorSelectionPanelInside.y + 80 * 1 + 10, 60, 60, Q_PURPLE, Q_VIOLET, false) ) {
                    color = "purple";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( colorSelectionPanelInside.x + 80 * 2 + 10, colorSelectionPanelInside.y + 80 * 1 + 10, 60, 60, Q_DARKGRAY, Q_LIGHTBLACK, false) ) {
                    color = "black";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( colorSelectionPanelInside.x + 80 * 3 + 10, colorSelectionPanelInside.y + 80 * 1 + 10, 60, 60, Q_LIGHTGRAY, Q_GRAY, false) ) {
                    color = "gray";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( colorSelectionPanelInside.x + 80 * 4 + 10, colorSelectionPanelInside.y + 80 * 1 + 10, 60, 60, Q_PINK, Q_MAGENTA, false) ) {
                    color = "pink";
                    showColorSelectionPanel = false;
                }
                
                if ( IsMouseButtonDown( MOUSE_LEFT_BUTTON ) && !CheckCollisionPointRec( GetMousePosition(), colorSelectionPanelMain ) ) {
                    showColorSelectionPanel = false;
                }
            }
            
            //Next Button
            if ( makeButtonTextCenter( GetScreenWidth() / 2, GetScreenHeight() / 4 * 3, "Next", 60, false) ) {
                gameLayout = "chooseQuimbertStats";
            }

            currentColor = stoc( color );

            EndDrawing();
        } else if ( gameLayout == "chooseQuimbertStats") {
            BeginDrawing();
            ClearBackground( Q_RAYWHITE );


            Rectangle backButton = {20, 20, 120, 80};

            // Back button
            if (!CheckCollisionPointRec(GetMousePosition(), backButton)) {
                DrawRectangleRec(backButton, Q_BLACK);
                DrawRectangle(30, 30, 100, 60, Q_LIGHTGRAY);
                DrawLineEx( { 115, 60 }, { 60, 60 }, 15, Q_BLACK);
                DrawTriangle({ 45, 60 }, { 70, 80 }, { 70, 40 }, Q_BLACK);
                DrawRectangle(140, 25, 5, 80, Q_DARKGRAY);
                DrawRectangle(25, 100, 115, 5, Q_DARKGRAY);
            } else {
                if (!IsMouseButtonDown( MOUSE_LEFT_BUTTON )) {
                    DrawRectangle(20, 20, 120, 80, Q_BLACK);
                    DrawRectangle(30, 30, 100, 60, Q_GRAY);
                    DrawLineEx( { 115, 60 }, { 60, 60 }, 15, Q_BLACK);
                    DrawTriangle( { 45, 60 }, { 70, 80 }, { 70, 40 }, Q_BLACK);
                    DrawRectangle(140, 25, 5, 80, Q_DARKGRAY);
                    DrawRectangle(25, 100, 115, 5, Q_DARKGRAY);
                } else {
                    DrawRectangle(25, 25, 120, 80, Q_BLACK);
                    DrawRectangle(35, 35, 100, 60, Q_GRAY);
                    DrawLineEx( { 120, 65 }, { 65, 65 }, 15, Q_BLACK);
                    DrawTriangle( { 50, 65 }, { 75, 85 }, { 75, 45 }, Q_BLACK);
                }

                if (IsMouseButtonReleased(0)) {
                    gameLayout = "createQuimbertDetails";
                }
            }
            EndDrawing();
        }
    }
}