#pragma once

bool inmenu = true;
bool inmap = false;
bool inaboutus = false;
bool ininfo = false;

// ASSETS LOADING
Font font;

SoundBuffer owletmoveBuffer, startbuffer, clickbuffer, cluebuffer, wonbuffer;

Sound Cluefound, clicksound, owletmoveSound, startsound, won;

Texture backgroundTexture, startt, quit, info, emptyy, back, cslogo, one, nine, five, zero, seven, banner, win,
maptexture, cs, palace, edu, science, law, masscomm, start, csl, palacel, edul, sciencel, lawl, masscomml, csd, palaced, edud, scienced, lawd, masscommd, greendone, csbackground, char1, aboutustext;

Sprite background, Start, Quit, Info, Empty, Back, CSlogo, first, second, third, fourth, fifth, sixth, Banner,
Win, Gamemap, Start1, CS, Palace, Edu, Law, Science, massComm, csback, owlet, aboutus;

Sprite done[5];

Text infootext, credittext, infotext, cstext, edutext, lawtext, masstext, sctext, palacetext, enter;

bool infoname, text = false;

float soundCooldown;
Clock soundTimer;

Clock gameClock;
float deltaTime = 0;
float timer = 0;
float delay = 0.1;
int owletframe = 0;

void loadAssets(RenderWindow&);
void mapfunction(RenderWindow&);
void MainMenu(RenderWindow& window)
{
    loadAssets(window);
    
    while (window.isOpen())
    {
        if (stateChanged)
            break;
        
        //Variable For Mouse position
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        
        bool mousePressed = false;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            
            if (event.type == Event::MouseButtonPressed)
                mousePressed = true;
        }
        
        //Playing a clicking sound
        if (mousePressed)
            clicksound.play();
        
        Back.setPosition(110 , 60);
        Back.setScale(0.35, 0.35);
        
        //Main Menu
        if (inmenu)
        {
            //Start Button
            if (Start.getGlobalBounds().contains(mousePos))
            {
                Start.setScale(0.5, 0.5);
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    inmap = true;
                    inmenu = false;
                    startsound.play();
                }
            }
            else
                Start.setScale(0.45, 0.45);
            
            //Quit Button
            if (Quit.getGlobalBounds().contains(mousePos))
            {
                Quit.setScale(0.35, 0.35);
                
                if(mousePressed)
                {
                    mousePressed = false;
                    window.close();
                }
            }
            else
                Quit.setScale(0.3, 0.3);
            
            //Info Button
            if (Info.getGlobalBounds().contains(mousePos))
            {
                Info.setScale(1.1, 1.1);
                infoname = true;
                
                if(Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    ininfo = true;
                    inmenu = false;
                }
            }
            else
            {
                Info.setScale(0.9 , 0.9);
                infoname = false;
            }
            
            //About us Button
            if(aboutus.getGlobalBounds().contains(mousePos))
            {
                aboutus.setScale(0.63, 0.63);
                
                if(Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    inaboutus = true;
                    inmenu = false;
                }
            }
            else
                aboutus.setScale(0.55, 0.55);
            
            window.clear();
            window.draw(background);
            window.draw(Start);
            window.draw(Quit);
            window.draw(Info);
            window.draw(aboutus);
            
            if (infoname)
                window.draw(infootext);
            
            window.display();
        }
        
        //Loading the Map
        if (inmap)
            mapfunction(window);

        //About Us menu
        if (inaboutus)
        {
            if (Back.getGlobalBounds().contains(mousePos))
            {
                Back.setScale(0.35, 0.35);
                
                if (mousePressed)
                {
                    mousePressed = false;
                    inmenu = true;
                    inaboutus = false;
                }
            }
            else
                Back.setScale(0.3, 0.3);
            
            window.clear();
            window.draw(Empty);
            window.draw(credittext);
            window.draw(Back);
            window.draw(CSlogo);
            window.display();
        }
        
        //info Menu
        if (ininfo)
        {
            if (Back.getGlobalBounds().contains(mousePos))
            {
                Back.setScale(0.35, 0.35);
                
                if (mousePressed)
                {
                    mousePressed = false;
                    inmenu = true;
                    ininfo = false;
                }
            }
            else
                Back.setScale(0.3, 0.3);
            
            window.clear();
            window.draw(Empty);
            window.draw(infotext);
            window.draw(Back);
            window.display();
        }
    }
}

