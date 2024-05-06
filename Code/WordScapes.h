#pragma once

//bool allFunctionsDone = false;
void inter(int x, int y, int posx, int posy, Sprite objects[], RectangleShape squares[], Sound& correctSound, bool played[], bool& allCorrect)
{

    if (objects[x].getGlobalBounds().intersects(squares[y].getGlobalBounds()))
    {
        for (int i = 0; i < 25; i++)
        {
            if (squares[y].getGlobalBounds().intersects(objects[i].getGlobalBounds()) && i != x)
                return;
        }
        
        objects[x].setPosition(posx, posy);
        objects[x].setScale(1.0, 1.0);
        squares[y].setOutlineColor(Color::Green);


        if (!played[x])
        {
            correctSound.play();
            played[x] = true;
        }
    }

    allCorrect = true;
    for (int i = 0; i < 25; i++)
    {
        if (!played[i]) 
        {
            allCorrect = false;
            break;
        }
    }
}

bool IsDragging(bool isDragging[])
{
    for (int i = 0; i < 25; i++)
        if (isDragging[i])
            return true;
    return false;
}

void WordScapes(RenderWindow& window)
{
    Clock clock;
    while (clock.getElapsedTime().asSeconds() <= 3.f)
    {
        RectangleShape goalScreenRect((Vector2f)window.getView().getSize());
        goalScreenRect.setFillColor(Color(0, 0, 0, 150));
        
        Text goalScreenText("Use the hints and form the correct words to get your clue!", gameFont, 36);
        goalScreenText.setOrigin(goalScreenText.getGlobalBounds().getSize() / 2.f + goalScreenText.getLocalBounds().getPosition());
        goalScreenText.setPosition(menuUiCenterX, menuUiPartsY * 3.f);
        
        window.clear();
        window.draw(goalScreenRect);
        window.draw(goalScreenText);
        window.display();
    }
    //elarrays
    Sprite objects[25];
    RectangleShape squares[26];
    Vector2f offset[25];
    bool isDragging[25] = { false };
    Text text[4];


    Vector2f velocity(0, 0);

    //Textures
    //elbakcground
    Texture backGroundTexture;
    backGroundTexture.loadFromFile("Resources/WordCapse/wordscapes.png");

    Sprite ground(backGroundTexture);

    // load font
    Font wordscapesfont;
    if (!wordscapesfont.loadFromFile("Resources/WordCapse/boldfont.ttf"))
    {
        exit(1);
    }

    // text
   text[0].setString("Hint: Where algorithms meet innovation, bytes and bits dance in harmony.");
   text[1].setString("Hint: Advertising & Promotion, Branding, Audio/Visual Production,\n Broadcasting, Corporate Communication, and Public Relations.");
   text[2].setString("Hint: a place for education and research on science and experiments\n are the language of discovery.");
   text[3].setString("Hint: involved with literature and writing");


   Text textH; //el title hint
   textH.setString("Touch the icons ");
   textH.setCharacterSize(50);
   textH.setPosition(870, 77);
   textH.setFillColor(Color::White);
   textH.setFont(wordscapesfont);
    //sound
    SoundBuffer correctSoundBuffer;
    if (!correctSoundBuffer.loadFromFile("Resources/WordCapse/cluefound.wav")) {
        cout << "Failed to load correct sound" << endl;
        exit(1);
    }
    Sound correctSound;
    correctSound.setBuffer(correctSoundBuffer);

    ///  logos



    //static Clock cwordscapes;
    //elcharacter
    Texture owletTexture;
    if (!owletTexture.loadFromFile("Resources/WordCapse/owlet.png")) {
        cout << "Failed to load owlet texture" << endl;
        exit(1);
    }
    Sprite owlet(owletTexture);
    owlet.setPosition(38, 590);
    owlet.setScale(4.0f, 4.0f);

    //el letters
    Texture letterU;
    if (!letterU.loadFromFile("Resources/WordCapse/U.png")) {
        cout << "Failed to load LETTER U" << endl;
        exit(1);
    }
    objects[0].setTexture(letterU);
    objects[0].setPosition(990, 274);//

    Texture letterA;
    if (!letterA.loadFromFile("Resources/WordCapse/A.png"))
    {
        cout << "Failed to load letter A";
        exit(1);
    }
    objects[1].setTexture(letterA);
    objects[1].setPosition(850, 134);//

    /*
    Texture letterA2;
    if (!letterA2.loadFromFile("Resources/WordCapse/A.png"))
    {
        cout << "Failed to load letter A";
        exit(1);
    }
     */
    
    objects[2].setTexture(letterA);
    objects[2].setPosition(1060, 274);//

    Texture letterC;
    if (!letterC.loadFromFile("Resources/WordCapse/C.png"))
    {
        cout << "Failed to load letter C";
        exit(1);
    }
    objects[3].setTexture(letterC);
    objects[3].setPosition(920, 134);//

    /*
    Texture letterC2;
    if (!letterC2.loadFromFile("C.png"))
    {
        cout << "Failed to load letter C";
        exit(1);
    }
     */
    objects[4].setTexture(letterC);
    objects[4].setPosition(850, 274);//

    /*
    Texture letterC3;
    if (!letterC3.loadFromFile("C.png"))
    {
        cout << "Failed to load letter C";
        exit(1);
    }
     */
    objects[5].setTexture(letterC);
    objects[5].setPosition(1130, 274);

    /*
    Texture letterC4;
    if (!letterC4.loadFromFile("C.png"))
    {
        cout << "Failed to load letter C";
        exit(1);
    }
     */
    objects[6].setTexture(letterC);
    objects[6].setPosition(990, 414);//

    Texture letterE;
    if (!letterE.loadFromFile("Resources/WordCapse/E.png"))
    {
        cout << "Failed to load LETTER E" << endl;
        exit(1);
    }
    objects[7].setTexture(letterE);
    objects[7].setPosition(920, 414);//

    /*
    Texture letterE2;
    if (!letterE2.loadFromFile("E.png")) {
        cout << "Failed to load LETTER E" << endl;
        exit(1);
    }
     */
    objects[8].setTexture(letterE);
    objects[8].setPosition(1060, 204);

    /*
    Texture letterE3;
    if (!letterE3.loadFromFile("E.png")) {
        cout << "Failed to load LETTER E" << endl;
        exit(1);
    }
     */
    objects[9].setTexture(letterE);
    objects[9].setPosition(990, 344);

    Texture letterI;
    if (!letterI.loadFromFile("Resources/WordCapse/I.png"))
    {
        cout << "Failed to load LETTER I" << endl;
        exit(1);
    }
    objects[10].setTexture(letterI);
    objects[10].setPosition(990, 134);//

    Texture letterT;
    if (!letterT.loadFromFile("Resources/WordCapse/T.png"))
    {
        cout << "Failed to load LETTER T" << endl;
        exit(1);
    }
    objects[11].setTexture(letterT);
    objects[11].setPosition(1130, 204);//

    /*
    Texture letterT2;
    if (!letterT2.loadFromFile("T.png")) {
        cout << "Failed to load LETTER T" << endl;
        exit(1);
    }
     */
    objects[12].setTexture(letterT);
    objects[12].setPosition(1060, 414);//

    Texture letterM;
    if (!letterM.loadFromFile("Resources/WordCapse/M.png"))
    {
        cout << "Failed to load LETTER M" << endl;
        exit(1);
    }
    objects[13].setTexture(letterM);
    objects[13].setPosition(990, 204);//

    /*
    Texture letterM2;
    if (!letterM2.loadFromFile("M.png")) {
        cout << "Failed to load LETTER M" << endl;
        exit(1);
    }
     */
    objects[14].setTexture(letterM);
    objects[14].setPosition(920, 344);

    /*
    Texture letterM3;
    if (!letterM3.loadFromFile("M.png")) {
        cout << "Failed to load LETTER M" << endl;
        exit(1);
    }
     */
    objects[15].setTexture(letterM);
    objects[15].setPosition(1130, 414);//

    Texture letterN;
    if (!letterN.loadFromFile("Resources/WordCapse/N.png")) {
        cout << "Failed to load LETTER N" << endl;
        exit(1);
    }
    objects[16].setTexture(letterN);
    objects[16].setPosition(1060, 344);

    Texture letterO;
    if (!letterO.loadFromFile("Resources/WordCapse/O.png")) {
        cout << "Failed to load LETTER O" << endl;
        exit(1);
    }
    objects[17].setTexture(letterO);
    objects[17].setPosition(1060, 134);//

    /*
    Texture letterO2;
    if (!letterO2.loadFromFile("O.png")) {
        cout << "Failed to load LETTER O" << endl;
        exit(1);
    }
     */
    objects[18].setTexture(letterO);
    objects[18].setPosition(850, 344);//

    Texture letterP;
    if (!letterP.loadFromFile("Resources/WordCapse/P.png")) {
        cout << "Failed to load LETTER P" << endl;
        exit(1);
    }
    objects[19].setTexture(letterP);
    objects[19].setPosition(850, 204);//

    Texture letterR;
    if (!letterR.loadFromFile("Resources/WordCapse/R.png")) {
        cout << "Failed to load LETTER R" << endl;
        exit(1);
    }
    objects[20].setTexture(letterR);
    objects[20].setPosition(920, 204);//


    Texture letterS;
    if (!letterS.loadFromFile("Resources/WordCapse/S.png")) {
        cout << "Failed to load LETTER S" << endl;
        exit(1);
    }
    objects[21].setTexture(letterS);
    objects[21].setPosition(1130, 134);//

    /*
    Texture letterS2;
    if (!letterS2.loadFromFile("S.png")) {
        cout << "Failed to load LETTER S" << endl;
        exit(1);
    }
     */
    objects[22].setTexture(letterS);
    objects[22].setPosition(920, 274);//

    /*
    Texture letterS3;
    if (!letterS3.loadFromFile("S.png")) {
        cout << "Failed to load LETTER S" << endl;
        exit(1);
    }
     */
    objects[23].setTexture(letterS);
    objects[23].setPosition(850, 414);//

    /*
    Texture letterS4;
    if (!letterS4.loadFromFile("S.png")) {
        cout << "Failed to load LETTER S" << endl;
        exit(1);
    }
     */
    objects[24].setTexture(letterS);
    objects[24].setPosition(1130, 344);//

    for (int i = 0; i < 25; i++) {
        objects[i].setScale(1.0, 1.0);
    }

    //set el squares
    for (int i = 0; i < 26; i++)
    {
        squares[i].setSize(Vector2f(60, 60));
        squares[i].setFillColor(Color::White);
        squares[i].setOutlineThickness(5);
        squares[i].setOutlineColor(Color::Transparent);
    }
    //positions el squares
    squares[0].setPosition(100, 134);  //C
    squares[1].setPosition(170, 134);  //O
    squares[2].setPosition(240, 134);  //M
    squares[3].setPosition(310, 134);  //P
    squares[4].setPosition(380, 134);  //U
    squares[5].setPosition(450, 134);  //T
    squares[6].setPosition(520, 134);  //E
    squares[7].setPosition(590, 134);  //R
    squares[8].setPosition(660, 134);  //S
    squares[9].setPosition(240, 204);  //A
    squares[10].setPosition(240, 274); //S
    squares[11].setPosition(240, 344); //S
    squares[12].setPosition(240, 414); //C
    squares[13].setPosition(240, 484); //O
    squares[14].setPosition(240, 554); //M
    squares[15].setPosition(240, 624); //M
    squares[16].setPosition(590, 64);  //A
    squares[17].setPosition(590, 204); //T
    squares[18].setPosition(590, 274); //S
    squares[19].setPosition(660, 204); //C
    squares[20].setPosition(660, 274); //I
    squares[21].setPosition(660, 344); //E
    squares[22].setPosition(660, 414); //N
    squares[23].setPosition(660, 484); //C
    squares[24].setPosition(660, 554); //E

    bool played[25] = { false };
    bool allCorrect = false; // Flag to track if all letters are in correct places

    
    while (window.isOpen())
    {
        PollEventloop(window);
        
        if (stateChanged)
            break;
        
        //da 3shan n3raf meno el dimenesions
        // cout << "Mouse: " << Mouse::getPosition(wordscapes).x << " " << Mouse::getPosition(wordscapes).y << "\n";

        if (!paused && !lost && !gameWon)
        {
            //get mouse position
            Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));
            
            
            for (int n = 0; n < 4; n++)
            {
                text[n].setFont(wordscapesfont);
                text[n].setCharacterSize(30);
                text[n].setFillColor(Color::Black);
                text[n].setPosition(340.0f, 625.f);
            }
            
            //text appearance
            bool mouse0 = (mousePosition.x > 19 && mousePosition.x < 88
                           && mousePosition.y > 134 && mousePosition.y < 185);
            
            bool mouse1 = (mousePosition.x > 230 && mousePosition.x < 300
                           && mousePosition.y > 55 && mousePosition.y < 120);
            
            bool mouse2 = (mousePosition.x > 657 && mousePosition.x < 718
                           && mousePosition.y > 40 && mousePosition.y < 120);
            
            bool mouse3 = (mousePosition.x > 586 && mousePosition.x < 650
                           && mousePosition.y > 338 && mousePosition.y < 395);
            
            if (mouse0)
                text[0].setFillColor(Color::Black);
            else
                text[0].setFillColor(Color::Transparent);
            
            
            if (mouse1)
                text[1].setFillColor(Color::Black);
            else
                text[1].setFillColor(Color::Transparent);
            
            if (mouse2)
                text[2].setFillColor(Color::Black);
            else
                text[2].setFillColor(Color::Transparent);
            
            
            if (mouse3)
                text[3].setFillColor(Color::Black);
            else
                text[3].setFillColor(Color::Transparent);
            
            //drag
            for (int i = 0; i < 25; i++)
            {
                if (Mouse::isButtonPressed(Mouse::Button::Left) && !IsDragging(isDragging))
                {
                    if (objects[i].getGlobalBounds().contains(mousePosition))
                    {
                        isDragging[i] = true;
                        offset[i] = objects[i].getPosition() - mousePosition;
                    }
                }
                if (Mouse::isButtonPressed(Mouse::Button::Left) && isDragging[i])
                {
                    objects[i].setPosition(mousePosition + offset[i]);
                }
                else
                {
                    isDragging[i] = false;
                }
                
                /*
                 switch (event.type)
                 {
                 case Event::MouseButtonPressed:
                 if (event.mouseButton.button == Mouse::Left)
                 {
                 if (objects[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                 isDragging[i] = true;
                 offset[i] = objects[i].getPosition() - Vector2f(event.mouseButton.x, event.mouseButton.y);
                 }
                 }
                 break;
                 
                 case Event::MouseButtonReleased:
                 if (event.mouseButton.button == Mouse::Left)
                 {
                 isDragging[i] = false;
                 }
                 break;
                 
                 default:
                 break;
                 }
                 // If dragging is in progress, update the position of the object
                 if (isDragging[i])
                 {
                 objects[i].setPosition(Vector2f(Mouse::getPosition(wordscapes)) + offset[i]);
                 }
                 */
            }
            
            //el intersection (function mawgooda fo2)
            inter(3, 0, 100, 134, objects, squares, correctSound, played, allCorrect);
            inter(3, 12, 240, 414, objects, squares, correctSound, played, allCorrect);
            inter(3, 19, 660, 204, objects, squares, correctSound, played, allCorrect);
            inter(3, 23, 660, 484, objects, squares, correctSound, played, allCorrect);
            inter(4, 0, 100, 134, objects, squares, correctSound, played, allCorrect);
            inter(4, 12, 240, 414, objects, squares, correctSound, played, allCorrect);
            inter(4, 19, 660, 204, objects, squares, correctSound, played, allCorrect);
            inter(4, 23, 660, 484, objects, squares, correctSound, played, allCorrect);
            inter(5, 0, 100, 134, objects, squares, correctSound, played, allCorrect);
            inter(5, 12, 240, 414, objects, squares, correctSound, played, allCorrect);
            inter(5, 19, 660, 204, objects, squares, correctSound, played, allCorrect);
            inter(5, 23, 660, 484, objects, squares, correctSound, played, allCorrect);
            inter(6, 0, 100, 134, objects, squares, correctSound, played, allCorrect);
            inter(6, 12, 240, 414, objects, squares, correctSound, played, allCorrect);
            inter(6, 19, 660, 204, objects, squares, correctSound, played, allCorrect);
            inter(6, 23, 660, 484, objects, squares, correctSound, played, allCorrect); //C
            inter(17, 1, 170, 134, objects, squares, correctSound, played, allCorrect);
            inter(17, 13, 240, 484, objects, squares, correctSound, played, allCorrect);
            inter(18, 1, 170, 134, objects, squares, correctSound, played, allCorrect);
            inter(18, 13, 240, 484, objects, squares, correctSound, played, allCorrect);//O
            inter(13, 2, 240, 134, objects, squares, correctSound, played, allCorrect);
            inter(13, 14, 240, 554, objects, squares, correctSound, played, allCorrect);
            inter(13, 15, 240, 624, objects, squares, correctSound, played, allCorrect);
            inter(14, 2, 240, 134, objects, squares, correctSound, played, allCorrect);
            inter(14, 14, 240, 554, objects, squares, correctSound, played, allCorrect);
            inter(14, 15, 240, 624, objects, squares, correctSound, played, allCorrect);
            inter(15, 2, 240, 134, objects, squares, correctSound, played, allCorrect);
            inter(15, 14, 240, 554, objects, squares, correctSound, played, allCorrect);
            inter(15, 15, 240, 624, objects, squares, correctSound, played, allCorrect);//M
            inter(19, 3, 310, 134, objects, squares, correctSound, played, allCorrect);//P
            inter(0, 4, 380, 134, objects, squares, correctSound, played, allCorrect);//U
            inter(11, 5, 450, 134, objects, squares, correctSound, played, allCorrect);
            inter(11, 17, 590, 204, objects, squares, correctSound, played, allCorrect);
            inter(12, 5, 450, 134, objects, squares, correctSound, played, allCorrect);
            inter(12, 17, 590, 204, objects, squares, correctSound, played, allCorrect);//T
            inter(7, 6, 520, 134, objects, squares, correctSound, played, allCorrect);
            inter(7, 21, 660, 344, objects, squares, correctSound, played, allCorrect);
            inter(7, 24, 660, 554, objects, squares, correctSound, played, allCorrect);
            inter(8, 6, 520, 134, objects, squares, correctSound, played, allCorrect);
            inter(8, 21, 660, 344, objects, squares, correctSound, played, allCorrect);
            inter(8, 24, 660, 554, objects, squares, correctSound, played, allCorrect);
            inter(9, 6, 520, 134, objects, squares, correctSound, played, allCorrect);
            inter(9, 21, 660, 344, objects, squares, correctSound, played, allCorrect);
            inter(9, 24, 660, 554, objects, squares, correctSound, played, allCorrect);//E
            inter(20, 7, 590, 134, objects, squares, correctSound, played, allCorrect);//R
            inter(1, 9, 240, 204, objects, squares, correctSound, played, allCorrect);
            inter(1, 16, 590, 64, objects, squares, correctSound, played, allCorrect);
            inter(2, 9, 240, 204, objects, squares, correctSound, played, allCorrect);
            inter(2, 16, 590, 64, objects, squares, correctSound, played, allCorrect);//A
            inter(21, 8, 660, 134, objects, squares, correctSound, played, allCorrect);
            inter(21, 10, 240, 274, objects, squares, correctSound, played, allCorrect);
            inter(21, 11, 240, 344, objects, squares, correctSound, played, allCorrect);
            inter(21, 18, 590, 274, objects, squares, correctSound, played, allCorrect);
            inter(22, 8, 660, 134, objects, squares, correctSound, played, allCorrect);
            inter(22, 10, 240, 274, objects, squares, correctSound, played, allCorrect);
            inter(22, 11, 240, 344, objects, squares, correctSound, played, allCorrect);
            inter(22, 18, 590, 274, objects, squares, correctSound, played, allCorrect);
            inter(23, 8, 660, 134, objects, squares, correctSound, played, allCorrect);
            inter(23, 10, 240, 274, objects, squares, correctSound, played, allCorrect);
            inter(23, 11, 240, 344, objects, squares, correctSound, played, allCorrect);
            inter(23, 18, 590, 274, objects, squares, correctSound, played, allCorrect);
            inter(24, 8, 660, 134, objects, squares, correctSound, played, allCorrect);
            inter(24, 10, 240, 274, objects, squares, correctSound, played, allCorrect);
            inter(24, 11, 240, 344, objects, squares, correctSound, played, allCorrect);
            inter(24, 18, 590, 274, objects, squares, correctSound, played, allCorrect);//S
            inter(10, 20, 660, 274, objects, squares, correctSound, played, allCorrect);//I
            inter(16, 22, 660, 414, objects, squares, correctSound, played, allCorrect);//N
        }
        window.clear();
        //draw
        window.draw(ground);
        window.draw(owlet);

        //draw 24 square
        for (int i = 0; i < 25; i++) {
            window.draw(squares[i]);
        }

        // wordscapes.draw(square);
         //DRAW 24 letters
        for (int j = 0; j < 25; j++)
        {
            window.draw(objects[j]);
        }


        //draw el text
        for (int w = 0; w < 4; w++) {
            window.draw(text[w]);
        }
        
        window.draw(textH);

        CheckForUIChanges(window);
        
        window.display();
        if (allCorrect)
        {
            cout << "All correct: " << allCorrect << endl;
            //allFunctionsDone = true;
            gameWon = true; //Win Game
            
            /*
            static bool timerStarted = false;
            if (!timerStarted) {
                cwordscapes.restart();
                timerStarted = true;
            }

            if (cwordscapes.getElapsedTime().asSeconds() >= 2) 
            {
                wordscapes.close();
            }
             */

        }
    }
}
