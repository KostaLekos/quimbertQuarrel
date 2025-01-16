package com.quimbertco.QuimbertQuarrel;
import java.util.Scanner;

import com.raylib.Jaylib.Color;
import com.raylib.Jaylib.Rectangle;
import com.raylib.Jaylib.Vector2;
import com.raylib.Raylib.Camera2D;
import com.raylib.Raylib.Image;
import com.raylib.Raylib.Music;
import com.raylib.Raylib.Texture;

import java.util.Random;
import java.util.ArrayList;
import static com.raylib.Jaylib.*;
import static com.raylib.Raylib.BeginDrawing;
import static com.raylib.Raylib.CheckCollisionPointRec;
import static com.raylib.Raylib.ClearBackground;
import static com.raylib.Raylib.CloseAudioDevice;
import static com.raylib.Raylib.CloseWindow;
import static com.raylib.Raylib.DrawFPS;
import static com.raylib.Raylib.DrawLineEx;
import static com.raylib.Raylib.DrawRectangle;
import static com.raylib.Raylib.DrawRectangleRec;
import static com.raylib.Raylib.DrawText;
import static com.raylib.Raylib.DrawTexture;
import static com.raylib.Raylib.DrawTriangle;
import static com.raylib.Raylib.EndDrawing;
import static com.raylib.Raylib.FLAG_WINDOW_MAXIMIZED;
import static com.raylib.Raylib.FLAG_WINDOW_RESIZABLE;
import static com.raylib.Raylib.GetKeyPressed;
import static com.raylib.Raylib.GetMonitorHeight;
import static com.raylib.Raylib.GetMonitorWidth;
import static com.raylib.Raylib.GetMousePosition;
import static com.raylib.Raylib.GetScreenHeight;
import static com.raylib.Raylib.GetScreenWidth;
import static com.raylib.Raylib.ImageCrop;
import static com.raylib.Raylib.InitAudioDevice;
import static com.raylib.Raylib.InitWindow;
import static com.raylib.Raylib.IsKeyPressed;
import static com.raylib.Raylib.IsMouseButtonDown;
import static com.raylib.Raylib.IsMouseButtonReleased;
import static com.raylib.Raylib.LoadImage;
import static com.raylib.Raylib.LoadMusicStream;
import static com.raylib.Raylib.LoadTextureFromImage;
import static com.raylib.Raylib.MaximizeWindow;
import static com.raylib.Raylib.MeasureText;
import static com.raylib.Raylib.PlayMusicStream;
import static com.raylib.Raylib.SetConfigFlags;
import static com.raylib.Raylib.SetMusicVolume;
import static com.raylib.Raylib.SetTargetFPS;
import static com.raylib.Raylib.SetWindowMaxSize;
import static com.raylib.Raylib.SetWindowMinSize;
import static com.raylib.Raylib.SetWindowPosition;
import static com.raylib.Raylib.UnloadImage;
import static com.raylib.Raylib.UnloadMusicStream;
import static com.raylib.Raylib.UpdateMusicStream;
import static com.raylib.Raylib.WindowShouldClose;

/*
src\main\java\com\quimbertco\QuimbertQuarrel\

path = ("D:\Registries\microsoft-jdk-21.0.4-windows-x64\jdk-21.0.4+7\bin;D:\Registries\apache-maven-3.9.9-bin\apache-maven-3.9.9\bin;D:\Apps\w64devkit\w64devkit\bin;D:\Registries\git\Git\bin;$env:path")

D:\Registries\git\Git\bin\git.exe

git pull

git add <changed files>
git commit -m "message"

git pull --rebase

git push --set-upstream origin main (only do set upstream if first time you run)

to esc from weird console app thing

i
enter
:wq
*/

/*
compile it: cmd +
"D:\Registries\java\bin\javac.exe" -cp .\lib\jaylib-5.0.0-0.jar .\QuimbertQuarrel.java .\Quimbert.java
run it: cmd +
"D:\Registries\java\bin\java.exe" -cp .\lib\jaylib-5.0.0-0.jar;. QuimbertQuarrel
*/

public class QuimbertQuarrel {
    private static int randInt(int min, int max) {
        Random rand = new Random();
        int randomNum = rand.nextInt((max - min) + 1) + min;

        return randomNum;
    }