void loadAssets(RenderWindow& window)
{
    // LOADING THE ASSETS
    if (!font.loadFromFile("Resources/MainMenu/Media/font/font.otf"))
        cout << "Font failed to load" << endl;

    // SOUNDS
    if (!owletmoveBuffer.loadFromFile("Resources/MainMenu/Media/Sounds/mapmove.wav") ||
        !startbuffer.loadFromFile("Resources/MainMenu/Media/Sounds/startsound.wav") ||
        !clickbuffer.loadFromFile("Resources/MainMenu/Media/Sounds/click.wav") ||
        !cluebuffer.loadFromFile("Resources/MainMenu/Media/Sounds/cluefound.wav") ||
        !wonbuffer.loadFromFile("Resources/MainMenu/Media/Sounds/gamewon.wav"))

        cout << "Failed to load owlet move sound" << endl;

    Cluefound.setBuffer(cluebuffer);
    clicksound.setBuffer(clickbuffer);
    owletmoveSound.setBuffer(owletmoveBuffer);
    startsound.setBuffer(startbuffer);
    won.setBuffer(wonbuffer);
    soundCooldown = 0.6f;

    // ######################   Menu sprites and stuff  ####################
    if (!backgroundTexture.loadFromFile("Resources/MainMenu/Media/menu/wall.jpg") ||
        !startt.loadFromFile("Resources/MainMenu/Media/menu/start.png") ||
        !quit.loadFromFile("Resources/MainMenu/Media/menu/quit.png") ||
        !info.loadFromFile("Resources/MainMenu/Media/menu/info.png") ||
        !emptyy.loadFromFile("Resources/MainMenu/Media/menu/empty.png") ||
        !back.loadFromFile("Resources/MainMenu/Media/menu/back.png") ||
        !cslogo.loadFromFile("Resources/MainMenu/Media/menu/cslogo.png") ||
        !aboutustext.loadFromFile("Resources/MainMenu/Media/menu/aboutus1.png"))
    {
        cout << "failed to load background" << endl;
    }
    background.setTexture(backgroundTexture);
    Start.setTexture(startt);
    Quit.setTexture(quit);
    Info.setTexture(info);
    Empty.setTexture(emptyy);
    Back.setTexture(back);
    CSlogo.setTexture(cslogo);
    aboutus.setTexture(aboutustext);

    // Scale the sprite to fit the window size
    background.setScale(
        static_cast<float>(window.getView().getSize().x) / background.getLocalBounds().width,
        static_cast<float>(window.getView().getSize().y) / background.getLocalBounds().height);

    Empty.setScale(
        static_cast<float>(window.getView().getSize().x) / Empty.getLocalBounds().width,
        static_cast<float>(window.getView().getSize().y) / Empty.getLocalBounds().height);



    Start.setPosition(640, 440 );
    Start.setScale(0.45, 0.45 );

    Quit.setPosition(100 , 40);
    //Quit.setPosition(640 , 630);
    Quit.setScale(0.3 , 0.3);

    Info.setPosition(280, 550);
    Info.setScale(0.9, 0.9 );

    Back.setPosition(110 , 60 );
    Back.setScale(0.35, 0.35);

    CSlogo.setPosition(640, 670);
    CSlogo.setScale(0.6 , 0.6);

    //aboutus.setPosition(640, 630);
    aboutus.setPosition(1000, 550);
    aboutus.setScale(0.55 , 0.55);



    Start.setOrigin(Start.getTextureRect().width / 2, Start.getTextureRect().height / 2);
    Quit.setOrigin(Quit.getTextureRect().width / 2, Quit.getTextureRect().height / 2);
    Info.setOrigin(Info.getTextureRect().width / 2, Info.getTextureRect().height / 2);
    Back.setOrigin(Back.getTextureRect().width / 2, Back.getTextureRect().height / 2);
    CSlogo.setOrigin(CSlogo.getTextureRect().width / 2, CSlogo.getTextureRect().height / 2);
    aboutus.setOrigin(aboutus.getTextureRect().width / 2, aboutus.getTextureRect().height / 2);

    // text infotext
    infootext.setFont(font);
    infootext.setString("INFO");
    infootext.setCharacterSize(50);
    infootext.setFillColor(Color::White);
    infootext.setPosition(230, 605);

    // for credit and info text appearance
    infoname = false;



    //################### CREDIT STUFF #######################

    credittext.setFont(font);
    credittext.setString("Mostafa Hagras \t Nour Hany \n Ahmed Gohary \t Carol Hany \nYousef Wael \t Menna Ahmed \n \t\t \t Karim Amr ");
    credittext.setCharacterSize(62);
    credittext.setFillColor(Color::White);
    credittext.setPosition(270 , 310 );


    //############  INFO STUFF #############################


    infotext.setFont(font);
    infotext.setString("Welcome our champion to AinShams Treasure Hunt,\nIt's a game made from AinShams Students to AinShams Students.\n\n Help Owlet (the character) finish all the missions\n and find the 6 Clues \n \n Then you will join the Hall of Fame and you will be\n named the Champion of AinShams Treasure Hunt! ");
    infotext.setCharacterSize(48);
    infotext.setFillColor(Color::White);
    infotext.setPosition(50 , 135);



    // ############# CLUES ON THE MAP STUFF (NUMBERS) ########################



    if (!one.loadFromFile("Resources/MainMenu/Media/map/1.png") ||
        !nine.loadFromFile("Resources/MainMenu/Media/map/9.png") ||
        !five.loadFromFile("Resources/MainMenu/Media/map/5.png") ||
        !seven.loadFromFile("Resources/MainMenu/Media/map/7.png") ||
        !zero.loadFromFile("Resources/MainMenu/Media/map/0.png") ||
        !banner.loadFromFile("Resources/MainMenu/Media/map/banner.png"))
    {
        cout << "clue failed";
    }

    first.setTexture(one);
    second.setTexture(seven);
    third.setTexture(one);
    fourth.setTexture(nine);
    fifth.setTexture(five);
    sixth.setTexture(zero);
    Banner.setTexture(banner);

    first.setPosition(934, 60);
    second.setPosition(970, 60);
    third.setPosition(1010, 60);
    fourth.setPosition(1040, 60);
    fifth.setPosition(1080, 60);
    sixth.setPosition(1120, 62);

    Banner.setOrigin(Banner.getTextureRect().width / 2, Banner.getTextureRect().height / 2);
    Banner.setPosition(1030, 80);
    Banner.setScale(8, 4);




    float xs = 0.21;
    float ys = 0.17;


    first.setScale(xs, ys);
    second.setScale(xs, ys);
    third.setScale(xs, ys);
    fourth.setScale(xs, ys);
    fifth.setScale(xs, ys);
    sixth.setScale(xs, ys);



    // ################### WIN Photo #######################


    if (!win.loadFromFile("Resources/MainMenu/Media/inpalace/win.png")) {

        cout << "map failed to load";
    }
    Win.setTexture(win);

    // Scale the sprite to fit the window size
    Win.setScale(
        static_cast<float>(window.getView().getSize().x) / Win.getLocalBounds().width,
        static_cast<float>(window.getView().getSize().y) / Win.getLocalBounds().height);



    //#################   MAP STUFF #######################


    if (!maptexture.loadFromFile("Resources/MainMenu/Media/map/map0.jpg")) {

        cout << "map failed to load";
    }


    if (!cs.loadFromFile("Resources/MainMenu/Media/map/CS.png") ||
        !palace.loadFromFile("Resources/MainMenu/Media/map/palace.png") ||
        !edu.loadFromFile("Resources/MainMenu/Media/map/edu.png") ||
        !law.loadFromFile("Resources/MainMenu/Media/map/law.png") ||
        !science.loadFromFile("Resources/MainMenu/Media/map/science.png") ||
        !masscomm.loadFromFile("Resources/MainMenu/Media/map/masscomm.png") ||
        !start.loadFromFile("Resources/MainMenu/Media/map/Start.png"))
    {
        cout << "One or more photos failed to load" << endl;

    }


    if (!csl.loadFromFile("Resources/MainMenu/Media/map/CSlight.png") ||
        !palacel.loadFromFile("Resources/MainMenu/Media/map/palacelight.png") ||
        !edul.loadFromFile("Resources/MainMenu/Media/map/edulight.png") ||
        !sciencel.loadFromFile("Resources/MainMenu/Media/map/sciencelight.png") ||
        !lawl.loadFromFile("Resources/MainMenu/Media/map/lawlight.png") ||
        !masscomml.loadFromFile("Resources/MainMenu/Media/map/masscommlight.png"))

        cout << "light failed";



    if (!csd.loadFromFile("Resources/MainMenu/Media/map/CSdark.png") ||
        !palaced.loadFromFile("Resources/MainMenu/Media/map/palacedark.png") ||
        !edud.loadFromFile("Resources/MainMenu/Media/map/edudark.png") ||
        !scienced.loadFromFile("Resources/MainMenu/Media/map/sciencedark.png") ||
        !lawd.loadFromFile("Resources/MainMenu/Media/map/lawdark.png") ||
        !masscommd.loadFromFile("Resources/MainMenu/Media/map/masscommdark.png"))

        cout << "dark failed";


    cstext.setFont(font);
    cstext.setString("Computer Science");
    cstext.setCharacterSize(36);
    cstext.setFillColor(Color::Black);
    cstext.setPosition(100, 470);



    edutext.setFont(font);
    edutext.setString("Arts");
    edutext.setCharacterSize(40);
    edutext.setFillColor(Color::Black);
    edutext.setPosition(160, 10);


    lawtext.setFont(font);
    lawtext.setString("Law");
    lawtext.setCharacterSize(40);
    lawtext.setFillColor(Color::Black);
    lawtext.setPosition(150, 220);


    masstext.setFont(font);
    masstext.setString("Mass Communication");
    masstext.setCharacterSize(28);
    masstext.setFillColor(Color::Black);
    masstext.setPosition(1000, 450);

    sctext.setFont(font);
    sctext.setString("Sciences");
    sctext.setCharacterSize(37);
    sctext.setFillColor(Color::Black);
    sctext.setPosition(440, 490);

    palacetext.setFont(font);
    palacetext.setString("El-Zaafrana Palace");
    palacetext.setCharacterSize(36);
    palacetext.setFillColor(Color::Black);
    palacetext.setPosition(750, 130);


    Start1.setTexture(start);
    CS.setTexture(csd);
    Palace.setTexture(palaced);
    Edu.setTexture(edud);
    Law.setTexture(lawd);
    Science.setTexture(scienced);
    massComm.setTexture(masscommd);

    Gamemap.setTexture(maptexture);

    // Scale the sprite to fit the window size
    Gamemap.setScale(
        static_cast<float>(window.getView().getSize().x) / Gamemap.getLocalBounds().width,
        static_cast<float>(window.getView().getSize().y) / Gamemap.getLocalBounds().height);

    // Set positions for the majors
    CS.setPosition(200, 600);
    Palace.setPosition(930, 285);
    Edu.setPosition(250, 130);
    Law.setPosition(250, 370);
    massComm.setPosition(1100, 600);
    Science.setPosition(590, 620);
    Start1.setPosition(475, 20);

    Start1.setScale(0.3, 0.3);
    CS.setScale(0.36, 0.36);
    Palace.setScale(0.35, 0.35);
    Edu.setScale(0.35, 0.35);
    Law.setScale(0.35, 0.35);
    massComm.setScale(0.45, 0.45);
    Science.setScale(0.35, 0.35);



    CS.setOrigin(CS.getTextureRect().width / 2, CS.getTextureRect().height / 2);
    Palace.setOrigin(Palace.getTextureRect().width / 2, Palace.getTextureRect().height / 2);
    Edu.setOrigin(Edu.getTextureRect().width / 2, Edu.getTextureRect().height / 2);
    Law.setOrigin(Law.getTextureRect().width / 2, Law.getTextureRect().height / 2);
    massComm.setOrigin(massComm.getTextureRect().width / 2, massComm.getTextureRect().height / 2);
    Science.setOrigin(Science.getTextureRect().width / 2, Science.getTextureRect().height / 2);



    if (!greendone.loadFromFile("Resources/MainMenu/Media/map/greendone.png"))
    {

        cout << "Extras failed to load";
    }

    // ##############  DONE SPRITES##################
    float ds = 0.15;

    //   ARRAY OF DONE SPRITES

    for (int i = 0; i < 5; i++) {

        done[i].setTexture(greendone);
        done[i].setOrigin(done[i].getTextureRect().width / 2, done[i].getTextureRect().height / 2);
        done[i].setScale(ds, ds);
    }

    done[0].setPosition(410, 190);   //First done

    done[1].setPosition(380, 360); // second done

    done[2].setPosition(320, 580);   //third done

    done[3].setPosition(620, 500); //fourth done

    done[4].setPosition(920, 540);  //fifth done


    //#############################################

    text = false;

    // SPACE TO ENETR

    enter.setFont(font);
    enter.setString("|| Press Space to Enter ||");
    enter.setCharacterSize(32);
    enter.setFillColor(Color::Black);
    enter.setPosition(420, 20);


    // ###########################   MAP DONE  ###################

    //######### CS CLUE STUFF ###################



    if (!csbackground.loadFromFile("Resources/MainMenu/Media/incs/board.png"))
    {

        cout << "empty failed to load";
    }

    csback.setTexture(csbackground);

    // Scale the sprite to fit the window size
    csback.setScale(
        static_cast<float>(window.getView().getSize().x) / csback.getLocalBounds().width,
        static_cast<float>(window.getView().getSize().y) / csback.getLocalBounds().height);


    // ###############  Owlet creation  ##############
    if (!char1.loadFromFile("Resources/MainMenu/Media/char/charmove.png"))
    {

        cout << "char failed to load";
    }

    owlet.setTexture(char1);

    owlet.setTextureRect(IntRect(0, 0, 32, 32));

    owlet.setOrigin(owlet.getTextureRect().width / 2, owlet.getTextureRect().height / 2);
    owlet.setScale(2.6, 2.6);
    owlet.setPosition(550, 100);


    // ################  owlet done #####################
}

