#pragma once

void MarioGame(RenderWindow& window)
{
    Clock clock;
    while (clock.getElapsedTime().asSeconds() <= 3.f)
    {
        RectangleShape goalScreenRect((Vector2f)window.getView().getSize());
        goalScreenRect.setFillColor(Color(0, 0, 0, 150));
        
        Text goalScreenText("Collect the coins to get your clue!", gameFont, 40);
        goalScreenText.setOrigin(goalScreenText.getGlobalBounds().getSize() / 2.f + goalScreenText.getLocalBounds().getPosition());
        goalScreenText.setPosition(menuUiCenterX, menuUiPartsY * 3.f);
        
        window.clear();
        window.draw(goalScreenRect);
        window.draw(goalScreenText);
        window.display();
    }
    RectangleShape rectangle;
    rectangle.setFillColor(Color::White);
    rectangle.setSize(Vector2f(1300, 200));
    rectangle.setPosition(0, 550);

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Resources/Mario/Background.jpeg"))
    {
        cerr << "Failed to load background" << endl;
        exit(1);
    }
    Sprite background(backgroundTexture);
    

    Texture ground;
    if(!ground.loadFromFile("Resources/Mario/ground.jpg"))
    {
        cout<<"error"<<endl;
        exit(1);
    }
    rectangle.setTexture(&ground);
    
    //3mlt array le texture elowl
    Texture character[2];

    character[0].loadFromFile("Resources/Mario/Owlet_Monster_Run_6.png");
    character[1].loadFromFile("Resources/Mario/Owlet_Monster_Idle_4.png");

    Sprite owl;
    owl.setTexture(character[0]);
    owl.setTextureRect(IntRect(0, 0, 32, 32));
    owl.setPosition(75, 300);
    owl.setScale(3, 3);
    owl.setOrigin(owl.getTextureRect().width / 2, owl.getTextureRect().height / 2);

Texture coinA;
    if(!coinA.loadFromFile("Resources/Mario/coin.png"))
    {
        cout<<"error\n";
    }
    Sprite coin(coinA);
    coin.setScale(0.04,0.04);
    coin.setPosition(400, 300);

    Texture s;
    if(!s.loadFromFile("Resources/Mario/spike.png"))
    {
        cout<<"error\n";
        exit(1);
    }
    Sprite spike(s);
    Sprite spike2(s);
    spike.setPosition(1400,750);
    spike.setScale(0.15,0.15);
    spike2.setScale(0.15, 0.15);
    spike2.setPosition(1400, 700);
    
    
    SoundBuffer winsound,losesound,jumpsound ,coinsound;
    winsound.loadFromFile("Resources/Mario/win.wav");
    losesound.loadFromFile("Resources/Mario/lose.wav");
    jumpsound.loadFromFile("Resources/Mario/jump.wav");
    coinsound.loadFromFile("Resources/Mario/coinmove.wav");
    Sound coinmove(coinsound);
    Sound win(winsound);
    Sound lose(losesound);
    Sound jump(jumpsound);
    

    Vector2f velocity ={ 0,0 };//bta3t elowl
    Vector2f velocity2 ={ 0,0 };//bta3t elcoin
    Vector2f velocity3 ={0,0};//bta3t el4ok
    float gravity = -10;
    float jumpHeight = 8.0f;
    bool grounded = false;//dy 3l4ane 2t2kd 2no 3la el2rd 2bl ma ynot
    Clock Clock;
    float deltaTime = 0;
    float delay = 0.1f;
    float time = 0;
    int i = 0;
    float distance=100.0f;//dy 3l4ane 27rk elcoin lma 22rb
    
    
    bool coinposition[4]={false,false,false,false};//array le positon

    while (window.isOpen()) 
    {
        Clock.restart();

        PollEventloop(window);
        
        if (stateChanged)
            break;

        if (!paused && !lost && !gameWon)
        {
            if (Keyboard::isKeyPressed(Keyboard::Right)&& owl.getPosition().x+owl.getGlobalBounds().width/2 <window.getView().getSize().x)
            {
                owl.setTexture(character[0]);
                owl.setScale(3, 3);// dy 3l4ane lma kont b5o4 ymen kan fyh space
                if (time < 0) {//animation
                    i++;
                    i = i % 6;
                    owl.setTextureRect(IntRect((i * 32), 0, 32, 32));
                    time = delay;
                }
                else {
                    time -= deltaTime;
                }
                
                // move the player
                velocity.x = 200 * deltaTime;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left) && owl.getPosition().x- owl.getGlobalBounds().width/2>0)
            {
                owl.setTexture(character[0]);
                
                owl.setScale(-3, 3);// dy 3l4ane lma kont b5o4 4mal kan fyh space
                
                if (time < 0) {//animation
                    
                    i++;
                    i = i % 6;
                    owl.setTextureRect(IntRect((i * 32), 0, 32, 32));
                    time = delay;
                    
                    
                }
                else {
                    time -= deltaTime;
                }
                
                // move the player
                velocity.x = -200 * deltaTime;
            }
            else {
                velocity.x = 0;//dy 3l4ane kan byt7rk mn8ar ma 2dos
                owl.setTexture(character[1]);
                if (time < 0) {
                    i++;
                    i = i % 4;
                    
                    owl.setTextureRect(IntRect((i * 32), 0, 32, 32));
                    time = delay;
                }
                else {
                    time -= deltaTime;
                }
                
            }
            
            if (Keyboard::isKeyPressed(Keyboard::Space) && grounded) {
                jump.play();
                owl.setTexture(character[1]);
                velocity.y -= jumpHeight;
                grounded = false;//3l4ane my3ml4 double jump
                
            }
            
            owl.move(velocity);
            
            if (owl.getGlobalBounds().intersects(rectangle.getGlobalBounds())) {
                velocity.y = 0;
                grounded = true;//3l4ane 2wl ma ylms elground y3rf ynot
            }
            else {
                velocity.y -= gravity * deltaTime;
            }
            
            if(coin.getGlobalBounds().intersects(rectangle.getGlobalBounds()))
            {
                velocity2.y=0;
            }
            else
            {
                velocity2.y-=gravity*deltaTime;
            }
            
            //collison elspike
            if(owl.getGlobalBounds().intersects(spike.getGlobalBounds()))
            {
                lose.play();
                distance=100;
                owl.setPosition(75, 300);
                spike.setPosition(1400,700);
                spike2.setPosition(1400, 700);
                coin.setPosition(400, 300);
                for(int i=0;i<4;i++)//bdl mktb el tlata = false
                {
                    coinposition[i]=false;
                }
                velocity3.x=0;
            }
            
            if(owl.getGlobalBounds().intersects(spike2.getGlobalBounds()))
            {
                lose.play();
                distance=100;
                velocity3={0,0};
                owl.setPosition(75, 300);
                spike.setPosition(1400,700);
                spike2.setPosition(1400, 700);
                coin.setPosition(400, 300);
                for(int i=0;i<4;i++)
                {
                    coinposition[i]=false;
                }
            }
            //collison bta3 elmksb
            if(owl.getGlobalBounds().intersects(coin.getGlobalBounds()))
            {
                win.play();
                gameWon = true;
                /*
                sleep(seconds(2));
                mario.close();
                 */
            }
            
            //lma 22rb elcoin ym4y
            if (!coinposition[0] && abs(owl.getPosition().x - coin.getPosition().x) < distance &&  abs(owl.getPosition().y - coin.getPosition().y) < distance)
                
            {
                coinmove.play();
                coin.setPosition(750, 300);
                spike.setPosition(385,516);
                coinposition[0]=true;
            }
            
            if (!coinposition[1] && abs(owl.getPosition().x - coin.getPosition().x) < distance &&  abs(owl.getPosition().y - coin.getPosition().y) < distance)
            {
                coinmove.play();
                coin.setPosition(1000, 300);
                spike2.setPosition(735, 516);
                coinposition[1]=true;
            }
            
            if (!coinposition[2] && abs(owl.getPosition().x - coin.getPosition().x) < distance &&  abs(owl.getPosition().y - coin.getPosition().y) < distance)
            {
                coinmove.play();
                coin.setPosition(100, 300);
                coinposition[2]=true;
                distance=300;
            }
            
            if (!coinposition[3] && abs(owl.getPosition().x - coin.getPosition().x) < distance &&  abs(owl.getPosition().y - coin.getPosition().y) < distance)
            {
                velocity3.x-=400*deltaTime;
                coinposition[3]=true;
            }
        }
        
        spike2.move(velocity3);
        coin.move(velocity2);
        
        window.clear(Color::White);
        window.draw(background);
        window.draw(rectangle);
        window.draw(coin);
        window.draw(spike);
        window.draw(spike2);
        window.draw(owl);
        
        CheckForUIChanges(window);
        
        window.display();

        deltaTime = Clock.getElapsedTime().asSeconds();
    }
}


