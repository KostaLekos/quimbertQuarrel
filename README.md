if you have access to this please go away

me no like you

# Quimbert Quarrel
"Turn based battle royale"

# MUST KNOWS

- Know how headers and source files work
- Learn c++ standard library
- Learn c++ build process
- Learn c++ class semantics
- Learn c++ in general
- Seriously, read the comments in *all* files, it is actually important you do this before you start development, because I have added hints in places on how to do things, as well as documented how things work.
- Learn markdown (.md files), so you can add to this file todo's and mark them as complete, as well as add other notes
- Don't ask me to help during lunch, but I will answer questions about my implemntation details, and if you do have a question, WRITE A COMMENT NEXT TO THE ISSUE EXPLAINING WHAT IT DOES
- Also, WRITE SOME GODDAMN COMMENTS, it doesn't matter when you are working alone, but I am working with you on this and it is so annoying trying to figure what stuff does



# BUILD
This is for you, here is the build instructions

## Make sure your path variables are set correctly
The following will show your path

``` powershell
$env:path
```

Make sure that it shows `DRIVELETTER:\path\to\apps\w64devkit\w64devkit\bin`, THIS IS CRUCIAL
*Note, Must be before all of the `C:\` paths, ideally the first one but not necessarily*

## Check current working directory

Ensure that your CWD is `path\to\quimbert\cpp`

## Commands

Run `make all` to build the game
Run `make clean` if there are build errors

# Java version
The Java version is depracated and unfinished, it should only be used as a reference. If you want to build it anyway, run the c.bat and run.bat, and if on linux, figure it out.

# Development

## Migration
main.cpp == QuimbertQuarrel.java
quimbert.cpp == Quimbert.java
textbox.cpp == QuimbertTextBox.java

You will also need to run `git submodule init` and `git submodule update` if third/raylib is empty or doesn't exist

If you are cloning for the first time clone with `git clone --recurse-submodules https://github.com/HairyJade/quimbertquarrel`


## TODO
- - [x] Wrote quimbert.hpp
- - [x] Write quimbert.cpp
- - - [x] Write Quimbert() 
- - - [x] Write randInt()
- - - [x] Write sniff()
- - - [x] Write block()
- - - [x] Write getInventory()
- - - [x] Write getHealth()
- - - [x] Write infoOfItem()
- - - [x] Write useItem()
- - - [x] Write getStatsString()
- - - [x] Write getStat()
- - [x] Write textbox.hpp
- - [x] Write textbox.cpp
- - - [x] Write QuimbertTextBox()
- - - [x] Write setCharLength()
- - - [x] Write getText()
- - - [x] Write clear()
- - - [x] Write setBox()
- - - [x] Write processTextInput()
- - - [x] Write render()
- - [ ] Write main.cpp
- - - [x] Write randInt()
- - - [x] Write makeButtonText() - Rewritten, read notes
- - - [x] Write makeButtonColor()
- - - [x] Write makeButtonImage()
- - - [x] Write isLetterPressed()
- - - [x] Write drawPlus()
- - - [ ] Write main()
- - - - [x] Write main function globals
- - - - [ ] Write everything else
- - - - - [x] Start menu
- - - - - [x] HMQ
- - - - - [x] Create Q: info
- - - - - [ ] Create Q: stats
- - - - - - [x] Port the background things to manage the quimberts creation
- - - - - - [ ] Rewrite the stat selection buttons
- - [ ] Finish game
- - - [x] Layout for game screen created
- - - [ ] Write the layout
- - - [ ] Adapt the CLI version bits to GUI version bits

## Changes from java version
- REMOVED sniff() in QuimbertQuarrel.java (main.cpp) file, see header notes in quimert.hpp for `void sniff()`
- REMOVED getRandomString() in Quimbert.java (quimbert.hpp/quimbert.cpp). Replaced functionality with an array of items and randint
- REMOVED stats() in Quimbert.java (quimbert.hpp/quimbert.cpp) replaced with getStatsString()
- ADDED getIntStat() in Quimbert.java (quimbert.hpp/quimbert.cpp) to get individual stat of type int
- ADDED getStrStat() in Quimbert.java (quimbert.hpp/quimbert.cpp) to get individual stat of type std::string
- MODIFIED makeButtonText, now automatically determines the buttons width
- ADDED makeButtonTextCenter, same as makeButtonText, but the given coords are the center of the button and not the top left corner
- ADDED makeButtonColorCenter, figure it out
- ADDED drawPlusCenter