    //Text Button
    private static boolean makeButtonText(int pos_x, int pos_y, int size_x, int size_y, String text, int fontSize, boolean isDisabled) {
        boolean result = false;
        // background rectangle / collision rectangle
        Rectangle main = new Rectangle(pos_x, pos_y, size_x, size_y);
        if (!isDisabled) {
            if (!CheckCollisionPointRec(GetMousePosition(), main)) {
                // background / button bounding box / outline
                DrawRectangleRec(main, BLACK);
                // inner body color
                DrawRectangle(pos_x + 10, pos_y + 10, size_x - 20, size_y - 20, LIGHTGRAY);
                // drop shadow
                DrawRectangle(pos_x + size_x, pos_y + 5, 5, size_y, DARKGRAY);
                DrawRectangle(pos_x + 5, pos_y + size_y, size_x, 5, DARKGRAY);

                DrawText(text, pos_x + 20, pos_y + 20 - 20, fontSize, BLACK);
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
                    DrawText(text, pos_x + 20, pos_y + 20 - 20, fontSize, BLACK);
                } else {
                    DrawRectangle(pos_x + 5, pos_y + 5, size_x, size_y, BLACK);
                    DrawRectangle(pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, GRAY);
                    DrawText(text, pos_x + 25, pos_y + 25 - 20, fontSize, BLACK);
                }
            }
        } else {
            DrawRectangle(pos_x + 5, pos_y + 5, size_x, size_y, BLACK);
            DrawRectangle(pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, GRAY);
            DrawText(text, pos_x + 25, pos_y + 25 - 20, fontSize, BLACK);
        }
        return result;
    }

    private static boolean makeButtonColor(int pos_x, int pos_y, int size_x, int size_y, Color color1, Color color2, boolean isDisabled) {
        boolean result = false;
        // background rectangle / collision rectangle
        Rectangle main = new Rectangle(pos_x, pos_y, size_x, size_y);
        if (!isDisabled) {
            if (!CheckCollisionPointRec(GetMousePosition(), main)) {
                // background / button bounding box / outline
                DrawRectangleRec(main, BLACK);
                // inner body color
                DrawRectangle(pos_x + 10, pos_y + 10, size_x - 20, size_y - 20, color1);
                // drop shadow
                DrawRectangle(pos_x + size_x, pos_y + 5, 5, size_y, DARKGRAY);
                DrawRectangle(pos_x + 5, pos_y + size_y, size_x, 5, DARKGRAY);
            } else {
                if (IsMouseButtonReleased(0)) {
                    result = true;
                }

                if (!IsMouseButtonDown(0) && !result) {
                    // same except dark interior
                    DrawRectangleRec(main, BLACK);
                    DrawRectangle(pos_x + 10, pos_y + 10, size_x - 20, size_y - 20, color2);
                    DrawRectangle(pos_x + size_x, pos_y + 5, 5, size_y, DARKGRAY);
                    DrawRectangle(pos_x + 5, pos_y + size_y, size_x, 5, DARKGRAY);
                } else {

                    DrawRectangle(pos_x + 5, pos_y + 5, size_x, size_y, BLACK);
                    DrawRectangle(pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, color2);
                }
            }
        } else {
            DrawRectangle(pos_x + 5, pos_y + 5, size_x, size_y, BLACK);
            DrawRectangle(pos_x + 15, pos_y + 15, size_x - 20, size_y - 20, color2);
        }
        return result;
    }

    private static boolean makeButtonImage(int pos_x, int pos_y, int size_x, int size_y, String path, boolean isDisabled) {
        // load image
        Image img = LoadImage(path);
        ImageCrop(img, new Rectangle(pos_x + 10, pos_y + 10, size_x - 20, size_y - 20));
        Texture tex = LoadTextureFromImage(img);
        UnloadImage(img);
        boolean result = false;

        // background rectangle / collision rectangle
        Rectangle main = new Rectangle(pos_x, pos_y, size_x, size_y);
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


    public String sniff(Quimbert currentQuimbert) {
        String itemFound;
        String toReturn;
        itemFound = currentQuimbert.sniff();
        if (itemFound.equals("fail")) {
            toReturn = "fail";
        } else {
            currentQuimbert.inv.add(itemFound);
            toReturn = itemFound;
            if (currentQuimbert.smell == 10 && randInt(0, 3) == 3) {
                itemFound = currentQuimbert.sniff();
                if (!itemFound.equals("fail")) {
                    currentQuimbert.inv.add(itemFound);
                    toReturn = toReturn.concat("+" + itemFound);
                } else {
                    toReturn = toReturn.concat("+" + "fail");
                }
            } else {
                toReturn = toReturn.concat("+" + "fail");
            }
        }
        return toReturn;
        //How to retrieve value:
        //sniffResults = sniff(quimberts.get(currentQuimbert));
        //item1 = sniffResults.substring(0, sniffResults.indexOf(+));
        //item2 = sniffResults.substring(sniffResults.indexOf(+) + 1);
        //only return values if they do not equal "fail"
    }

    boolean IsAnyKeyPressed() {
        boolean keyPressed = false;
        int key = GetKeyPressed();
        
        if ((key >= 32) && (key <= 126)) {
            keyPressed = true;
        }

        return keyPressed;
    }

    public static int drawPlus(Rectangle rec, int posx, int posy, boolean isGrayedOut, int numToIncrement, int maxMinVal, boolean isMinus) {
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
    
    public static void main(String[] args) {
        Scanner action = new Scanner(System.in);
        String choice;
        int quimbertQuantity = 2;
        String newLine = System.getProperty("line.separator");
        int a = 0;
        int b = 0;
        String c = "";
        int d = 0;
        int e = 0;
        int f = 0;
        String g = ""; // ovveride java stupidness
        String h = "";
        int points = randInt(25, 35);
        ArrayList<Quimbert> quimberts = new ArrayList<Quimbert>();
        boolean gameEnd = false;
        String tempS;
        boolean tempB;
        boolean n = false;
        boolean removePlayer = false;
        int protection = 0;
        boolean endAttack = false;
        boolean attacked = false;
        boolean gumptionSigma = false;
        boolean madeQuimbert;
        String layout = "start";
        int mWidth = GetMonitorWidth(0), mHeight = GetMonitorHeight(0);
        int makingQuimbert = 0;
        int framesCounter = 0;
        boolean isTextBoxName = false;
        boolean displayColors = false;
        String muteImage = "./resources/textures/UI/unmuted.png";
        boolean isMuted = false;
        final Color RAYWHITE = new Color(245, 245, 245, 255);
        final Color OFFWHITE = new Color(230, 230, 230, 255);
        final Color WHITE = new Color(255, 255, 255, 255);
        final Color RED = new Color(230, 41, 55, 255);
        final Color MAROON = new Color(190, 33, 55, 255);
        final Color ORANGE = new Color(255, 161, 0, 255);
        final Color DARKORANGE = new Color(215, 135, 0, 255);
        final Color YELLOW = new Color(253, 249, 0, 255);
        final Color GOLD = new Color(255, 203, 0, 255);
        final Color LIME = new Color(0, 158, 47, 255);
        final Color GREEN = new Color(0, 228, 48, 255);
        final Color LIGHTBLUE = new Color(102, 191, 255, 255);
        final Color DARKLIGHTBLUE = new Color(0, 148, 255, 255);
        final Color BLUE = new Color(0, 121, 241, 255);
        final Color DARKBLUE = new Color(0, 82, 172, 255);
        final Color VIOLET = new Color(135, 60, 190, 255);
        final Color PURPLE = new Color(200, 122, 255, 255);
        final Color DARKPURPLE = new Color(112, 31, 126, 255);
        final Color DARKGRAY = new Color(80, 80, 80, 255);
        final Color LIGHTBLACK = new Color(39, 39, 39, 255);
        final Color BLACK = new Color(0, 0, 0, 255);
        final Color LIGHTGRAY = new Color(200, 200, 200, 255);
        final Color GRAY = new Color(130, 130, 130, 255);
        final Color PINK = new Color(255, 109, 194, 255);
        final Color MAGENTA = new Color(255, 82, 183, 255);
        Color sColor1 = OFFWHITE;
        Color sColor2 = WHITE;
        Color sColor3;
        boolean color0Taken = false;
        boolean color1Taken = false;
        boolean color2Taken = false;
        boolean color3Taken = false;
        boolean color4Taken = false;
        boolean color5Taken = false;
        boolean color6Taken = false;
        boolean color7Taken = false;
        boolean color8Taken = false;
        boolean color9Taken = false;
        boolean needColor = false;
        boolean isEnabled = true;
        
        Image info1 = LoadImage("./resources/textures/UI/infoButton1.png");
        Image info2 = LoadImage("./resources/textures/UI/infoButton2.png");
        Image info3 = LoadImage("./resources/textures/UI/infoButton3.png");
        Texture infoButton1 = LoadTextureFromImage(info1);
        Texture infoButton2 = LoadTextureFromImage(info2);
        Texture infoButton3 = LoadTextureFromImage(info3);
        UnloadImage(info1);
        UnloadImage(info2);
        UnloadImage(info3);

        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);

        InitWindow(1840, 1000, "Quimbert Quarrel");
        //InitWindow(1366, 768, "Quimbert Quarrel");
        SetWindowMinSize(600, 500); 
        SetWindowMaxSize(mWidth, mHeight);
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

        Camera2D camera = new Camera2D()
            .target(new Vector2());


        QuimbertTextBox textBoxName = new QuimbertTextBox (new Rectangle(GetScreenWidth () / 2 + 20, 250, 375, 75));
        textBoxName.setCharLength(25);

        QuimbertTextBox textBoxOwner = new QuimbertTextBox (new Rectangle(GetScreenWidth () / 2 + 20, 350, 375, 75));
        textBoxOwner.setCharLength(25);


        
        while (!WindowShouldClose()) {
            
            if (!isMuted) {
                UpdateMusicStream(blippy);
            }

            if (layout.equals("start")) {
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Quimbert Quarrel", (GetScreenWidth() / 2) - (MeasureText("Quimbert Quarrel", 96) / 2), (GetScreenHeight() / 4), 96, BLACK);
                DrawText("A Green Apple Game", (GetScreenWidth() / 2) - (MeasureText("A Green Apple Game", 36) / 2), (GetScreenHeight() / 4 + 100), 36, BLACK);
                
                Rectangle localButton = new Rectangle((GetScreenWidth() / 2) - 155, GetScreenHeight() / 2, 300, 150);

                //local button
                if (!CheckCollisionPointRec(GetMousePosition(), localButton)) {
                    DrawRectangleRec(localButton, BLACK);
                    DrawRectangle((GetScreenWidth() / 2) - 145, (GetScreenHeight() / 2) + 10, 280, 130, LIGHTGRAY);
                    DrawRectangle((GetScreenWidth() / 2) + 145, (GetScreenHeight() / 2) + 5, 5, 150, DARKGRAY);
                    DrawRectangle((GetScreenWidth() / 2) - 150, (GetScreenHeight() / 2) + 150, 295, 5, DARKGRAY);
                    DrawText("Local", ((GetScreenWidth() / 2) - 5) - (MeasureText("Local", 80) / 2), (GetScreenHeight() / 2) + 37, 80, BLACK);
                } else {
                    if (!IsMouseButtonDown(0)) {
                        DrawRectangle((GetScreenWidth() / 2) - 155, GetScreenHeight() / 2, 300, 150, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) - 145, (GetScreenHeight() / 2) + 10, 280, 130, GRAY);
                        DrawRectangle((GetScreenWidth() / 2) + 145, (GetScreenHeight() / 2) + 5, 5, 150, DARKGRAY);
                        DrawRectangle((GetScreenWidth() / 2) - 150, (GetScreenHeight() / 2) + 150, 295, 5, DARKGRAY);
                        DrawText("Local", ((GetScreenWidth() / 2) - 5) - (MeasureText("Local", 80) / 2), (GetScreenHeight() / 2) + 37, 80, BLACK);
                    } else {
                        DrawRectangle((GetScreenWidth() / 2) - 150, (GetScreenHeight() / 2) + 5, 300, 150, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) - 140, (GetScreenHeight() / 2) + 15, 280, 130, GRAY);
                        DrawText("Local", ((GetScreenWidth() / 2)) - (MeasureText("Local", 80) / 2), (GetScreenHeight() / 2) + 42, 80, BLACK);
                    }

                    if (IsMouseButtonReleased(0)) {
                        EndDrawing();
                        layout = "howManyQ";
                    }
                }

                //Exit Button
                if (makeButtonImage(GetScreenWidth() - 85, 10, 70, 70, "./resources/textures/UI/exit.png", false)) {
                    break;
                }

                //mute button
                if (makeButtonImage(GetScreenWidth() - 170, 10, 70, 70, muteImage, false)) {
                    if (isMuted) {
                        isMuted = false;
                        muteImage = "./resources/textures/UI/unmuted.png";
                    } else {
                        isMuted = true;
                        muteImage = "./resources/textures/UI/muted.png";
                    }
                }

                DrawFPS(20, 20);
            } else if (layout.equals("howManyQ")) {
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("How many Quimberts are", (GetScreenWidth() / 2) - (MeasureText("How many Quimberts are", 72) / 2), (GetScreenHeight() / 4), 72, BLACK);
                DrawText("you playing with?", (GetScreenWidth() / 2) - (MeasureText("you playing with?", 72) / 2), (GetScreenHeight() / 4) + 75, 72, BLACK);

                DrawRectangle((GetScreenWidth() / 2) - 60, (GetScreenHeight() / 2) + 20, 120, 150, BLACK);
                DrawRectangle((GetScreenWidth() / 2) - 50, (GetScreenHeight() / 2) + 30, 100, 130, LIGHTGRAY);
                DrawText(Integer.toString(quimbertQuantity), (GetScreenWidth() / 2) - (MeasureText(Integer.toString(quimbertQuantity), 108) / 2), (GetScreenHeight() / 2) + 45, 108, BLACK);
                
                Rectangle backButton = new Rectangle(20, 20, 120, 80);

                //back button
                if (!CheckCollisionPointRec(GetMousePosition(), backButton)) {
                    DrawRectangleRec(backButton, BLACK);
                    DrawRectangle(30, 30, 100, 60, LIGHTGRAY);
                    DrawLineEx(new Vector2().x(115).y(60), new Vector2().x(60).y(60), 15, BLACK);
                    DrawTriangle(new Vector2().x(45).y(60), new Vector2().x(70).y(80), new Vector2().x(70).y(40), BLACK);
                    DrawRectangle(140, 25, 5, 80, DARKGRAY);
                    DrawRectangle(25, 100, 115, 5, DARKGRAY);
                } else {
                    if (!IsMouseButtonDown(0)) {
                        DrawRectangle(20, 20, 120, 80, BLACK);
                        DrawRectangle(30, 30, 100, 60, GRAY);
                        DrawLineEx(new Vector2().x(115).y(60), new Vector2().x(60).y(60), 15, BLACK);
                        DrawTriangle(new Vector2().x(45).y(60), new Vector2().x(70).y(80), new Vector2().x(70).y(40), BLACK);
                        DrawRectangle(140, 25, 5, 80, DARKGRAY);
                        DrawRectangle(25, 100, 115, 5, DARKGRAY);
                    } else {
                        DrawRectangle(25, 25, 120, 80, BLACK);
                        DrawRectangle(35, 35, 100, 60, GRAY);
                        DrawLineEx(new Vector2().x(120).y(65), new Vector2().x(65).y(65), 15, BLACK);
                        DrawTriangle(new Vector2().x(50).y(65), new Vector2().x(75).y(85), new Vector2().x(75).y(45), BLACK);
                    }

                    if (IsMouseButtonReleased(0)) {
                        layout = "start";
                    }
                }

                Rectangle nextButton = new Rectangle((GetScreenWidth() / 2) - 105, ((GetScreenHeight() / 4) * 3) + 50, 200, 100);

                //next button
                if (!CheckCollisionPointRec(GetMousePosition(), nextButton)) {
                    DrawRectangleRec(nextButton, BLACK);
                    DrawRectangle((GetScreenWidth() / 2) - 95, ((GetScreenHeight() / 4) * 3) + 60, 180, 80, LIGHTGRAY);
                    DrawRectangle((GetScreenWidth() / 2) - 100, ((GetScreenHeight() / 4) * 3) + 150, 195, 5, DARKGRAY);
                    DrawRectangle((GetScreenWidth() / 2) + 95, ((GetScreenHeight() / 4) * 3) + 55, 5, 100, DARKGRAY);
                    DrawText("Next", ((GetScreenWidth() / 2) - 5) - (MeasureText("Next", 60) / 2), ((GetScreenHeight() / 4) * 3) + 70, 60, BLACK);
                } else {
                    if (!IsMouseButtonDown(0)) {
                        DrawRectangle((GetScreenWidth() / 2) - 105, ((GetScreenHeight() / 4) * 3) + 50, 200, 100, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) - 95, ((GetScreenHeight() / 4) * 3) + 60, 180, 80, GRAY);
                        DrawRectangle((GetScreenWidth() / 2) - 100, ((GetScreenHeight() / 4) * 3) + 150, 195, 5, DARKGRAY);
                        DrawRectangle((GetScreenWidth() / 2) + 95, ((GetScreenHeight() / 4) * 3) + 55, 5, 100, DARKGRAY);
                        DrawText("Next", ((GetScreenWidth() / 2) - 5) - (MeasureText("Next", 60) / 2), ((GetScreenHeight() / 4) * 3) + 70, 60, BLACK);
                    } else {
                        DrawRectangle((GetScreenWidth() / 2) - 100, ((GetScreenHeight() / 4) * 3) + 55, 200, 100, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) - 90, ((GetScreenHeight() / 4) * 3) + 65, 180, 80, GRAY);
                        DrawText("Next", ((GetScreenWidth() / 2)) - (MeasureText("Next", 60) / 2), ((GetScreenHeight() / 4) * 3) + 75, 60, BLACK);
                    }

                    if (IsMouseButtonReleased(0)) {
                        layout = "createQuimbert";
                    }
                }

                Rectangle plusButton = new Rectangle((GetScreenWidth() / 2) + 70, (GetScreenHeight() / 2) + 40, 100, 100);

                //plus button
                if (quimbertQuantity < 8) {
                    if(!CheckCollisionPointRec(GetMousePosition(), plusButton)) {
                        DrawRectangleRec(plusButton, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) + 80, (GetScreenHeight() / 2) + 50, 80, 80, LIGHTGRAY);
                        DrawRectangle((GetScreenWidth() / 2) + 115, (GetScreenHeight() / 2) + 65, 10, 50, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) + 95, (GetScreenHeight() / 2) + 85, 50, 10, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) + 75, (GetScreenHeight() / 2) + 140, 95, 5, DARKGRAY);
                        DrawRectangle((GetScreenWidth() / 2) + 170, (GetScreenHeight() / 2) + 45, 5, 100, DARKGRAY); 
                    } else {
                        if (IsMouseButtonReleased(0)) {
                            quimbertQuantity += 1;

                            if (quimbertQuantity > 7) {
                                DrawRectangle((GetScreenWidth() / 2) + 75, (GetScreenHeight() / 2) + 45, 100, 100, BLACK);
                                DrawRectangle((GetScreenWidth() / 2) + 85, (GetScreenHeight() / 2) + 55, 80, 80, DARKGRAY);
                                DrawRectangle((GetScreenWidth() / 2) + 120, (GetScreenHeight() / 2) + 70, 10, 50, BLACK);
                                DrawRectangle((GetScreenWidth() / 2) + 100, (GetScreenHeight() / 2) + 90, 50, 10, BLACK);
                            }
                        }

                        if (IsMouseButtonDown(0)) {
                            DrawRectangle((GetScreenWidth() / 2) + 75, (GetScreenHeight() / 2) + 45, 100, 100, BLACK);
                            DrawRectangle((GetScreenWidth() / 2) + 85, (GetScreenHeight() / 2) + 55, 80, 80, GRAY);
                            DrawRectangle((GetScreenWidth() / 2) + 120, (GetScreenHeight() / 2) + 70, 10, 50, BLACK);
                            DrawRectangle((GetScreenWidth() / 2) + 100, (GetScreenHeight() / 2) + 90, 50, 10, BLACK);
                        } else if (quimbertQuantity < 8) {
                            DrawRectangle((GetScreenWidth() / 2) + 70, (GetScreenHeight() / 2) + 40, 100, 100, BLACK);
                            DrawRectangle((GetScreenWidth() / 2) + 80, (GetScreenHeight() / 2) + 50, 80, 80, GRAY);
                            DrawRectangle((GetScreenWidth() / 2) + 115, (GetScreenHeight() / 2) + 65, 10, 50, BLACK);
                            DrawRectangle((GetScreenWidth() / 2) + 95, (GetScreenHeight() / 2) + 85, 50, 10, BLACK);
                            DrawRectangle((GetScreenWidth() / 2) + 75, (GetScreenHeight() / 2) + 140, 95, 5, DARKGRAY);
                            DrawRectangle((GetScreenWidth() / 2) + 170, (GetScreenHeight() / 2) + 45, 5, 100, DARKGRAY);
                        }
                    }
                } else {
                    DrawRectangle((GetScreenWidth() / 2) + 75, (GetScreenHeight() / 2) + 45, 100, 100, BLACK);
                    DrawRectangle((GetScreenWidth() / 2) + 85, (GetScreenHeight() / 2) + 55, 80, 80, DARKGRAY);
                    DrawRectangle((GetScreenWidth() / 2) + 120, (GetScreenHeight() / 2) + 70, 10, 50, BLACK);
                    DrawRectangle((GetScreenWidth() / 2) + 100, (GetScreenHeight() / 2) + 90, 50, 10, BLACK);
                }

                Rectangle minusButton = new Rectangle((GetScreenWidth() / 2) - 175, (GetScreenHeight() / 2) + 40, 100, 100);

                //minus button
                if (quimbertQuantity > 2) {
                    if(!CheckCollisionPointRec(GetMousePosition(), minusButton)) {
                        DrawRectangleRec(minusButton, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) - 165, (GetScreenHeight() / 2) + 50, 80, 80, LIGHTGRAY);
                        DrawRectangle((GetScreenWidth() / 2) - 150, (GetScreenHeight() / 2) + 85, 50, 10, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) - 170, (GetScreenHeight() / 2) + 140, 95, 5, DARKGRAY);
                        DrawRectangle((GetScreenWidth() / 2) - 75, (GetScreenHeight() / 2) + 45, 5, 100, DARKGRAY);
                    } else {
                        if (IsMouseButtonReleased(0)) {
                            quimbertQuantity -= 1;

                            if (quimbertQuantity < 3) {
                                DrawRectangle((GetScreenWidth() / 2) - 170, (GetScreenHeight() / 2) + 45, 100, 100, BLACK);
                                DrawRectangle((GetScreenWidth() / 2) - 160, (GetScreenHeight() / 2) + 55, 80, 80, DARKGRAY);
                                DrawRectangle((GetScreenWidth() / 2) - 145, (GetScreenHeight() / 2) + 90, 50, 10, BLACK);
                            }
                        }

                        if (IsMouseButtonDown(0))
                        {
                            DrawRectangle((GetScreenWidth() / 2) - 170, (GetScreenHeight() / 2) + 45, 100, 100, BLACK);
                            DrawRectangle((GetScreenWidth() / 2) - 160, (GetScreenHeight() / 2) + 55, 80, 80, GRAY);
                            DrawRectangle((GetScreenWidth() / 2) - 145, (GetScreenHeight() / 2) + 90, 50, 10, BLACK);
                        }
                        else if (quimbertQuantity > 2)
                        {
                            DrawRectangle((GetScreenWidth() / 2) - 175, (GetScreenHeight() / 2) + 40, 100, 100, BLACK);
                            DrawRectangle((GetScreenWidth() / 2) - 165, (GetScreenHeight() / 2) + 50, 80, 80, GRAY);
                            DrawRectangle((GetScreenWidth() / 2) - 150, (GetScreenHeight() / 2) + 85, 50, 10, BLACK);
                            DrawRectangle((GetScreenWidth() / 2) - 170, (GetScreenHeight() / 2) + 140, 95, 5, DARKGRAY);
                            DrawRectangle((GetScreenWidth() / 2) - 75, (GetScreenHeight() / 2) + 45, 5, 100, DARKGRAY);
                        }
                    }
                }
                else
                {
                    DrawRectangle((GetScreenWidth() / 2) - 170, (GetScreenHeight() / 2) + 45, 100, 100, BLACK);
                    DrawRectangle((GetScreenWidth() / 2) - 160, (GetScreenHeight() / 2) + 55, 80, 80, DARKGRAY);
                    DrawRectangle((GetScreenWidth() / 2) - 145, (GetScreenHeight() / 2) + 90, 50, 10, BLACK);
                }
            } else if (layout.equals("createQuimbert")) {
                BeginDrawing();
                ClearBackground(RAYWHITE);

                Rectangle backButton = new Rectangle(20, 20, 120, 80);

                //back button
                if (!CheckCollisionPointRec(GetMousePosition(), backButton)) {
                    DrawRectangleRec(backButton, BLACK);
                    DrawRectangle(30, 30, 100, 60, LIGHTGRAY);
                    DrawLineEx(new Vector2().x(115).y(60), new Vector2().x(60).y(60), 15, BLACK);
                    DrawTriangle(new Vector2().x(45).y(60), new Vector2().x(70).y(80), new Vector2().x(70).y(40), BLACK);
                    DrawRectangle(140, 25, 5, 80, DARKGRAY);
                    DrawRectangle(25, 100, 115, 5, DARKGRAY);
                } else {
                    if (!IsMouseButtonDown(0)) {
                        DrawRectangle(20, 20, 120, 80, BLACK);
                        DrawRectangle(30, 30, 100, 60, GRAY);
                        DrawLineEx(new Vector2().x(115).y(60), new Vector2().x(60).y(60), 15, BLACK);
                        DrawTriangle(new Vector2().x(45).y(60), new Vector2().x(70).y(80), new Vector2().x(70).y(40), BLACK);
                        DrawRectangle(140, 25, 5, 80, DARKGRAY);
                        DrawRectangle(25, 100, 115, 5, DARKGRAY);
                    } else {
                        DrawRectangle(25, 25, 120, 80, BLACK);
                        DrawRectangle(35, 35, 100, 60, GRAY);
                        DrawLineEx(new Vector2().x(120).y(65), new Vector2().x(65).y(65), 15, BLACK);
                        DrawTriangle(new Vector2().x(50).y(65), new Vector2().x(75).y(85), new Vector2().x(75).y(45), BLACK);
                    }

                    if (IsMouseButtonReleased(0)) {
                        layout = "howManyQ";
                    }    
                }
                
                madeQuimbert = false;

                DrawText(("Quimbert #" + (makingQuimbert + 1)), (GetScreenWidth() / 2) - (MeasureText("Quimbert #1", 96) / 2), 20, 96, BLACK);
                DrawText(("Make your Quimbert"), (GetScreenWidth() / 2) - (MeasureText("Make your Quimbert", 96) / 2), 120, 96, BLACK);

                DrawText("Name:", ((GetScreenWidth() / 2) - MeasureText("Name:", 72)) - 30, 250, 72, BLACK);
                DrawText("Owner:", ((GetScreenWidth() / 2) - MeasureText("Owner:", 72)) - 30, 350, 72, BLACK);
                DrawText("Color:", ((GetScreenWidth() / 2) - MeasureText("Color:", 72)) - 30, 450, 72, BLACK);

                Rectangle colorDisplay = new Rectangle((GetScreenWidth () / 2) + 110, 455, 405, 180);

                Rectangle colorButton = new Rectangle ((GetScreenWidth () / 2) + 20, 450, 75, 75);

                if (displayColors) {
                    //Color button
                    if (CheckCollisionPointRec(GetMousePosition(), colorButton)) {
                        DrawRectangle((GetScreenWidth () / 2) + 25, 455, 75, 75, BLACK);

                        if (!needColor) {
                            DrawRectangle((GetScreenWidth () / 2) + 35, 465, 55, 55, sColor1);
                        } else {
                            DrawRectangle((GetScreenWidth () / 2) + 35, 465, 55, 55, MAROON);
                        }

                        if (IsMouseButtonReleased(0)) {
                            displayColors = false;

                            if (needColor) {
                                needColor = false;
                                sColor2 = WHITE;
                            }
                        }
                    } else {
                        DrawRectangle((GetScreenWidth () / 2) + 25, 455, 75, 75, BLACK);
                        DrawRectangle((GetScreenWidth () / 2) + 35, 465, 55, 55, sColor2);
                    }

                    //Color Display
                    DrawRectangleRec(colorDisplay, BLACK);
                    DrawRectangle((GetScreenWidth () / 2) + 120, 465, 385, 160, LIGHTGRAY);

                    //Colors: Red, Orange, Yellow, Green, Blue, DarkBlue, Purple, Black, Gray, Pink

                    //Red
                    if (makeButtonColor((GetScreenWidth() / 2) + 130, 475, 60, 60, RED, MAROON, color0Taken)) {
                        sColor2 = RED;
                        sColor1 = MAROON;
                        c = "Red";
                        displayColors = false;
                    }
                    
                    //Orange
                    if (makeButtonColor((GetScreenWidth() / 2) + 205, 475, 60, 60, ORANGE, DARKORANGE, color1Taken)) {
                        sColor2 = ORANGE;
                        sColor1 = DARKORANGE;
                        c = "Orange";
                        displayColors = false;
                    }

                    //Yellow
                    if (makeButtonColor((GetScreenWidth() / 2) + 280, 475, 60, 60, YELLOW, GOLD, color2Taken)) {
                        sColor2 = YELLOW;
                        sColor1 = GOLD;
                        c = "Yellow";
                        displayColors = false;
                    }

                    //Green
                    if (makeButtonColor((GetScreenWidth() / 2) + 355, 475, 60, 60, GREEN, LIME, color3Taken)) {
                        sColor2 = GREEN;
                        sColor1 = LIME;
                        c = "Green";
                        displayColors = false;
                    }

                    //Light Blue
                    if (makeButtonColor((GetScreenWidth() / 2) + 430, 475, 60, 60, LIGHTBLUE, DARKLIGHTBLUE, color4Taken)) {
                        sColor2 = LIGHTBLUE;
                        sColor1 = DARKLIGHTBLUE;
                        c = "Light Blue";
                        displayColors = false;
                    }

                    //Blue
                    if (makeButtonColor((GetScreenWidth() / 2) + 130, 550, 60, 60, BLUE, DARKBLUE, color5Taken)) {
                        sColor2 = BLUE;
                        sColor1 = DARKBLUE;
                        c = "Blue";
                        displayColors = false;
                    }

                    //Purple
                    if (makeButtonColor((GetScreenWidth() / 2) + 205, 550, 60, 60, PURPLE, VIOLET, color6Taken)) {
                        sColor2 = PURPLE;
                        sColor1 = VIOLET;
                        c = "Purple";
                        displayColors = false;
                    }

                    //Black
                    if (makeButtonColor((GetScreenWidth() / 2) + 280, 550, 60, 60, DARKGRAY, LIGHTBLACK, color7Taken)) {
                        sColor2 = DARKGRAY;
                        sColor1 = LIGHTBLACK;
                        c = "Black";
                        displayColors = false;
                    }

                    //Gray
                    if (makeButtonColor((GetScreenWidth() / 2) + 355, 550, 60, 60, LIGHTGRAY, GRAY, color8Taken)) {
                        sColor2 = LIGHTGRAY;
                        sColor1 = GRAY;
                        c = "Gray";
                        displayColors = false;
                    }

                    //Pink
                    if (makeButtonColor((GetScreenWidth() / 2) + 430, 550, 60, 60, PINK, MAGENTA, color9Taken)) {
                        sColor2 = PINK;
                        sColor1 = MAGENTA;
                        c = "Pink";
                        displayColors = false;
                    }

                } else {
                    //Color button
                    if (!CheckCollisionPointRec(GetMousePosition(), colorButton)) {
                        if (!displayColors) {
                            DrawRectangleRec(colorButton, BLACK);
                            DrawRectangle((GetScreenWidth () / 2) + 30, 460, 55, 55, sColor2);
                            DrawRectangle((GetScreenWidth () / 2) + 95, 455, 5, 75, DARKGRAY);
                            DrawRectangle((GetScreenWidth () / 2) + 25, 525, 70, 5, DARKGRAY);
                        }
                    } else {
                        if (IsMouseButtonReleased(0))
                        {
                            if (needColor) {
                                needColor = false;
                                sColor2 = WHITE;
                            }

                            displayColors = true;

                            DrawRectangle((GetScreenWidth () / 2) + 25, 455, 75, 75, BLACK);

                            if (!needColor) {
                                DrawRectangle((GetScreenWidth () / 2) + 35, 465, 55, 55, sColor1);
                            } else {
                                DrawRectangle((GetScreenWidth () / 2) + 35, 465, 55, 55, MAROON);
                            }
                        }
                        
                        if (!displayColors) {
                            if (IsMouseButtonDown(0))
                            {
                                DrawRectangle((GetScreenWidth () / 2) + 25, 455, 75, 75, BLACK);

                                if (!needColor) {
                                    DrawRectangle((GetScreenWidth () / 2) + 35, 465, 55, 55, sColor1);
                                } else {
                                    DrawRectangle((GetScreenWidth () / 2) + 35, 465, 55, 55, MAROON);
                                }
                            } else {
                                DrawRectangleRec(colorButton, BLACK);
                                
                                if (!needColor) {
                                    DrawRectangle((GetScreenWidth () / 2) + 30, 460, 55, 55, sColor1);
                                } else {
                                    DrawRectangle((GetScreenWidth () / 2) + 30, 460, 55, 55, MAROON);
                                }

                                DrawRectangle((GetScreenWidth () / 2) + 95, 455, 5, 75, DARKGRAY);
                                DrawRectangle((GetScreenWidth () / 2) + 25, 525, 70, 5, DARKGRAY);
                            }
                        }
                    }
                }

                textBoxName.setPos(new Rectangle(GetScreenWidth () / 2 + 20, 250, 375, 75));
                textBoxName.render();
                textBoxName.processTextInput();
                textBoxOwner.setPos(new Rectangle(GetScreenWidth () / 2 + 20, 350, 375, 75));
                textBoxOwner.render();
                textBoxOwner.processTextInput();

                Rectangle nextButton = new Rectangle((GetScreenWidth() / 2) - 105, ((GetScreenHeight() / 4) * 3) + 50, 200, 100);

                //Next button
                if (!CheckCollisionPointRec(GetMousePosition(), nextButton)) {
                    DrawRectangleRec(nextButton, BLACK);
                    DrawRectangle((GetScreenWidth() / 2) - 95, ((GetScreenHeight() / 4) * 3) + 60, 180, 80, LIGHTGRAY);
                    DrawRectangle((GetScreenWidth() / 2) - 100, ((GetScreenHeight() / 4) * 3) + 150, 195, 5, DARKGRAY);
                    DrawRectangle((GetScreenWidth() / 2) + 95, ((GetScreenHeight() / 4) * 3) + 55, 5, 100, DARKGRAY);
                    DrawText("Next", ((GetScreenWidth() / 2) - 5) - (MeasureText("Next", 60) / 2), ((GetScreenHeight() / 4) * 3) + 70, 60, BLACK);
                } else {
                    if (!IsMouseButtonDown(0)) {
                        DrawRectangle((GetScreenWidth() / 2) - 105, ((GetScreenHeight() / 4) * 3) + 50, 200, 100, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) - 95, ((GetScreenHeight() / 4) * 3) + 60, 180, 80, GRAY);
                        DrawRectangle((GetScreenWidth() / 2) - 100, ((GetScreenHeight() / 4) * 3) + 150, 195, 5, DARKGRAY);
                        DrawRectangle((GetScreenWidth() / 2) + 95, ((GetScreenHeight() / 4) * 3) + 55, 5, 100, DARKGRAY);
                        DrawText("Next", ((GetScreenWidth() / 2) - 5) - (MeasureText("Next", 60) / 2), ((GetScreenHeight() / 4) * 3) + 70, 60, BLACK);
                    } else {
                        DrawRectangle((GetScreenWidth() / 2) - 100, ((GetScreenHeight() / 4) * 3) + 55, 200, 100, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) - 90, ((GetScreenHeight() / 4) * 3) + 65, 180, 80, GRAY);
                        DrawText("Next", ((GetScreenWidth() / 2)) - (MeasureText("Next", 60) / 2), ((GetScreenHeight() / 4) * 3) + 75, 60, BLACK);
                    }
                
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
                            }

                            if (sColor1 == OFFWHITE) {
                                sColor2 = MAROON;
                                needColor = true;
                            }
                        }
                    }
                }
                
            } else if (layout.equals("createQuimbert2")) {
                BeginDrawing();
                ClearBackground(RAYWHITE);


                Rectangle doneButton = new Rectangle(GetScreenWidth() - 175, 20, 150, 80);

                //Create Quimbert button
                if (points < 1) {
                    if (!CheckCollisionPointRec(GetMousePosition(), doneButton)) {
                        DrawRectangleRec(doneButton, BLACK);
                        DrawRectangle(GetScreenWidth() - 165, 30, 130, 60, LIGHTGRAY);
                        DrawRectangle(GetScreenWidth() - 170, 100, 145, 5, DARKGRAY);
                        DrawRectangle(GetScreenWidth() - 25, 25, 5, 80, DARKGRAY);
                        DrawText("Done", (GetScreenWidth() - 85) - (MeasureText("Done", 60) / 2), 37, 48, BLACK);
                    } else {
                        if (!IsMouseButtonDown(0)) {
                            DrawRectangleRec(doneButton, BLACK);
                            DrawRectangle(GetScreenWidth() - 165, 30, 130, 60, GRAY);
                            DrawRectangle(GetScreenWidth() - 170, 100, 145, 5, DARKGRAY);
                            DrawRectangle(GetScreenWidth() - 25, 25, 5, 80, DARKGRAY);
                            DrawText("Done", (GetScreenWidth() - 85) - (MeasureText("Done", 60) / 2), 37, 48, BLACK);
                        } else {
                            DrawRectangle(GetScreenWidth() - 170, 25, 150, 80, BLACK);
                            DrawRectangle(GetScreenWidth() - 160, 35, 130, 60, GRAY);
                            DrawText("Done", (GetScreenWidth() - 80) - (MeasureText("Done", 60) / 2), 42, 48, BLACK);
                        }

                        if (IsMouseButtonReleased(0)) {
                            if (points == 0 && makingQuimbert + 1 <= quimbertQuantity) {
                                if (makingQuimbert + 1 <= quimbertQuantity) {
                                    quimberts.add(new Quimbert(a, b, c, d, e, f, g, h));
                                    quimberts.get(makingQuimbert).startingHealth = (randInt(3, 5) * quimberts.get(makingQuimbert).looks) / 2;
                                    quimberts.get(makingQuimbert).health = quimberts.get(makingQuimbert).startingHealth;

                                    if (quimberts.get(makingQuimbert).health < 1) {
                                        quimberts.get(makingQuimbert).health++;
                                        quimberts.get(makingQuimbert).startingHealth++;
                                    }

                                    sColor1 = OFFWHITE;
                                    sColor2 = WHITE;

                                    if (c == "Red") {
                                        color0Taken = true;
                                    } else if (c == "Orange") {
                                        color1Taken = true;
                                    } else if (c == "Yellow") {
                                        color2Taken = true;
                                    } else if (c == "Green") {
                                        color3Taken = true;
                                    } else if (c == "Light Blue") {
                                        color4Taken = true;
                                    } else if (c == "Blue") {
                                        color5Taken = true;
                                    } else if (c == "Purple") {
                                        color6Taken = true;
                                    } else if (c == "Black") {
                                        color7Taken = true;
                                    } else if (c == "Gray") {
                                        color8Taken = true;
                                    } else if (c == "Pink") {
                                        color9Taken = true;
                                    }

                                    a = 0; b = 0; d = 0; c = ""; e = 0; f = 0; g = ""; h = "";
                                    textBoxName.clear();
                                    textBoxOwner.clear();
                                    points = randInt(25, 35);
                                    if (makingQuimbert + 1 < quimbertQuantity) {
                                        layout = "createQuimbert";
                                    } else {
                                        break; // REMOVE: temporary, replace with ```layout = "fightLayout"``` or equivilent when implemented
                                    }
                                    makingQuimbert++;
                                }
                            }
                        }
                    }
                } else {
                    DrawRectangle(GetScreenWidth() - 170, 25, 150, 80, BLACK);
                    DrawRectangle(GetScreenWidth() - 160, 35, 130, 60, DARKGRAY);
                    DrawText("Done", (GetScreenWidth() - 80) - (MeasureText("Done", 60) / 2), 42, 48, BLACK);
                }

                Rectangle backButton = new Rectangle(20, 20, 120, 80);

                //back button
                if (!CheckCollisionPointRec(GetMousePosition(), backButton)) {
                    DrawRectangleRec(backButton, BLACK);
                    DrawRectangle(30, 30, 100, 60, LIGHTGRAY);
                    DrawLineEx(new Vector2().x(115).y(60), new Vector2().x(60).y(60), 15, BLACK);
                    DrawTriangle(new Vector2().x(45).y(60), new Vector2().x(70).y(80), new Vector2().x(70).y(40), BLACK);
                    DrawRectangle(140, 25, 5, 80, DARKGRAY);
                    DrawRectangle(25, 100, 115, 5, DARKGRAY);
                } else {
                    if (!IsMouseButtonDown(0)) {
                        DrawRectangle(20, 20, 120, 80, BLACK);
                        DrawRectangle(30, 30, 100, 60, GRAY);
                        DrawLineEx(new Vector2().x(115).y(60), new Vector2().x(60).y(60), 15, BLACK);
                        DrawTriangle(new Vector2().x(45).y(60), new Vector2().x(70).y(80), new Vector2().x(70).y(40), BLACK);
                        DrawRectangle(140, 25, 5, 80, DARKGRAY);
                        DrawRectangle(25, 100, 115, 5, DARKGRAY);
                    } else {
                        DrawRectangle(25, 25, 120, 80, BLACK);
                        DrawRectangle(35, 35, 100, 60, GRAY);
                        DrawLineEx(new Vector2().x(120).y(65), new Vector2().x(65).y(65), 15, BLACK);
                        DrawTriangle(new Vector2().x(50).y(65), new Vector2().x(75).y(85), new Vector2().x(75).y(45), BLACK);
                    }

                    if (IsMouseButtonReleased(0)) {
                        layout = "createQuimbert";
                    }    
                }



                int posx = 300;
                int posy = 175;


                // plus and minus buttons for a, / looks
                int aOld = a;
                DrawText("Looks: ", posx + 40 - (MeasureText("Looks: ", 72) / 2), posy - 55, 72, BLACK);
                a = drawPlus(new Rectangle(70 + posx, 40 + posy, 100, 100), posx, posy, (a > 9 || points < 1), a, 10, false);
                DrawText("" + a, posx + 18 - (MeasureText(Integer.toString(a), 72) / 2),  + posy + 55, 72, BLACK);
            
                    Rectangle infoCollider = new Rectangle(posx + 165, posy - 55, 64, 64);
                    
                    if (isEnabled) {
                        DrawTexture(infoButton3, posx + 165, posy - 55, WHITE);
                        
                        if (!CheckCollisionPointRec(GetMousePosition(), infoCollider) && IsMouseButtonReleased(0)) {
                            isEnabled = false;
                        }
            
                    } else {
                        if (!CheckCollisionPointRec(GetMousePosition(), infoCollider)) {
                            DrawTexture(infoButton1, posx + 165, posy - 55, WHITE);
                        } else {
                            DrawTexture(infoButton2, posx + 165, posy - 55, WHITE);
            
                            if (IsMouseButtonReleased(0)) {
                                isEnabled = true;
                            }
                        }
                    }

                posx -= 210;
                a = drawPlus(new Rectangle(70 + posx, 40 + posy, 100, 100), posx, posy, (a < 1), a, 0, true);
                posx += 210;
                posy += 300;

                if (a != aOld) {
                    points += aOld - a;
                }

                if (makeButtonText(posx - 40,  + posy - 150, 120, 65, "++", 72, (a > 9 || points < 1))) {
                    for (int i = 0; points > 0 && a < 10; i++) {
                        points--;
                        a++;
                    }
                }


                // d / personality
                int dOld = d;
                DrawText("Personality: ", posx + 40 - (MeasureText("Personality: ", 72) / 2),  + posy - 55, 72, BLACK);
                d = drawPlus(new Rectangle(70 + posx, 40 + posy, 100, 100), posx, posy, (d > 9 || points < 1), d, 10, false);
                DrawText("" + d, posx + 18 - (MeasureText(Integer.toString(d), 72) / 2),  + posy + 55, 72, BLACK);

                posx -= 210;
                d = drawPlus(new Rectangle(70 + posx, 40 + posy, 100, 100), posx, posy, (d < 1), d, 0, true);
                posx += 210;
                posy += 300;
                
                if (d != dOld) {
                    points += dOld - d;
                }

                if (makeButtonText(posx - 40,  + posy - 150, 120, 65, "++", 72, (d > 9 || points < 1))) {
                    for (int i = 0; points > 0 && d < 10; i++) {
                        points--;
                        d++;
                    }
                }
                
                // shift to right
                posx = GetScreenWidth() / 2;
                posy = 175;

                // b / smell
                int bOld = b;
                DrawText("Smell: ", posx + 52 - (MeasureText("Smell:  ", 72) / 2),  + posy - 55, 72, BLACK);
                b = drawPlus(new Rectangle(70 + posx, 40 + posy, 100, 100), posx, posy, (b > 9 || points < 1), b, 10, false);
                DrawText("" + b, posx + 18 - (MeasureText(Integer.toString(b), 72) / 2),  + posy + 55, 72, BLACK);

                posx -= 210;
                b = drawPlus(new Rectangle(70 + posx, 40 + posy, 100, 100), posx, posy, (b < 1), b, 0, true);
                posx += 210;
                posy += 300;
                if (b != bOld) {
                    points += bOld - b;
                }

                if (makeButtonText(posx - 40,  + posy - 150, 120, 65, "++", 72, (b > 9 || points < 1))) {
                    for (int i = 0; points > 0 && b < 10; i++) {
                        points--;
                        b++;
                    }
                }

                posx = GetScreenWidth() - 300;

                // e / gumption
                int eOld = e;
                DrawText("Gumption: ", posx + 52 - (MeasureText("Gumption:  ", 72) / 2),  + posy - 55, 72, BLACK);
                e = drawPlus(new Rectangle(70 + posx, 40 + posy, 100, 100), posx, posy, (e > 9 || points < 1), e, 10, false);
                DrawText("" + e, posx + 18 - (MeasureText(Integer.toString(e), 72) / 2),  + posy + 55, 72, BLACK);

                posx -= 210;
                e = drawPlus(new Rectangle(70 + posx, 40 + posy, 100, 100), posx, posy, (e < 1), e, 0, true);
                posx += 210;
                posy += 300;

                if (e != eOld) {
                    points += eOld - e;
                }

                if (makeButtonText(posx - 40,  + posy - 150, 120, 65, "++", 72, (e > 9 || points < 1))) {
                    for (int i = 0; points > 0 && e < 10; i++) {
                        points--;
                        e++;
                    }
                }

        
                // shift down
                posy = 175;

                
                // f / length
                int fOld = f;
                DrawText("Length: ", posx + 52 - (MeasureText("Length:  ", 72) / 2),  + posy - 55, 72, BLACK);
                f = drawPlus(new Rectangle(70 + posx, 40 + posy, 100, 100), posx, posy, (f > 9 || points < 1), f, 10, false);
                DrawText("" + f, posx + 18 - (MeasureText(Integer.toString(f), 72) / 2),  + posy + 55, 72, BLACK);

                posx -= 210;
                f = drawPlus(new Rectangle(70 + posx, 40 + posy, 100, 100), posx, posy, (f < 1), f, 0, true);
                posx += 210;
                posy += 300;

                if (f != fOld) {
                    points += fOld - f;
                }

                if (makeButtonText(posx - 40,  + posy - 150, 120, 65, "++", 72, (f > 9 || points < 1))) {
                    for (int i = 0; points > 0 && f < 10; i++) {
                        points--;
                        f++;
                    }
                }
                
                posx = GetScreenWidth() / 2;

                DrawText("Points: " + points, posx - (MeasureText("Points:  ", 72) / 2), 20, 72, BLACK);
                
            } else if (layout.equals("game")) {
                
            }

            EndDrawing();
        }

        UnloadMusicStream(blippy);   // Unload music stream buffers from RAM

        CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)
                

        CloseWindow();
        
        int currentQuimbert;
        boolean endTurn;
        
        for (currentQuimbert = 0; !gameEnd; currentQuimbert++)
        {
            if (removePlayer)
            {
                try
                {
                    if (currentQuimbert == 0)
                    {
                        quimberts.remove(quimberts.size() - 1);
                    }
                    else
                    {
                        quimberts.remove(currentQuimbert - 1);
                        currentQuimbert -= 1;
                    }
                }
                catch(Exception q)
                {
                    System.out.println("Error 2: .remove(currentQuimbert - 1)");
                }
                
                removePlayer = false;
            }
            
            if (currentQuimbert >= quimberts.size())
            {
                currentQuimbert = 0;
            }
            
            if (quimberts.size() < 2)
            {
                try
                {
                    System.out.println(newLine + quimberts.get(currentQuimbert).name + " has won the game!");
                    gameEnd = true;
                }
                catch(Exception q)
                {
                    System.out.println("Error 4: GameEnd");
                }
            }
            
            if (!gameEnd)
            {
            for (quimberts.get(currentQuimbert).turns += 1; quimberts.get(currentQuimbert).turns > 0; quimberts.get(currentQuimbert).turns--)
            {
                
                System.out.println(newLine + "It is now " + quimberts.get(currentQuimbert).name + "'s turn!");
                System.out.println(newLine + quimberts.get(currentQuimbert).name + ", what would you like to do? (type help for more info)" + 
                newLine);
                
                endTurn = false;
                
                while (!endTurn)
                {
                    choice = action.nextLine();
                    
                    if (choice.toLowerCase().equals("help"))
                    {
                        System.out.println(newLine + "Actions:" + newLine + newLine + "Doesn't take a turn:" + newLine + "Help" + 
                        newLine + "Inventory" + newLine + "Info" + newLine + "Stats" + newLine + "Health" + newLine + "Blocks" + 
                        newLine + newLine + "Takes a turn:" + newLine + "Sniff" + newLine + "Use" + newLine + "Attack" + newLine +
                        "Block" + newLine + "Invest" + newLine + "Skip" + newLine);
                                
                        System.out.println(newLine + "Pick another action.");
                    }
                    
                    if (choice.toLowerCase().equals("health") || choice.toLowerCase().equals("hp"))
                    {
                        for (int i = 0; i < quimberts.size(); i++)
                        {
                            quimberts.get(i).health();
                        }
                        
                        System.out.println(newLine + "Pick another action.");
                    }
                    
                    if (choice.toLowerCase().equals("blocks"))
                    {
                        for (int i = 0; i < quimberts.size(); i++)
                        {
                            System.out.println(newLine + quimberts.get(i).name + " has " + quimberts.get(i).blocks + " blocks.");
                        }
                    }
                
                    if (choice.toLowerCase().equals("inventory") || choice.toLowerCase().equals("inv"))
                    {
                        for (int i = 0; i < quimberts.size(); i++)
                        {
                            quimberts.get(i).inventory();
                        }
                        
                        System.out.println(newLine + "Pick another action.");
                    }
                    
                    if (choice.toLowerCase().equals("stats"))
                    {
                        quimberts.get(currentQuimbert).stats();
                        
                        System.out.println(newLine + "Pick another action.");
                    }
                    
                    if (choice.toLowerCase().equals("info"))
                    {
                        System.out.println(newLine + "What item would like to learn more about? (Type list for more info)");
                        choice = action.nextLine();
                        
                        if (choice.toLowerCase().equals("list"))
                        {
                            System.out.println(newLine + "Black Truffle" + newLine + "White Truffle" + newLine + "Mushroom" + 
                            newLine + "Twig" + newLine + "Rock" + newLine + "Unidentified Piece of Flesh" + newLine + 
                            "Carrot" + newLine + "Knife" + newLine + "AK47" + newLine + "Bazooka" + newLine + "Turnip" + 
                            newLine + "Yellow Flower" + newLine + "Green Flower" + newLine + "Purple Flower" + newLine + 
                            "Orange Flower" + newLine + "Red Flower");
                            System.out.println(newLine + "Which would like to learn more about?");
                        }
                        else if (choice.toLowerCase().equals("inventory") || choice.toLowerCase().equals("inv"))
                        {
                            quimberts.get(currentQuimbert).inventory();
                        }
                        else
                        {
                            quimberts.get(currentQuimbert).info(choice);
                        }
                        
                        System.out.println(newLine + "Pick another action.");
                    }
                    
                    if (choice.toLowerCase().equals("sniff"))
                    {
                        tempS = quimberts.get(currentQuimbert).sniff();
                        
                        if (tempS.equals("fail"))
                        {
                            System.out.println(newLine + quimberts.get(currentQuimbert).name + " failed to sniff. :'(" + newLine);
                            
                            endTurn = true;
                        }
                        else
                        {
                            quimberts.get(currentQuimbert).inv.add(tempS);
                            
                            System.out.println(newLine + quimberts.get(currentQuimbert).name + 
                            " successfully sniffed and found a " + tempS + "!" + newLine);
                            
                            if (quimberts.get(currentQuimbert).smell == 10 && randInt(1, 4) == 4)
                            {
                                tempS = quimberts.get(currentQuimbert).sniff();
                                
                                if (!tempS.equals("fail"))
                                {
                                    quimberts.get(currentQuimbert).inv.add(tempS);
                                    
                                    System.out.println(newLine + quimberts.get(currentQuimbert).name + 
                                    "'s sniffing was so exquisite that they also found a " + tempS + "!" + newLine);
                                }
                            }
                            
                            endTurn = true;
                        }
                    }
                    
                    if (choice.toLowerCase().equals("skip"))
                    {
                        endTurn = true;
                        System.out.println(newLine + quimberts.get(currentQuimbert).name + " has skipped their turn.");
                    }
                    
                    if (choice.toLowerCase().equals("use") || choice.toLowerCase().equals("use "))
                    {
                        System.out.println(newLine + "What item would you like to use? (type inventory to view inventory)");
                        
                        tempB = false;
                        while (!tempB)
                        {
                            System.out.println(newLine + "What item would you like to use?");
                            choice = action.nextLine();
                            
                            if (quimberts.get(currentQuimbert).inv.contains(choice.toLowerCase()))
                            {
                                tempB = true;
                            }
                            else if (choice.toLowerCase().equals("inventory") || choice.toLowerCase().equals("inv"))
                            {
                                quimberts.get(currentQuimbert).inventory();
                            }
                            else if (choice.toLowerCase().equals("skip"))
                            {
                                tempB = true;
                            }
                            else
                            {
                                System.out.println(newLine + "You do not have a " + choice + " in you inventory.");
                            }
                        }
                        
                        if (quimberts.get(currentQuimbert).gumption == 10 && randInt(1, 4) == 4)
                        {
                            gumptionSigma = true;
                        }
                        
                        tempS = choice;
                        endAttack = false;
                        while (!endAttack)
                        {
                        endAttack = true;
                        quimberts.get(currentQuimbert).use(tempS);
                        
                        if (quimberts.get(currentQuimbert).health < 1)
                        {
                            if (quimberts.get(currentQuimbert).lives < 2)
                            {
                                System.out.println(newLine + quimberts.get(currentQuimbert).name + " has died.");
                                
                                removePlayer = true;
                                quimberts.get(currentQuimbert).turns = 1;
                            }
                            else
                            {
                                quimberts.get(currentQuimbert).lives -= 1;
                                quimberts.get(currentQuimbert).health = quimberts.get(currentQuimbert).startingHealth;
                                System.out.println(newLine + quimberts.get(currentQuimbert).name + 
                                " lost a life. They now have " + quimberts.get(currentQuimbert).lives + " lives remaining");
                            }
                        }
                                
                        if (quimberts.get(currentQuimbert).toDeal > 0)
                        {
                            System.out.println(newLine + "Pick a player to use your " + choice + " on.");
                            
                            for (int i = 0; i < quimberts.size(); i++)
                            {
                                System.out.println(quimberts.get(i).name + ": " + quimberts.get(i).health + "/" + quimberts.get(i).startingHealth);
                            }
                            
                            System.out.println();
                            choice = action.nextLine();     
                            
                            for (int i = 0; i < quimberts.size(); i++)
                            {
                                if (choice.toLowerCase().equals(quimberts.get(i).name.toLowerCase()) && quimberts.get(i).blocks > 0)
                                {
                                    quimberts.get(i).blocks -= 1;
                                    System.out.println(newLine + quimberts.get(i).name + " blocked the attack. They now have " + 
                                    quimberts.get(i).blocks + " blocks remaining");
                                }
                                else if (choice.toLowerCase().equals(quimberts.get(i).name.toLowerCase()) && quimberts.get(i).blocks < 1)
                                {
                                    System.out.println(newLine + "Dealt " + quimberts.get(currentQuimbert).toDeal + 
                                    " damage to " + quimberts.get(i).name + "!");
                                    if (quimberts.get(i).looks == 10)
                                    {
                                        protection = randInt(0, 3);
                                        quimberts.get(currentQuimbert).toDeal -= protection;
                                        if (quimberts.get(currentQuimbert).toDeal < 0)
                                        {
                                            quimberts.get(currentQuimbert).toDeal = 0;
                                        }
                                    }
                                    
                                    if (protection > 0)
                                    {
                                        System.out.println(newLine + quimberts.get(currentQuimbert).name + " was too distracted by " +
                                        quimberts.get(i).name + "'s look and dealt " + protection + " less damage.");
                                    }
                                    protection = 0;
                                    quimberts.get(i).health -= quimberts.get(currentQuimbert).toDeal;
                                    System.out.println(quimberts.get(i).name + "'s health is now " + quimberts.get(i).health + "/" + quimberts.get(i).startingHealth);
                                    
                                    if (quimberts.get(i).health < 1)
                                    {
                                        if (quimberts.get(i).lives < 2)
                                        {
                                            System.out.println(quimberts.get(i).name + " has been killed by " + 
                                            quimberts.get(currentQuimbert).name + ".");
                                            
                                            if (quimberts.get(i) != quimberts.get(currentQuimbert))
                                            {
                                                try
                                                {
                                                    quimberts.remove(i);
                                                    
                                                    if (i < currentQuimbert)
                                                    {
                                                        currentQuimbert -= 1;
                                                    }
                                                }
                                                catch(Exception q)
                                                {
                                                    System.out.println("Error 2: .remove(i)");
                                                }
                                            }
                                            else if (quimberts.get(i) == quimberts.get(currentQuimbert))
                                            {
                                                removePlayer = true;
                                                quimberts.get(currentQuimbert).turns = 1;
                                            }
                                        }
                                        else
                                        {
                                            quimberts.get(i).lives -= 1;
                                            quimberts.get(i).health = quimberts.get(i).startingHealth;
                                            System.out.println(newLine + quimberts.get(i).name + " lost a life to " + 
                                            quimberts.get(i).name + ". They now have " + quimberts.get(i).lives + " lives remaining");
                                        }
                                    }
                                }
                            }
                            
                            try 
                            {
                                quimberts.get(currentQuimbert).toDeal = 0;
                            }
                            catch(Exception q)
                            {
                                System.out.println("Error 1: toDeal = 0");
                            }
                            
                            if (gumptionSigma && !attacked)
                            {
                                try
                                {
                                    endAttack = false;
                                    attacked = true;
                                    System.out.println(newLine + quimberts.get(currentQuimbert).name  + 
                                    " is the gumption sigma and gets to use another " + tempS + ".");
                                }
                                catch(Exception q)
                                {
                                    
                                }
                            }
                        }
                        }
                        attacked = false;
                        endAttack = false;
                        endTurn = true;
                    }
                    
                    if (choice.toLowerCase().equals("block"))
                    {
                        quimberts.get(currentQuimbert).block();
                        
                        endTurn = true;
                    }
                    
                    double damage;
                    
                    if (choice.toLowerCase().equals("attack") || choice.toLowerCase().equals("fight") || 
                    choice.toLowerCase().equals("sexually assualt") || choice.toLowerCase().equals("attack ") || 
                    choice.toLowerCase().equals("fight ") ||  choice.toLowerCase().equals("sexually assualt "))
                    {
                        damage = (((double) (quimberts.get(currentQuimbert).length * 2) + randInt(-10, 30)) / 10.0);
                        quimberts.get(currentQuimbert).toDeal = (int) (damage + 0.5);
                        
                        if (quimberts.get(currentQuimbert).toDeal < 0)
                        {
                            quimberts.get(currentQuimbert).toDeal = 0;
                        }
                        
                        System.out.println(newLine + "Which Quimbert would you like to attack?");
                        
                        endAttack = false;
                        while (!endAttack)
                        {
                        endAttack = true;
                        for (int i = 0; i < quimberts.size(); i++)
                        {
                            System.out.println(quimberts.get(i).name + ": " + quimberts.get(i).health + "/" + quimberts.get(i).startingHealth);
                        }
                        
                        System.out.println();
                        choice = action.nextLine();
                    
                        for (int i = 0; i < quimberts.size(); i++)
                        {
                            if (choice.toLowerCase().equals(quimberts.get(i).name.toLowerCase()) && quimberts.get(i).blocks > 0)
                            {
                                quimberts.get(i).blocks -= 1;
                                System.out.println(newLine + quimberts.get(i).name + " blocked the attack. They now have " + 
                                quimberts.get(i).blocks + " blocks remaining");
                            }
                            else if (choice.toLowerCase().equals(quimberts.get(i).name.toLowerCase()) && quimberts.get(i).blocks < 1)
                            {
                                System.out.println(newLine + "Dealt " + quimberts.get(currentQuimbert).toDeal + 
                                " damage to " + quimberts.get(i).name + "!");
                                if (quimberts.get(i).looks == 10)
                                {
                                    protection = randInt(0, 3);
                                    quimberts.get(currentQuimbert).toDeal -= protection;
                                    if (quimberts.get(currentQuimbert).toDeal < 0)
                                    {
                                        quimberts.get(currentQuimbert).toDeal = 0;
                                    }
                                }
                                
                                if (protection > 0)
                                {
                                    System.out.println(newLine + quimberts.get(currentQuimbert).name + " was too distracted by " +
                                    quimberts.get(i).name + "'s look and dealt " + protection + " less damage.");
                                }
                                protection = 0;
                                quimberts.get(i).health -= quimberts.get(currentQuimbert).toDeal;
                                System.out.println(quimberts.get(i).name + "'s health is now " + quimberts.get(i).health + "/" + quimberts.get(i).startingHealth);
                                
                                if (quimberts.get(i).health < 1)
                                {
                                    if (quimberts.get(i).lives < 2)
                                    {
                                        System.out.println(quimberts.get(i).name + " has been killed by " + 
                                        quimberts.get(currentQuimbert).name + ".");
                                        
                                        if (quimberts.get(i) != quimberts.get(currentQuimbert))
                                        {
                                            try
                                            {
                                                quimberts.remove(i);
                                                
                                                if (i < currentQuimbert)
                                                {
                                                    currentQuimbert -= 1;
                                                }
                                            }
                                            catch(Exception q)
                                            {
                                                System.out.println("Error 2: .remove(i)");
                                            }
                                        }
                                        else if (quimberts.get(i) == quimberts.get(currentQuimbert))
                                        {
                                            removePlayer = true;
                                            quimberts.get(currentQuimbert).turns = 1;
                                        }
                                    }
                                    else
                                    {
                                        quimberts.get(i).lives -= 1;
                                        quimberts.get(i).health = quimberts.get(i).startingHealth;
                                        System.out.println(newLine + quimberts.get(i).name + " lost a life to " + 
                                        quimberts.get(i).name + ". They now have " + quimberts.get(i).lives + " lives remaining");
                                    }
                                }
                            }
                        }
                        try 
                        {
                            quimberts.get(currentQuimbert).toDeal = 0;
                        }
                        catch(Exception q)
                        {
                            System.out.println("Error 1: toDeal = 0");
                        }
                        
                        
                        try
                        {
                            if (quimberts.get(currentQuimbert).length == 10 && randInt(1, 4) == 4 && !attacked)
                            {
                                endAttack = false;
                                attacked = true;
                                
                                damage = (((double) (quimberts.get(currentQuimbert).length * 2) + randInt(-10, 30)) / 10.0);
                                quimberts.get(currentQuimbert).toDeal = (int) (damage + 0.5);
                        
                                if (quimberts.get(currentQuimbert).toDeal < 0)
                                {
                                    quimberts.get(currentQuimbert).toDeal = 0;
                                }
                                
                                System.out.println(newLine + quimberts.get(currentQuimbert).name + 
                                " is so long that they get to attack again. Pick another quimbert to attack.");
                            }
                        }
                        catch(Exception q)
                        {
                            
                        }
                        }
                        attacked = false;
                        endAttack = false;
                        endTurn = true;
                    }
                    
                }
            }
            }
        }
        action.close();
    }
}
