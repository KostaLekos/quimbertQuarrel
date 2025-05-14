
#include "../include/quimbert.hpp"
#include "../include/textbox.hpp"

#include "../third/raylib/src/raylib.h"

#include <stdexcept>
#include <string>
#include <iostream>
#include <random>

#define Q_WHITE Color{255, 255, 255, 255}
#define Q_RAYWHITE Color{245, 245, 245, 255}
#define Q_OFFWHITE Color{230, 230, 230, 255}
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
}//kokk /* what? */

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
bool makeButtonTextEx( RenderTexture rentex, int pos_x, int pos_y, int size_x, int size_y, std::string text, int fontSize, bool isDisabled = false ) {

    float sf_x = static_cast< float >( rentex.texture.width ) / GetScreenWidth();
    float sf_y = static_cast< float >( rentex.texture.height ) / GetScreenHeight();

    Rectangle main = { static_cast< float >( pos_x ), static_cast< float >( pos_y ), static_cast< float >( size_x ), static_cast< float >( size_y ) };
    Rectangle coll = main;
    coll.width += 5; coll.height += 5;

    bool buttonDown = isDisabled || ( CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, coll ) && ( IsMouseButtonDown( MOUSE_LEFT_BUTTON ) || IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) ) );
    if ( buttonDown ) {
        main.x += 5; main.y += 5;
    }

    Rectangle inside = { main.x + 10, main.y + 10, main.width - 20, main.height - 20 };



    DrawRectangleRec( main, Q_BLACK ); // Draw Q_BLACK boarder
    DrawRectangleRec( inside, CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, coll ) ? Q_DARKGRAY : Q_GRAY ); // inside color

    // Drop shaddow
    if ( !buttonDown ) {
        DrawRectangleRec( { main.x + main.width, main.y + 5, 5, main.height }, Q_DARKGRAY );
        DrawRectangleRec( { main.x + 5, main.y + main.height, main.width, 5 }, Q_DARKGRAY );
    }
    DrawText( text.c_str(), static_cast< float >( main.x + main.width / 2 ) - static_cast< float >( MeasureText( text.c_str(), fontSize ) ) / 2, static_cast< float >( main.y + main.height / 2 ) - static_cast< float >( MeasureTextEx( GetFontDefault(), text.c_str(), fontSize, static_cast< float >( fontSize ) / 10 ).y ) / 2, fontSize, Q_BLACK );

    return IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, coll );

}

bool makeButtonText( RenderTexture rentex, int pos_x, int pos_y, std::string text, int fontSize, bool isDisabled = false ) {
    return makeButtonTextEx( rentex, pos_x, pos_y, MeasureText( text.c_str(), fontSize ) + 40, MeasureTextEx( GetFontDefault(), text.c_str(), fontSize, static_cast< float >( fontSize ) / 10 ).y + 40, text, fontSize, isDisabled);
}


/*
** Makes a button, but with the center at the coordinates listed
*/
bool makeButtonTextCenter( RenderTexture rentex, int pos_x, int pos_y, std::string text, int fontSize, bool isDisabled = false ) {
    return makeButtonText( rentex, pos_x - 10 - 10 - MeasureText( text.c_str(), fontSize ) / 2,
                               pos_y - 10 - 10 - MeasureTextEx( GetFontDefault(), text.c_str(), fontSize, static_cast< float >( fontSize ) / 10 ).y,
                               text, fontSize, isDisabled );
}


bool makeButtonColor( RenderTexture rentex, int pos_x, int pos_y, int size_x, int size_y, Color color1, Color color2, bool isDisabled = false ) {
    float sf_x = static_cast< float >( rentex.texture.width ) / GetScreenWidth();
    float sf_y = static_cast< float >( rentex.texture.height ) / GetScreenHeight();

    Rectangle main = { static_cast< float >( pos_x ), static_cast< float >( pos_y ), static_cast< float >( size_x ), static_cast< float >( size_y ) };
    Rectangle coll = main;
    coll.width += 5; coll.height += 5;

    bool buttonDown = isDisabled || ( CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, coll ) && ( IsMouseButtonDown( MOUSE_LEFT_BUTTON ) || IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) ) );
    if ( buttonDown ) {
        main.x += 5; main.y += 5;
    }

    Rectangle inside = { main.x + 10, main.y + 10, main.width - 20, main.height - 20 };



    DrawRectangleRec( main, Q_BLACK ); // Draw Q_BLACK boarder
    DrawRectangleRec( inside, CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, coll ) ? color2 : color1 ); // inside color

    // Drop shaddow
    if ( !buttonDown ) {
        DrawRectangleRec( { main.x + main.width, main.y + 5, 5, main.height }, Q_DARKGRAY );
        DrawRectangleRec( { main.x + 5, main.y + main.height, main.width, 5 }, Q_DARKGRAY );
    }


    return !isDisabled && IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, coll );

}

bool makeButtonColorCenter( RenderTexture rentex, int pos_x, int pos_y, int size_x, int size_y, Color color1, Color color2, bool isDisabled = false ) {
    return makeButtonColor( rentex, pos_x - size_x / 2, pos_y - size_y / 2, size_x, size_y, color1, color2, isDisabled );
}


/*
** NOTE: Call with the "image" part as &someImg, and unload it after ( if desired )
*/
bool makeButtonImage( RenderTexture rentex, int pos_x, int pos_y, Texture2D tex, Color background = Q_GRAY, bool isDisabled = false ) {
    float sf_x = static_cast< float >( rentex.texture.width ) / GetScreenWidth();
    float sf_y = static_cast< float >( rentex.texture.height ) / GetScreenHeight();


    Rectangle main = { static_cast< float >( pos_x ), static_cast< float >( pos_y ), static_cast< float >( tex.width + 20 ), static_cast< float >( tex.height + 20 ) };
    Rectangle coll = main;
    coll.width += 5; coll.height += 5;
    
    bool buttonDown = isDisabled || ( CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, coll ) && ( IsMouseButtonDown( MOUSE_LEFT_BUTTON ) || IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) ) );
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


    return IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, coll );

}

bool makeButtonImageCenter( RenderTexture rentex, int pos_x, int pos_y, Texture2D tex, Color background = Q_GRAY, bool isDisabled = false ) {
    return makeButtonImage( rentex, pos_x - ( tex.width + 40 ) / 2, pos_y - ( tex.height + 40 ) / 2, tex, background, isDisabled );
}


