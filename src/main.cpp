
#include "../include/quimbert.hpp"
#include "../include/textbox.hpp"

#include "../third/raylib/src/raylib.h"

#include <stdexcept>
#include <string>
#include <iostream>
#include <random>

std::mt19937_64::result_type randInt( int min, int max ) {
    std::random_device randomDev;
    std::mt19937_64 rng( randomDev() );
    std::uniform_int_distribution< std::mt19937::result_type > dist( min, max );

    return dist( rng );
}



/*
** Rewrote makeButtonText, give position of top-left corner, text, fontsize, and whether or not to ignore input
** Made better than the previous one!
*/
bool makeButtonText( int pos_x, int pos_y, std::string text, int fontSize, bool isDisabled ) {

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



    DrawRectangleRec( main, BLACK ); // Draw black boarder
    DrawRectangleRec( inside, CheckCollisionPointRec( GetMousePosition(), coll ) ? DARKGRAY : GRAY ); // inside color

    // Drop shaddow
    if ( !buttonDown ) {
        DrawRectangleRec( { main.x + main.width, main.y + 5, 5, main.height }, DARKGRAY );
        DrawRectangleRec( { main.x + 5, main.y + main.height, main.width, 5 }, DARKGRAY );
    }
    DrawText( text.c_str(), main.x + 10 + 10, main.y + 10 + 10, fontSize, BLACK );

    return IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec( GetMousePosition(), coll );

}


/*
** Makes a button, but with the center at the coordinates listed
*/
bool makeButtonTextCenter( int pos_x, int pos_y, std::string text, int fontSize, bool isDisabled ) {
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
    std::string text, int fontSize, bool isDisabled ) {
    
    Rectangle main{ ( float ) pos_x, ( float ) pos_y, ( float ) size_x, ( float ) size_y };

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
                size_x - 20, size_y - 20, LIGHTGRAY);

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

bool makeButtonColor( int pos_x, int pos_y, int size_x, int size_y, Color color1, Color color2, bool isDisabled ) {
    Rectangle main = { ( float ) pos_x, ( float ) pos_y, ( float ) size_x, ( float ) size_y };
    Rectangle coll = main;
    coll.width += 5; coll.height += 5;

    bool buttonDown = isDisabled || CheckCollisionPointRec( GetMousePosition(), coll ) && IsMouseButtonDown( MOUSE_LEFT_BUTTON );
    if ( buttonDown ) {
        main.x += 5; main.y += 5;
    }

    Rectangle inside = { main.x + 10, main.y + 10, main.width - 20, main.height - 20 };



    DrawRectangleRec( main, BLACK ); // Draw black boarder
    DrawRectangleRec( inside, CheckCollisionPointRec( GetMousePosition(), coll ) ? color2 : color1 ); // inside color

    // Drop shaddow
    if ( !buttonDown ) {
        DrawRectangleRec( { main.x + main.width, main.y + 5, 5, main.height }, DARKGRAY );
        DrawRectangleRec( { main.x + 5, main.y + main.height, main.width, 5 }, DARKGRAY );
    }


    return IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec( GetMousePosition(), coll );

}

