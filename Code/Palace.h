#pragma once

bool AllLettersCorrect(bool soundCorrectPlayed[])
{
    for (int i = 0; i < 6; i++)
        if (!soundCorrectPlayed[i])
            return false;
    return true;
}

void LoadPalace(RenderWindow& window)
{
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Resources/Palace/background2.png"))
    {
        cout << "Failed to load background" << endl;
        exit(1);
    }
    Sprite background(backgroundTexture);

    //array for the input text
    Text TextEntered[6];

    Font inputtext;
    if (!inputtext.loadFromFile("Resources/Palace/font.ttf"))
    {
        cout << "Failed to load font" << endl;
        exit(1);
    }

    RectangleShape rectangle[6];
    int positonrectangle = 1100;
    //int X = 136;
    for (int i = 0; i < 6; i++)
    {
        rectangle[i].setFillColor(Color::White);
        rectangle[i].setSize(Vector2f(150, 150));
        rectangle[i].setPosition(positonrectangle, 440);
        rectangle[i].setOutlineColor(Color::Transparent);
        rectangle[i].setOutlineThickness(5);

        TextEntered[i].setFont(inputtext);
        TextEntered[i].setCharacterSize(80);
        TextEntered[i].setFillColor(Color::Black);

        positonrectangle -= 200;
    }
    TextEntered[0].setPosition(136, 465);
    TextEntered[1].setPosition(321, 465);
    TextEntered[2].setPosition(538, 465);
    TextEntered[3].setPosition(726, 465);
    TextEntered[4].setPosition(925, 465);
    TextEntered[5].setPosition(1125, 465);

    string userInput;

    Text text;
    text.setFont(inputtext);
    text.setString("ENTER THE CLUE");
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::Black);
    text.setPosition(200, 220);

    //sound
    SoundBuffer cluefound;
    if (!cluefound.loadFromFile("Resources/Palace/cluefound.wav"))
        exit(1);

    Sound correct;
    correct.setBuffer(cluefound);
                               
    SoundBuffer cluefail;
    if (!cluefail.loadFromFile("Resources/Palace/fail.wav"))
        exit(1);

    Sound failed;
    failed.setBuffer(cluefail);

    bool soundCORRECTPlayed[6] = { false };
    bool soundFAILEDPlayed[6] = { false };

    while (window.isOpen())
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
            // Handle text input events
            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode == '\b') // Check if the backspace key was pressed
                {
                    if (!userInput.empty()) // Check if there's anything to delete
                    {
                        userInput.pop_back(); // Remove the last character
                    }
                }
                // If the entered character is a digit, add it to userInput
                if (isdigit(event.text.unicode))
                {
                    userInput += static_cast<char>(event.text.unicode);
                }
                // Update the TextEntered array with userInput
                for (int i = 0; i < userInput.size() && i < 6; ++i)
                {
                    TextEntered[i].setString(string(1, userInput[i]));
                }
            }
        }
        
        if (stateChanged)
            break;
        
        //Load Win Screen if Won
        if (AllLettersCorrect(soundCORRECTPlayed))
        {
            window.clear();
            window.draw(Win);
            window.display();
            sleep(seconds(3));
            states[6].done = true;
            SwitchCurrentState(window, 0);
        }
        else
        {
            if (userInput.size() > 0 && userInput[0] == '1') {
                rectangle[5].setOutlineColor(Color::Green);
                rectangle[5].setOutlineThickness(5);
                
                if (!soundCORRECTPlayed[0])
                {
                    correct.play();
                    soundCORRECTPlayed[0] = true;
                }
            }
            if (userInput.size() > 0 && userInput[0] != '1') {
                rectangle[5].setOutlineColor(Color::Red);
                if (!soundFAILEDPlayed[0])
                {
                    failed.play();
                    soundFAILEDPlayed[0] = true;
                }
            }
            if (userInput.size() > 1 && userInput[1] == '7') {
                rectangle[4].setOutlineColor(Color::Green);
                rectangle[4].setOutlineThickness(5);
                if (!soundCORRECTPlayed[1])
                {
                    correct.play();
                    soundCORRECTPlayed[1] = true;
                }
            }
            if (userInput.size() > 1 && userInput[1] != '7') {
                rectangle[4].setOutlineColor(Color::Red);
                if (!soundFAILEDPlayed[1])
                {
                    failed.play();
                    soundFAILEDPlayed[1] = true;
                }
            }
            if (userInput.size() > 2 && userInput[2] == '1') {
                rectangle[3].setOutlineColor(Color::Green);
                rectangle[3].setOutlineThickness(5);
                if (!soundCORRECTPlayed[2])
                {
                    correct.play();
                    soundCORRECTPlayed[2] = true;
                }
            }
            if (userInput.size() > 2 && userInput[2] != '1') {
                rectangle[3].setOutlineColor(Color::Red);
                if (!soundFAILEDPlayed[2])
                {
                    failed.play();
                    soundFAILEDPlayed[2] = true;
                }
            }
            if (userInput.size() > 3 && userInput[3] == '9') {
                rectangle[2].setOutlineColor(Color::Green);
                rectangle[2].setOutlineThickness(5);
                if (!soundCORRECTPlayed[3])
                {
                    correct.play();
                    soundCORRECTPlayed[3] = true;
                }
            }
            if (userInput.size() > 3 && userInput[3] != '9') {
                rectangle[2].setOutlineColor(Color::Red);
                if (!soundFAILEDPlayed[3])
                {
                    failed.play();
                    soundFAILEDPlayed[3] = true;
                }
            }
            if (userInput.size() > 4 && userInput[4] == '5') {
                rectangle[1].setOutlineColor(Color::Green);
                rectangle[1].setOutlineThickness(5);
                if (!soundCORRECTPlayed[4])
                {
                    correct.play();
                    soundCORRECTPlayed[4] = true;
                }
            }
            if (userInput.size() > 4 && userInput[4] != '5') {
                rectangle[1].setOutlineColor(Color::Red);
                if (!soundFAILEDPlayed[4])
                {
                    failed.play();
                    soundFAILEDPlayed[4] = true;
                }
            }
            if (userInput.size() > 5 && userInput[5] == '0') {
                rectangle[0].setOutlineColor(Color::Green);
                rectangle[0].setOutlineThickness(5);
                if (!soundCORRECTPlayed[5])
                {
                    correct.play();
                    soundCORRECTPlayed[5] = true;
                }
            }
            if (userInput.size() > 5 && userInput[5] != '0') {
                rectangle[0].setOutlineColor(Color::Red);
                if (!soundFAILEDPlayed[5])
                {
                    failed.play();
                    soundFAILEDPlayed[5] = true;
                }
            }
            window.clear();
            
            window.draw(background);
            for (int i = 0; i < 6; i++)
            {
                window.draw(rectangle[i]);
            }
            for (int i = 0; i < userInput.size(); i++)
            {
                window.draw(TextEntered[i]); // Draw text inside squares
            }
            window.draw(text);
            window.draw(Banner);
            window.draw(first);
            window.draw(second);
            window.draw(third);
            window.draw(fourth);
            window.draw(fifth);
            window.draw(sixth);
            
            window.display();
        }
    }
}

