/*
    Names: Samuel Sanchez, Sandra Flores
    Date: 6 November 2015
    Description: The Camel Game
    Mods made: Added a stat track system to give a number count of how many time a decision was made
               Increased the chances of finding an oasis to 1 in 40
               Added a weather factor that slows down player and native speed as game goes on
*/
#include <iostream> // cin, cout
#include <cstdlib> // srand(), rand()
#include <ctime> // time()
#include <cmath> // abs()
using namespace std;

//**************************************************************************************************************
void drink(int& thirst, int& water);
// Summary: Allows player to drink and reset their thirst count
// Precondition: Needs a waterContainer level that is > 0 and must be in options()
// Postcondition: Thirst is set to 0 and waterContainer is subtracted by one
//**************************************************************************************************************
void moveNorm(int& thirst, int& camelTiredness, double& nativeMiles, double& milesTravelled, int& water, int turn);
// Summary: Allows for basic movement of between 5-12 miles
// Precondition: Player must still be alive and must be in options()
// Postcondition: Reassigns thirst, camelTiredness, nativeMiles, and milesTravelled
//**************************************************************************************************************
void moveFast(int& thirst, int& camelTiredness, double& nativeMiles, double& milesTravelled, int& water, int turn);
// Summary: Allows for faster movement of between 10-20 miles
// Precondition: Player must still be alive and must be in options()
// Postcondition: Reassigns thirst, camelTiredness, nativeMiles, and milesTravelled
//**************************************************************************************************************
void rest(int& camelTiredness, double& nativeMiles);
// Summary: Allows the camel to rest, but also lets the natives get closer
// Precondition: Player needs to be alive and must be in options()
// Postcondition: Camel's tiredness returns to 0
//**************************************************************************************************************
void status(int thirst, int camelTiredness, double nativeMiles, double milesTravelled, int water);
// Summary: Prints the stats of the player, their camel's health, and how close the natives are
// Precondition: Player needs to be alive and must be in options()
// Postcondition: Prints out necessary info
//**************************************************************************************************************
void oasis(int& thirst, int& camelTiredness,int& water);
// Summary: Resets thirst and camel tiredness to zero and water jug to 5
// Precondition: Player needs to be alive and has to be in traveling
// Postcondition: Resets respective stats
//**************************************************************************************************************
char options(int n);
// Summary: Allows player to choose their next move
// Precondition: Program must be running and done must equate to false
// Postcondition: Returns a character according to one of the following presented choices
//**************************************************************************************************************
bool gameCheck(int thirst, int camelTiredness, double nativeMiles, double milesTravelled, int water);
// Summary: Reviews a number of conditions to see the player's progress, check water level, camel fatigue, and native proximity
// Precondition: Player needs to have completed one move for anything to be recorded
// Postcondition: Prints out 
//**************************************************************************************************************
void statTrack(int drinksTaken, int timesMovedNorm,int timesMovedFast, int restsTaken);
// Summary: Allows player to view their stats after the game
// Precondition: While loop in int main must have broken
// Postcondition: Returns a character according to one of the following presented choices
//**************************************************************************************************************
int quit(int dT, int mN, int mF, int rests);
// Summary: Allows the user to quit the game
// Precondition: User must be present within the options() function
// Postcondition: Will quit the program
//**************************************************************************************************************

int main()
{
    char again;
    cout << left // Intro
         << "Welcome to Camel Escape 2.0!" << endl
         << "You have stolen a camel to make your way across the great Mobi desert." << endl
         << "The natives want their camel back and are chasing you down! Survive your" << endl
         << "desert trek and out run the natives." << endl
         << right;
    do{
        int thirst = 0; // Necessary stats to check progress of the game
        int camelTiredness = 0;
        double nativeMiles = -20;
        double milesTravelled = 0; 
        int waterContainer = 5;
        int turn = 1;
        int restsTaken = 0, travelledNorm = 0, travelledFast = 0, drinksTaken = 0; 
    
        bool session = true;
        while(session)
        {
            srand(time(0)); // Creates a new seed every turn
            char decision = options(turn); // Gives the player options on what they can do
            switch(decision) // Determines what to increment based off of player's choice
            {
                case 'A': drink(thirst, waterContainer); drinksTaken++; turn++; break;
                case 'B': moveNorm(thirst, camelTiredness, nativeMiles, milesTravelled, waterContainer, turn); travelledNorm++; turn++; break;
                case 'C': moveFast(thirst, camelTiredness, nativeMiles, milesTravelled, waterContainer, turn); travelledFast++; turn++; break;
                case 'D': rest(camelTiredness, nativeMiles); restsTaken++; turn++; break;
                case 'E': status(thirst, camelTiredness, nativeMiles, milesTravelled, waterContainer); break;
                case 'Q': quit(restsTaken, travelledNorm, travelledFast, restsTaken); break;
                default: cout << "Not a valid response"; break;
            }
            session = gameCheck(thirst, camelTiredness, nativeMiles, milesTravelled, waterContainer);
        } // end of while
        statTrack(drinksTaken, travelledNorm, travelledFast, restsTaken);
        cout << endl << "Try again? (y/n) ";
        cin >> again;
        cout << endl;
    }while(again == 'y'); // End of do while. Let's user player again
    
    return 0;
}