int drawPlus( RenderTexture rentex, int pos_x, int pos_y, int size_x, int size_y, bool canNotBePressed, int startNum, int maxOrMinVal, bool isMinus = false ) {
    float sf_x = static_cast< float >( rentex.texture.width ) / GetScreenWidth();
    float sf_y = static_cast< float >( rentex.texture.height ) / GetScreenHeight();


    Rectangle main = { static_cast< float >( pos_x ), static_cast< float >( pos_y ), static_cast< float >( size_x ), static_cast< float >( size_y ) }; /* Main body (Q_BLACK outline) */
    Rectangle coll = main; /* Collision hitbox */
    coll.width += 5; coll.height += 5; /* Update collision hitbox to include Q_GRAY area, to prevent jankyness */
    
    canNotBePressed |= isMinus ? ( startNum <= maxOrMinVal ) : ( startNum >= maxOrMinVal ); /* update canBePressed if it is outside the bounds */

    /* check if the button should be down, down if cant be pressed or mouse is down inside box */
    /* button release added to prevent jankyness with the button flickering */
    bool isDown = canNotBePressed || ( CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, coll ) && ( IsMouseButtonDown( MOUSE_LEFT_BUTTON ) || IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) ) );

    if ( isDown ) {
        main.x += 5; main.y += 5;
    }

    /* Q_GRAY / darkgray area inside the box */
    Rectangle inside = { main.x + 10, main.y + 10, main.width - 20, main.height - 20 };

    /* vert and hori bars of the plus or minus*/
    Rectangle hBar = { main.x + main.width / 5, main.y + main.height * 0.45f , main.width * 3 / 5, main.height / 10 };
    Rectangle vBar = { main.x + main.width * 0.45f, main.y + main.width / 5, main.height / 10, main.width * 3 / 5 };

    DrawRectangleRec( main, Q_BLACK ); // draw Q_BLACK outling
    DrawRectangleRec( inside, CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, coll ) ? Q_DARKGRAY : Q_GRAY ); // draw Q_GRAY inside
    DrawRectangleRec( hBar, Q_BLACK ); // draw the minus sign
    if ( !isMinus ) {
        DrawRectangleRec( vBar, Q_BLACK ); // turn into a plus if not a minus
    }
    if ( !isDown ) {
        DrawRectangleRec( Rectangle{ main.x + main.width, main.y + 5, 5, main.height }, Q_DARKGRAY ); // drop shadow if not down
        DrawRectangleRec( Rectangle{ main.x + 5, main.y + main.height, main.width, 5 }, Q_DARKGRAY );
    }

    if ( !canNotBePressed && CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, coll ) && IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) ) { // can i haz increment??????
        return startNum + ( isMinus ? -1 : 1 ); // yes
    }
    return startNum;
}

