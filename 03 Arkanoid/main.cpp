#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <time.h>
using namespace sf;

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode({520, 450}), "Arkanoid!");
    app.setFramerateLimit(60);

    Texture t1,t2,t3,t4;
    t1.loadFromFile("images/block01.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/ball.png");
    t4.loadFromFile("images/paddle.png");

   

    Sprite sBackground(t2), sBall(t3), sPaddle(t4);
    sPaddle.setPosition(Vector2f(300,440));

    std::vector<Sprite> block;

    int n=0;
    for (int i=1;i<=10;i++)
    for (int j=1;j<=10;j++)
      {
         block.emplace_back(t1);
         block[n].setPosition(Vector2f(i*43,j*20));
         n++;
      }

    float dx=6, dy=5;
    float x=300, y=300;
    bool gameOver = false;

    while (app.isOpen())
    {
       while (const std::optional event = app.pollEvent())
       {
         if (event->is<Event::Closed>())
             app.close();
       }

    

    if (!gameOver)
{
    x+=dx;
    for (int i=0;i<n;i++)
        if ( FloatRect({x+3,y+3},{6,6}).findIntersection(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(Vector2f(-100,0)); dx=-dx;}

    y+=dy;
    for (int i=0;i<n;i++)
        if ( FloatRect({x+3,y+3},{6,6}).findIntersection(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(Vector2f(-100,0)); dy=-dy;}

    if (x<0 || x>520)  dx=-dx;
    if (y < 0)
    dy = -dy;

if (y > 450)
    gameOver = true;
    

    if (Keyboard::isKeyPressed(Keyboard::Key::Right)) sPaddle.move(Vector2f(6,0));
    if (Keyboard::isKeyPressed(Keyboard::Key::Left)) sPaddle.move(Vector2f(-6,0));

    if ( FloatRect({x,y},{12,12}).findIntersection(sPaddle.getGlobalBounds()) ) dy=-(rand()%5+2);

    sBall.setPosition(Vector2f(x,y));
}

    app.clear();
    app.draw(sBackground);
    app.draw(sBall);
    app.draw(sPaddle);

    for (int i=0;i<n;i++)
     app.draw(block[i]);

    if(gameOver)
    app.draw(over);

    app.display();
    }

  return 0;
}
