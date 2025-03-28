import java.util.Scanner;
import java.util.Random;
import java.util.ArrayList;

// compile : cmd
// : "E:\Actually Useful\NonZips\java\jdk-21.0.4+7\bin\javac.exe" -cp .\jaylib-5.0.0-0.jar .\QuimbertQuarrel.java .\Quimbert.java
// run : cmd
// : "E:\Actually Useful\NonZips\java\jdk-21.0.4+7\bin\java.exe" -cp jaylib-5.0.0-0.jar;. QuimbertQuarrel
public class QuimbertQuarrel
{
    private static int randInt(int min, int max) 
    {
        Random rand = new Random();
        int randomNum = rand.nextInt((max - min) + 1) + min;

        return randomNum;
    }
    
    public static void main(String[] args)
    {
        Scanner action = new Scanner(System.in);
        String choice;
        int quimbertQuantity = 0;
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
        
        System.out.println("How many Quimberts are you playing with?");
        while(!n)
        {
            try
            {
                quimbertQuantity = Integer.valueOf(action.nextLine());
                n = true;
            }
            catch(Exception q)
            {
                System.out.println(newLine + "Invalid quantity of quimberts. Please try again.");
            }
              
            if (quimbertQuantity < 2)
            {
                System.out.println(newLine + "Invalid quantity of quimberts. Please try again.");
                n = false;
            }
            
            if (quimbertQuantity > 8)
            {
                System.out.println(newLine + "Invalid quantity of quimberts. Please try again.");
                n = false;
            }
        }
        n = false;
        
        for (int i = 0; i < quimbertQuantity; i++)
        {
            points = randInt(25, 35);
            
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
        }
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