char options(int n)
{
    char choice;
    cout << "Turn " << n << endl
         << "A. Drink from canteen" << endl
         << "B. Move ahead normally" << endl
         << "C. Move ahead quickly" << endl
         << "D. Rest for the night" << endl
         << "E. Status check" << endl
         << "Q. Quit" << endl
         << "Your choice? ";
    cin >> choice;
    cout << endl;
    choice = toupper(choice);
    return choice;
}

void oasis(int& thirst, int& camelTiredness,int& water)
{
    int val = (rand() % 41);//produces random numbers from 0-40
    int match = (rand() % 41);
    if(val == match)//if the two random numbers match then everything will reset
    {
        cout << "You found an oasis!" << endl
             << "Your thirst is gone, your camel is healthy, and you have full water!" << endl;
        water = 5;
        camelTiredness = 0;
        thirst = 0;
    }
    return;
}

void drink(int& thirst, int& water)
{
    if(water > 0)
    {
        thirst = 0;
        water--;
        cout << "Your thirst level is: " << thirst << endl;
        cout << "Drinks left: " << water << endl;
    }
    else
    {
        cout << "You're out of water!" << endl;
    }
    return;
}

void moveNorm(int& thirst, int& camelTiredness, double& nativeMiles, double& milesTravelled, int& water, int turn)
{
    thirst++;
    if(turn > 0 && turn < 9)
    {
        camelTiredness += (rand() % 3) + 1;//camel's tiredness will increase random miles from 1-3
        milesTravelled += (rand() % 7) + 6;//miles travelled will increase a random number form 6-13
        nativeMiles += (rand() % 7) + 8;
    }
    else if(turn >= 9 && turn <= 18)
    {
        cout << "The heat is getting to you" << endl
             << "It's going to be harder to move now." << endl;
        camelTiredness += (rand() % 3) + 1;//will generate random numbers for the milestravelled, cameltiredness and the nativemiles
        milesTravelled += (rand() % 7) + 4;
        nativeMiles += (rand() % 7) + 7;
    }
    else if(turn >= 19 && turn <= 30)
    {
        cout << "This weather is apocalyptic!" << endl
             << "A huge sandstorm has set in!" << endl
             << "Movement has slowed even more" << endl;
        camelTiredness += (rand() % 3) + 1;
        milesTravelled += (rand() % 7) + 2;//will generate random numbers for the milestravelled, cameltiredness and the nativemiles
        nativeMiles += (rand() % 7) + 6;
    }
    else
    {
        cout << "And now there is lightning in the sandstorm" << endl
             << "Good lucky buddy" << endl
             << "You're not moving far anytime soon." << endl;
        camelTiredness += (rand() % 3) + 1;
        milesTravelled += (rand() % 7) + 1;
        nativeMiles += (rand() % 7) + 5;     
    }
        cout << "Miles Travelled: " << milesTravelled << endl;
    
    oasis(thirst, camelTiredness, water);
    
    return;
}

