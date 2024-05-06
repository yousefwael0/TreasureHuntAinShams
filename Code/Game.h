#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

#define StateCount 7

struct GameState
{
    int index = 0;
    string name = "Treasure Hunt ASU";
    bool isActive = false, done = false;
}states[StateCount];

//Variables used for changing the UI
bool stateChanged = false, paused = false, lost = false, gameWon = false; //Booleans to handle Game logic
int menuUiCenterX, menuUiPartsY;//center of the x axis on screen and dividing the y axis on screen to 6 parts (To Format Text nicely)
//Font for the text
Font gameFont;

//Funtion called at the start of the game to initailize the states array
void InitializeStates()
{
    //states[6].done = false;
    for (int i = 0; i < StateCount; i++)
        states[i].index = i;
    
    states[0].isActive = true;
    
    states[1].name = "Faculty Of Arts";
    
    states[2].name = "Faculty Of Law";
    
    states[3].name = "Faculty Of Computer & Information Sciences";
    
    states[4].name = "Faculty Of Science";
    
    states[5].name = "Faculty Of Mass Communication";
    
    states[6].name = "Zaafarana Palace";
}

//Funtion that returns the current active state on screen
GameState GetActiveState()
{
    for (int i = 0; i < StateCount; i++)
        if (states[i].isActive)
            return states[i];
    return states[0];
}

//Funtion to Switch From state to another ex.(Main menu to map = 0 to 1)
void SwitchCurrentState(RenderWindow& window, int newStateIndex)
{
    states[GetActiveState().index].isActive = false;
    states[newStateIndex].isActive = true;
    window.setTitle(GetActiveState().name);
    gameWon = false; lost = false;  paused = false;
    stateChanged = true;
}

//Funtion to handle events in all games
void PollEventloop(RenderWindow& window)
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
            
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            paused = !paused;
        
        if (event.type == Event::Resized)
        {
            menuUiPartsY = window.getView().getSize().y / 6;
            menuUiCenterX = window.getView().getSize().x / 2;
        }
    }
}

void DrawPauseMenu(RenderWindow& window)
{
    //Black faded rectangle for pause menu to draw on
    RectangleShape pauseRectangle((Vector2f)window.getView().getSize());
    pauseRectangle.setFillColor(Color(0, 0, 0, 150));
    
    //Initializing Text array of 3
    Text pauseMenuText[3] {Text("PAUSED", gameFont, 80), Text("RESUME", gameFont, 80), Text("BACK TO MAP", gameFont, 80)};
    
    //loop to set text origins to  the center
    for (int i = 0; i < 3; i++)
    {
        pauseMenuText[i].setOrigin(pauseMenuText[i].getGlobalBounds().getSize() / 2.f + pauseMenuText[i].getLocalBounds().getPosition());
        pauseMenuText[i].setOutlineColor(Color::Black);
        pauseMenuText[i].setOutlineThickness(10.f);
    }
     
    //Setting the texts' positions relative to the view(screen)
    pauseMenuText[0].setPosition(menuUiCenterX, menuUiPartsY * 1);
    pauseMenuText[1].setPosition(menuUiCenterX, menuUiPartsY * 3);
    pauseMenuText[2].setPosition(menuUiCenterX, menuUiPartsY * 4);
    
    //Variable to hold the mouse position relative to the window
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    
    //Checking for mouse Hover and press to resume
    if(pauseMenuText[1].getGlobalBounds().contains(mousePos))
    {
        pauseMenuText[1].scale(1.2, 1.2);
        if (Mouse::isButtonPressed(Mouse::Button::Left))
            paused = false;
    }
    
    //Checking for mouse Hover and press to go to main menu
    if(pauseMenuText[2].getGlobalBounds().contains(mousePos))
    {
        pauseMenuText[2].scale(1.2, 1.2);
        if (Mouse::isButtonPressed(Mouse::Button::Left))
            SwitchCurrentState(window, 0);//Function to switch game states
    }
    
    //Drawing the pause menu
    window.draw(pauseRectangle);
    for (int i = 0; i < 3; i++)
        window.draw(pauseMenuText[i]);
}

