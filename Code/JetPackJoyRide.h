struct jetpack
{
    Sprite rocket, laser, elec, elec_rot, jet;
    vector<Texture> rocketFrames, elecFrames, electrifiedFrames, elec_rotFrames;
    Texture rocket_txtr, elec_txtr, elec_rot_txtr;
    bool up = false, down = false;
    float time = 0;
};

void elec_fn(RenderWindow&, jetpack&);
void rocket_fn(RenderWindow&, jetpack&);
void electrified(RenderWindow&, jetpack&);
bool pixelPerfectCollision(const Sprite& sprite1, const Sprite& sprite2);
void jetPackGame(RenderWindow& window)
{
    jetpack game;
    Clock clock;
    while (clock.getElapsedTime().asSeconds() <= 3.f)
    {
        RectangleShape goalScreenRect((Vector2f)window.getView().getSize());
        goalScreenRect.setFillColor(Color(0, 0, 0, 150));
        
        Text goalScreenText("Survive for 10 seconds to get your clue!", gameFont, 40);
        goalScreenText.setOrigin(goalScreenText.getGlobalBounds().getSize() / 2.f + goalScreenText.getLocalBounds().getPosition());
        goalScreenText.setPosition(menuUiCenterX, menuUiPartsY * 3.f);
        
        window.clear();
        window.draw(goalScreenRect);
        window.draw(goalScreenText);
        window.display();
    }
    srand(time(0));
    Clock win;
    Text scoreText("Time: ", gameFont, 20);
    Texture bg1_txtr, bg2_txtr, bullet_txtr, txtr;
    if (!bg1_txtr.loadFromFile("Resources/JetPack/bg1.png"))//load background 1
    {
        cout << "Error Loading Background Texture!!/n";
        exit(1);
    }
    if (!bg2_txtr.loadFromFile("Resources/JetPack/bg2.png"))//load background 2
    {
        cout << "Error Loading Background Texture!!/n";
        exit(1);
    }
    vector<Texture> runningFrames;
    for (int i = 1; i <= 4; i++)//load running animation
    {
        if (!txtr.loadFromFile("Resources/JetPack/jet" + to_string(i) + ".png"))
        {
            cout << "Error Loading jet" << i << ".png" << endl;
            exit(1);
        }
        runningFrames.push_back(txtr);
    }
    vector<Texture> upFrames;
    if (!txtr.loadFromFile("Resources/JetPack/jetUp.png"))//load upward animation
    {
        cout << "Error Loading jetUp2.png" << endl;
        exit(1);
    }
    upFrames.push_back(txtr);
    vector<Texture> downFrames;
    if (!txtr.loadFromFile("Resources/JetPack/jetDown.png"))//load downward animation
    {
        cout << "Error Loading jetUp1.png" << endl;
        exit(1);
    }
    downFrames.push_back(txtr);
    for (int i = 1; i <= 2; i++)//load dying animation (getting electrified)
    {
        if (!txtr.loadFromFile("Resources/JetPack/electrified" + to_string(i) + ".png"))
        {
            cout << "Error Loading elec" << i << ".png" << endl;
            exit(1);
        }
        game.electrifiedFrames.push_back(txtr);
    }
    for (int i = 1; i <= 4; i++)//load electricity (obstacle 1) animation
    {
        if (!txtr.loadFromFile("Resources/JetPack/elec" + to_string(i) + ".png"))
        {
            cout << "Error Loading elec" << i << ".png" << endl;
            exit(1);
        }
        game.elecFrames.push_back(txtr);
    }
    for (int i = 1; i <= 4; i++)//load rocket (obstacle 2) animation
    {
        if (!game.rocket_txtr.loadFromFile("Resources/JetPack/rocket" + to_string(i) + ".png"))
        {
            cout << "Error Loading rocket" << i << ".png" << endl;
            exit(1);
        }
        game.rocketFrames.push_back(game.rocket_txtr);
    }
    vector<Sprite> bulletFrames;
    if (!bullet_txtr.loadFromFile("Resources/JetPack/bullet.png"))//load jetpack bullets
    {
        cout << "Error Loading bullet.png" << endl;
        exit(1);
    }
    Sprite bg1, bg2, bullets, bullet_right, bullet_left;;
    bg1.setTexture(bg1_txtr);
    bg2.setTexture(bg2_txtr);
    bg1.setPosition(0, 0);
    bg2.setPosition(bg1_txtr.getSize().x, 0);
    int currentFrame = 0;
    game.jet.setPosition(300, 550);
    game.jet.setTexture(runningFrames[currentFrame]);
    float frameDuration = 0.03f, elapsed = 0.08f;
    const float bulletcooldown = 0.06f;//Time between bullet projections
    game.up = false; game.down = false;
    Clock bullet_clock, jet_clock;
    
    while (window.isOpen())
    {
        PollEventloop(window);
        
        if (stateChanged)
            break;
        
        if (!lost && !paused && !gameWon) 
        {
            scoreText.setString("Time: "+to_string((int)win.getElapsedTime().asSeconds()));
            if (win.getElapsedTime().asSeconds() >= 10.f)
                gameWon = true;
            if (Keyboard::isKeyPressed(Keyboard::Space))//Upward Movement and bullet Positioning initialized when pressing space bar
            {
                if (bullet_clock.getElapsedTime().asSeconds() >= bulletcooldown)//Bullet Positioning and Rotation
                {
                    bullets.setTexture(bullet_txtr);
                    bullets.setPosition(360, game.jet.getPosition().y + 70);
                    bullets.setRotation(90);
                    bulletFrames.push_back(bullets);
                    bullet_right.setTexture(bullet_txtr);
                    bullet_left.setTexture(bullet_txtr);
                    bullet_right.setPosition(360, game.jet.getPosition().y + 70);
                    bullet_left.setPosition(360, game.jet.getPosition().y + 70);
                    bullet_left.setRotation(95);
                    bullet_right.setRotation(85);
                    bulletFrames.push_back(bullet_left);
                    bulletFrames.push_back(bullet_right);
                    bullet_clock.restart();
                }
                game.up = true;
                game.down = false;
                game.jet.setTexture(upFrames[0]);
            }
            else
            {
                game.down = true;
                game.up = false;
            }
            elapsed += game.time;
            for (size_t i = 0; i < bulletFrames.size(); i++)//Bullet Movement
            {
                bulletFrames[i].move(cos(bulletFrames[i].getRotation() * 3.14 / 180.0) * 2000* game.time, sin(bulletFrames[i].getRotation() * 3.14 / 180.0) *2000* game.time);
                
                if (bulletFrames[i].getPosition().y >= 640)//Erase Bullets when hitting ground
                {
                    bulletFrames.erase(bulletFrames.begin() + i);
                }
            }
            if (elapsed >= frameDuration)//Frame Update (Animation)
            {
                elapsed = 0;
                if (game.up && game.jet.getPosition().y > 10)
                {
                    game.jet.move(0, -900.0f* game.time);
                }
                if (game.down)
                {
                    
                    if (game.jet.getPosition().y >= 550)//Jet on ground
                    {
                        game.down = false;
                    }
                    else if (game.jet.getPosition().y < 550)
                    {
                        game.jet.move(0, 1300.0f * game.time);
                        game.jet.setTexture(downFrames[0]);
                    }
                }
                if (game.jet.getPosition().y >= 550)//Running Animation
                {
                    currentFrame = (currentFrame + 1) % runningFrames.size();
                    game.jet.setTexture(runningFrames[currentFrame]);
                    elapsed -= frameDuration;
                }
            }
            //Obstacle Function Call
            elec_fn(window, game);
            rocket_fn(window, game);
            bg1.move(-600.f* game.time, 0.0f);
            bg2.move(-600.f* game.time, 0.0f);
            //Background positioning
            if (bg1.getPosition().x + bg1_txtr.getSize().x < 0)
                bg1.setPosition(bg2.getPosition().x + bg2_txtr.getSize().x, 0);
            if (bg2.getPosition().x + bg2_txtr.getSize().x < 0)
                bg2.setPosition(bg1.getPosition().x + bg1_txtr.getSize().x, 0);
            
        }
        window.clear();
        window.draw(bg1);
        window.draw(bg2);
        for (double i = 0; i < bulletFrames.size(); i++)
        {
            window.draw(bulletFrames[i]);
        }
        window.draw(game.jet);
        window.draw(game.rocket);
        window.draw(game.elec);
        window.draw(scoreText);
        
        CheckForUIChanges(window);
        window.display();
        game.time = jet_clock.restart().asSeconds();
    }
}
void elec_fn(RenderWindow& window, jetpack& game)
{
    static Clock elec_clock;
    static int elecCurrentFrame = 0;
    static float elec_elapsed = 0;
    static bool elec_visible = true;
    float elecframeDuration = 0.08f;
    if (!elec_visible)
    {
        elec_visible = true;//leave function when elec goes off screen
        return;
    }
    if (elecCurrentFrame == 0 && elec_elapsed == 0)//set position and rotation once
    {
        game.elec.setPosition(1500, (rand() % 171) + 280);
        game.elec.setRotation(rand() % 361);
    }
    elec_elapsed += elec_clock.restart().asSeconds();
    game.elec.setTexture(game.elecFrames[elecCurrentFrame]);
    if (elec_elapsed >= elecframeDuration)//Electricity Animation
    {
        elecCurrentFrame = (elecCurrentFrame + 1) % game.elecFrames.size();
        game.elec.setTexture(game.elecFrames[elecCurrentFrame]);
        elec_elapsed -= elecframeDuration;
    }
    game.elec.move(-600.f* game.time, 0);
    if (game.elec.getPosition().x <= -200)
    {
        elec_visible = false;
        elecCurrentFrame = 0;
        elec_elapsed = 0;
    }
    if (pixelPerfectCollision(game.jet, game.elec))//Check for collision
        electrified(window, game);
}
void rocket_fn(RenderWindow& window, jetpack& game)
{
    static Clock rocket_clock;
    static int rocketCurrentFrame = 0;
    static float rocket_elapsed = 0;
    static bool rocket_visible = true;
    float rocketframeDuration = 0.05f;
    if (!rocket_visible)
    {
        rocket_visible = true;//leave function when rocket goes off screen
        return;
    }
    if (rocketCurrentFrame == 0 && rocket_elapsed == 0)//set position once
    {
        game.rocket.setPosition(1300, (rand() % 601) + 50);
    }
    rocket_elapsed += rocket_clock.restart().asSeconds();
    game.rocket.setTexture(game.rocketFrames[rocketCurrentFrame]);
    if (rocket_elapsed >= rocketframeDuration)//Rocket Animation
    {
        rocketCurrentFrame = (rocketCurrentFrame + 1) % game.rocketFrames.size();
        game.rocket.setTexture(game.rocketFrames[rocketCurrentFrame]);
        rocket_elapsed -= rocketframeDuration;
    }
    game.rocket.move(-1200.f * game.time, 0);
    if (game.rocket.getPosition().x < -75)
    {
        rocket_visible = false;
        rocketCurrentFrame = 0;
        rocket_elapsed = 0;
    }
    if (game.jet.getGlobalBounds().intersects(game.rocket.getGlobalBounds()))//Check for collision
        electrified(window, game);
}
void electrified(RenderWindow& window, jetpack& game)
{
    //Negate movement
    game.down = false;
    game.up = false;

    static Clock electrified_clock;
    static Clock die;
    static int electrifiedCurrentFrame = 0;
    static float electrified_elapsed = 0;
    float electrifiedframeDuration = 0.02f;
    electrified_elapsed += electrified_clock.restart().asSeconds();
    game.jet.setTexture(game.electrifiedFrames[electrifiedCurrentFrame]);
    if (electrified_elapsed >= electrifiedframeDuration)//Dying Animation
    {
        electrifiedCurrentFrame = (electrifiedCurrentFrame + 1) % game.electrifiedFrames.size();
        game.jet.setTexture(game.electrifiedFrames[electrifiedCurrentFrame]);
        electrified_elapsed -= electrifiedframeDuration;
        if (electrifiedCurrentFrame == 0)
            lost = true;//DIEEEE
    }
}
bool pixelPerfectCollision(const Sprite& sprite1, const Sprite& sprite2)
{
    FloatRect intersection;
    if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds(), intersection))
    {
        IntRect rect1 = sprite1.getTextureRect();
        IntRect rect2 = sprite2.getTextureRect();
        Image image1 = sprite1.getTexture()->copyToImage();
        Image image2 = sprite2.getTexture()->copyToImage();

        //Go over each pixel
        for (int i = intersection.left; i < intersection.left + intersection.width; i++)
        {
            for (int j = intersection.top; j < intersection.top + intersection.height; j++)
            {
                //Bring pixel coordinates into the sprites' local space
                Vector2f sprite1Pos = sprite1.getInverseTransform().transformPoint(i, j);
                Vector2f sprite2Pos = sprite2.getInverseTransform().transformPoint(i, j);

                //Ensuring pixel coordiantes are within valid bounds
                if (sprite1Pos.x >= 0 && sprite1Pos.y >= 0 && sprite2Pos.x >= 0 && sprite2Pos.y >= 0 && sprite1Pos.x < rect1.width && sprite1Pos.y < rect1.height && sprite2Pos.x < rect2.width && sprite2Pos.y < rect2.height)
                {
                    //Ensuring pixel coordiantes (now in local space) are within actual dimentions of texture images
                    if ((sprite1Pos.x + rect1.left < image1.getSize().x) && (sprite1Pos.y + rect1.top < image1.getSize().y) && (sprite2Pos.x + rect2.left < image2.getSize().x) && (sprite2Pos.y + rect2.top < image2.getSize().y))
                    {
                        if (image1.getPixel(sprite1Pos.x + rect1.left, sprite1Pos.y + rect1.top).a > 0 && image2.getPixel(sprite2Pos.x + rect2.left, sprite2Pos.y + rect2.top).a > 0)//Get Transparency of the pixel and if not transparent (>0), collision is detected
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

