#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

using namespace sf;

void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
// Where is the player/branch - Left or Right
enum class side { LEFT, RIGHT, NONE };
side branchPosition[NUM_BRANCHES];

int main() 
{
  // Create a video mode - sets resolution to display
  /* 
    change it to mintor resolution or else it will default back to
    original monitor resolution it supports 
  */
  VideoMode vm(960, 540);

  // Create and open window
  // "Timber!!!" used to give window a name
  // Edited for low res mode
  RenderWindow window(vm, "Timber!!!");
  View view(sf::FloatRect(0, 0, 1920, 1080));
  window.setView(view);

  // Create a texture to hold a graphic on the GPU
  Texture textureBackground;

  // Load a graphic into the texture
  textureBackground.loadFromFile("graphics/background.png");

  // Create a sprite
  Sprite spriteBackground;

  // Attach the texture to the sprite
  spriteBackground.setTexture(textureBackground);

  // Set the spriteBackground to cover the screen
  spriteBackground.setPosition(0, 0);

  // Make a tree sprite
  Texture textureTree;
  textureTree.loadFromFile("graphics/tree.png");
  Sprite spriteTree;
  spriteTree.setTexture(textureTree);
  spriteTree.setPosition(810, 0);

  // Add more trees
  Texture textureTree2;
  textureTree2.loadFromFile("graphics/tree2.png");
  Sprite spriteTree2;
  spriteTree2.setTexture(textureTree2);
  Sprite spriteTree3;
  spriteTree3.setTexture(textureTree2);
  Sprite spriteTree4;
  spriteTree4.setTexture(textureTree2);
  Sprite spriteTree5;
  spriteTree5.setTexture(textureTree2);
  Sprite spriteTree6;
  spriteTree6.setTexture(textureTree2);

  spriteTree2.setPosition(20, 0);
  spriteTree3.setPosition(300, -400);
  spriteTree4.setPosition(1300, -400);
  spriteTree5.setPosition(1500, -500);
  spriteTree6.setPosition(1900, 0);

  // Prepare the bee
  Texture textureBee;
  textureBee.loadFromFile("graphics/bee.png");
  Sprite spriteBee;
  spriteBee.setTexture(textureBee);
  spriteBee.setPosition(0, 800);
  // setting movement to bee as false
  bool beeActive = false;
  // speed of bee
  float beeSpeed = 0.0f;

  // making 3 cloud sprites
  Texture textureCloud;
  // Load cloud texture
  textureCloud.loadFromFile("graphics/cloud.png");

  // Making clouds with array
  const int NUM_CLOUDS = 6;
  Sprite clouds[NUM_CLOUDS];
  int cloudSpeeds[NUM_CLOUDS];
  bool cloudsActive[NUM_CLOUDS];

  for(int i = 0; i < NUM_CLOUDS; i++)
  {
    clouds[i].setTexture(textureCloud);
    clouds[i].setPosition(-300, i * 150);
    cloudsActive[i] = false;
    cloudSpeeds[i] = 0;
  }

  // 3 new sprites with same texture
  // Sprite spriteCloud1;
  // Sprite spriteCloud2;
  // Sprite spriteCloud3;
  // spriteCloud1.setTexture(textureCloud);
  // spriteCloud2.setTexture(textureCloud);
  // spriteCloud3.setTexture(textureCloud);
  // // Position of the clouds off screen
  // spriteCloud1.setPosition(0, 0);
  // spriteCloud2.setPosition(0, 150);
  // spriteCloud3.setPosition(0, 300);
  // // Making cloud not visible on screen
  // bool cloud1Active = false;
  // bool cloud2Active = false;
  // bool cloud3Active = false;
  // // Speed of clouds
  // float cloud1Speed = 0.0f;
  // float cloud2Speed = 0.0f;
  // float cloud3Speed = 0.0f;

  // Controlling time
  Clock clock;

  // Time bar
  RectangleShape timeBar;
  float timeBarStartWidth = 400;
  float timeBarHeight = 80;
  timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
  timeBar.setFillColor(Color::Red);
  timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

  Time gameTimeTotal;
  float timeRemaining = 6.0f;
  float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

  // Tracking game running or not
  bool paused = true;

  // Draw some text
  int score = 0;
  sf::Text messageText;
  sf::Text scoreText;
  sf::Text fpsText;

  // Choosing font
  Font font;
  font.loadFromFile("fonts/KOMIKAP_.ttf");

  // Setting font for our message
  messageText.setFont(font);
  scoreText.setFont(font);
  fpsText.setFont(font);

  // Set FPS text
  fpsText.setFillColor(Color::White);
  fpsText.setCharacterSize(100);
  fpsText.setPosition(1200, 20);

  // Assign the actual message
  messageText.setString("Press Enter to start");
  scoreText.setString("Score = 0");

  // Chaning size
  messageText.setCharacterSize(75);
  scoreText.setCharacterSize(100);

  // Set color
  messageText.setFillColor(Color::White);
  scoreText.setFillColor(Color::White);

  // Set position of text
  FloatRect textRect = messageText.getLocalBounds();
  messageText.setOrigin(textRect.left +
    textRect.width / 2.0f,
    textRect.top +
    textRect.height / 2.0f);
  messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
  scoreText.setPosition(20, 20);

  // Background for text
  RectangleShape rect1;
  rect1.setFillColor(Color(0, 0, 0, 150));
  rect1.setSize(Vector2f(600, 105));
  rect1.setPosition(0, 30);

  RectangleShape rect2;
  rect2.setFillColor(Color(0, 0, 0, 150));
  rect2.setSize(Vector2f(1000, 105));
  rect2.setPosition(1150, 30);

  // Prepare branches - 6 in number
  Texture textureBranch;
  textureBranch.loadFromFile("graphics/branch.png");
  // Set the texture for each branch sprite
  for(int i = 0; i < NUM_BRANCHES; i++)
  {
    branches[i].setTexture(textureBranch);
    branches[i].setPosition(-2000, -2000);
    // Set sprites origin to center
    // Spin it around without changing it's position
    branches[i].setOrigin(220, 20);
  }

  // Prepare player
  Texture texturePlayer;
  texturePlayer.loadFromFile("graphics/player.png");
  Sprite spritePlayer;
  spritePlayer.setTexture(texturePlayer);
  spritePlayer.setPosition(580, 720);

  // Player starting point on left
  side playerSide = side::LEFT;

  // Prepare gravestone
  Texture textureRIP;
  textureRIP.loadFromFile("graphics/rip.png");
  Sprite spriteRIP;
  spriteRIP.setTexture(textureRIP);
  spriteRIP.setPosition(600, 860);

  // Prepare axe
  Texture textureAxe;
  textureAxe.loadFromFile("graphics/axe.png");
  Sprite spriteAxe;
  spriteAxe.setTexture(textureAxe);
  spriteAxe.setPosition(700, 830);

  // Line the axe up with the tree
  const float AXE_POSITION_LEFT = 700;
  const float AXE_POSITION_RIGHT = 1075;

  // Prepare flying log
  Texture textureLog;
  textureLog.loadFromFile("graphics/log.png");
  Sprite spriteLog;
  spriteLog.setTexture(textureLog);
  spriteLog.setPosition(810, 720);

  // Log related status
  bool logActive = false;
  float logSpeedX = 1000;
  float logSpeedY = -1500;

  // Accept input
  bool acceptInput = false;

  // Prepare sound
  SoundBuffer chopBuffer;
  chopBuffer.loadFromFile("sound/chop.wav");
  Sound chop;
  chop.setBuffer(chopBuffer);

  SoundBuffer deathBuffer;
  deathBuffer.loadFromFile("sound/death.wav");
  Sound death;
  death.setBuffer(deathBuffer);

  SoundBuffer outoftimeBuffer;
  outoftimeBuffer.loadFromFile("sound/out_of_time.wav");
  Sound outOfTime;
  outOfTime.setBuffer(outoftimeBuffer);

  // control drawing of score
  int lastDrawn = 0;

  // Main game loop
  while(window.isOpen()) 
  {

    // handle player input
    Event event;
    while(window.pollEvent(event))
    {
      if(event.type == Event::KeyReleased && !paused)
      {
        // Listen key press again
        acceptInput = true;

        // hide the axe
        spriteAxe.setPosition(2000,
          spriteAxe.getPosition().y);
      }
    }


    if(Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
    }

    // Start the game
    if(Keyboard::isKeyPressed(Keyboard::Return))
    {
      paused = false;

      // Reset the time and the score
      score = 0;
      timeRemaining = 6;

      // Make all branches disappear
      for(int i = 1; i < NUM_BRANCHES; i++)
      {
        branchPosition[i] = side::NONE;
      }

      // Hidding gravestone
      spriteRIP.setPosition(675, 2000);

      // Positing player
      spritePlayer.setPosition(580, 720);
      acceptInput = true;
    }

    // Makign sure we are accepting input
    if(acceptInput)
    {
      // Handling pressing right cursor
      if(Keyboard::isKeyPressed(Keyboard::Right))
      {
        // make player on right
        playerSide = side::RIGHT;
        score++;

        // Add time
        timeRemaining += (2 / score) + .15;

        spriteAxe.setPosition(AXE_POSITION_RIGHT,
          spriteAxe.getPosition().y);

        spritePlayer.setPosition(1200, 720);

        // update braches
        updateBranches(score);

        // set fying log to left
        spriteLog.setPosition(810, 720);
        logSpeedX = -5000;
        logActive = true;

        acceptInput = false;

        chop.play();
      }

      // Handling pressing left cursor
      if(Keyboard::isKeyPressed(Keyboard::Left))
      {
        // make player on right
        playerSide = side::LEFT;
        score++;

        // Add time
        timeRemaining += (2 / score) + .15;

        spriteAxe.setPosition(AXE_POSITION_LEFT,
          spriteAxe.getPosition().y);

        spritePlayer.setPosition(580, 720);

        // update braches
        updateBranches(score);

        // set fying log to left
        spriteLog.setPosition(810, 720);
        logSpeedX = 5000;
        logActive = true;

        acceptInput = false;

        chop.play();
      }
    }
    
    // checking game is paused or not
    if(!paused)
    {
      // update the game
      Time dt = clock.restart();

      // Substract from the amount of time remaining
      timeRemaining -= dt.asSeconds();
      // Size up the time bar
      timeBar.setSize(Vector2f(timeBarWidthPerSecond *
        timeRemaining, timeBarHeight));

      if(timeRemaining <= 0.0f)
      {
        // pause the game
        paused = true;

        // Change the message shown to the player
        messageText.setString("Out of time!!");

        // Resposition the text based on its new size
        FloatRect textRect = messageText.getLocalBounds();
        messageText.setOrigin(textRect.left +
          textRect.width / 2.0f,
          textRect.top +
          textRect.height / 2.0f);
        messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

        outOfTime.play();
      }

      // Setup bee
      if(!beeActive) 
      {
        // Speed of bee
        srand((int)time(0) * 10);
        beeSpeed = (rand() % 200) + 200;

        // hieght og the bee
        srand((int)time(0) * 10);
        float height = (rand() % 500) + 500;
        spriteBee.setPosition(2000, height);
        beeActive = true;
      }
      else
      {
        spriteBee.setPosition(
          spriteBee.getPosition().x -
          (beeSpeed * dt.asSeconds()),
          spriteBee.getPosition().y);

        if(spriteBee.getPosition().x < -100)
        {
          beeActive = false;
        }
      }

      // Using arrays for clouds
      for(int i = 0; i < NUM_CLOUDS; i++)
      {
        if(!cloudsActive[i])
        {
          // speed of cloud
          srand((int)time(0) * i);
          cloudSpeeds[i] = (rand() % 200);

          // Height of cloud
          srand((int)time(0) * i);
          float height = (rand() % 150);
          clouds[i].setPosition(-200, height);
          cloudsActive[i] = true;
        }
        else
        {
          // Set new position
          clouds[i].setPosition(
            clouds[i].getPosition().x +
            (cloudSpeeds[i] * dt.asSeconds()),
            clouds[i].getPosition().y);
          
          // Check for right edge
          if(clouds[i].getPosition().x > 1920)
          {
            // new cloud in next frame
            cloudsActive[i] = false;
          }
        }
      }

      // Manage clouds
      // Cloud 1
      /*
      if (!cloud1Active)
      {

        // How fast is the cloud
        srand((int)time(0) * 10);
        cloud1Speed = (rand() % 200);

        // How high is the cloud
        srand((int)time(0) * 10);
        float height = (rand() % 150);
        spriteCloud1.setPosition(-200, height);
        cloud1Active = true;


      }
      else
      {

        spriteCloud1.setPosition(
          spriteCloud1.getPosition().x +
          (cloud1Speed * dt.asSeconds()),
          spriteCloud1.getPosition().y);

        // Has the cloud reached the right hand edge of the screen?
        if (spriteCloud1.getPosition().x > 1920)
        {
          // Set it up ready to be a whole new cloud next frame
          cloud1Active = false;
        }
      }
      // Cloud 2
      if (!cloud2Active)
      {

        // How fast is the cloud
        srand((int)time(0) * 20);
        cloud2Speed = (rand() % 200);

        // How high is the cloud
        srand((int)time(0) * 20);
        float height = (rand() % 300) - 150;
        spriteCloud2.setPosition(-200, height);
        cloud2Active = true;


      }
      else
      {

        spriteCloud2.setPosition(
          spriteCloud2.getPosition().x +
          (cloud2Speed * dt.asSeconds()),
          spriteCloud2.getPosition().y);

        // Has the cloud reached the right hand edge of the screen?
        if (spriteCloud2.getPosition().x > 1920)
        {
          // Set it up ready to be a whole new cloud next frame
          cloud2Active = false;
        }
      }

      if (!cloud3Active)
      {

        // How fast is the cloud
        srand((int)time(0) * 30);
        cloud3Speed = (rand() % 200);

        // How high is the cloud
        srand((int)time(0) * 30);
        float height = (rand() % 450) - 150;
        spriteCloud3.setPosition(-200, height);
        cloud3Active = true;


      }
      else
      {

        spriteCloud3.setPosition(
          spriteCloud3.getPosition().x +
          (cloud3Speed * dt.asSeconds()),
          spriteCloud3.getPosition().y);

        // Has the cloud reached the right hand edge of the screen?
        if (spriteCloud3.getPosition().x > 1920)
        {
          // Set it up ready to be a whole new cloud next frame
          cloud3Active = false;
        }
      }
      */

     // draw score and framerate after every 100 frames
     lastDrawn++;
     if(lastDrawn == 100)
     {
        // Update the score text
        std::stringstream ss;
        ss << "Score = " << score;
        scoreText.setString(ss.str());

        // draw fps
        std::stringstream ss2;
        ss2 << "FPS = " << 1/dt.asSeconds();
        fpsText.setString(ss2.str());
        lastDrawn = 0; 
     }

      // update the branch sprites
      for(int i = 0; i < NUM_BRANCHES; i++)
      {
        float height = i * 150;
        if(branchPosition[i] == side::LEFT)
        {
          // Move the sprite to left side
          branches[i].setPosition(610, height);
          // Flip the sprite round other way
          branches[i].setRotation(180);
        }
        else if(branchPosition[i] == side::RIGHT)
        {
          // Move the sprite to right side
          branches[i].setPosition(1330, height);
          // Sprite rotation setting - normal
          branches[i].setRotation(0);
        }
        else
        {
          // Hide the branch
          branches[i].setPosition(3000, height);
        }
      }

      // handle flying log
      if(logActive)
      {
        spriteLog.setPosition(
          spriteLog.getPosition().x +
          (logSpeedX * dt.asSeconds()),
          spriteLog.getPosition().y +
          (logSpeedY * dt.asSeconds()));

        // check if log reached right hand side or not
        if((spriteLog.getPosition().x < -100) ||
            (spriteLog.getPosition().x > 2000))
        {
          // set whole new log
          logActive = false;
          spriteLog.setPosition(810, 720);
        }
      }

      // player been squished check
      if(branchPosition[5] == playerSide)
      {
        // death
        paused = true;
        acceptInput = false;

        // Draw gravestone
        spriteRIP.setPosition(525, 760);

        // hide player
        spritePlayer.setPosition(2000, 660);

        // change the text of message
        messageText.setString("SQUISHED!!!");

        // center it on screen
        FloatRect textRect = messageText.getLocalBounds();

        messageText.setOrigin(textRect.left +
          textRect.width / 2.0f,
          textRect.top + textRect.height /  2.0f);

        messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

        death.play();        
      }
    }
    // end of pause block

    // draw on screen
    // clear everything from the last frame
    window.clear();

    // draw our game scene
    window.draw(spriteBackground);

    // Draw clouds
    // window.draw(spriteCloud1);
    // window.draw(spriteCloud2);
    // window.draw(spriteCloud3);
    for(int i = 0; i < NUM_CLOUDS; i++)
    {
      window.draw(clouds[i]);
    }

    window.draw(spriteTree2);
    window.draw(spriteTree3);
    window.draw(spriteTree4);
    window.draw(spriteTree5);
    window.draw(spriteTree6);

    // Draw branches
    for(int i = 0; i < NUM_BRANCHES; i++)
    {
      window.draw(branches[i]);
    }

    // Draw the tree
    window.draw(spriteTree);

    // Draw player
    window.draw(spritePlayer);

    // Draw axe
    window.draw(spriteAxe);

    // Draw flying log
    window.draw(spriteLog);

    // Draw gravestome
    window.draw(spriteRIP);

    // Draw backgrounds for text
    window.draw(rect1);
    window.draw(rect2);

    // Draw the insect
    window.draw(spriteBee);

    // Draw the score
    window.draw(scoreText);

    // Draw fpscounter
    window.draw(fpsText);

    // draw timebar
    window.draw(timeBar);
    
    // Draw the timebar
    window.draw(timeBar);

    if(paused)
    {
      // Draw the message
      window.draw(messageText);
    }

    // show everything we drew
    window.display();

  }
  return 0;
}

void updateBranches(int seed)
{
  // Move all the branches down one place
  for(int j = NUM_BRANCHES - 1; j > 0; j--)
  {
    branchPosition[j] = branchPosition[j - 1];
  }

  // Spawn a new branch at top of tree
  srand((int)time(0) + seed);
  int r = (rand() % 5);
  switch(r)
  {
    case 0:
      branchPosition[0] = side::LEFT;
      break;
    case 1:
      branchPosition[0] = side::RIGHT;
      break;
    default:
      branchPosition[0] = side::NONE;
      break;
  }
}