#pragma once

#include "raylib.h"


#include <string>

class QuimbertTextBox {

public:


    /*
    ** Simple cntr
    */
    QuimbertTextBox( Rectangle boundingBox );
    
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
    void setBox( Rectangle boundingBox);

    /*
    ** Processes text input
    ** Reccomended to be ran every frame the textbox is supposed to be onscreen
    */
    void processTextInput();

    /*
    ** Renders the text box
    ** Assumes after a BeginDrawing() call
    */
    void render();


    /*
    ** Sets _needsText to true, to turn it red and signify that it needs an input
    */
    void needsText();

private:
    std::string _text;
    size_t _maxCharCount;
    bool _mouseOnText;
    Rectangle _boundingBox;
    size_t _frameCounter;
    bool _needsText;

};