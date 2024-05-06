#pragma once

#define initialScore 6

struct SnakeGame
{
    //Constructor
    SnakeGame(RenderWindow&);
    
    //Variables
    int blockSize = 40; //In pixels
    int numOfBlocksOnX, numOfBlocksOnY;
    
    //Textures, sprites, Fonts and Texts
    Texture backGroundBlockTexture, snakeBlockTexture;
    Sprite snakeSprite, backGroundBlockSprite;
    Font scoreFont;
    Text scoreText;

    int  score = initialScore; //the length of the snake
    char direction = 'D'; //Snake can only move in one direction at once

    //Functions
    void UpdateSnakeGame(RenderWindow&);
    void Draw(RenderWindow&);
    void SpawnFruit();
    void Movement();
    void KeyboardInput();
};

SnakeGame::SnakeGame(RenderWindow& window)
{
    snakeSprite.scale((float)blockSize / 16.f, (float)blockSize / 16.f);
    backGroundBlockSprite.scale((float)blockSize / 16.f, (float)blockSize / 16.f);
    //Initializing width and height count
    numOfBlocksOnX = window.getView().getSize().x / blockSize; //n is the number of blocks on x
    numOfBlocksOnY = window.getView().getSize().y / blockSize; //m is the number of blocks on y
    
    //Loading red and white tiles(16x16)pixels
    if(!backGroundBlockTexture.loadFromFile("Resources/Snake/white.png"))
        exit(1);
    if(!snakeBlockTexture.loadFromFile("Resources/Snake/red.png"))
        exit(1);
    snakeSprite.setTexture(snakeBlockTexture);
    backGroundBlockSprite.setTexture(backGroundBlockTexture);
    
    //Loading score font
    scoreFont.loadFromFile("Resources/Snake/SnakeScoreFont.ttf");
    scoreText.setFont(scoreFont);
    
    UpdateSnakeGame(window);
}

//Struct to hold the snake sections' Positions
struct SnakeSection
{
    float x, y;
}snake[20];

//Struct to hold the fruit's Position
struct Fruit
{
    float x, y;
}fruit;

void SnakeGame::UpdateSnakeGame(RenderWindow& window)
{
    //initializing the game's clock, timer and delay between each frame
    Clock clock;
    float timer = 0, delay = 0.06;
    
    while (clock.getElapsedTime().asSeconds() <= 2.5f)
    {
        RectangleShape goalScreenRect((Vector2f)window.getView().getSize());
        goalScreenRect.setFillColor(Color(0, 0, 0, 150));
        
        Text goalScreenText("Achieve a Score Of 5 To Get Your Clue!", gameFont, 40);
        goalScreenText.setOrigin(goalScreenText.getGlobalBounds().getSize() / 2.f + goalScreenText.getLocalBounds().getPosition());
        goalScreenText.setPosition(menuUiCenterX, menuUiPartsY * 3.f);
        
        window.clear();
        window.draw(goalScreenRect);
        window.draw(goalScreenText);
        window.display();
    }
    //Initialising the fruit and the snake
    snake[0].x = rand() % numOfBlocksOnX; snake[0].y = rand() % numOfBlocksOnY;
    SpawnFruit();
    
    //Initialzing the score text
    scoreText.setCharacterSize(30); scoreText.setFillColor(Color::Red);
    
    //Main GameLoop
    while (window.isOpen())
    {
        //Checks for pause Menu input, closing the window,
        PollEventloop(window);
        
        //To break out of the loop in case of change in the scene
        if (stateChanged)
            break;
        
        //Condition to stop updating the game if won, lost or paused
        if (!paused && !lost && !gameWon)
        {
            //keeping track of elapsed time in the timer variable, and restarting the clock each frame
            timer += clock.getElapsedTime().asSeconds();
            clock.restart();
            //Setting the score each frame
            scoreText.setString("SCORE: "+to_string(score - initialScore));
            
            //Slowing down the snake to be playable
            if (timer >= delay)
            {
                //Handles keybord Input and movement
                KeyboardInput();
                Movement();
                timer = 0;
            }
        }
        //handles claring, drwaing and displaying the frame
        Draw(window);
    }
        
}

void SnakeGame::KeyboardInput()
{
    if (direction == 'R' || direction == 'L')
    {
        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
            direction = 'D';
        
        else if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
            direction = 'U';
    }
    else if (direction == 'U' || direction == 'D')
    {
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
            direction = 'L';
        
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
            direction = 'R';
    }
}

void SnakeGame::SpawnFruit()
{
    //spawn the fruit at a random position in between the frame
    fruit.x = rand() % numOfBlocksOnX; fruit.y = rand() % numOfBlocksOnY;
}

void SnakeGame::Draw(RenderWindow& window)
{
    //Clearing the Previous Frame
    window.clear();
    
    //Drawing the backround
    for (int i = 0; i < numOfBlocksOnX; i++)
    {
        for (int j = 0; j < numOfBlocksOnY; j++)
        {
            backGroundBlockSprite.setPosition(i * blockSize, j * blockSize);
            window.draw(backGroundBlockSprite);
        }
    }
    
    //Drawing the score
    window.draw(scoreText);
    
    //Drawing the snake
    for (int i = 0; i < score; i++)
    {
        snakeSprite.setPosition(snake[i].x * blockSize, snake[i].y * blockSize);
        window.draw(snakeSprite);
    }
    
    //Drawing the fruit
    snakeSprite.setPosition(fruit.x * blockSize, fruit.y * blockSize);
    window.draw(snakeSprite);
    
    //Checking For Pause, Lose and win screens
    CheckForUIChanges(window);
    
    //Displaying the new frame
    window.display();
}

void SnakeGame::Movement()
{
    //setting each block to the block before it near the head of the snake
    for (int i = score; i > 0; i--)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    
    if (direction == 'L') snake[0].x--; //Move the head left
    if (direction == 'U') snake[0].y--; //Move the head up
    if (direction == 'R') snake[0].x++; //Move the head right
    if (direction == 'D') snake[0].y++; //Move the head down
    
    
    //Check for collision with the fruit
    if (snake[0].x == fruit.x && snake[0].y == fruit.y)
    {
        if (score-initialScore == 4)
            gameWon = true;
        score++;
        SpawnFruit();
    }
    
    //snake Edge Detection
    if (snake[0].x < 0) snake[0].x = numOfBlocksOnX-1; //left edge
    if (snake[0].x >= numOfBlocksOnX) snake[0].x = 0; //right edge
    if (snake[0].y < 0) snake[0].y = numOfBlocksOnY-1; //top edge
    if (snake[0].y >= numOfBlocksOnY) snake[0].y = 0; //bottom edge
    
    //Lose condition
    for (int i = 1; i < score; i++)
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            lost = true;
}
