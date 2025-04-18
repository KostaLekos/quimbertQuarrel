#pragma once

#include "../third/raylib/src/raylib.h"


#include <string>
#include <vector>
#include <cstddef>

class QuimbertTextBox {

public:


    /*
    ** Simple cntr
    */
    QuimbertTextBox( Rectangle boundingBox );

    inline ~QuimbertTextBox() {
    for ( std::size_t i = 0; i < _textBoxes.size(); i++ ) {
        if ( _textBoxes[ i ] == this ) {
            _textBoxes.erase( _textBoxes.begin() + i );
        }
    }
}
    
    /*
    ** Sets the maximum char length, defaults to zero so must be called at least once to have
    **  a useful textbox
    */
    void setCharLength( int charLength );

    /*
    ** returns the current text
    */
    std::string getText();

    /*
    ** Clears the text
    */
    void clear();

    /*
    ** Sets the bounding box
    */
    void setBox( Rectangle boundingBox );

    /*
    ** Processes text input
    ** Reccomended to be ran every frame the textbox is supposed to be onscreen
    */
    void processTextInput( RenderTexture rentex );

    /*
    ** Renders the text box
    ** Assumes after a BeginDrawing() call
    */
    void render( RenderTexture rentex );


    /*
    ** Sets _needsText to true, to turn it red and signify that it needs an input
    */
    void needsText();

    /* returns a copy of the bounding box to be used (hopefully) non-nefariously */
    Rectangle getBox();

    bool isSelectedAndHovered( RenderTexture rentex );

private:
    std::string _text;
    size_t _maxCharCount;
    bool _mouseOnText;
    static bool _mouseOnAnyText;
    static std::vector< QuimbertTextBox * > _textBoxes;
    Rectangle _boundingBox;
    size_t _frameCounter;
    bool _needsText;

};