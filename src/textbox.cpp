

#include "../include/textbox.hpp"

#include "../third/raylib/src/raylib.h"

#include <string>
#include <format>
#include <vector>

bool QuimbertTextBox::_mouseOnAnyText;
std::vector< QuimbertTextBox * > QuimbertTextBox::_textBoxes;

QuimbertTextBox::QuimbertTextBox( Rectangle boundingBox )
    : _text( "" ),
      _maxCharCount( 40 ),
      _boundingBox( boundingBox ),
      _frameCounter( 0 ),
      _needsText( false )
{
    _mouseOnText = false;
    _textBoxes.push_back( this );
}



void QuimbertTextBox::needsText() {
    _needsText = true;
}

void QuimbertTextBox::setCharLength( int charLength ) {
    _maxCharCount = charLength;
}

std::string QuimbertTextBox::getText() {
    return _text;
}

void QuimbertTextBox::clear() {
    _text = "";
}

void QuimbertTextBox::setBox( Rectangle boundingBox ) {
    _boundingBox = boundingBox;
}

bool QuimbertTextBox::isSelectedAndHovered( RenderTexture rentex ) {
    float sf_x = static_cast< float >( rentex.texture.width ) / GetScreenWidth();
    float sf_y = static_cast< float >( rentex.texture.height ) / GetScreenHeight();
    return _mouseOnText && CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, _boundingBox );
}

void QuimbertTextBox::processTextInput( RenderTexture rentex ) {
    float sf_x = static_cast< float >( rentex.texture.width ) / GetScreenWidth();
    float sf_y = static_cast< float >( rentex.texture.height ) / GetScreenHeight();

    /*
    ** Checks if mouse is in bounding box
    */
    if ( CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, _boundingBox ) && 
        IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) )  {
            
        _mouseOnText = true;
        _needsText = false;
        _mouseOnAnyText = true;
    }
    /*
    ** Else, it isn't
    */
    else if ( !CheckCollisionPointRec( Vector2{ GetMouseX() * sf_x, GetMouseY() * sf_y }, _boundingBox ) && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) ) {
        _mouseOnText = false;
    }

    _mouseOnAnyText = false;
    for ( QuimbertTextBox *tb : _textBoxes ) {
        _mouseOnAnyText |= tb->isSelectedAndHovered( rentex );
    }

    if ( _mouseOnAnyText ) {
        SetMouseCursor( MOUSE_CURSOR_IBEAM );
    } else {
        SetMouseCursor( MOUSE_CURSOR_DEFAULT );
    }

    if ( _mouseOnText ) {
        /*
        ** Get the ascii character pressed
        */
        char key = GetCharPressed();

        /*
        ** Continue checking the keys until there isn't any
        */
        while ( key > 0 ) {
            if ( key >= 32 && key <= 126 && _text.length() < _maxCharCount ) {
                _text += key;
            }

            key = GetCharPressed();
        }

        if ( IsKeyPressed( KEY_BACKSPACE ) || IsKeyPressedRepeat( KEY_BACKSPACE )) {
            if ( _text.length() < 2 ) {
                _text = "";
            } else {
                _text = _text.substr( 0, _text.length() - 1 );
            }
        }

    }
}


void QuimbertTextBox::render( RenderTexture rentex ) {
    float sf_x = static_cast< float >( rentex.texture.width ) / GetScreenWidth();
    float sf_y = static_cast< float >( rentex.texture.height ) / GetScreenHeight();


    _frameCounter++;

    if ( _mouseOnText ) {
        DrawRectangleRec( _boundingBox, GRAY );
        _needsText = false;
    } else if ( _needsText ) {
        DrawRectangleRec( _boundingBox, MAROON );
    } else {
        DrawRectangleRec( _boundingBox, LIGHTGRAY );
    }
    DrawRectangleLinesEx( _boundingBox, 10.0f, BLACK );

    // MeasureTextEx( GetFontDefault(), text.c_str(), fontSize, ( float ) fontSize / 10 ).y + 40 }

    if ( _mouseOnText ) {
        DrawText( std::format( "INPUT CHARS: {}/{}", _text.length(), _maxCharCount ).c_str(),
            _boundingBox.x, _boundingBox.y + _boundingBox.height, 20, DARKGRAY);
        

        if ( _text.length() < _maxCharCount ) {
            /*
            ** Draw blinking underscore
            */
            if ( _frameCounter / 20 % 2 == 0 ) {
                DrawText( "_", _boundingBox.x + 23
                    + MeasureText( _text.c_str(), 40 ),
                    _boundingBox.y + 15, 40, DARKGRAY);
            }
        } else {
            DrawText( "Press BACKSPACE to delete characters...", _boundingBox.x, _boundingBox.y - 20, 20, GRAY);
        }
    }

    /*
    ** Draw the text
    */
    DrawText( _text.c_str(), _boundingBox.x + 20,
        _boundingBox.y + 15, 40, DARKGRAY);
}

Rectangle QuimbertTextBox::getBox() {
    return _boundingBox;
}