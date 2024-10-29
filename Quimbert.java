import java.util.Random;
import java.util.ArrayList;
import static com.raylib.Jaylib.*;

public class Quimbert
{
    public int looks;
    public int smell;
    private String color;
    public int personality;
    public int gumption;
    public int length;
    public String name;
    private String owner;
    private String foundItem;
    public ArrayList<String> inv = new ArrayList<>();
    private String newLine = System.getProperty("line.separator");
    public int health;
    public int startingHealth;
    public int turns = 0;
    public int toDeal = 0;
    public int blocks;
    public int lives = 1;
    public int yellowFlowers = 0;
    public int greenFlowers = 0;
    public int purpleFlowers = 0;
    public int orangeFlowers = 0;
    public int redFlowers = 0;
    
    public Quimbert(int l, int s, String c, int p, int g, int L, String n, String o)
    {
        looks = l;
        smell = s;
        color = c;
        personality = p;
        gumption = g;
        length = L;
        name = n;
        owner = o;
    }
    
    private int randInt(int min, int max) 
    {
        Random rand = new Random();
        int randomNum = rand.nextInt((max - min) + 1) + min;

        return randomNum;
    }
    
    public String getRandomString(String a, String b, String c, String d, 
        String e, String f, String g, String h, String i, String j, String k, 
        String l, String m, String n, String o, String p, String a1, String b1, String c1, String d1, 
        String e1, String f1, String g1, String h1, String i1, String j1, String k1, 
        String l1, String m1, String n1, String o1, String p1, String a2, String b2, String c2, String d2, 
        String e2, String f2, String g2)
    {
        int r = (int) (Math.random()*16);
        String ranItem = new String [] {a, b, c, d, e, f, g, h, i, j, k, l, m, 
        n, o, p, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, 
        n1, o1, p1, a2, b2, c2, d2, e2, f2, g2}[r];
        
        return ranItem;
    }
    
    public String sniff()
    {
        if (0 < 0 + smell + randInt(-10, 10))
        {
            foundItem = getRandomString("black truffle", "mushroom", "twig", "rock",
            "white truffle", "unidentified piece of flesh", "carrot", "knife", "ak47",
            "bazooka", "turnip", "yellow flower", "green flower", "purple flower", 
            "orange flower", "red flower", "black truffle", "mushroom", "twig", "rock",
            "unidentified piece of flesh", "carrot", "knife",
            "turnip", "yellow flower", "green flower", "purple flower", 
            "orange flower", "red flower", "twig", "rock",
            "unidentified piece of flesh", "carrot",
            "turnip", "yellow flower", "green flower", "purple flower", 
            "orange flower", "red flower");
            
            return foundItem;
        }
        else
        {
            return "fail";
        }
    }
    
    public void block()
    {
        if ((personality + randInt(-7, 10)) >= 10)
        {
            blocks += 1;
            System.out.println(newLine + "Successfully added a block! You now have " + blocks + " blocks.");
            
            if (personality == 10 && randInt(1, 4) == 4)
            {
                if ((personality + randInt(-7, 10)) >= 10)
                {
                    blocks += 1;
                    System.out.println(newLine + name + " is so sigma that they blocked again and now have " + blocks + " blocks.");
                }
            }
        }
        else
        {
            System.out.println(newLine + name + " failed to block. " + name + " has " + blocks + " blocks.");
        }
    }
    
    public void inventory()
    {
        System.out.println(newLine + name +"'s Inventory: " + newLine + inv.toString() + newLine);
    }
    
    public void health()
    {
        System.out.println(newLine + name + " Health: " + health + "/" + startingHealth);
    }
    
    private String temp;
    
