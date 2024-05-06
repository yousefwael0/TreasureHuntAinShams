#include "Game.h"
#include "MainMenu.h"
#include "SnakeGame.h"
#include "WordScapes.h"
#include "MarioGame.h"
#include "Palace.h"
#include "PlaneGame.h"
#include "JetPackJoyRide.h"

/*
Game States Chart:
    0 MainMenu
    1 SnakeGame(Arts)
    2 Mario(Law)
    3 JetPackJoyRide(cs)
    4 PlaneGame(Sc)
    5 WordScapes(mass)
    6 EnterTheClue(palace)
*/

int main(void)
{
    //Initializing the game window & UI Variables
    RenderWindow window(VideoMode(1280, 720), states[0].name);
    window.setFramerateLimit(60);
    
    gameFont.loadFromFile("Resources/Snake/SnakeScoreFont.ttf");
    menuUiPartsY = window.getView().getSize().y / 6;
    menuUiCenterX = window.getView().getSize().x / 2;
    
    //Initializing the states array
    InitializeStates();
    
    //Game States loop
    while (window.isOpen())
    {
        if (GetActiveState().index == 0)
        {
            stateChanged = false;
            //Load MainMenu
            MainMenu(window);
        }
        else if (GetActiveState().index == 1)
        {
            stateChanged = false;
            //Load Arts
            SnakeGame snake(window);
        }
        else if (GetActiveState().index == 2)
        {
            stateChanged = false;
            //Load Law
            MarioGame(window);
        }
        else if (GetActiveState().index == 3)
        {
            stateChanged = false;
            //Load Computer Science
            jetPackGame(window);
        }
        else if (GetActiveState().index == 4)
        {
            stateChanged = false;
            //Load SC
            PlaneGame(window);
        }
        else if (GetActiveState().index == 5)
        {
            stateChanged = false;
            //Load MassComm
            WordScapes(window);
        }
        else if (GetActiveState().index == 6)
        {
            stateChanged = false;
            //Load Palace
            won.play();
            LoadPalace(window);
        }
    }
    return 0;
}