void moveFast(int& thirst, int& camelTiredness, double& nativeMiles, double& milesTravelled, int& water, int turn)
{
    oasis(thirst, camelTiredness, water);    
    thirst++;
    if(turn > 0 && turn < 9)
    {
        camelTiredness += (rand() % 4) + 1;
        milesTravelled += (rand() % 10) + 10;//will generate random numbers for the milestravelled, cameltiredness and the nativemiles
        nativeMiles += (rand() % 7) + 8;
    }
    if(turn == 9)
    {
        cout << "The heat is getting to you." << endl
             << "It's going to be harder to move now." << endl;
    }
     else if(turn >= 9 && turn <= 18)
    {
        camelTiredness += (rand() % 4) + 1;
        milesTravelled += (rand() % 10) + 8;//will generate random numbers for the milestravelled, cameltiredness and the nativemiles
        nativeMiles += (rand() % 7) + 7;
    }
    if(turn == 19)
    {
        cout << "This weather is apocalyptic!" << endl
             << "A huge sandstorm has set in!" << endl
             << "Movement has slowed even more!" << endl;
    }
    else if(turn >= 19 && turn <= 30)
    {
        camelTiredness += (rand() % 4) + 1;
        milesTravelled += (rand() % 10) + 6;//will generate random numbers for the milestravelled, cameltiredness and the nativemiles
        nativeMiles += (rand() % 7) + 6;
    }
    if(turn == 31)
    {
        cout << "And now there is lightning in the sandstorm" << endl
             << "Good lucky buddy" << endl
             << "You're not moving far anytime soon." << endl;
    }
    else
    {
        camelTiredness += (rand() % 4) + 1;
        milesTravelled += (rand() % 10) + 4;
        nativeMiles += (rand() % 7) + 5;
    }
    cout << "Miles Travelled: " << milesTravelled << endl;
    oasis(thirst, camelTiredness, water);
    
    return;
}

void rest(int& camelTiredness, double& nativeMiles)
{
    camelTiredness = 0;
    cout << "Your camel is happy" << endl;
    nativeMiles += (rand() % 8) + 8;
    
    return;
}

bool gameCheck(int thirst, int camelTiredness, double nativeMiles, double milesTravelled, int water)
{
    if(milesTravelled >= 200) // Player wins when they reach 200 miles or more
    {
        cout << "You made it out alive! You won!" << endl;
        return false;
    }
    if(thirst > 6 && milesTravelled < 200) // Player dies when thirst reaches 6
    {
        cout << "You have died of thirst!" << endl;
        cout << "Game Over" << endl;
        return false;
    } 
    if(camelTiredness > 10) // If camel dies, player loses
    {
        cout << "Your camel has died!" << endl
             << "You can no longer travel, so the natives" << endl
             << "have caught up to you!" << endl
             << "Game Over" << endl;
             return false;
    } 
    if((nativeMiles >= milesTravelled) && milesTravelled < 200) // Game ends when natives' miles = player miles travelled. 20 Added to compensate for -20 intial value
    {
        cout << "The natives captured you!" << endl
             << "Game Over" << endl;
        return false;
    }
    if(camelTiredness > 3)
    {
        cout << "Your camel is getting pretty tired. You should take a rest" << endl;
        return true;
    }
    if(thirst > 4)
    {
        cout << "You're getting pretty thirsty" << endl;
        return true;
    }
    
    if(nativeMiles >= milesTravelled - 15) // If natives are within 15 miles of the player
    {
        cout << "The natives are getting close!" << endl;
        return true;
    }
    else
        return true;
}

void status(int thirst, int camelTiredness, double nativeMiles, double milesTravelled, int water)
{
    cout << "Miles Travelled: " << milesTravelled << endl
         << "Drinks left: " << water << endl
         << "On a scale of 1-6, you're a " << thirst << " on the thirst scale" << endl
         << "On a scale of 1-10, your camel is a " << camelTiredness << " on the tired scale" << endl 
         << "Natives are " << abs(milesTravelled - abs(nativeMiles)) << " miles behind you." << endl;
    return;
}

void statTrack(int drinksTaken, int timesMovedNorm,int timesMovedFast, int restsTaken) // Shows overall stats after game ends
{
    cout << endl << "Stats:" << endl
         << "You chose the drink option: " << drinksTaken << " time(s)" << endl
         << "Times travelled normally: " << timesMovedNorm << endl
         << "Time travelled fast: " << timesMovedFast << endl 
         << "Rests taken: " << restsTaken << endl;
    
    return;
}

int quit(int dT, int mN, int mF, int rests)
{
    char decision;
    cout << "Are you sure? (y/n) "; // Let's the user decide if they really want to quit
    cin >> decision;
    decision = tolower(decision);
    if(decision == 'y')
    {
        statTrack(dT, mN, mF, rests);
        cout << "Thanks for playing!" << endl;
        exit (0);
    }
}
