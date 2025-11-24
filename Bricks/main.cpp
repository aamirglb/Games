#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <cstdint>

constexpr int32_t width{800}, height{650};
constexpr float ballRadius{10.0F};
// sf::Vector2f ballVelocity{2.0F, 2.0F};
 float ballVelocity{4.0F};
constexpr float paddleWidth{100.f}, paddleHeight{20.f}, paddleVelocity{6.f};

struct Paddle
{
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    Paddle(float mx, float my)
    {
        shape.setPosition({mx, my});
        shape.setSize({paddleWidth, paddleHeight});
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin({paddleWidth / 2.0F, paddleHeight / 2.0F});
    }

    void update()
    {
        shape.move(velocity);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && left() > 0) {
            velocity.x = -paddleVelocity;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && right() < 600+4) {
            velocity.x = paddleVelocity;
        } else {
            velocity.x = 0;
        }
    }

    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left() { return x() - shape.getSize().x / 2.0F; }
    float right() { return x() + shape.getSize().x / 2.0F; }
    float top() { return y() - shape.getSize().y / 2.0F; }
    float bottom() { return y() - shape.getSize().y / 2.0F; }
};

struct Ball
{
    sf::CircleShape shape;
    sf::Vector2f m_Pos{};
    sf::Vector2f m_Velocity{};

    Ball(sf::Vector2f pos)
    {
        m_Pos = pos;
        shape.setPosition(m_Pos);
        shape.setRadius(ballRadius);
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin({ballRadius, ballRadius});
    }

    void SetVelocity(sf::Vector2f vel)
    {
        m_Velocity = vel;
    }

    void Update()
    {
        shape.move(m_Velocity);

        if(left() < 0) m_Velocity.x = ballVelocity;
        // else if(right() > width) m_Velocity.x = -ballVelocity;
        else if(right() > 600+4) m_Velocity.x = -ballVelocity;

        if(top() < 0) m_Velocity.y = ballVelocity;
        else if(bottom() > 600+4) m_Velocity.y = -ballVelocity;
    }

    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left() { return x() - shape.getRadius(); }
    float right() { return x() + shape.getRadius(); }
    float top() { return y() - shape.getRadius(); }
    float bottom() { return y() + shape.getRadius(); }
};

template <typename T1, typename T2>
bool isColliding(T1& obj1, T2& obj2)
{
    return obj1.right() >= obj2.left() && obj1.left() <= obj2.right()
    && obj1.bottom() >= obj2.top() && obj1.top() <= obj2.bottom();
}

void checkForCollision(Paddle& paddle, Ball& ball)
{
    if(isColliding(paddle, ball))
    {
        ball.m_Velocity.y = -ballVelocity;

        if(ball.x() < paddle.x())
        {
            ball.m_Velocity.x = -ballVelocity;
        }
        else
        {
            ball.m_Velocity.x = ballVelocity;
        }
    }
}

int main()
{
    sf::Clock clock;
    int32_t frameCount{};

    sf::Vector2f pos{width/2, height/2};
    sf::Vector2f dir{1, 0};
    Ball ball{pos};
    ball.SetVelocity({ballVelocity, ballVelocity});

    Paddle paddle{600/2, 600 - 40};

    sf::RenderWindow window{sf::VideoMode({width, height}), "Bricks Game"};

    const auto onClose = [&window](const sf::Event::Closed&)
    {
        std::cout << "Closing Window!!" << std::endl;
        window.close();
    };

    const auto onKeyPressed = [&window, &paddle](const sf::Event::KeyPressed& keyPressed)
    {
        // if(keyPressed.code == sf::Keyboard::Key::Up)
        // {
        //     ballVelocity -= 1;
        // }
        // if(keyPressed.code == sf::Keyboard::Key::Down)
        // {
        //     ballVelocity += 1;
        // }
        // if(keyPressed.code == sf::Keyboard::Key::Left)
        // {
        //     paddle.velocity.x = -paddleVelocity;
        // }
        // if(keyPressed.code == sf::Keyboard::Key::Right)
        // {
        //     paddle.velocity.x = paddleVelocity;
        // }
        
        if(keyPressed.scancode == sf::Keyboard::Scancode::Escape)
        {
            std::cout << "Escape key pressed, closing window!!\n";
            window.close();
        }
    };

    window.setFramerateLimit(60);

    sf::RectangleShape boundary({600, 600});
    boundary.setPosition({4, 4});
    boundary.setFillColor(sf::Color(64, 64, 64));
    boundary.setOutlineColor(sf::Color::White);
    boundary.setOutlineThickness(2.0f);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        window.handleEvents(onClose, onKeyPressed);
        // sf::Time elapsed = clock.getElapsedTime();
        // if(elapsed.asSeconds() >= 1.0F)
        // {
        //     float fps = frameCount / elapsed.asSeconds();
        //     std::stringstream ss;
        //     ss << "FPS: " << static_cast<int32_t>(fps);
        //     window.setTitle(ss.str());
        //     frameCount = 0;
        //     clock.restart();
        // }

        // check all the window's events that were triggered since the last iteration of the loop
        // while (const std::optional event = window.pollEvent())
        // {
        //     // "close requested" event: we close the window
        //     if (event->is<sf::Event::Closed>())
        //         window.close();
        // }
        window.clear(sf::Color(64, 64, 64));
        window.draw(boundary);
        // ball.SetVelocity(ballVelocity);
        ball.Update();
        paddle.update();
        // window.clear();

        // checkForCollision(paddle, ball);
        window.draw(ball.shape);
        window.draw(paddle.shape);
        window.display();
    }
    return 0;
}