    public void info(String item)
    {
        if (item.toLowerCase().equals("black truffle") || item.toLowerCase().equals("black"))
        {
            temp = "Take an extra turn.";
        }
        else if (item.toLowerCase().equals("mushroom") || item.toLowerCase().equals("mush"))
        {
            temp = "Heal 2-4 hp.";
        }
        else if (item.toLowerCase().equals("twig"))
        {
            temp = "Deal 2 damage.";
        }
        else if (item.toLowerCase().equals("rock"))
        {
            temp = "Deal 2-3 damage.";
        }
        else if (item.toLowerCase().equals("white truffle") || item.toLowerCase().equals("white"))
        {
            temp = "Take two extra turns.";
        }
        else if (item.toLowerCase().equals("unidentified piece of flesh") || item.toLowerCase().equals("piece of flesh") ||
        item.toLowerCase().equals("flesh"))
        {
            temp = "Heal 1-5 hp or take 1-5 damage (or do nothing).";
        }
        else if (item.toLowerCase().equals("carrot"))
        {
            temp = "Heal 2 hp.";
        }
        else if (item.toLowerCase().equals("knife"))
        {
            temp = "One time use. Deal 5 damage.";
        }
        else if (item.toLowerCase().equals("ak47") || item.toLowerCase().equals("ak"))
        {
            temp = "One time use. Deal 5-10 damage.";
        }
        else if (item.toLowerCase().equals("bazooka") || item.toLowerCase().equals("baz") || item.toLowerCase().equals("bazook"))
        {
            temp = "One time use. Deal 8-14 damage.";
        }
        else if (item.toLowerCase().equals("turnip"))
        {
            temp = "Heal 1-3 hp.";
        }
        else if (item.toLowerCase().equals("yellow flower") || item.toLowerCase().equals("yellow"))
        {
            temp = "Useless alone.";
        }
        else if (item.toLowerCase().equals("green flower") || item.toLowerCase().equals("green"))
        {
            temp = "Useless alone.";
        }
        else if (item.toLowerCase().equals("purple flower") || item.toLowerCase().equals("purple"))
        {
            temp = "Useless alone.";
        }
        else if (item.toLowerCase().equals("orange flower") || item.toLowerCase().equals("orange"))
        {
            temp = "Useless alone.";
        }
        else if (item.toLowerCase().equals("red flower") || item.toLowerCase().equals("red"))
        {
            temp = "Useless alone.";
        }
        else
        {
            temp = "Does not exist.";
        }
        
        System.out.println(item + ": " + temp + newLine);
    }
    
    private int temp2;
    
