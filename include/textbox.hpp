#pragma once

#include "../third/raylib/src/raylib.h"


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



private:
    std::string _text;
    int _maxCharCount;
    bool _mouseOnText;
    Rectangle _boundingBox;
    int _frameCounter;
    bool _needsText;

};