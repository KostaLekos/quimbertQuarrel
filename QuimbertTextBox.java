import java.util.Scanner;
import java.util.Random;
import java.util.ArrayList;
import static com.raylib.Jaylib.*;
import static com.raylib.Raylib.*;

/*Kosta
 * Make sure to have a BeginDrawing(); before calling .render()
 * You have made this codebase in a way that requires so
 */






public class QuimbertTextBox {
    private String text;
    private int maxCharCount;
    private boolean mouseOnText;
    com.raylib.Jaylib.Rectangle boundingBox;
    private int framesCounter;

    public void setCharLength (int charCount) {
        maxCharCount = charCount;
    }

    public String getText () {
        return text;
    }

    public QuimbertTextBox (com.raylib.Jaylib.Rectangle bound) {
        boundingBox = bound;
        text = "";
    }

    public void processTextInput () {
        if (CheckCollisionPointRec(GetMousePosition(), boundingBox) && IsMouseButtonPressed(0)) mouseOnText = true;
        else if (!CheckCollisionPointRec(GetMousePosition(), boundingBox) && IsMouseButtonPressed(0)) mouseOnText = false;

        if (mouseOnText)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && text.length() < maxCharCount)
                {
                    text += (char)key;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                if (text.length() < 2) {
                    text = "";
                } else {
                    text = text.substring(0, text.length() - 1);
                }
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    public void render () {

        framesCounter++;

        
        if (mouseOnText) {
            DrawRectangleRec(boundingBox, GRAY);
        } else {
            DrawRectangleRec(boundingBox, LIGHTGRAY); 
        }
        DrawRectangleLinesEx(boundingBox, 10.0f, BLACK);

        DrawText(String.format("INPUT CHARS: %d/%d", text.length(), maxCharCount), 315, 250, 20, DARKGRAY);
        
        
        if (mouseOnText)
        {
            if (text.length() < maxCharCount)
            {
                // Draw blinking underscore char
                if (((framesCounter/20)%2) == 0) {
                    DrawText("_", (int)boundingBox.x() + 23 + MeasureText(text, 40), (int)boundingBox.y() + 19, 40, DARKGRAY);
                }
            } else {
                DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
            }
        }
        
        //draw typed text
        DrawText(text, (int)boundingBox.x() + 20, (int)boundingBox.y() + 15, 40, DARKGRAY);
    }
}