    public void use(String item)
    {
        if (item.toLowerCase().equals("black truffle") || item.toLowerCase().equals("black"))
        {
            inv.remove("black truffle");
            
            if ((gumption + randInt(-2, 10)) >= 10)
            {
                turns += 2;
                
                System.out.println(newLine + "Added an extra turn.");
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("mushroom") || item.toLowerCase().equals("mush"))
        {
            inv.remove("mushroom");
            
            if ((gumption + randInt(-1, 10)) >= 10)
            {
                temp2 = randInt(2, 4);
                health += temp2;
            
                System.out.println(newLine + "Healed " + temp2 + " hp.");
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("twig"))
        {
            inv.remove("twig");
            
            if ((gumption + randInt(0, 10)) >= 10)
            {
                toDeal = 2;
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("rock"))
        {
            inv.remove("rock");
            
            if ((gumption + randInt(-1, 10)) >= 10)
            {
                toDeal = randInt(2, 3);
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("white truffle") || item.toLowerCase().equals("white"))
        {
            inv.remove("white truffle");
            
            if ((gumption + randInt(-3, 10)) >= 10)
            {
                turns += 3;
            
                System.out.println(newLine + "Added two extra turns.");
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("unidentified piece of flesh") || item.toLowerCase().equals("piece of flesh") || 
        item.toLowerCase().equals("flesh"))
        {
            inv.remove("unidentified piece of flesh");
            
            if ((gumption + randInt(1, 10)) >= 10)
            {
                temp2 = randInt(-5, 5);
                health += temp2;
            
                if (temp2 >= 0)
                {
                    System.out.println(newLine + "Healed " + temp2 + " hp.");
                }
                else
                {
                    System.out.println(newLine + "Took " + temp2 + " damage.");
                }
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("carrot"))
        {
            inv.remove("carrot");
            
            if ((gumption + randInt(0, 10)) >= 10)
            {
                health += 2;
            
                System.out.println(newLine + "Healed 2 hp.");
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("knife"))
        {
            inv.remove("knife");
            
            if ((gumption + randInt(-3, 10)) >= 10)
            {
                toDeal = 5;
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("ak47") || item.toLowerCase().equals("ak"))
        {
            inv.remove("ak47");
            
            if ((gumption + randInt(-6, 10)) >= 10)
            {
                toDeal = randInt(5, 10);
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("bazooka") || item.toLowerCase().equals("baz") || item.toLowerCase().equals("bazook"))
        {
            inv.remove("bazooka");
            
            if ((gumption + randInt(-10, 10)) >= 10)
            {
                toDeal = randInt(8, 14);
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("turnip"))
        {
            inv.remove("turnip");
            
            if ((gumption + randInt(-1, 10)) >= 10)
            {
                temp2 = randInt(1, 3);
                health += temp2;
            
                System.out.println(newLine + "Healed " + temp2 + " hp.");
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("yellow flower") || item.toLowerCase().equals("yellow"))
        {
            inv.remove("yellow flower");
            
            if ((gumption + randInt(4, 10)) >= 10)
            {
                yellowFlowers += 1;
                
                if (yellowFlowers >= 1 && greenFlowers >= 1 && purpleFlowers >= 1 && orangeFlowers >= 1 && redFlowers >= 1)
                {
                    lives += 1;
                    System.out.println("All five flowers collected. " + name + " has unlocked another life.");
                    
                    yellowFlowers -= 1;
                    greenFlowers -= 1;
                    purpleFlowers -= 1;
                    orangeFlowers -= 1;
                    redFlowers -= 1;
                }
                else
                {
                    System.out.println(newLine + "Nothing happened yet.");
                }
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("green flower") || item.toLowerCase().equals("green"))
        {
            inv.remove("green flower");
            
            if ((gumption + randInt(4, 10)) >= 10)
            {
                greenFlowers += 1;
                
                if (yellowFlowers >= 1 && greenFlowers >= 1 && purpleFlowers >= 1 && orangeFlowers >= 1 && redFlowers >= 1)
                {
                    lives += 1;
                    System.out.println("All five flowers collected. " + name + " has unlocked another life.");
                    
                    yellowFlowers -= 1;
                    greenFlowers -= 1;
                    purpleFlowers -= 1;
                    orangeFlowers -= 1;
                    redFlowers -= 1;
                }
                else
                {
                    System.out.println(newLine + "Nothing happened yet.");
                }
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("purple flower") || item.toLowerCase().equals("purple"))
        {
            inv.remove("purple flower");
            
            if ((gumption + randInt(4, 10)) >= 10)
            {
                purpleFlowers += 1;
                
                if (yellowFlowers >= 1 && greenFlowers >= 1 && purpleFlowers >= 1 && orangeFlowers >= 1 && redFlowers >= 1)
                {
                    lives += 1;
                    System.out.println("All five flowers collected. " + name + " has unlocked another life.");
                    
                    yellowFlowers -= 1;
                    greenFlowers -= 1;
                    purpleFlowers -= 1;
                    orangeFlowers -= 1;
                    redFlowers -= 1;
                }
                else
                {
                    System.out.println(newLine + "Nothing happened yet.");
                }
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("orange flower") || item.toLowerCase().equals("orange"))
        {
            inv.remove("orange flower");
            
            if ((gumption + randInt(4, 10)) >= 10)
            {
                orangeFlowers += 1;
                
                if (yellowFlowers >= 1 && greenFlowers >= 1 && purpleFlowers >= 1 && orangeFlowers >= 1 && redFlowers >= 1)
                {
                    lives += 1;
                    System.out.println("All five flowers collected. " + name + " has unlocked another life.");
                    
                    yellowFlowers -= 1;
                    greenFlowers -= 1;
                    purpleFlowers -= 1;
                    orangeFlowers -= 1;
                    redFlowers -= 1;
                }
                else
                {
                    System.out.println(newLine + "Nothing happened yet.");
                }
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else if (item.toLowerCase().equals("red flower") || item.toLowerCase().equals("red"))
        {
            inv.remove("red flower");
            
            if ((gumption + randInt(4, 10)) >= 10)
            {
                redFlowers += 1;
                
                if (yellowFlowers >= 1 && greenFlowers >= 1 && purpleFlowers >= 1 && orangeFlowers >= 1 && redFlowers >= 1)
                {
                    lives += 1;
                    System.out.println("All five flowers collected. " + name + " has unlocked another life.");
                    
                    yellowFlowers -= 1;
                    greenFlowers -= 1;
                    purpleFlowers -= 1;
                    orangeFlowers -= 1;
                    redFlowers -= 1;
                }
                else
                {
                    System.out.println(newLine + "Nothing happened yet.");
                }
            }
            else
            {
                System.out.println(newLine + name + " failed to use " + item.toLowerCase() + ".");
            }
        }
        else
        {
            System.out.println(newLine + item + " is not an item.");
            
            turns += 1;
        }
    }
    
    public void stats()
    {
        System.out.println(name + " stats: " + newLine + "Looks: " + looks + 
        "/10" + newLine + "Smell: " + smell + "/10" + newLine + "Color: " + 
        color + newLine + "Personality: " + personality + "/10" + newLine + 
        "Gumption: " + gumption + "/10" + newLine + "Length: " + length + "/10" +
        newLine + "Owner: " + owner + newLine);
    }
}