int drawPlusCenter( RenderTexture rentex, int pos_x, int pos_y, int size_x, int size_y, bool canNotBePressed, int startNum, int maxOrMinVal, bool isMinus = false ) {
    return drawPlus( rentex, pos_x - size_x / 2 , pos_y - size_y / 2, size_x, size_y, canNotBePressed, startNum, maxOrMinVal, isMinus );
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


int main( int argc, char** argv ) {

    bool DEBUG;
    for ( int i = 0; i < argc; i++ ) {
        if ( std::string( argv[ i ] ) == "--debug" ) DEBUG = true;
    }

    /*
    ** IDK
    */
    std::string choice;
    int quimbertQuantity = 2;

    /*
    ** Temp quimbert stats
    */
    int looks = 0;
    int smell = 0;
    std::string color = "red";
    int personality = 0;
    int gumption = 0;
    int length = 0;
    std::string name = "";
    std::string owner = "";
    
    int points = randInt( 25, 35 );
    std::vector< Quimbert > quimbertArr;
    bool gameDone = false;
    bool isMusicMuted = false;
    std::string gameLayout = "start";
    
    int currentQuimbert = 0;
    
    int monitorWidth = GetMonitorWidth( 0 ), monitorHeight = GetMonitorHeight( 0 );
    
    bool showColorSelectionPanel = false;
    Color currentColor = stoc( color );
        
    bool takenColors[ 10 ] = { false };

    bool showStatsInfoBoxLooks = false;
    bool showStatsInfoBoxSmell = false;
    bool showStatsInfoBoxPersonality = false;
    bool showStatsInfoBoxGumption = false;
    bool showStatsInfoBoxLength = false;

    bool showInventory = false;
    int inventoryScrollCount = 0;
    bool showGambleUi = false;
    bool showStatsBox = false;

    SetConfigFlags( FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED );

    InitWindow(1366, 768, "Quimbert Quarrel");

    RenderTexture rentex = LoadRenderTexture( 1920, 1080 );


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

    SetMusicVolume( blippy, 1 );
    SetMusicVolume( ambient, 1 );
    SetMusicVolume( mania, 1 );
    SetMusicVolume( quimbertcall, 1 );
    PlayMusicStream( mania );
    PlayMusicStream( quimbertcall );
    PlayMusicStream( blippy );
    PlayMusicStream( ambient );

    QuimbertTextBox textBoxName(
        Rectangle{
            static_cast< float >( rentex.texture.width / 2 + 20 ),
            250,
            375,
            75
        }
    );

    QuimbertTextBox textBoxOwner(
        Rectangle{
            static_cast< float >( rentex.texture.width / 2 + 20 ),
            350,
            375,
            75
        }
    );

    textBoxName.setCharLength( 25 );
    textBoxOwner.setCharLength( 25 );
    

    Image exitImage = LoadImage( "./resources/textures/UI/exit.png" );
    ImageResize( &exitImage, 70, 70 );
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

    Image info2Image = LoadImage( "./resources/textures/UI/infoButton2.png");
    ImageResize( &info2Image, 40, 40 );
    Texture2D info2Tex = LoadTextureFromImage( info2Image );
    UnloadImage( info2Image );

    Image backgroundImage = LoadImage( "resources/textures/backgrounds/quimbert_hell.png");
    Texture2D backgroundTex = LoadTextureFromImage( backgroundImage );
    UnloadImage( backgroundImage );

    while ( !WindowShouldClose() ) {

        BeginTextureMode( rentex );

        float sf_x = static_cast< float >( rentex.texture.width ) / GetScreenWidth();
        float sf_y = static_cast< float >( rentex.texture.height ) / GetScreenHeight();

        ClearBackground( Q_WHITE );

        if ( !isMusicMuted ) {
            // UpdateMusicStream( blippy );
            // UpdateMusicStream( quimbertcall );
            // UpdateMusicStream( mania );
            UpdateMusicStream( ambient );
        }

        if ( gameLayout == "start" ) {

            DrawText("Quimbert Quarrel", ( rentex.texture.width / 2 ) - ( MeasureText( "Quimbert Quarrel", 96 ) / 2 ), ( rentex.texture.height / 4), 96, Q_BLACK);
            DrawText("A Green Apple Game", ( rentex.texture.width / 2 ) - ( MeasureText( "A Green Apple Game", 36 ) / 2 ), ( rentex.texture.height / 4 + 100), 36, Q_BLACK);

            Rectangle localButton{ static_cast< float >( rentex.texture.width ) / 2 - 155, static_cast< float >( rentex.texture.height ) / 2, 300, 150 };

            //Local Button (Next Layout)
            if ( makeButtonTextCenter( rentex, rentex.texture.width / 2, rentex.texture.height / 2 + 200, "Local", 80, false ) ) {
                gameLayout = "howManyQuimberts";
            }

            //Mute/Unmute Button
            if ( makeButtonImage( rentex, rentex.texture.width - 235, 10, ( isMusicMuted ? mutedTex : unmutedTex ), Q_GRAY, false ) ) {
                isMusicMuted = !isMusicMuted;
            }

            //Exit Button
            if ( makeButtonImage( rentex, rentex.texture.width - 120, 10, exitTex ) ) {
                /* Break out of the main game loop and stop execution */
                break; 
            }
            if ( DEBUG ) {
                isMusicMuted = true;
                quimbertArr.emplace_back( 10, 10, "blue", 10, 5, 0, "a", "a");
                quimbertArr.emplace_back( 10, 10, "green", 10, 5, 0, "ab", "ab");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                quimbertArr[ 0 ].getInventoryDangerous()->emplace_back("NOT AN ITEM DUMBASS");
                currentQuimbert = 0;
                gameLayout = "game";
            }

        } else if ( gameLayout == "howManyQuimberts" ) {
            
            Rectangle backButton = {20, 20, 120, 80};
            
            // Back button
            if (!CheckCollisionPointRec(Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, backButton)) {
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
            
            
            DrawText( "How many Quimberts?", rentex.texture.width / 2 - MeasureText("How many Quimberts?", 80) / 2, 140, 80, Q_BLACK);
            
            /* Draw the current numbers box */
            DrawRectangle((rentex.texture.width / 2) - 60, rentex.texture.height / 2 - 70, 120, 150, Q_BLACK);
            DrawRectangle((rentex.texture.width / 2) - 50, rentex.texture.height / 2 + 10 - 70, 100, 130, Q_LIGHTGRAY);
            /* Actually draw the number */
            DrawText(std::to_string(quimbertQuantity).c_str(), ( rentex.texture.width / 2 ) - MeasureText(std::to_string(quimbertQuantity).c_str(), 108) / 2, rentex.texture.height / 2 + 25 - 70, 108, Q_BLACK);

            quimbertQuantity = drawPlusCenter( rentex, rentex.texture.width / 2 + 130, rentex.texture.height / 2 + 80 - 70, 100, 100, false, quimbertQuantity, 8, false);
            quimbertQuantity = drawPlusCenter( rentex, rentex.texture.width / 2 - 130, rentex.texture.height / 2 + 80 - 70, 100, 100, false, quimbertQuantity, ( currentQuimbert > 0 ) ? currentQuimbert + 1 : 2, true);

            if ( makeButtonTextCenter( rentex, rentex.texture.width / 2, rentex.texture.height / 2 + 260 - 70, "Next", 60, false) ) {
                gameLayout = "createQuimbertDetails";
            }
            
        } else if ( gameLayout == "createQuimbertDetails" ) {
            Rectangle backButton = {20, 20, 120, 80};

            // Back button
            if (!CheckCollisionPointRec(Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, backButton)) {
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

            textBoxName.processTextInput( rentex );
            textBoxName.render( rentex );

            textBoxOwner.processTextInput( rentex );
            textBoxOwner.render( rentex );

            DrawText( ( ( std::string( "Quimbert #" ) + std::to_string( currentQuimbert + 1 ) ).c_str() ), (rentex.texture.width / 2) - (MeasureText("Quimbert #1", 96) / 2), 20, 96, Q_BLACK);
            DrawText(("Make your Quimbert"), (rentex.texture.width / 2) - (MeasureText("Make your Quimbert", 96) / 2), 120, 96, Q_BLACK);

            DrawText("Name:", ((rentex.texture.width / 2) - MeasureText("Name:", 72)) - 30, 250, 72, Q_BLACK);
            DrawText("Owner:", ((rentex.texture.width / 2) - MeasureText("Owner:", 72)) - 30, 350, 72, Q_BLACK);
            DrawText("Color:", ((rentex.texture.width / 2) - MeasureText("Color:", 72)) - 30, 450, 72, Q_BLACK);

            // textBoxName.setBox(
            //     Rectangle{
            //         static_cast< float >( rentex.texture.width / 2 + 20 ),
            //         250,
            //         375,
            //         75
            //     }
            // );
            // textBoxOwner.setBox(
            //     Rectangle{
            //         static_cast< float >( rentex.texture.width / 2 + 20 ),
            //         350,
            //         375,
            //         75
            //     }
            // );

            if ( makeButtonColor( rentex, rentex.texture.width / 2 + 20, 450, 60, 60, currentColor, stocDark(color), false ) ) {
                showColorSelectionPanel = true;
            }


            
            if ( showColorSelectionPanel ) {                
                /*
                ** The box that the color buttons are in
                */
                Rectangle colorSelectionPanelMain = { static_cast< float >( rentex.texture.width ) / 2 + 60 + 20 + 20, 450, 80 * 5 + 25, 80 * 2 + 25 };
                Rectangle colorSelectionPanelInside = colorSelectionPanelMain;
                colorSelectionPanelInside.x += 10; colorSelectionPanelInside.y += 10; 
                colorSelectionPanelInside.width -= 20; colorSelectionPanelInside.height -= 20;

                /*
                ** Draw the box that the selector buttons are in
                */
                DrawRectangleRec( colorSelectionPanelMain, Q_BLACK );
                DrawRectangleRec( colorSelectionPanelInside, Q_LIGHTGRAY );

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

                if ( makeButtonColor( rentex, colorSelectionPanelInside.x + 80 * 0 + 10, colorSelectionPanelInside.y + 80 * 0 + 10, 60, 60, takenColors[ 0 ] ? Q_MAROON : Q_RED, Q_MAROON, takenColors[ 0 ] ) ) {
                    color = "red";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( rentex, colorSelectionPanelInside.x + 80 * 1 + 10, colorSelectionPanelInside.y + 80 * 0 + 10, 60, 60, takenColors[ 1 ] ? Q_DARKORANGE : Q_ORANGE, Q_DARKORANGE, takenColors[ 1 ] ) ) {
                    color = "orange";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( rentex, colorSelectionPanelInside.x + 80 * 2 + 10, colorSelectionPanelInside.y + 80 * 0 + 10, 60, 60, takenColors[ 2 ] ? Q_GOLD : Q_YELLOW, Q_GOLD, takenColors[ 2 ] ) ) {
                    color = "yellow";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( rentex, colorSelectionPanelInside.x + 80 * 3 + 10, colorSelectionPanelInside.y + 80 * 0 + 10, 60, 60, takenColors[ 3 ] ? Q_LIME : Q_GREEN, Q_LIME, takenColors[ 3 ] ) ) {
                    color = "green";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( rentex, colorSelectionPanelInside.x + 80 * 4 + 10, colorSelectionPanelInside.y + 80 * 0 + 10, 60, 60, takenColors[ 4 ] ? Q_DARKLIGHTBLUE : Q_LIGHTBLUE, Q_DARKLIGHTBLUE, takenColors[ 4 ] ) ) {
                    color = "lightblue";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( rentex, colorSelectionPanelInside.x + 80 * 0 + 10, colorSelectionPanelInside.y + 80 * 1 + 10, 60, 60, takenColors[ 5 ] ? Q_DARKBLUE : Q_BLUE, Q_DARKBLUE, takenColors[ 5 ] ) ) {
                    color = "blue";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( rentex, colorSelectionPanelInside.x + 80 * 1 + 10, colorSelectionPanelInside.y + 80 * 1 + 10, 60, 60, takenColors[ 6 ] ? Q_VIOLET : Q_PURPLE, Q_VIOLET, takenColors[ 6 ] ) ) {
                    color = "purple";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( rentex, colorSelectionPanelInside.x + 80 * 2 + 10, colorSelectionPanelInside.y + 80 * 1 + 10, 60, 60, takenColors[ 7 ] ? Q_LIGHTBLACK : Q_DARKGRAY, Q_LIGHTBLACK, takenColors[ 7 ] ) ) {
                    color = "black";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( rentex, colorSelectionPanelInside.x + 80 * 3 + 10, colorSelectionPanelInside.y + 80 * 1 + 10, 60, 60, takenColors[ 8 ] ? Q_GRAY : Q_LIGHTGRAY, Q_GRAY, takenColors[ 8 ] ) ) {
                    color = "gray";
                    showColorSelectionPanel = false;
                }
                
                if ( makeButtonColor( rentex, colorSelectionPanelInside.x + 80 * 4 + 10, colorSelectionPanelInside.y + 80 * 1 + 10, 60, 60, takenColors[ 9 ] ? Q_MAGENTA : Q_PINK, Q_MAGENTA, takenColors[ 9 ] ) ) {
                    color = "pink";
                    showColorSelectionPanel = false;
                }
                
                if ( IsMouseButtonDown( MOUSE_LEFT_BUTTON ) && !CheckCollisionPointRec( GetMousePosition(), colorSelectionPanelMain ) ) {
                    showColorSelectionPanel = false;
                }
            }
            
            //Next Button

            /*
            if (IsMouseButtonReleased(0)) {
                if (textBoxName.getText().length() > 0 && textBoxOwner.getText().length() > 0 && sColor1 != OFFWHITE) {
                    g = textBoxName.getText();
                    h = textBoxOwner.getText();
                    layout = "createQuimbert2";
                } else {
                    if (!(textBoxName.getText().length() > 0)) {
                        textBoxName.needText = true;
                    }
                    
                    if (!(textBoxOwner.getText().length() > 0)) {
                        textBoxOwner.needText = true;
                    
                    if (sColor1 == OFFWHITE) {
                        sColor2 = MAROON;
                        needColor = true;
                    }
                }
            }
            */
            //VERY IMPORTANT, TAKE THE ABOVE FUNCTION AND APPLY IT TO THE ONE BELOW
            //THE FUNCION MUST ONLY GO TO NEXT PAGE IF TEXTBOX AND COLOR BUTTON HAVE CONTENT SELECTED

            /* NOTE: I implemented it but don't know about the color shenagans, i think i fixed that somewhere else though already ( takenColors[] i believe) so if its an issue refer back here
            ** --Liam */
            if ( makeButtonTextCenter( rentex, rentex.texture.width / 2, rentex.texture.height - 80, "Next", 60, false ) ) {
                if ( textBoxName.getText().length() > 0 && textBoxOwner.getText().length() > 0 ) {
                    gameLayout = "chooseQuimbertStats";
                } else {
                    if ( textBoxName.getText().length() < 1 ) {
                        textBoxName.needsText();
                    }
                    if ( textBoxOwner.getText().length() < 1 ) {
                        textBoxOwner.needsText();    
                    }
                }
            }

            currentColor = stoc( color );

        } else if ( gameLayout == "chooseQuimbertStats") {


            Rectangle backButton = {20, 20, 120, 80};

            // Back button
            if (!CheckCollisionPointRec(Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, backButton)) {
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

            Rectangle doneButton = { static_cast< float >( rentex.texture.width ) - 175, 20, 150, 80 };

            //Create Quimbert button
            if ( makeButtonText( rentex, rentex.texture.width - 175, 20, "Done", 48, points != 0 ) ) {
                if (points == 0 && currentQuimbert + 1 <= quimbertQuantity) {
                    if (currentQuimbert + 1 <= quimbertQuantity) {
                        quimbertArr.emplace_back( Quimbert( looks, smell, color, personality, gumption, length, name, owner ) );
                        /* added to constructor instead
                        quimbertArr[ currentQuimbert ].setHealth( (randInt(3, 5) * quimbertArr[ currentQuimbert ].getLooks() ) / 2 );
                        quimbertArr[ currentQuimbert ].setHealth( quimbertArr[ currentQuimbert ].startingHealth );

                        if (quimbertArr[ currentQuimbert ].health < 1) {
                            quimbertArr[ currentQuimbert ].health++;
                            quimbertArr[ currentQuimbert ].startingHealth++;
                        }
                        

                        sColor1 = OFFWHITE;
                        sColor2 = WHITE;
                        */

                        if ( color == "red" ) {
                            takenColors[ 0 ] = true;
                        } else if ( color == "orange" ) {
                            takenColors[ 1 ] = true;
                        } else if ( color == "yellow" ) {
                            takenColors[ 2 ] = true;
                        } else if ( color == "green" ) {
                            takenColors[ 3 ] = true;
                        } else if ( color == "lightblue" ) {
                            takenColors[ 4 ] = true;
                        } else if ( color == "blue" ) {
                            takenColors[ 5 ] = true;
                        } else if ( color == "purple" ) {
                            takenColors[ 6 ] = true;
                        } else if ( color == "black" ) {
                            takenColors[ 7 ] = true;
                        } else if ( color == "gray" ) {
                            takenColors[ 8 ] = true;
                        } else if ( color == "pink" ) {
                            takenColors[ 9 ] = true;
                        }

                        looks = 0; smell = 0; personality = 0; gumption = 0; length = 0; name = ""; owner = "";

                        if ( !takenColors[ 0 ] ) {
                            color = "red";
                        } else if ( !takenColors[ 1 ] ) {
                            color = "orange";
                        } else if ( !takenColors[ 2 ] ) {
                            color = "yellow";
                        } else if ( !takenColors[ 3 ] ) {
                            color = "green";
                        } else if ( !takenColors[ 4 ] ) {
                            color = "lightblue";
                        } else if ( !takenColors[ 5 ] ) {
                            color = "blue";
                        } else if ( !takenColors[ 6 ] ) {
                            color = "purple";
                        } else if ( !takenColors[ 7 ] ) {
                            color = "black";
                        } else if ( !takenColors[ 8 ] ) {
                            color = "gray";
                        } else if ( !takenColors[ 9 ] ) {
                            color = "pink";
                        }
                            

                        textBoxName.clear();
                        textBoxOwner.clear();
                        points = randInt(25, 35);

                        if ( ++currentQuimbert < quimbertQuantity) {
                            showStatsInfoBoxLooks = false;
                            showStatsInfoBoxSmell = false;
                            showStatsInfoBoxPersonality = false;
                            showStatsInfoBoxGumption = false;
                            showStatsInfoBoxLength = false;
                            showColorSelectionPanel = false;

                            gameLayout = "createQuimbertDetails";
                        } else {
                            currentQuimbert = 0;
                            gameLayout = "game";
                        }
                    }
                }
            }

            /* Initial vars for the stat buttons */

            int pos_x = 280;
            int pos_y = 220;

            int oldLooks = looks;
            int oldSmell = smell;
            int oldPersonality = personality;
            int oldGumption = gumption;
            int oldLength = length;

            
            /* Draw the looks buttons */
            std::string looks_string = std::to_string( looks );
            Rectangle looks_stat_main = {
                pos_x - static_cast< float >( MeasureText( looks_string.c_str(), 60 ) ) / 2 - 20,
                pos_y - static_cast< float >( MeasureTextEx( GetFontDefault(), looks_string.c_str(), 60, 6 ).y ) / 2 - 20,
                static_cast< float >( MeasureText( looks_string.c_str(), 60 ) + 40 ),
                static_cast< float >( MeasureTextEx( GetFontDefault(), looks_string.c_str(), 60, 6 ).y ) + 40
            };
            Rectangle looks_stat_inside = looks_stat_main;
            
            DrawText( "Looks", pos_x - MeasureText( "Looks", 48 ) / 2, pos_y - 110, 48, Q_BLACK );
            
            looks_stat_inside.x += 10; looks_stat_inside.y += 10;
            looks_stat_inside.width -= 20; looks_stat_inside.height -= 20;

            DrawRectangleRec( looks_stat_main, Q_BLACK);
            DrawRectangleRec( looks_stat_inside, Q_GRAY );

            DrawText( std::to_string( looks ).c_str(), looks_stat_inside.x + 10, looks_stat_inside.y + 10, 60, Q_BLACK );

            
            looks = drawPlusCenter( rentex, pos_x - 90, pos_y, 60, 60,  false, looks, 0, true );
            looks = drawPlusCenter( rentex, pos_x + 90, pos_y, 60, 60, points == 0, looks, 10 );


            if ( makeButtonTextEx( rentex, pos_x + 200 - MeasureText( "++", 60 ) / 2 - 20, pos_y - 30, MeasureText( "++", 60 ) + 40, 60, "++", 60, looks > 9 || points < 1 ) ) {
                if ( 10 - looks > points ) {
                    looks += points;
                } else {
                    looks = 10;
                }
            }
            
            if ( makeButtonTextEx( rentex, pos_x - 200 - MeasureText( "--", 60 ) / 2 - 20, pos_y - 30, MeasureText( "--", 60 ) + 40, 60, "--", 60, looks < 1 ) ) {
                looks = 0;
            }
            /* Stats Button, same for all of the below */
            if ( makeButtonImageCenter( rentex, pos_x + 7, pos_y + 100, info2Tex ) ) {
                showStatsInfoBoxLooks = !showStatsInfoBoxLooks;
                showStatsInfoBoxSmell = false;
                showStatsInfoBoxPersonality = false;
                showStatsInfoBoxGumption = false;
                showStatsInfoBoxLength = false;
            }

            const std::string looksHelp{
                "The Looks stat\n"
                "improves your health."
            };
            if ( showStatsInfoBoxLooks ) {
                DrawText(
                    looksHelp.c_str(),
                    pos_x - MeasureText(
                        looksHelp.c_str(),
                        48
                    ) / 2,
                    pos_y + 140,
                    48,
                    Q_BLACK
                );
            }
            /* Move it down a bit so they don't overlap */
            pos_y += 40 + rentex.texture.height / 3;


            /* Smell */
            std::string smell_string = std::to_string( smell );
            Rectangle smell_stat_main = {
                pos_x - static_cast< float >( MeasureText( smell_string.c_str(), 60 ) ) / 2 - 20,
                pos_y - static_cast< float >( MeasureTextEx( GetFontDefault(), smell_string.c_str(), 60, 6 ).y ) / 2 - 20,
                static_cast< float >( MeasureText( smell_string.c_str(), 60 ) + 40 ),
                static_cast< float >( MeasureTextEx( GetFontDefault(), smell_string.c_str(), 60, 6 ).y ) + 40
            };
            Rectangle smell_stat_inside = smell_stat_main;
            
            DrawText( "smell", pos_x - MeasureText( "smell", 48 ) / 2, pos_y - 110, 48, Q_BLACK );
            
            smell_stat_inside.x += 10; smell_stat_inside.y += 10;
            smell_stat_inside.width -= 20; smell_stat_inside.height -= 20;

            DrawRectangleRec( smell_stat_main, Q_BLACK);
            DrawRectangleRec( smell_stat_inside, Q_GRAY );

            DrawText( std::to_string( smell ).c_str(), smell_stat_inside.x + 10, smell_stat_inside.y + 10, 60, Q_BLACK );

            
            smell = drawPlusCenter( rentex, pos_x - 90, pos_y, 60, 60,  false, smell, 0, true );
            smell = drawPlusCenter( rentex, pos_x + 90, pos_y, 60, 60, points == 0, smell, 10 );

            if ( makeButtonTextEx( rentex, pos_x + 200 - MeasureText( "++", 60 ) / 2 - 20, pos_y - 30, MeasureText( "++", 60 ) + 40, 60, "++", 60, smell > 9 || points < 1 ) ) {
                if ( 10 - smell > points ) {
                    smell += points;
                } else {
                    smell = 10;
                }
            }
            
            if ( makeButtonTextEx( rentex, pos_x - 200 - MeasureText( "--", 60 ) / 2 - 20, pos_y - 30, MeasureText( "--", 60 ) + 40, 60, "--", 60, smell < 1 ) ) {
                smell = 0;
            }
            if ( makeButtonImageCenter( rentex, pos_x + 7, pos_y + 100, info2Tex ) ) {
                showStatsInfoBoxLooks = false;
                showStatsInfoBoxSmell = !showStatsInfoBoxSmell;
                showStatsInfoBoxPersonality = false;
                showStatsInfoBoxGumption = false;
                showStatsInfoBoxLength = false;
            }
            const std::string smellHelp{
                "The Smell stat\n"
                "improves your ability\n"
                "to \"Sniff\" (get items)."
            };
            if ( showStatsInfoBoxSmell ) {
                DrawText(
                    smellHelp.c_str(),
                    pos_x - MeasureText(
                        smellHelp.c_str(),
                        48
                    ) / 2,
                    pos_y + 140,
                    48,
                    Q_BLACK
                );
            }


            /* Move it to the middle */
            pos_y = 320;
            pos_x = rentex.texture.width / 2;


            /* Personality */
            std::string personality_string = std::to_string( personality );
            Rectangle personality_stat_main = {
                pos_x - static_cast< float >( MeasureText( personality_string.c_str(), 60 ) ) / 2 - 20,
                pos_y - static_cast< float >( MeasureTextEx( GetFontDefault(), personality_string.c_str(), 60, 6 ).y ) / 2 - 20,
                static_cast< float >( MeasureText( personality_string.c_str(), 60 ) + 40 ),
                static_cast< float >( MeasureTextEx( GetFontDefault(), personality_string.c_str(), 60, 6 ).y ) + 40
            };
            Rectangle personality_stat_inside = personality_stat_main;
            
            DrawText( "personality", pos_x - MeasureText( "personality", 48 ) / 2, pos_y - 110, 48, Q_BLACK );
            
            personality_stat_inside.x += 10; personality_stat_inside.y += 10;
            personality_stat_inside.width -= 20; personality_stat_inside.height -= 20;

            DrawRectangleRec( personality_stat_main, Q_BLACK);
            DrawRectangleRec( personality_stat_inside, Q_GRAY );

            DrawText( std::to_string( personality ).c_str(), personality_stat_inside.x + 10, personality_stat_inside.y + 10, 60, Q_BLACK );

            
            personality = drawPlusCenter( rentex, pos_x - 90, pos_y, 60, 60,  false, personality, 0, true );
            personality = drawPlusCenter( rentex, pos_x + 90, pos_y, 60, 60, points == 0, personality, 10 );
            
            if ( makeButtonTextEx( rentex, pos_x + 200 - MeasureText( "++", 60 ) / 2 - 20, pos_y - 30, MeasureText( "++", 60 ) + 40, 60, "++", 60, personality > 9 || points < 1 ) ) {
                if ( 10 - personality > points ) {
                    personality += points;
                } else {
                    personality = 10;
                }
            }
            
            if ( makeButtonTextEx( rentex, pos_x - 200 - MeasureText( "--", 60 ) / 2 - 20, pos_y - 30, MeasureText( "--", 60 ) + 40, 60, "--", 60, personality < 1 ) ) {
                personality = 0;
            }
            if ( makeButtonImageCenter( rentex, pos_x + 7, pos_y + 100, info2Tex ) ) {
                showStatsInfoBoxLooks = false;
                showStatsInfoBoxSmell = false;
                showStatsInfoBoxPersonality = !showStatsInfoBoxPersonality;
                showStatsInfoBoxGumption = false;
                showStatsInfoBoxLength = false;
            }
            const std::string personalityHelp{
                "The Personality stat\n"
                "improves your blocks."
            };
            if ( showStatsInfoBoxPersonality ) {
                DrawText(
                    personalityHelp.c_str(),
                    pos_x - MeasureText(
                        personalityHelp.c_str(),
                        48
                    ) / 2,
                    pos_y + 140,
                    48,
                    Q_BLACK
                );
            }
            /* Move it to the other side */
            pos_x = rentex.texture.width - 280;
            pos_y = 220;


            /* gumption */
            std::string gumption_string = std::to_string( gumption );
            Rectangle gumption_stat_main = {
                pos_x - static_cast< float >( MeasureText( gumption_string.c_str(), 60 ) ) / 2 - 20,
                pos_y - static_cast< float >( MeasureTextEx( GetFontDefault(), gumption_string.c_str(), 60, 6 ).y ) / 2 - 20,
                static_cast< float >( MeasureText( gumption_string.c_str(), 60 ) + 40 ),
                static_cast< float >( MeasureTextEx( GetFontDefault(), gumption_string.c_str(), 60, 6 ).y ) + 40
            };
            Rectangle gumption_stat_inside = gumption_stat_main;
            
            DrawText( "gumption", pos_x - MeasureText( "gumption", 48 ) / 2, pos_y - 110, 48, Q_BLACK );
            
            gumption_stat_inside.x += 10; gumption_stat_inside.y += 10;
            gumption_stat_inside.width -= 20; gumption_stat_inside.height -= 20;

            DrawRectangleRec( gumption_stat_main, Q_BLACK);
            DrawRectangleRec( gumption_stat_inside, Q_GRAY );

            DrawText( std::to_string( gumption ).c_str(), gumption_stat_inside.x + 10, gumption_stat_inside.y + 10, 60, Q_BLACK );

            
            gumption = drawPlusCenter( rentex, pos_x - 90, pos_y, 60, 60,  false, gumption, 0, true );
            gumption = drawPlusCenter( rentex, pos_x + 90, pos_y, 60, 60, points == 0, gumption, 10 );
            
            if ( makeButtonTextEx( rentex, pos_x + 200 - MeasureText( "++", 60 ) / 2 - 20, pos_y - 30, MeasureText( "++", 60 ) + 40, 60, "++", 60, gumption > 9 || points < 1 ) ) {
                if ( 10 - gumption > points ) {
                    gumption += points;
                } else {
                    gumption = 10;
                }
            }
            
            if ( makeButtonTextEx( rentex, pos_x - 200 - MeasureText( "--", 60 ) / 2 - 20, pos_y - 30, MeasureText( "--", 60 ) + 40, 60, "--", 60, gumption < 1 ) ) {
                gumption = 0;
            }
            if ( makeButtonImageCenter( rentex, pos_x + 7, pos_y + 100, info2Tex ) ) {
                showStatsInfoBoxLooks = false;
                showStatsInfoBoxSmell = false;
                showStatsInfoBoxPersonality = false;
                showStatsInfoBoxGumption = !showStatsInfoBoxGumption;
                showStatsInfoBoxLength = false;
            }
            const std::string gumptionHelp{
                "The Looks stat\n"
                "improves your item\n"
                "use chances/ability."
            };
            if ( showStatsInfoBoxGumption ) {
                DrawText(
                    gumptionHelp.c_str(),
                    pos_x - MeasureText(
                        gumptionHelp.c_str(),
                        48
                    ) / 2,
                    pos_y + 140,
                    48,
                    Q_BLACK
                );
            }
            

            /* Move it down */
            pos_y += 40 + rentex.texture.height / 3;

            /* length */
            std::string length_string = std::to_string( length );
            Rectangle length_stat_main = {
                pos_x - static_cast< float >( MeasureText( length_string.c_str(), 60 ) ) / 2 - 20,
                pos_y - static_cast< float >( MeasureTextEx( GetFontDefault(), length_string.c_str(), 60, 6 ).y ) / 2 - 20,
                static_cast< float >( MeasureText( length_string.c_str(), 60 ) + 40 ),
                static_cast< float >( MeasureTextEx( GetFontDefault(), length_string.c_str(), 60, 6 ).y ) + 40
            };
            Rectangle length_stat_inside = length_stat_main;
            
            DrawText( "length", pos_x - MeasureText( "length", 48 ) / 2, pos_y - 110, 48, Q_BLACK );
            
            length_stat_inside.x += 10; length_stat_inside.y += 10;
            length_stat_inside.width -= 20; length_stat_inside.height -= 20;

            DrawRectangleRec( length_stat_main, Q_BLACK);
            DrawRectangleRec( length_stat_inside, Q_GRAY );

            DrawText( std::to_string( length ).c_str(), length_stat_inside.x + 10, length_stat_inside.y + 10, 60, Q_BLACK );

            
            length = drawPlusCenter( rentex, pos_x - 90, pos_y, 60, 60,  false, length, 0, true );
            length = drawPlusCenter( rentex, pos_x + 90, pos_y, 60, 60, points == 0, length, 10 );
            
            if ( makeButtonTextEx( rentex, pos_x + 200 - MeasureText( "++", 60 ) / 2 - 20, pos_y - 30, MeasureText( "++", 60 ) + 40, 60, "++", 60, length > 9 || points < 1 ) ) {
                if ( 10 - length > points ) {
                    length += points;
                } else {
                    length = 10;
                }
            }
            
            if ( makeButtonTextEx( rentex, pos_x - 200 - MeasureText( "--", 60 ) / 2 - 20, pos_y - 30, MeasureText( "--", 60 ) + 40, 60, "--", 60, length < 1 ) ) {
                length = 0;
            }
            if ( makeButtonImageCenter( rentex, pos_x + 7, pos_y + 100, info2Tex ) ) {
                showStatsInfoBoxLooks = false;
                showStatsInfoBoxSmell = false;
                showStatsInfoBoxPersonality = false;
                showStatsInfoBoxGumption = false;
                showStatsInfoBoxLength = !showStatsInfoBoxLength;
            }
            const std::string lengthHelp{
                "The Looks stat\n"
                "improves your damage."
            };
            if ( showStatsInfoBoxLength ) {
                DrawText(
                    lengthHelp.c_str(),
                    pos_x - MeasureText(
                        lengthHelp.c_str(),
                        48
                    ) / 2,
                    pos_y + 140,
                    48,
                    Q_BLACK
                );
            }
            points += oldLooks - looks;
            points += oldSmell - smell;
            points += oldPersonality - personality;
            points += oldGumption - gumption;
            points += oldLength - length;


            DrawText(
                (
                    std::string( "Points: " ) + std::to_string( points )
                ).c_str(),
                rentex.texture.width / 2 - MeasureText(
                    (
                        std::string( "Points: " ) + std::to_string( points )
                    ).c_str(),
                    48
                ) / 2,
                150,
                48,
                Q_BLACK
            );
            const char* statsHelpText =
                "Stats Descriptions:\n"
                "Looks: \n"
                "Smell: \n"
                "Personality: \n"
                "Gumption: \n"
                "Length: \n";

            const char *titleText = "Select Stats";
            DrawText( titleText, rentex.texture.width / 2 - MeasureText( titleText, 80 ) / 2, 30, 80, Q_BLACK );

        } else if ( gameLayout == "game" ) {

            /* no longer necessary for because of the scaling system */
            // Image tmpImage = ImageCopy( backgroundImage );

            const double BACKGROUND_ASPECT_RATIO = static_cast< double >( backgroundImage.width ) / static_cast< double >( backgroundImage.height );
            if ( static_cast< double >( rentex.texture.width ) / static_cast< double >( rentex.texture.height ) > BACKGROUND_ASPECT_RATIO ) {
                ImageResize( &tmpImage, rentex.texture.height * BACKGROUND_ASPECT_RATIO, rentex.texture.height );
            } else {
                ImageResize( &tmpImage, rentex.texture.width, rentex.texture.width / BACKGROUND_ASPECT_RATIO );
            }
            
            // Texture2D backgroundTex = LoadTextureFromImage( tmpImage );
            

            ClearBackground( Q_BLACK );
            DrawTexture( backgroundTex, 0, 0, Q_WHITE );
            

            /* Botton Row */
            const int TOTAL_BUTTON_WIDTH = MeasureText( "Gamble", 60 ) +
                                     MeasureText( "Block", 60 ) +
                                     MeasureText( "Sniff", 60 ) +
                                     MeasureText( "Inventory", 60 ) +
                                     MeasureText( "Attack", 60 ) + 
                                     45 * 5 /* account for button padding */;
            const int BUTTON_GAP = static_cast< float >( rentex.texture.width - TOTAL_BUTTON_WIDTH ) / 6; /* number of gaps */

            int button_position_y = rentex.texture.height - 40 - 20 - MeasureTextEx( GetFontDefault(), "DONT_CHANGE", 60, static_cast< float >( 60 ) / 10 ).y;
            int button_position_x = BUTTON_GAP;

            
            if ( makeButtonText( rentex, button_position_x, button_position_y, "Gamble", 60 ) ) {
                showGambleUi = true;
            }
            button_position_x += BUTTON_GAP + MeasureText( "Gamble", 60 ) + 45;

            if ( makeButtonText( rentex, button_position_x, button_position_y, "Block", 60 ) ) {}
            button_position_x += BUTTON_GAP + MeasureText( "Block", 60 ) + 45;

            if ( makeButtonText( rentex, button_position_x, button_position_y, "Sniff", 60 ) ) {}
            button_position_x += BUTTON_GAP + MeasureText( "Sniff", 60 ) + 45;
            
            /* Center of button x */
            int inventory_button_x = button_position_x + MeasureText("Inventory", 60) / 2 + 20;
            /* Top of button */
            int inventory_botton_y = button_position_y;
            if ( makeButtonText( rentex, button_position_x, button_position_y, "Inventory", 60) ) {
                showInventory = true;
            }



            /* this is here to get the location of the inventory button,
               and use that to get the location of the inventory box */
            int inventory_box_size_x = (
                10 /* border */ + 60 /* box */ ) * 3 /* 3 boxes */ +
                ( 10 /* border */ + 20 /* scroll bar */ + 10 /* border again */ );

            int inventory_box_size_y = (
                10 /* border */ + 60 /* box */ ) * 2 /* 2 boxes */ +
                ( 10 /* border */ );

            if ( showInventory ) {
                /* main background */
                Rectangle inventory_background{
                    inventory_button_x - static_cast< float >( inventory_box_size_x ) / 2,
                    static_cast< float >( inventory_botton_y - inventory_box_size_y - 10 ),
                    static_cast< float >( inventory_box_size_x ),
                    static_cast< float >( inventory_box_size_y )
                };
                
                /* draw the grid, where items will eventually be drawn */
                DrawRectangleRec( inventory_background, Q_BLACK );
                for ( int i = 0; i < 2; i++ ) {
                    int pos_y = inventory_background.y + 10 + 70 * i;
                    for ( int j = 0; j < 3; j++ ) {
                        int pos_x = inventory_background.x + 10 + 70 * j;
                        DrawRectangleRec( Rectangle{ static_cast< float >( pos_x ), static_cast< float >( pos_y ), 60, 60 }, Q_GRAY );
                    }
                }

                /* This is the scroll arrow section */
                Rectangle scroll_button = Rectangle{
                    inventory_background.x + inventory_background.width - 20 /* width of scroll bar */ - 10 /* border */,
                    inventory_background.y + 10,
                    20,
                    40
                };
                DrawRectangleRec( scroll_button, Q_GREEN );
                if ( IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, scroll_button ) ) { /* check collision with scroll up */
                    if ( inventoryScrollCount >= 1 ) {
                        inventoryScrollCount--;
                    }
                }
                DrawTriangle( /* triangle of up arrow */
                    Vector2{
                        scroll_button.x + scroll_button.width / 2,
                        scroll_button.y
                    },
                    Vector2{
                        scroll_button.x,
                        scroll_button.y + 20
                    },
                    Vector2{
                        scroll_button.x + scroll_button.width,
                        scroll_button.y + 20
                    },
                    Q_RED
                );
                DrawRectangle( /* the not triangle of the up arrow */
                    scroll_button.x + 5,
                    scroll_button.y + 20,
                    10,
                    20,
                    Q_PURPLE
                );

                scroll_button.y = inventory_background.y + inventory_background.height - scroll_button.height - 10;
                DrawRectangleRec( scroll_button, Q_GREEN );
                if ( IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, scroll_button ) ) { /* check collision with scroll down */
                    if ( ( inventoryScrollCount + 2 ) * 3 < quimbertArr[ currentQuimbert ].getInventoryDangerous()->size() / 3 ) {
                        inventoryScrollCount++;
                    }
                }

                DrawTriangle( /* the triangle of the down arrow */
                    Vector2{
                        scroll_button.x + scroll_button.width / 2,
                        scroll_button.y + scroll_button.height
                    },
                    Vector2{
                        scroll_button.x + scroll_button.width,
                        scroll_button.y + scroll_button.height - 20
                    },
                    Vector2{
                        scroll_button.x,
                        scroll_button.y + scroll_button.height - 20
                    },
                    Q_RED
                );
                DrawRectangle( /* the not triangle of the down arrow */
                    scroll_button.x + 5,
                    scroll_button.y + scroll_button.height - 20 - 20,
                    10,
                    20,
                    Q_PURPLE
                );

                std::cout << inventoryScrollCount << '\n';
            } else {
                inventoryScrollCount = 0;
            } /* end inventory drawing */



            button_position_x += BUTTON_GAP + MeasureText( "Inventory", 60 ) + 45;

            if ( makeButtonText( rentex, button_position_x, button_position_y, "Attack", 60 ) ) {}

            Rectangle healthBlockCorner = Rectangle{
                10,
                10,
                static_cast< float >( MeasureTextEx( 
                    GetFontDefault(),
                    "Health: 20\nBlocks: 10",
                    60,
                    6 
                ).x + 40 ),

                static_cast< float >( MeasureTextEx(
                    GetFontDefault(),
                    "Health: 20\nBlocks: 10",
                    60,
                    6
                ).y + 30 )
            };

            DrawRectangleRec( healthBlockCorner, Q_BLACK );
            healthBlockCorner.x += 10; healthBlockCorner.y += 10;
            healthBlockCorner.width -= 20; healthBlockCorner.height -= 20;
            DrawRectangleRec( healthBlockCorner, Q_GRAY );
            
            /* Draw the Health and Blocks values */
            DrawText(
                (
                    std::string( "Health: ")
                    + std::to_string( quimbertArr[ currentQuimbert ].getHealth() )
                    + std::string( "\nBlocks: " )
                    + std::to_string( quimbertArr[ currentQuimbert ].getBlocks() )
                ).c_str(),
                healthBlockCorner.x + 10, healthBlockCorner.x + 5, 60, Q_BLACK 
            );

            Vector2 statsCornerLabel = Vector2{
                rentex.texture.width - MeasureTextEx(
                    GetFontDefault(),
                    "Stats",
                    60,
                    static_cast< float >( 60 ) / 10
                ).x - 55,
                10
            };

            if ( makeButtonText(
                rentex,
                statsCornerLabel.x,
                statsCornerLabel.y,
                "Stats",
                60 )
            ) { showStatsBox = !showStatsBox; }

            if ( showStatsBox ) {
                Rectangle statsCornerBox = Rectangle{
                    rentex.texture.width - MeasureTextEx(
                        GetFontDefault(),
                        "Looks: 10\n"
                        "Smell: 10\n"
                        "Personality: 10\n"
                        "Gumption: 10\n"
                        "Length: 10",
                        60,
                        static_cast< float >( 60 ) / 10
                    ).x - 60,
                    MeasureTextEx(
                        GetFontDefault(),
                        "Stats",
                        60,
                        static_cast< float >( 60 ) / 10
                    ).y + 30 + 20 + 15,
                    MeasureTextEx(
                        GetFontDefault(),
                        "Looks: 10\n"
                        "Smell: 10\n"
                        "Personality: 10\n"
                        "Gumption: 10\n"
                        "Length: 10",
                        60,
                        static_cast< float >( 60 ) / 10
                    ).x + 50,
                    MeasureTextEx(
                        GetFontDefault(),
                        "Looks: 10\n"
                        "Smell: 10\n"
                        "Personality: 10\n"
                        "Gumption: 10\n"
                        "Length: 10",
                        60,
                        static_cast< float >( 60 ) / 10
                    ).y + 30,
                };
                DrawRectangleRec( statsCornerBox, Q_BLACK );
    
                statsCornerBox.x += 10; statsCornerBox.y += 10;
                statsCornerBox.width -= 20; statsCornerBox.height -= 20;
            
    
                DrawRectangleRec( statsCornerBox, Q_GRAY );
    
                DrawText(
                    (
                        std::string( "Looks: " ) +
                        std::to_string( quimbertArr[ currentQuimbert ].getLooks() ) +
                        std::string( "\nSmell: " ) +
                        std::to_string( quimbertArr[ currentQuimbert ].getSmell() ) +
                        std::string( "\nPersonality: " ) +
                        std::to_string( quimbertArr[ currentQuimbert ].getPersonality() ) +
                        std::string( "\nGumption: " ) +
                        std::to_string( quimbertArr[ currentQuimbert ].getGumption() ) +
                        std::string( "\nLength: " ) +
                        std::to_string( quimbertArr[ currentQuimbert ].getLength() )
                    ).c_str(),
                    statsCornerBox.x + 10,
                    statsCornerBox.y,
                    60,
                    Q_BLACK
                );

            }


        } /* end render if tree */

        EndTextureMode();
        BeginDrawing();
        ClearBackground( Q_WHITE );
        DrawTexturePro(
            rentex.texture,
            Rectangle{
                0,
                0,
                static_cast< float >( rentex.texture.width ),
                static_cast< float >( -rentex.texture.height )
            },
            Rectangle{
                0,
                0,
                static_cast< float >( GetScreenWidth() ),
                static_cast< float >( GetScreenHeight() )
            },
            Vector2{ 0, 0 },
            0,
            Q_WHITE
        );
        if ( DEBUG ) DrawFPS( 20, 200 );
        EndDrawing();
    }
    UnloadRenderTexture( rentex );
}