//owlet speed
float spd = 4.5;
void mapfunction(RenderWindow& window)
{
    Back.setPosition(80 , 30);
    // Calculate delta time
    deltaTime = gameClock.restart().asSeconds();
    
    // owlet Movement
    if (Keyboard::isKeyPressed(Keyboard::Right) &&
        owlet.getPosition().x + owlet.getGlobalBounds().width / 2 < window.getView().getSize().x)
    {
        owlet.move(spd, 0);
        owlet.setScale(2.6, 2.6);
        if (soundTimer.getElapsedTime().asSeconds() >= soundCooldown)
        {
            owletmoveSound.play();
            soundTimer.restart(); // Restart the timer after playing the sound
        }
    }
    
    if (Keyboard::isKeyPressed(Keyboard::Left)
        && owlet.getPosition().x - owlet.getGlobalBounds().width / 2 > 0)
    {
        owlet.move(-spd, 0);
        owlet.setScale(-2.6, 2.6);
        if (soundTimer.getElapsedTime().asSeconds() >= soundCooldown)
        {
            owletmoveSound.play();
            soundTimer.restart(); // Restart the timer after playing the sound
        }
        
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)
        && owlet.getPosition().y - owlet.getGlobalBounds().height / 2 > 0)
    {
        owlet.move(0, -spd);
        
        if (soundTimer.getElapsedTime().asSeconds() >= soundCooldown)
        {
            owletmoveSound.play();
            soundTimer.restart(); // Restart the timer after playing the sound
        }
    }
    
    if (Keyboard::isKeyPressed(Keyboard::Down)
        && owlet.getPosition().y + owlet.getGlobalBounds().height / 2 < window.getView().getSize().y)
    {
        owlet.move(0, spd);
        
        if (soundTimer.getElapsedTime().asSeconds() >= soundCooldown)
        {
            owletmoveSound.play();
            soundTimer.restart(); // Restart the timer after playing the sound
        }
    }
    
    // owlet Animation
    if (timer > delay)
    {
        owlet.setTexture(char1);
        owletframe = (owletframe + 1) % 6;
        
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            owlet.setTextureRect(IntRect(owletframe * 32, 0, 32, 32));
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            owlet.setTextureRect(IntRect(owletframe * 32, 0, 32, 32));
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            owlet.setTextureRect(IntRect(owletframe * 32, 0, 32, 32));
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            owlet.setTextureRect(IntRect(owletframe * 32, 0, 32, 32));
        }
        
        timer = 0;
    }
    
    timer += deltaTime;
    
    //Back button
    if (Back.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
    {
        Back.setScale(0.25, 0.25);
        
        if (Mouse::isButtonPressed(Mouse::Button::Left))
        {
            inmenu = true;
            inmap = false;
        }
    }
    else
        Back.setScale(0.2, 0.2);
    
    //Faculites
    //Arts
    if (!states[1].done)
    {
        if (owlet.getGlobalBounds().intersects(Edu.getGlobalBounds()))
        {
            Edu.setTexture(edul);
            Edu.setScale(0.39, 0.39);
            edutext.setCharacterSize(43);
            
            text = true;
            
            if (Keyboard::isKeyPressed(Keyboard::Space))
                SwitchCurrentState(window, 1);
        }
        else
        {
            Edu.setTexture(edu);
            Edu.setScale(0.35, 0.35);
            edutext.setCharacterSize(40);
            //text = false;
        }
    }
    else
        Edu.setTexture(edud);
    
    //Law
    if (!states[2].done)
    {
        if (owlet.getGlobalBounds().intersects(Law.getGlobalBounds()))
        {
            Law.setTexture(lawl);
            Law.setScale(0.4, 0.4);
            lawtext.setCharacterSize(43);
            
            text = true;
            
            if (Keyboard::isKeyPressed(Keyboard::Space))
                SwitchCurrentState(window, 2);
        }
        else
        {
            Law.setTexture(law);
            Law.setScale(0.35, 0.35);
            lawtext.setCharacterSize(40);
            //text = false;
        }
    }
    else
        Law.setTexture(lawd);
    
    //Computer Science
    if (!states[3].done)
    {
        if (owlet.getGlobalBounds().intersects(CS.getGlobalBounds()))
        {
            CS.setTexture(csl);
            CS.setScale(0.4, 0.4);
            cstext.setCharacterSize(43);
            
            text = true;
            
            if (Keyboard::isKeyPressed(Keyboard::Space))
                SwitchCurrentState(window, 3);
        }
        else
        {
            CS.setTexture(cs);
            CS.setScale(0.35, 0.35);
            cstext.setCharacterSize(40);
            //text = false;
        }
    }
    else
        CS.setTexture(csd);
    
    
    //Sciences
    if (!states[4].done)
    {
        if (owlet.getGlobalBounds().intersects(Science.getGlobalBounds()))
        {
            Science.setTexture(sciencel);
            Science.setScale(0.41, 0.41);
            sctext.setCharacterSize(37);
            
            text = true;
            
            if (Keyboard::isKeyPressed(Keyboard::Space))
                SwitchCurrentState(window, 4);
        }
        else
        {
            Science.setTexture(science);
            Science.setScale(0.35, 0.35);
            sctext.setCharacterSize(37);
            //text = false;
        }
    }
    else
        Science.setTexture(scienced);
        
    //Mass Commmunication
    if (!states[5].done)
    {
        if (owlet.getGlobalBounds().intersects(massComm.getGlobalBounds()))
        {
            massComm.setTexture(masscomml);
            massComm.setScale(0.5, 0.5);
            masstext.setCharacterSize(32);
            
            text = true;
            
            if (Keyboard::isKeyPressed(Keyboard::Space))
                SwitchCurrentState(window, 5);
        }
        else
        {
            massComm.setTexture(masscomm);
            massComm.setScale(0.45, 0.45);
            masstext.setCharacterSize(30);
            //text = false;
        }
    }
    else
        massComm.setTexture(masscommd);
                
    //Palace
    if (states[6].done)
        Palace.setTexture(palaced);
    else if (OpenPalace())
    {
        if (owlet.getGlobalBounds().intersects(Palace.getGlobalBounds()))
        {
            Palace.setTexture(palacel);
            Palace.setScale(0.4, 0.4);
            palacetext.setCharacterSize(38);
            
            text = true;
            
            if (Keyboard::isKeyPressed(Keyboard::Space))
                SwitchCurrentState(window, 6);
        }
        else
        {
            Palace.setTexture(palace);
            Palace.setScale(0.35, 0.35);
            palacetext.setCharacterSize(36);
            text = false;
        }
    }
    
        
    //Draw the Menu
    window.clear();
    window.draw(Gamemap);
    window.draw(Start1);
    window.draw(CS);
    window.draw(Palace);
    window.draw(Edu);
    window.draw(Law);
    window.draw(Science);
    window.draw(massComm);
    window.draw(cstext);
    window.draw(edutext);
    window.draw(lawtext);
    window.draw(sctext);
    window.draw(masstext);
    window.draw(palacetext);
    window.draw(Banner);
    window.draw(Back);
    
    if (states[1].done)
    {
        window.draw(done[0]);
        window.draw(first);
        window.draw(third);
    }
    if (states[2].done)
    {
        window.draw(done[1]);
        window.draw(second);
    }
    if (states[3].done)
    {
        window.draw(done[2]);
        window.draw(fourth);
    }
    if (states[4].done)
    {
        window.draw(done[3]);
        window.draw(fifth);
    }
    if (states[5].done)
    {
        window.draw(done[4]);
        window.draw(sixth);
    }
    
    if (text)
    {
        window.draw(enter);
        text = false;
    }
    
    window.draw(owlet);
    window.display();
}