void DrawLostScreen(RenderWindow& window)
{
    //Black faded rectangle for Lost screen to draw on
    RectangleShape lostScreenRect((Vector2f)window.getView().getSize());
    lostScreenRect.setFillColor(Color(0, 0, 0, 150));
    
    //Initializing Text array of 3
    Text lostScreenText[3] {Text("GAME OVER!", gameFont, 80), Text("RESTART", gameFont, 80), Text("BACK TO MAP", gameFont, 80)};
    
    //loop to set text origins to  the center
    for (int i = 0; i < 3; i++)
    {
        lostScreenText[i].setOrigin(lostScreenText[i].getGlobalBounds().getSize() / 2.f + lostScreenText[i].getLocalBounds().getPosition());
        lostScreenText[i].setOutlineColor(Color::Black);
        lostScreenText[i].setOutlineThickness(10.f);
    }
    
    //Setting the texts' positions relative to the view(screen)
    lostScreenText[0].setPosition(menuUiCenterX, menuUiPartsY * 1);
    lostScreenText[1].setPosition(menuUiCenterX, menuUiPartsY * 3);
    lostScreenText[2].setPosition(menuUiCenterX, menuUiPartsY * 4);
    
    //Variable to hold the mouse position relative to the window
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    
    //Checking for mouse Hover and press to restart
    if(lostScreenText[1].getGlobalBounds().contains(mousePos))
    {
        lostScreenText[1].scale(1.2, 1.2);
        if (Mouse::isButtonPressed(Mouse::Button::Left))
        {
            SwitchCurrentState(window, GetActiveState().index);//Restarting the current active game
        }
    }
    
    //Checking for mouse Hover and press to go to main menu
    if(lostScreenText[2].getGlobalBounds().contains(mousePos))
    {
        lostScreenText[2].scale(1.2, 1.2);
        if (Mouse::isButtonPressed(Mouse::Button::Left))
        {
            SwitchCurrentState(window, 0);//Function to switch game states
        }
    }
    
    //Drawing the lost Screen
    window.draw(lostScreenRect);
    for (int i = 0; i < 3; i++)
        window.draw(lostScreenText[i]);
}

void DrawWinScreen(RenderWindow& window)
{
    //Setting the won game to done
    states[GetActiveState().index].done = true;
    
    //Black faded rectangle for Win screen to draw on
    RectangleShape winScreenRect((Vector2f)window.getView().getSize());
    winScreenRect.setFillColor(Color(0, 0, 0, 150));
    
    //Initializing Text array of 3
    Text winScreenText[2] {Text("Congratulations!", gameFont, 80), Text("BACK TO MAP", gameFont, 80)};
    
    //loop to set text origins to  the center
    for (int i = 0; i < 2; i++)
    {
        winScreenText[i].setOrigin(winScreenText[i].getGlobalBounds().getSize() / 2.f + winScreenText[i].getLocalBounds().getPosition());
        winScreenText[i].setOutlineColor(Color::Black);
        winScreenText[i].setOutlineThickness(13.f);
    }
    
    //Setting the texts' positions relative to the view(screen)
    winScreenText[0].setPosition(menuUiCenterX, menuUiPartsY * 1);
    winScreenText[1].setPosition(menuUiCenterX, menuUiPartsY * 3);
    
    //Variable to hold the mouse position relative to the window
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    
    //Checking for mouse Hover and press to Go to map
    if(winScreenText[1].getGlobalBounds().contains(mousePos))
    {
        winScreenText[1].scale(1.2, 1.2);
        if (Mouse::isButtonPressed(Mouse::Button::Left))
        {
            SwitchCurrentState(window, 0);
        }
    }
    
    //Drawing the Win Screen
    window.draw(winScreenRect);
    for (int i = 0; i < 2; i++)
        window.draw(winScreenText[i]);
}

//Inserted before Displaying the frame to check for pause, lose, win screens
void CheckForUIChanges(RenderWindow& window)
{
    //PauseMenu Check
    if (paused)
        DrawPauseMenu(window);
    
    //Lost Screen check
    if (lost)
        DrawLostScreen(window);
    
    //win screen check
    if (gameWon)
        DrawWinScreen(window);
}

bool OpenPalace()
{
    for (int i = 1; i < StateCount-1; i++)
    {
        if (!states[i].done)
            return false;
    }
    return true;
}


