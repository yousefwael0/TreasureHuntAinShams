#pragma once

//#include"SFML/System.hpp"
//#include"SFML/Network.hpp"
//#include<vector>
//#include<cstdlib>
//#include<string>
#define winScore 5

void PlaneGame(RenderWindow& window)
{
    Clock clock;
    while (clock.getElapsedTime().asSeconds() <= 3.f)
    {
        RectangleShape goalScreenRect((Vector2f)window.getView().getSize());
        goalScreenRect.setFillColor(Color(0, 0, 0, 150));
        
        Text goalScreenText("Kill 5 enemies to get your clue!", gameFont, 40);
        goalScreenText.setOrigin(goalScreenText.getGlobalBounds().getSize() / 2.f + goalScreenText.getLocalBounds().getPosition());
        goalScreenText.setPosition(menuUiCenterX, menuUiPartsY * 3.f);
        
        window.clear();
        window.draw(goalScreenRect);
        window.draw(goalScreenText);
        window.display();
    }
    srand(time(NULL));
    SoundBuffer buffer1;
    buffer1.loadFromFile("Resources/PlaneGame/Buffers/hitenemy.wav");
    Sound soundhit;
    soundhit.setBuffer(buffer1);

    SoundBuffer buffer2;
    buffer2.loadFromFile("Resources/PlaneGame/Buffers/cluefound.wav");
    Sound cluefound;
    cluefound.setBuffer(buffer2);


    Texture spaceText;
    spaceText.loadFromFile("Resources/PlaneGame/Textures/space1.png.png");

    Sprite space;
    space.setTexture(spaceText);
    
    space.setScale(
        static_cast<float>(window.getView().getSize().x) / space.getLocalBounds().width,
        static_cast<float>(window.getView().getSize().y) / space.getLocalBounds().height);

    Texture coinenemyText;
    Sprite coinenemy;
    coinenemyText.loadFromFile("Resources/PlaneGame/Textures/coinenemy.png.png");
    coinenemy.setTexture(coinenemyText);
    coinenemy.setScale(0.3f, 0.3f);

    std::vector<Sprite> coins;


    //enemy
    Texture enemyText;
    Sprite enemy;
    enemyText.loadFromFile("Resources/PlaneGame/Textures/enemy.png.png");
    enemy.setTexture(enemyText);
    enemy.setScale(Vector2f(0.2f, 0.2f));
    std::vector<Sprite> enemies;
    enemies.push_back(Sprite(enemy));
    
    int enemySpawnTimer = 80;
    int enemiesDestroyedcount = 0;

    //plane
    Texture planeText;
    Sprite plane;
    planeText.loadFromFile("Resources/PlaneGame/Textures/plane5.png.png");
    plane.setTexture(planeText);
    plane.setScale(0.1f, 0.1f);
    int shootTimer = 0;

    //hpBar
    int hp = 10;
    RectangleShape hpBar;
    hpBar.setFillColor(Color::Red);
    hpBar.setSize(Vector2f((float)hp * 20.f, 20.f));
    hpBar.setPosition(500.f, 10.f);


    //fire
    Texture fireText;
    Sprite fire;
    std::vector<Sprite> fires;
    fires.push_back(Sprite(fire));
    fireText.loadFromFile("Resources/PlaneGame/Textures/fire5.png.png");
    fire.setTexture(fireText);
    fire.setScale(0.5f, 0.5f);
    
    //Text to display score
    Text scoreText("Score:", gameFont, 30);
    scoreText.setFillColor(Color::Red);

    //game loop
    while (window.isOpen())
    {

        PollEventloop(window);
        
        if (stateChanged)
            break;
        
        if (!paused && !lost && !gameWon) 
        {
            //Update
            //plane updates
            //float mousepos = window.mapPixelToCoords(Mouse::getPosition(window)).y;
            plane.setPosition(plane.getPosition().x, window.mapPixelToCoords(Mouse::getPosition(window)).y);
            
            if (plane.getPosition().y > window.getView().getSize().y - plane.getGlobalBounds().width)
                plane.setPosition(plane.getPosition().x, window.getView().getSize().y - plane.getGlobalBounds().width);
            
            if (plane.getPosition().y < 0)
                plane.setPosition(plane.getPosition().x, 0);
            
            
            //shooting
            if (shootTimer < 6)
                shootTimer++;
            
            if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= 6 )  //shooting
            {
                fire.setPosition(plane.getPosition().x + plane.getGlobalBounds().width/2, plane.getPosition().y + plane.getGlobalBounds().height/2);
                fire.move(40, 0);
                fires.push_back(Sprite(fire));
                soundhit.play();
                shootTimer = 0;
            }
            for (size_t i = 0; i < fires.size(); i++)
            {
                
                for (size_t j = 0; j < enemies.size(); j++)
                {
                    if (fires[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds()))
                    {
                        
                        fires.erase(fires.begin() + i);
                        enemies.erase(enemies.begin() + j);
                        
                        i--;
                        enemiesDestroyedcount++;
                        
                        break;
                    }
                }
            }
            
            
            //enemy updates
            for (size_t i = 0; i < enemies.size(); i++)
            {
                enemies[i].move(-9.f, 0.f);
                if (enemies[i].getPosition().x < 0)
                    enemies.erase(enemies.begin() + i);
            }
            if (enemySpawnTimer < 90)
            {
                enemySpawnTimer++;
            }
            
            if (enemySpawnTimer >= 90)
            {
                enemy.setPosition(window.getView().getSize().x, rand() % int((float)window.getView().getSize().y - enemy.getGlobalBounds().height));
                enemies.push_back(Sprite(enemy));
                enemySpawnTimer = 0;
            }
            
            for (size_t i = 0; i < enemies.size(); i++)
            {
                if (plane.getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
                {
                    hp--;
                    enemies.erase(enemies.begin() + i);
                    
                }
            }
            //coin
            if (enemiesDestroyedcount >= 10)
            {
                coinenemy.setPosition(window.getView().getSize().x, rand() % int((float)window.getView().getSize().y - coinenemy.getGlobalBounds().height));
                coins.push_back(Sprite(coinenemy));
                coinenemy.move(-20, 0);
                enemiesDestroyedcount = 0;
                
            }
            // Update coin enemy movement
            for (size_t i = 0; i < coins.size(); i++)
            {
                coins[i].move(-20, 0);
            }
            
            for (size_t i = 0; i < fires.size(); i++) {
                for (size_t j = 0; j < coins.size(); j++) {
                    if (fires[i].getGlobalBounds().intersects(coins[j].getGlobalBounds())) {
                        
                        fires.erase(fires.begin() + i);
                        coins.erase(coins.begin() + j);
                        cluefound.play();
                        std::cout << "win";
                        
                        break;
                    }
                }
            }
            for (size_t i = 0; i < coins.size(); i++)
            {
                
                if (plane.getGlobalBounds().intersects(coins[i].getGlobalBounds()))
                {
                    
                    hp -= 5;
                    coins.erase(coins.begin() + i);
                    break;
                }
            }
            
            //Score
            scoreText.setString("Score: " + to_string(enemiesDestroyedcount));
            
            //hp update
            hpBar.setSize(Vector2f((float)hp * 20.f, 20.f));
            
            if (hp <= 0)
                lost = true;
            
            if (enemiesDestroyedcount >= winScore)
                gameWon = true;
        }
    
        window.clear();


        //draw anything
        window.draw(space);
        window.draw(plane);

        for (size_t i = 0; i < enemies.size(); i++)
        {
            window.draw(enemies[i]);
        }

        for (size_t i = 0; i < fires.size(); i++)
        {

            window.draw(fires[i]);
            fires[i].move(40 , 0);
            if (fires[i].getPosition().x > window.getView().getSize().x)
            {
                fires.erase(fires.begin() + i);
            }
        }
        
        for (size_t i = 0; i < coins.size(); i++)
        {
            window.draw(coins[i]);
        }

        if (hp > 0)
        {
            window.draw(hpBar);
        }
        window.draw(scoreText);
        
        CheckForUIChanges(window);
        
        window.display();
        //end of app
    }
}

