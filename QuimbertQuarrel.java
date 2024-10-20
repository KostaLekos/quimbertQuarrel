import java.util.Scanner;
import java.util.Random;
import java.util.ArrayList;
import static com.raylib.Jaylib.*;

/*
 * git pull
 * 
 * git add <changed files>
 * git commit -m "message"
 * git push --set-upstream origin main
 */


/*
compile it: cmd +
"E:\Actually Useful\NonZips\java\jdk-21.0.4+7\bin\javac.exe" -cp .\jaylib-5.0.0-0.jar .\QuimbertQuarrel.java .\Quimbert.java
run it: cmd +
"E:\Actually Useful\NonZips\java\jdk-21.0.4+7\bin\java.exe" -cp jaylib-5.0.0-0.jar;. QuimbertQuarrel
*/
public class QuimbertQuarrel
{
    private static int randInt(int min, int max) 
    {
        Random rand = new Random();
        int randomNum = rand.nextInt((max - min) + 1) + min;

        return randomNum;
    }

    public String sniff(Quimbert currentQuimbert)
    {
        String itemFound;
        String toReturn;
        itemFound = currentQuimbert.sniff();
        if (itemFound.equals("fail"))
        {
            toReturn = "fail";
        }
        else
        {
            currentQuimbert.inv.add(itemFound);
            toReturn = itemFound;
            if (currentQuimbert.smell == 10 && randInt(0, 3) == 3)
            {
                itemFound = currentQuimbert.sniff();
                if (!itemFound.equals("fail"))
                {
                    currentQuimbert.inv.add(itemFound);
                    toReturn = toReturn.concat("+" + itemFound);
                }
                else
                {
                    toReturn = toReturn.concat("+" + "fail");
                }
            }
            else
            {
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

    boolean IsAnyKeyPressed()
    {
        boolean keyPressed = false;
        int key = GetKeyPressed();
        
        if ((key >= 32) && (key <= 126))
        {
            keyPressed = true;
        }

        return keyPressed;
    }
    
    public static void main(String[] args)
    {
        Scanner action = new Scanner(System.in);
        String choice;
        int quimbertQuantity = 2;
        String newLine = System.getProperty("line.separator");
        int a = 0;
        int b = 0;
        String c;
        int d = 0;
        int e = 0;
        int f = 0;
        String g;
        String h;
        int points;
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
        //final int MAX_INPUT_CHARS = 25;

        // char[] name = new char[MAX_INPUT_CHARS + 1];
        //String name = "";

        int framesCounter = 0;
        boolean isTextBoxName = false;

        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);

        InitWindow(1840, 1000, "Quimbert Quarrel");
        SetWindowMinSize(600, 500); 
        SetWindowMaxSize(mWidth, mHeight);
        SetWindowPosition(40, 70);
        MaximizeWindow();
        SetTargetFPS(60);
        Camera2D camera = new Camera2D()
                .target(new Vector2());


        QuimbertTextBox textBoxName = new QuimbertTextBox (new Rectangle(GetScreenWidth () / 2 + 20, 250, 375, 75));
        textBoxName.setCharLength(25);

        QuimbertTextBox textBoxOwner = new QuimbertTextBox (new Rectangle(GetScreenWidth () / 2 + 20, 350, 375, 75));
        textBoxOwner.setCharLength(25);

        
        while (!WindowShouldClose())
        {
            
            if (layout.equals("start"))
            {
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Quimbert Quarrel", (GetScreenWidth() / 2) - (MeasureText("Quimbert Quarrel", 96) / 2), (GetScreenHeight() / 4), 96, BLACK);
                DrawText("A Green Apple Game", (GetScreenWidth() / 2) - (MeasureText("A Green Apple Game", 36) / 2), (GetScreenHeight() / 4 + 100), 36, BLACK);
                
                Rectangle localButton = new Rectangle((GetScreenWidth() / 2) - 155, GetScreenHeight() / 2, 300, 150);

                //local button
                if (!CheckCollisionPointRec(GetMousePosition(), localButton))
                {
                    DrawRectangleRec(localButton, BLACK);
                    DrawRectangle((GetScreenWidth() / 2) - 145, (GetScreenHeight() / 2) + 10, 280, 130, LIGHTGRAY);
                    DrawRectangle((GetScreenWidth() / 2) + 145, (GetScreenHeight() / 2) + 5, 5, 150, DARKGRAY);
                    DrawRectangle((GetScreenWidth() / 2) - 150, (GetScreenHeight() / 2) + 150, 295, 5, DARKGRAY);
                    DrawText("Local", ((GetScreenWidth() / 2) - 5) - (MeasureText("Local", 80) / 2), (GetScreenHeight() / 2) + 37, 80, BLACK);
                }
                else
                {
                    if (!IsMouseButtonDown(0))
                    {
                        DrawRectangle((GetScreenWidth() / 2) - 155, GetScreenHeight() / 2, 300, 150, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) - 145, (GetScreenHeight() / 2) + 10, 280, 130, GRAY);
                        DrawRectangle((GetScreenWidth() / 2) + 145, (GetScreenHeight() / 2) + 5, 5, 150, DARKGRAY);
                        DrawRectangle((GetScreenWidth() / 2) - 150, (GetScreenHeight() / 2) + 150, 295, 5, DARKGRAY);
                        DrawText("Local", ((GetScreenWidth() / 2) - 5) - (MeasureText("Local", 80) / 2), (GetScreenHeight() / 2) + 37, 80, BLACK);
                    }
                    else
                    {
                        DrawRectangle((GetScreenWidth() / 2) - 150, (GetScreenHeight() / 2) + 5, 300, 150, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) - 140, (GetScreenHeight() / 2) + 15, 280, 130, GRAY);
                        DrawText("Local", ((GetScreenWidth() / 2)) - (MeasureText("Local", 80) / 2), (GetScreenHeight() / 2) + 42, 80, BLACK);
                    }

                    if (IsMouseButtonReleased(0))
                    {
                        EndDrawing();
                        layout = "howManyQ";
                    }
                }
                DrawFPS(20, 20);
            }
            else if (layout.equals("howManyQ"))
            {
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("How many Quimberts are", (GetScreenWidth() / 2) - (MeasureText("How many Quimberts are", 72) / 2), (GetScreenHeight() / 4), 72, BLACK);
                DrawText("you playing with?", (GetScreenWidth() / 2) - (MeasureText("you playing with?", 72) / 2), (GetScreenHeight() / 4) + 75, 72, BLACK);

                DrawRectangle((GetScreenWidth() / 2) - 60, (GetScreenHeight() / 2) + 20, 120, 150, BLACK);
                DrawRectangle((GetScreenWidth() / 2) - 50, (GetScreenHeight() / 2) + 30, 100, 130, LIGHTGRAY);
                DrawText(Integer.toString(quimbertQuantity), (GetScreenWidth() / 2) - (MeasureText(Integer.toString(quimbertQuantity), 108) / 2), (GetScreenHeight() / 2) + 45, 108, BLACK);
                
                Rectangle backButton = new Rectangle(25, 25, 120, 80);

                //back button
                if (!CheckCollisionPointRec(GetMousePosition(), backButton))
                {
                    DrawRectangleRec(backButton, BLACK);
                    DrawRectangle(35, 35, 100, 60, LIGHTGRAY);
                    DrawLineEx(new Vector2().x(120).y(65), new Vector2().x(65).y(65), 15, BLACK);
                    DrawTriangle(new Vector2().x(50).y(65), new Vector2().x(75).y(85), new Vector2().x(75).y(45), BLACK);
                    DrawRectangle(145, 30, 5, 80, DARKGRAY);
                    DrawRectangle(30, 105, 115, 5, DARKGRAY);
                }
                else    
                {
                    if (!IsMouseButtonDown(0))
                    {
                        DrawRectangle(25, 25, 120, 80, BLACK);
                        DrawRectangle(35, 35, 100, 60, GRAY);
                        DrawLineEx(new Vector2().x(120).y(65), new Vector2().x(65).y(65), 15, BLACK);
                        DrawTriangle(new Vector2().x(50).y(65), new Vector2().x(75).y(85), new Vector2().x(75).y(45), BLACK);
                        DrawRectangle(145, 30, 5, 80, DARKGRAY);
                        DrawRectangle(30, 105, 115, 5, DARKGRAY);
                    }
                    else
                    {
                        DrawRectangle(30, 30, 120, 80, BLACK);
                        DrawRectangle(40, 40, 100, 60, GRAY);
                        DrawLineEx(new Vector2().x(125).y(70), new Vector2().x(70).y(70), 15, BLACK);
                        DrawTriangle(new Vector2().x(55).y(70), new Vector2().x(80).y(90), new Vector2().x(80).y(50), BLACK);
                    }

                    if (IsMouseButtonReleased(0))
                    {
                        layout = "start";
                    }
                }

                Rectangle okayButton = new Rectangle((GetScreenWidth() / 2) - 105, ((GetScreenHeight() / 4) * 3) + 50, 200, 100);

                //okay button
                if (!CheckCollisionPointRec(GetMousePosition(), okayButton))
                {
                    DrawRectangleRec(okayButton, BLACK);
                    DrawRectangle((GetScreenWidth() / 2) - 95, ((GetScreenHeight() / 4) * 3) + 60, 180, 80, LIGHTGRAY);
                    DrawRectangle((GetScreenWidth() / 2) - 100, ((GetScreenHeight() / 4) * 3) + 150, 195, 5, DARKGRAY);
                    DrawRectangle((GetScreenWidth() / 2) + 95, ((GetScreenHeight() / 4) * 3) + 55, 5, 100, DARKGRAY);
                    DrawText("Okay", ((GetScreenWidth() / 2) - 5) - (MeasureText("Okay", 60) / 2), ((GetScreenHeight() / 4) * 3) + 70, 60, BLACK);
                }
                else
                {
                    if (!IsMouseButtonDown(0))
                    {
                        DrawRectangle((GetScreenWidth() / 2) - 105, ((GetScreenHeight() / 4) * 3) + 50, 200, 100, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) - 95, ((GetScreenHeight() / 4) * 3) + 60, 180, 80, GRAY);
                        DrawRectangle((GetScreenWidth() / 2) - 100, ((GetScreenHeight() / 4) * 3) + 150, 195, 5, DARKGRAY);
                        DrawRectangle((GetScreenWidth() / 2) + 95, ((GetScreenHeight() / 4) * 3) + 55, 5, 100, DARKGRAY);
                        DrawText("Okay", ((GetScreenWidth() / 2) - 5) - (MeasureText("Okay", 60) / 2), ((GetScreenHeight() / 4) * 3) + 70, 60, BLACK);
                    }
                    else
                    {
                        DrawRectangle((GetScreenWidth() / 2) - 100, ((GetScreenHeight() / 4) * 3) + 55, 200, 100, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) - 90, ((GetScreenHeight() / 4) * 3) + 65, 180, 80, GRAY);
                        DrawText("Okay", ((GetScreenWidth() / 2)) - (MeasureText("Okay", 60) / 2), ((GetScreenHeight() / 4) * 3) + 75, 60, BLACK);
                    }

                    if (IsMouseButtonReleased(0))
                    {
                        layout = "createQuimbert";
                    }
                }

                Rectangle plusButton = new Rectangle((GetScreenWidth() / 2) + 70, (GetScreenHeight() / 2) + 40, 100, 100);

                //plus button
                if (quimbertQuantity < 8)
                {
                    if(!CheckCollisionPointRec(GetMousePosition(), plusButton))
                    {
                        DrawRectangleRec(plusButton, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) + 80, (GetScreenHeight() / 2) + 50, 80, 80, LIGHTGRAY);
                        DrawRectangle((GetScreenWidth() / 2) + 115, (GetScreenHeight() / 2) + 65, 10, 50, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) + 95, (GetScreenHeight() / 2) + 85, 50, 10, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) + 75, (GetScreenHeight() / 2) + 140, 95, 5, DARKGRAY);
                        DrawRectangle((GetScreenWidth() / 2) + 170, (GetScreenHeight() / 2) + 45, 5, 100, DARKGRAY); 
                    }
                    else
                    {
                        if (IsMouseButtonReleased(0))
                        {
                            quimbertQuantity += 1;

                            if (quimbertQuantity > 7)
                            {
                                DrawRectangle((GetScreenWidth() / 2) + 75, (GetScreenHeight() / 2) + 45, 100, 100, BLACK);
                                DrawRectangle((GetScreenWidth() / 2) + 85, (GetScreenHeight() / 2) + 55, 80, 80, DARKGRAY);
                                DrawRectangle((GetScreenWidth() / 2) + 120, (GetScreenHeight() / 2) + 70, 10, 50, BLACK);
                                DrawRectangle((GetScreenWidth() / 2) + 100, (GetScreenHeight() / 2) + 90, 50, 10, BLACK);
                            }
                        }

                        if (IsMouseButtonDown(0))
                        {
                            DrawRectangle((GetScreenWidth() / 2) + 75, (GetScreenHeight() / 2) + 45, 100, 100, BLACK);
                            DrawRectangle((GetScreenWidth() / 2) + 85, (GetScreenHeight() / 2) + 55, 80, 80, GRAY);
                            DrawRectangle((GetScreenWidth() / 2) + 120, (GetScreenHeight() / 2) + 70, 10, 50, BLACK);
                            DrawRectangle((GetScreenWidth() / 2) + 100, (GetScreenHeight() / 2) + 90, 50, 10, BLACK);
                        }
                        else if (quimbertQuantity < 8)
                        {
                            DrawRectangle((GetScreenWidth() / 2) + 70, (GetScreenHeight() / 2) + 40, 100, 100, BLACK);
                            DrawRectangle((GetScreenWidth() / 2) + 80, (GetScreenHeight() / 2) + 50, 80, 80, GRAY);
                            DrawRectangle((GetScreenWidth() / 2) + 115, (GetScreenHeight() / 2) + 65, 10, 50, BLACK);
                            DrawRectangle((GetScreenWidth() / 2) + 95, (GetScreenHeight() / 2) + 85, 50, 10, BLACK);
                            DrawRectangle((GetScreenWidth() / 2) + 75, (GetScreenHeight() / 2) + 140, 95, 5, DARKGRAY);
                            DrawRectangle((GetScreenWidth() / 2) + 170, (GetScreenHeight() / 2) + 45, 5, 100, DARKGRAY);
                        }
                    }
                }
                else
                {
                    DrawRectangle((GetScreenWidth() / 2) + 75, (GetScreenHeight() / 2) + 45, 100, 100, BLACK);
                    DrawRectangle((GetScreenWidth() / 2) + 85, (GetScreenHeight() / 2) + 55, 80, 80, DARKGRAY);
                    DrawRectangle((GetScreenWidth() / 2) + 120, (GetScreenHeight() / 2) + 70, 10, 50, BLACK);
                    DrawRectangle((GetScreenWidth() / 2) + 100, (GetScreenHeight() / 2) + 90, 50, 10, BLACK);
                }

                Rectangle minusButton = new Rectangle((GetScreenWidth() / 2) - 175, (GetScreenHeight() / 2) + 40, 100, 100);

                //minus button
                if (quimbertQuantity > 2)
                {
                    if(!CheckCollisionPointRec(GetMousePosition(), minusButton))
                    {
                        DrawRectangleRec(minusButton, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) - 165, (GetScreenHeight() / 2) + 50, 80, 80, LIGHTGRAY);
                        DrawRectangle((GetScreenWidth() / 2) - 150, (GetScreenHeight() / 2) + 85, 50, 10, BLACK);
                        DrawRectangle((GetScreenWidth() / 2) - 170, (GetScreenHeight() / 2) + 140, 95, 5, DARKGRAY);
                        DrawRectangle((GetScreenWidth() / 2) - 75, (GetScreenHeight() / 2) + 45, 5, 100, DARKGRAY);
                    }
                    else
                    {
                        if (IsMouseButtonReleased(0))
                        {
                            quimbertQuantity -= 1;

                            if (quimbertQuantity < 3)
                            {
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
            }
            else if (layout.equals("createQuimbert"))
            {
                BeginDrawing();
                ClearBackground(RAYWHITE);

                Rectangle backButton = new Rectangle(25, 25, 120, 80);

                //back button
                if (!CheckCollisionPointRec(GetMousePosition(), backButton))
                {
                    DrawRectangleRec(backButton, BLACK);
                    DrawRectangle(35, 35, 100, 60, LIGHTGRAY);
                    DrawLineEx(new Vector2().x(120).y(65), new Vector2().x(65).y(65), 15, BLACK);
                    DrawTriangle(new Vector2().x(50).y(65), new Vector2().x(75).y(85), new Vector2().x(75).y(45), BLACK);
                    DrawRectangle(145, 30, 5, 80, DARKGRAY);
                    DrawRectangle(30, 105, 115, 5, DARKGRAY);
                }
                else
                {
                    if (!IsMouseButtonDown(0))
                    {
                        DrawRectangle(25, 25, 120, 80, BLACK);
                        DrawRectangle(35, 35, 100, 60, GRAY);
                        DrawLineEx(new Vector2().x(120).y(65), new Vector2().x(65).y(65), 15, BLACK);
                        DrawTriangle(new Vector2().x(50).y(65), new Vector2().x(75).y(85), new Vector2().x(75).y(45), BLACK);
                        DrawRectangle(145, 30, 5, 80, DARKGRAY);
                        DrawRectangle(30, 105, 115, 5, DARKGRAY);
                    }
                    else
                    {
                        DrawRectangle(30, 30, 120, 80, BLACK);
                        DrawRectangle(40, 40, 100, 60, GRAY);
                        DrawLineEx(new Vector2().x(125).y(70), new Vector2().x(70).y(70), 15, BLACK);
                        DrawTriangle(new Vector2().x(55).y(70), new Vector2().x(80).y(90), new Vector2().x(80).y(50), BLACK);
                    }

                    if (IsMouseButtonReleased(0))
                    {
                        layout = "howManyQ";
                    }    
                }    
                
                

                for (int i = 0; i < quimbertQuantity; i++)
                {
                    madeQuimbert = false;
                    points = randInt(25, 35);

                    //while (!madeQuimbert)
                    //{
                        DrawText(("Quimbert #" + (i + 1)), (GetScreenWidth() / 2) - (MeasureText("Quimbert #1", 96) / 2), 20, 96, BLACK);
                        DrawText(("Make your Quimbert"), (GetScreenWidth() / 2) - (MeasureText("Make your Quimbert", 96) / 2), 120, 96, BLACK);

                        DrawText("Name:", ((GetScreenWidth() / 2) - MeasureText("Name:", 72)) - 30, 250, 72, BLACK);
                        DrawText("Owner:", ((GetScreenWidth() / 2) - MeasureText("Owner:", 72)) - 30, 340, 72, BLACK);
                        DrawText("Color:", ((GetScreenWidth() / 2) - MeasureText("Color:", 72)) - 30, 430, 72, BLACK);


                        Rectangle colorButton = new Rectangle ((GetScreenWidth () / 2) + 20, 430, 75, 75);

                        //Rectangle();
                        //Rectangle();

                        textBoxName.render();
                        textBoxName.processTextInput();
                        textBoxOwner.render();
                        textBoxOwner.processTextInput();


                        // System.out.println(textBoxName.getText());
                        // System.out.println(textBoxOwner.getText());

                        // DrawRectangleRec(textBoxName, BLACK);
                        // DrawRectangleRec(textBoxOwner, BLACK); // Migrate to QuimbertTextBox
                        DrawRectangleRec(colorButton, BLACK);
                        
                        // DrawRectangle((GetScreenWidth() / 2) + 30, 260, 355, 55, LIGHTGRAY);
                        // DrawRectangle((GetScreenWidth() / 2) + 30, 350, 355, 55, LIGHTGRAY);
                        // DrawRectangle((GetScreenWidth() / 2) + 30, 440, 55, 55, WHITE); // ???

                        // if (CheckCollisionPointRec(GetMousePosition(), textBoxName))
                        // {
                        //     isTextBoxName = true;
                        // }
                        // else
                        // {
                        //     isTextBoxName = false;
                        // }

                        if (isTextBoxName)
                        {
                            // DrawRectangleLines((int)textBoxName.x(), (int)textBoxName.y(), (int)textBoxName.width(), (int)textBoxName.height(), RED);
                            // SetMouseCursor(MOUSE_CURSOR_IBEAM);

                            // int key = GetCharPressed();

                            // while (key > 0) {
                            //     if (key >= 32 && key <= 125 && (name.length() < MAX_INPUT_CHARS)) {
                            //         name = new String(name + (char)key);
                            //     }

                            // }
                    
                            
                            
                            // if (IsKeyPressed(KEY_BACKSPACE))
                            // {
                            //     if (name.length() <= 1) {
                            //         name = new String("");
                            //     } else {
                            //         name = new String(name.substring(0, name.length() - 2));
                            //     }
                            // }

                            // if (name.length() < MAX_INPUT_CHARS)
                            // {
                            //     // Draw blinking underscore char
                            //     if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBoxName.x() + 8 + MeasureText(name, 40), (int)textBoxName.y() + 12, 40, MAROON);
                            // }
                            // else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
                        }
                        else
                        {
                            // SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                            // DrawRectangleLines((int)textBoxName.x(), (int)textBoxName.y(), (int)textBoxName.width(), (int)textBoxName.height(), DARKGRAY);
                        }

                        // DrawText(String.format("%s", name), (int)textBoxName.x() + 5, (int)textBoxName.y() + 8, 40, MAROON);
                        // DrawText(String.format("INPUT CHARS: %f/%f", (float)name.length(), (float)MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

                        // System.out.println(name);

                        Rectangle okayButton = new Rectangle((GetScreenWidth() / 2) - 105, ((GetScreenHeight() / 4) * 3) + 50, 200, 100);

                        //okay button
                        if (!CheckCollisionPointRec(GetMousePosition(), okayButton))
                        {
                            DrawRectangleRec(okayButton, BLACK);
                            DrawRectangle((GetScreenWidth() / 2) - 95, ((GetScreenHeight() / 4) * 3) + 60, 180, 80, LIGHTGRAY);
                            DrawRectangle((GetScreenWidth() / 2) - 100, ((GetScreenHeight() / 4) * 3) + 150, 195, 5, DARKGRAY);
                            DrawRectangle((GetScreenWidth() / 2) + 95, ((GetScreenHeight() / 4) * 3) + 55, 5, 100, DARKGRAY);
                            DrawText("Okay", ((GetScreenWidth() / 2) - 5) - (MeasureText("Okay", 60) / 2), ((GetScreenHeight() / 4) * 3) + 70, 60, BLACK);
                        }
                        else
                        {
                            if (!IsMouseButtonDown(0))
                            {
                                DrawRectangle((GetScreenWidth() / 2) - 105, ((GetScreenHeight() / 4) * 3) + 50, 200, 100, BLACK);
                                DrawRectangle((GetScreenWidth() / 2) - 95, ((GetScreenHeight() / 4) * 3) + 60, 180, 80, GRAY);
                                DrawRectangle((GetScreenWidth() / 2) - 100, ((GetScreenHeight() / 4) * 3) + 150, 195, 5, DARKGRAY);
                                DrawRectangle((GetScreenWidth() / 2) + 95, ((GetScreenHeight() / 4) * 3) + 55, 5, 100, DARKGRAY);
                                DrawText("Okay", ((GetScreenWidth() / 2) - 5) - (MeasureText("Okay", 60) / 2), ((GetScreenHeight() / 4) * 3) + 70, 60, BLACK);
                            }
                            else
                            {
                                DrawRectangle((GetScreenWidth() / 2) - 100, ((GetScreenHeight() / 4) * 3) + 55, 200, 100, BLACK);
                                DrawRectangle((GetScreenWidth() / 2) - 90, ((GetScreenHeight() / 4) * 3) + 65, 180, 80, GRAY);
                                DrawText("Okay", ((GetScreenWidth() / 2)) - (MeasureText("Okay", 60) / 2), ((GetScreenHeight() / 4) * 3) + 75, 60, BLACK);
                            }
                        
                            if (IsMouseButtonReleased(0))
                            {
                                madeQuimbert = true;
                            }
                        }
                        
                        /*
                        System.out.print(newLine + "Quimbert #" + (i + 1) + ": " + newLine + "Name: ");
                        g = action.nextLine();

                        System.out.print(newLine + "Owner: ");
                        h = action.nextLine();

                        System.out.print(newLine + "Color: ");
                        c = action.nextLine();

                        System.out.println(newLine + "You have " + points + " points to spend on the following stats: " +
                        newLine + "Looks: helps with health" + newLine + "Smell: helps with sniff" + newLine + "Personality: helps with blocking" + 
                        newLine + "Gumption: helps with successful item use" + newLine + "Length: helps with damage when using attack" + 
                        newLine + newLine + "How many points would you like to spend your looks? Maximum 10 per stat.");

                        while(!n)
                        {
                            try
                            {
                                a = Integer.valueOf(action.nextLine());
                                n = true;
                            }
                            catch(Exception q)
                            {
                                System.out.println(newLine + "Invalid quantity of points assaigned. Please try again.");
                            }
                        }
                        n = false;

                        if (a > 10)
                        {
                            a = 10;
                        }
                        if (a < 0)
                        {
                            a = 0;
                        }
                        if (a > points)
                        {
                            a = points;
                        }
                        points -= a;

                        System.out.println(newLine + a + " points awarded to looks! " + points + " points remaining." + newLine + 
                        newLine + "How many points would you like to spend on your smell (sniffing ability not scent)?");

                        while(!n)
                        {
                            try
                            {
                                b = Integer.valueOf(action.nextLine());
                                n = true;
                            }
                            catch(Exception q)
                            {
                                System.out.println(newLine + "Invalid quantity of points assaigned. Please try again.");
                            }
                        }
                        n = false;

                        if (b > 10)
                        {
                            b = 10;
                        }
                        if (b < 0)
                        {
                            b = 0;
                        }
                        if (b > points)
                        {
                            b = points;
                        }
                        points -= b;

                        System.out.println(newLine + b + " points awarded to smell! " + points + " points remaining." + newLine + newLine + 
                        "How many points would you like to spend on your personality?");

                        while(!n)
                        {
                            try
                            {
                                d = Integer.valueOf(action.nextLine());
                                n = true;
                            }
                            catch(Exception q)
                            {
                                System.out.println(newLine + "Invalid quantity of points assaigned. Please try again.");
                            }
                        }
                        n = false;

                        if (d > 10)
                        {
                            d = 10;
                        }
                        if (d < 0)
                        {
                            d = 0;
                        }
                        if (d > points)
                        {
                            d = points;
                        }
                        points -= d;

                        System.out.println(newLine + d + " points awarded to personality! " + points + " points remaining." + newLine +
                        newLine + "How many points would you like to spend on your gumption?");

                        while(!n)
                        {
                            try
                            {
                                e = Integer.valueOf(action.nextLine());
                                n = true;
                            }
                            catch(Exception q)
                            {
                                System.out.println(newLine + "Invalid quantity of points assaigned. Please try again.");
                            }
                        }
                        n = false;

                        if (e > 10)
                        {
                            e = 10;
                        }
                        if (e < 0)
                        {
                            e = 0;
                        }
                        if (e > points)
                        {
                            e = points;
                        }
                        points -= e;

                        System.out.println(newLine + e + " points awarded to gumption! " + points + " points remaining." + newLine + 
                        newLine + "How many points would you like to spend on your length?");

                        while(!n)
                        {
                            try
                            {
                                f = Integer.valueOf(action.nextLine());
                                n = true;
                            }
                            catch(Exception q)
                            {
                                System.out.println(newLine + "Invalid quantity of points assaigned. Please try again.");
                            }
                        }
                        n = false;

                        if (f > 10)
                        {
                            f = 10;
                        }
                        if (f < 0)
                        {
                            f = 0;
                        }
                        if (f > points)
                        {
                            f = points;
                        }
                        points -= f;

                        System.out.println(newLine + f + " points awarded to length! " + points + " points remaining." + newLine);

                        quimberts.add(new Quimbert(a, b, c, d, e, f, g, h));

                        quimberts.get(i).startingHealth = (randInt(3, 5) * quimberts.get(i).looks) / 2;
                        quimberts.get(i).health = quimberts.get(i).startingHealth;
                        
                        if (quimberts.get(i).health < 1)
                        {
                            quimberts.get(i).health += 1;
                            quimberts.get(i).startingHealth += 1;
                        }
                        */
                    //}
                }
            }
            EndDrawing();
        }
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
