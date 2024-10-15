import java.util.Scanner;
import java.util.Random;
import java.util.ArrayList;
import static com.raylib.Jaylib.*;
import static com.raylib.Raylib.*;

public class QuimbertTextBox {
    private String text;
    private int maxCharCount;
    private bool isSelected;
    com.raylib.Jaylib.Rectangle boundingBox;

    public void setCharLength (int charCount) {
        maxCharCount = charCount;
    }

    public String getText () {
        return text;
    }

    public QuimbertTextBox (com.raylib.Raylib.Vector2 position, com.raylib.Raylib.Vector2 size) {
v       return;
    }
    public QuimbertTextBox (com.raylib.Jaylib.Rectangle bound) {
        boundingBox = bound;
    }

    public void processTextInput () {
        
    }

    public void render () {
        BeginDrawing();
        EndDrawing();
    }
}