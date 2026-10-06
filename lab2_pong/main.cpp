#include <SFML/Graphics.hpp>
#include <string>

const sf::Keyboard::Key controls[4] = {
  sf::Keyboard::A, // Player1 UP
  sf::Keyboard::Z, // Player1 Down
  sf::Keyboard::Up, // Player2 UP
  sf::Keyboard::Down, // Player2 Down
};

// Parameters
const sf::Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;
const float time_step = 0.017f; // 60 fps

// Objects of the game
sf::CircleShape ball;
sf::RectangleShape paddles[2];

sf::Vector2f ballVelocity;
bool isPlayer1Serving = true;
const float initialVelocityX = 100.f;  // horizontal velocity
const float initialVelocityY = 60.f;   // vertical velocity
const float velocityMultiplier = 1.1f; // speed up 10% per bounce

sf::Font font;
sf::Text text;
int score1 = 0;
int score2 = 0;

void reset() {
  // reset paddle positions
  paddles[0].setPosition(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f);
  paddles[1].setPosition(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f);
  // reset ball position and velocity
  ball.setPosition(gameWidth / 2.f, gameHeight / 2.f);
  ballVelocity = { (isPlayer1Serving ? initialVelocityX : -initialVelocityX), initialVelocityY };

  // update score text
  text.setString(std::to_string(score1) + " - " + std::to_string(score2));
  // keep score text centred
  text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0.f);
}

void init() {
  // Set size and origin of paddles
  for (sf::RectangleShape &p : paddles) {
    p.setSize(paddleSize);
    p.setOrigin(paddleSize / 2.f);
  }

  // Set size and origin of ball
  ball.setRadius(ballRadius);
  ball.setOrigin(ballRadius, ballRadius);

  // Load font and set up text
  font.loadFromFile("resources/fonts/RobotoMono-Regular.ttf");
  text.setFont(font);
  text.setCharacterSize(24);

  reset();
}

void update(float dt) {
  // handle paddle movement
  float direction = 0.0f;
  if (sf::Keyboard::isKeyPressed(controls[0])) {
    direction--;
  }
  if (sf::Keyboard::isKeyPressed(controls[1])) {
    direction++;
  }
  paddles[0].move(sf::Vector2f(0.f, direction * paddleSpeed * dt));

  // player 2 paddle movement
  float direction2 = 0.0f;
  if (sf::Keyboard::isKeyPressed(controls[2])) {
    direction2--;
  }
  if (sf::Keyboard::isKeyPressed(controls[3])) {
    direction2++;
  }
  paddles[1].move(sf::Vector2f(0.f, direction2 * paddleSpeed * dt));

  // keep paddles on screen
  for (sf::RectangleShape &p : paddles) {
    const float py = p.getPosition().y;
    if (py > gameHeight - paddleSize.y / 2.f) {
      // bottom: put it back at the lowest allowed position
      p.setPosition(p.getPosition().x, gameHeight - paddleSize.y / 2.f);
    } else if (py < paddleSize.y / 2.f) {
      // top: put it back at the highest allowed position
      p.setPosition(p.getPosition().x, paddleSize.y / 2.f);
    }
  }
  
  // ball movement
  ball.move(ballVelocity * dt);

  // check ball collision
  const float bx = ball.getPosition().x;
  const float by = ball.getPosition().y;
  if (by > gameHeight) {
    // bottom wall
    ballVelocity.x *= velocityMultiplier;
    ballVelocity.y *= -velocityMultiplier;
    ball.move(sf::Vector2f(0.f, -10.f));
  } else if (by < 0) {
    // top wall
    ballVelocity.x *= velocityMultiplier;
    ballVelocity.y *= -velocityMultiplier;
    ball.move(sf::Vector2f(0.f, 10.f));
    } else if (bx > gameWidth) {
    // right wall: player 1 scored, player 2 serves next
    score1++;
    isPlayer1Serving = false;
    reset();
  } else if (bx < 0) {
    // left wall: player 2 scored, player 1 serves next
    score2++;
    isPlayer1Serving = true;
    reset();
    } else if (
      // ball is in line with or behind the paddle AND
      bx < paddleSize.x + paddleOffsetWall &&
      // ball is below the top edge of the paddle AND
      by > paddles[0].getPosition().y - (paddleSize.y * 0.5f) &&
      // ball is above the bottom edge of the paddle
      by < paddles[0].getPosition().y + (paddleSize.y * 0.5f)) {
    // bounce off the left paddle
    ballVelocity.x *= -velocityMultiplier;
    ballVelocity.y *= velocityMultiplier;
    ball.move(sf::Vector2f(10.f, 0.f));
    } else if (
      // ball is in line with or behind the paddle AND
      bx > gameWidth - paddleSize.x - paddleOffsetWall &&
      // ball is below the top edge of the paddle AND
      by > paddles[1].getPosition().y - (paddleSize.y * 0.5f) &&
      // ball is above the bottom edge of the paddle
      by < paddles[1].getPosition().y + (paddleSize.y * 0.5f)) {
    // bounce off the right paddle
    ballVelocity.x *= -velocityMultiplier;
    ballVelocity.y *= velocityMultiplier;
    ball.move(sf::Vector2f(-10.f, 0.f));
  }
}

void render(sf::RenderWindow &window) {
  // Draw Everything
  window.draw(paddles[0]);
  window.draw(paddles[1]);
  window.draw(ball);
  window.draw(text);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "PONG");
    init();
    sf::Clock clock;
    while (window.isOpen()) {
        const float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        window.clear();
        update(dt);
        render(window);
        sf::sleep(sf::seconds(time_step));
        window.display();
    }
    return 0;
}