bool makeButtonColorCenter( int pos_x, int pos_y, int size_x, int size_y, Color color1, Color color2, bool isDisabled ) {
    return makeButtonColor( pos_x - size_x / 2, pos_y - size_y / 2, size_x, size_y, color1, color2, isDisabled );
}
/*
** Copy-pasted from Java verson
*/
bool makeButtonColor_DEPRECATED( int pos_x, int pos_y, int size_x, int size_y, Color color1, Color color2, bool isDisabled ) {
    bool result = false;
    // background rectangle / collision rectangle
    Rectangle main{ ( float ) pos_x, ( float ) pos_y, ( float ) size_x, ( float ) size_y };
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
** NOTE: Call with the "image" part as &someImg, and unload it after ( if desired )
*/
bool makeButtonImage( int pos_x, int pos_y, Texture2D tex, Color background, bool isDisabled ) {

    Rectangle main = { ( float ) pos_x, ( float ) pos_y, ( float ) tex.width + 20, ( float ) tex.height + 20 };
    Rectangle coll = main;
    coll.width += 5; coll.height += 5;
    
    bool buttonDown = isDisabled || CheckCollisionPointRec( GetMousePosition(), coll ) && IsMouseButtonDown( MOUSE_LEFT_BUTTON );
    if ( buttonDown ) {
        main.x += 5; main.y += 5;
    }
    
    Rectangle inside = { main.x + 10, main.y + 10, main.width - 20, main.height - 20 };
    
    DrawRectangleRec( main, BLACK ); // Draw black boarder
    DrawRectangleRec( inside, background ); // Draw grey inside
    
    DrawTexture( tex, inside.x, inside.y, WHITE );


    // Drop shaddow
    if ( !buttonDown ) {
        DrawRectangleRec( { main.x + main.width, main.y + 5, 5, main.height }, DARKGRAY );
        DrawRectangleRec( { main.x + 5, main.y + main.height, main.width, 5 }, DARKGRAY );
    }


    return IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec( GetMousePosition(), coll );

}

bool makeButtonImageCenter( int pos_x, int pos_y, int size_x, int size_y, Texture2D tex, Color background, bool isDisabled ) {
    return makeButtonImage( pos_x - ( tex.width + 40 ) / 2, pos_y - ( tex.height + 40 ) / 2, tex, background, isDisabled );
}

/*
** Copy-pasted again
** NOTE: Call with the "image" part as &someImg, and unload it after ( if desired )
*/
bool makeButtonImage_DEPRACATED(int pos_x, int pos_y, int size_x, int size_y, Image* image, bool isDisabled) {
    // load image
    ImageCrop( image , { ( float ) pos_x + 10, ( float ) pos_y + 10, ( float ) size_x - 20, ( float ) size_y - 20 } );
    Texture tex = LoadTextureFromImage( *image );
    bool result = false;

    // background rectangle / collision rectangle
    Rectangle main{ ( float ) pos_x, ( float ) pos_y, ( float ) size_x, ( float ) size_y };
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
    UnloadTexture( tex );
    return result;
}



int drawPlus( int pos_x, int pos_y, bool canNotBePressed, int startNum, int maxOrMinVal, bool isMinus ) {
    Rectangle main = { ( float ) pos_x, ( float ) pos_y, 100, 100 }; /* Main body (Black outline) */
    Rectangle coll = main; /* Collision hitbox */
    coll.width += 5; coll.height += 5; /* Update collision hitbox to include gray area, to prevent jankyness */
    
    canNotBePressed |= isMinus ? ( startNum <= maxOrMinVal ) : ( startNum >= maxOrMinVal ); /* update canBePressed if it is outside the bounds */

    /* check if the button should be down, down if cant be pressed or mouse is down inside box */
    /* button release added to prevent jankyness with the button flickering */
    bool isDown = canNotBePressed || ( CheckCollisionPointRec( GetMousePosition(), coll ) && ( IsMouseButtonDown( MOUSE_LEFT_BUTTON ) || IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) ) );

    if ( isDown ) {
        main.x += 5; main.y += 5;
    }

    /* gray / darkgray area inside the box */
    Rectangle inside = { main.x + 10, main.y + 10, main.width - 20, main.height - 20 };

    /* vert and hori bars of the plus or minus*/
    Rectangle hBar = { main.x + 20, main.y + 45 , 60, 10 };
    Rectangle vBar = { main.x + 45, main.y + 20, 10, 60 };

    DrawRectangleRec( main, BLACK ); // draw black outling
    DrawRectangleRec( inside, CheckCollisionPointRec( GetMousePosition(), coll ) ? DARKGRAY : GRAY ); // draw gray inside
    DrawRectangleRec( hBar, BLACK ); // draw the minus sign
    if ( !isMinus ) {
        DrawRectangleRec( vBar, BLACK ); // turn into a plus if not a minus
    }
    if ( !isDown ) {
        DrawRectangleRec( { main.x + main.width, main.y + 5, 5, main.height }, DARKGRAY ); // drop shadow if not down
        DrawRectangleRec( { main.x + 5, main.y + main.height, main.width, 5 }, DARKGRAY );
    }

    if ( !canNotBePressed && CheckCollisionPointRec( GetMousePosition(), coll ) && IsMouseButtonReleased( MOUSE_LEFT_BUTTON ) ) { // can i haz increment??????
        return startNum + ( isMinus ? -1 : 1 ); // yes
    }
    return startNum;
}

int drawPlusCenter( int pos_x, int pos_y, bool canNotBePressed, int startNum, int maxOrMinVal, bool isMinus ) {
    return drawPlus( pos_x - 50, pos_y - 50, canNotBePressed, startNum, maxOrMinVal, isMinus );
}

