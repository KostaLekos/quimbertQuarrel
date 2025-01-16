if you have access to this please go away

me no like you

# Quimbert Quarrel
"Turn based battle royale" (*Kosta Lekos*)

# KOSTA MUST KNOWS

- Know how headers and source files work
- Learn c++ standard library
- Learn c++ build process
- Learn c++ class semantics
- Learn c++ in general


# BUILD
This is for you Kosta, here is the build instructions

## Make sure your path variables are set correctly
The following will show your path

``` powershell
$env:path
```

Make sure that it shows `DRIVELETTER:\path\to\apps\w64devkit\w64devkit\bin`, THIS IS CRUCIAL
*Note, Must be before all of the `C:\` paths*

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
- - [ ] Write quimbert.cpp
- - - [x] Write Quimbert() 
- - - [x] Write randInt()
- - - [ ] Write sniff()
- - - [ ] Write block()
- - - [ ] Write getInventory()
- - - [ ] Write getHealth()
- - - [ ] Write infoOfItem()
- - - [ ] Write useItem()
- - - [ ] Write getStatsString()
- - - [ ] Write getStat()
- - [ ] Write textbox.hpp
- - [ ] Write textbox.cpp
- - [ ] Write main.cpp
- - - [x] Write randInt()
- - - [ ] Write drawButtonText()
- - - [ ] Write drawButtonColor()
- - - [ ] Write drawButtomImage()
- - - [ ] Write isLetterPressed()
- - - [ ] Write drawPlus()
- - - [ ] Write main()
- - - - [ ] Write main function globals
- - - - [ ] Write everything else
- - [ ] Finish game

## DONE