/*
** You guessed it! Copy-pasted
*/
int drawPlus_DEPRECATED(int posx, int posy, bool isGrayedOut, int numToIncrement, int maxMinVal, bool isMinus) {
    Rectangle rec = { (float) posx, (float) posy, 100, 100 };
    if (!isGrayedOut) {
        if(!CheckCollisionPointRec(GetMousePosition(), rec)) {
            DrawRectangleRec(rec, BLACK);
            DrawRectangle(80 + posx, 50 + posy, 80, 80, LIGHTGRAY);
            if (!isMinus) {
                DrawRectangle(115 + posx, 65 + posy, 10, 50, BLACK);
            }
            DrawRectangle(95 + posx, 85 + posy, 50, 10, BLACK);
            DrawRectangle(75 + posx, 140 + posy, 95, 5, DARKGRAY);
            DrawRectangle(170 + posx, 45 + posy, 5, 100, DARKGRAY); 
        } else {
            if (IsMouseButtonReleased(0)) {
                if (!isMinus) {
                    numToIncrement++;
                } else {
                    numToIncrement--;
                }

                if ((!isMinus) ? (numToIncrement <= maxMinVal) : (numToIncrement >= maxMinVal)) {
                    DrawRectangle(75 + posx, 45 + posy, 100, 100, BLACK);
                    DrawRectangle(85 + posx, 55 + posy, 80, 80, DARKGRAY);
                    if (!isMinus) {
                        DrawRectangle(120 + posx, 70 + posy, 10, 50, BLACK);
                    }
                    DrawRectangle(100 + posx, 90 + posy, 50, 10, BLACK);
                }
            }

            if (IsMouseButtonDown(0)) {
                DrawRectangle(75 + posx, 45 + posy, 100, 100, BLACK);
                DrawRectangle(85 + posx, 55 + posy, 80, 80, GRAY);
                if (!isMinus) {
                    DrawRectangle(120 + posx, 70 + posy, 10, 50, BLACK);
                }
                DrawRectangle(100 + posx, 90 + posy, 50, 10, BLACK);
            } else if ((!isMinus) ? (numToIncrement < maxMinVal) : (numToIncrement > maxMinVal)) {
                DrawRectangle(70 + posx, 40 + posy, 100, 100, BLACK);
                DrawRectangle(80 + posx, 50 + posy, 80, 80, GRAY);
                if (!isMinus) {
                    DrawRectangle(115 + posx, 65 + posy, 10, 50, BLACK); //correct
                }
                DrawRectangle(95 + posx, 85 + posy, 50, 10, BLACK);
                DrawRectangle(75 + posx, 140 + posy, 95, 5, DARKGRAY);
                DrawRectangle(170 + posx, 45 + posy, 5, 100, DARKGRAY);
            }
        }
    } else {
        DrawRectangle(75 + posx, 45 + posy, 100, 100, BLACK);
        DrawRectangle(85 + posx, 55 + posy, 80, 80, DARKGRAY);
        if (!isMinus) {
            DrawRectangle(120 + posx, 70 + posy, 10, 50, BLACK);
        }
        DrawRectangle(100 + posx, 90 + posy, 50, 10, BLACK);
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
    std::string color;
    int personality;
    int gumption;
    int length;
    std::string name;
    std::string owner;

    int startingPoints = randInt( 25, 35 );
    std::vector< Quimbert > quimbertArr;
    bool gameDone;
    bool isMusicMuted;
    std::string gameLayout = "start";

    int monitorWidth = GetMonitorWidth( 0 ), monitorHeight = GetMonitorHeight( 0 );


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
            ClearBackground( RAYWHITE );

            DrawText("Quimbert Quarrel", (GetScreenWidth() / 2) - (MeasureText("Quimbert Quarrel", 96) / 2), (GetScreenHeight() / 4), 96, BLACK);
            DrawText("A Green Apple Game", (GetScreenWidth() / 2) - (MeasureText("A Green Apple Game", 36) / 2), (GetScreenHeight() / 4 + 100), 36, BLACK);

            Rectangle localButton{ ( float ) GetScreenWidth() / 2 - 155, ( float ) GetScreenHeight() / 2, 300, 150 };


            if ( makeButtonTextCenter( GetScreenWidth() / 2, GetScreenHeight() / 2, "Local", 80, false ) ) {
                gameLayout = "howManyQuimberts";
            }

            if ( makeButtonImage( GetScreenWidth() - 170, 10, ( isMusicMuted ? mutedTex : unmutedTex ), GRAY, false ) ) {
                isMusicMuted = !isMusicMuted;
            }

            DrawFPS( 20, 20 );
            EndDrawing();
        } else if ( gameLayout == "howManyQuimberts" ) {
            BeginDrawing();
            ClearBackground( RAYWHITE );
            DrawRectangle((GetScreenWidth() / 2) - 60, (GetScreenHeight() / 2) + 20, 120, 150, BLACK);
            DrawRectangle((GetScreenWidth() / 2) - 50, (GetScreenHeight() / 2) + 30, 100, 130, LIGHTGRAY);
            DrawText(std::to_string(quimbertQuantity).c_str(), (GetScreenWidth() / 2) - MeasureText(std::to_string(quimbertQuantity).c_str(), 108) / 2, (GetScreenHeight() / 2) + 45, 108, BLACK);

            Rectangle backButton = {20, 20, 120, 80};

            // Back button
            if (!CheckCollisionPointRec(GetMousePosition(), backButton)) {
                DrawRectangleRec(backButton, BLACK);
                DrawRectangle(30, 30, 100, 60, LIGHTGRAY);
                DrawLineEx( { 115, 60 }, { 60, 60 }, 15, BLACK);
                DrawTriangle({ 45, 60 }, { 70, 80 }, { 70, 40 }, BLACK);
                DrawRectangle(140, 25, 5, 80, DARKGRAY);
                DrawRectangle(25, 100, 115, 5, DARKGRAY);
            } else {
                if (!IsMouseButtonDown( MOUSE_LEFT_BUTTON )) {
                    DrawRectangle(20, 20, 120, 80, BLACK);
                    DrawRectangle(30, 30, 100, 60, GRAY);
                    DrawLineEx( { 115, 60 }, { 60, 60 }, 15, BLACK);
                    DrawTriangle( { 45, 60 }, { 70, 80 }, { 70, 40 }, BLACK);
                    DrawRectangle(140, 25, 5, 80, DARKGRAY);
                    DrawRectangle(25, 100, 115, 5, DARKGRAY);
                } else {
                    DrawRectangle(25, 25, 120, 80, BLACK);
                    DrawRectangle(35, 35, 100, 60, GRAY);
                    DrawLineEx( { 120, 65 }, { 65, 65 }, 15, BLACK);
                    DrawTriangle( { 50, 65 }, { 75, 85 }, { 75, 45 }, BLACK);
                }

                if (IsMouseButtonReleased(0)) {
                    gameLayout = "start";
                }
            }

            if ( makeButtonTextCenter( GetScreenWidth() / 2, GetScreenHeight() / 4 * 3, "Next", 60, false) ) {
                gameLayout = "createQuimbertDetails";
            }
            
            quimbertQuantity = drawPlusCenter( GetScreenWidth() / 2 + 130, GetScreenHeight() / 2 + 90, false, quimbertQuantity, 8, false);
            quimbertQuantity = drawPlusCenter( GetScreenWidth() / 2 - 130, GetScreenHeight() / 2 + 90, false, quimbertQuantity, 2, true);
            EndDrawing();
        } else if ( gameLayout == "createQuimbertDetails" ) {
            BeginDrawing();
            ClearBackground( RAYWHITE );

            Rectangle backButton = {20, 20, 120, 80};

            // Back button
            if (!CheckCollisionPointRec(GetMousePosition(), backButton)) {
                DrawRectangleRec(backButton, BLACK);
                DrawRectangle(30, 30, 100, 60, LIGHTGRAY);
                DrawLineEx( { 115, 60 }, { 60, 60 }, 15, BLACK);
                DrawTriangle({ 45, 60 }, { 70, 80 }, { 70, 40 }, BLACK);
                DrawRectangle(140, 25, 5, 80, DARKGRAY);
                DrawRectangle(25, 100, 115, 5, DARKGRAY);
            } else {
                if (!IsMouseButtonDown( MOUSE_LEFT_BUTTON )) {
                    DrawRectangle(20, 20, 120, 80, BLACK);
                    DrawRectangle(30, 30, 100, 60, GRAY);
                    DrawLineEx( { 115, 60 }, { 60, 60 }, 15, BLACK);
                    DrawTriangle( { 45, 60 }, { 70, 80 }, { 70, 40 }, BLACK);
                    DrawRectangle(140, 25, 5, 80, DARKGRAY);
                    DrawRectangle(25, 100, 115, 5, DARKGRAY);
                } else {
                    DrawRectangle(25, 25, 120, 80, BLACK);
                    DrawRectangle(35, 35, 100, 60, GRAY);
                    DrawLineEx( { 120, 65 }, { 65, 65 }, 15, BLACK);
                    DrawTriangle( { 50, 65 }, { 75, 85 }, { 75, 45 }, BLACK);
                }

                if (IsMouseButtonReleased(0)) {
                    gameLayout = "howManyQuimberts";
                }
            }

            bool madeQuimbert = false;

            EndDrawing();
        }
    }
}