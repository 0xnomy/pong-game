#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
using namespace std;

enum eDir
{
    STOP = 0,
    LEFT = 1,
    UPLEFT = 2,
    DOWNLEFT = 3,
    RIGHT = 4,
    UPRIGHT = 5,
    DOWNRIGHT = 6
};
class Ball
{
private:
    int x, y;
    int origx, origy;
    eDir direction;

public:
    Ball(int posx, int posy)
    {
        origx = posx;
        origy = posy;
        x = posx;
        y = posy;
        direction = STOP;
    }
    void reset() // use to make the x,y corrdiantes equal to the initial coordinates of ball
    {
        x = origx;
        y = origy;
        direction = STOP;
    }
    void changedir(eDir d)
    {
        direction = d;
    }
    void random_dir()
    {
        direction = (eDir)((rand() % 6) + 1); // 6direction for position, +1 for randomaization
    }
    inline int getx()
    {
        return x;
    }
    inline int gety()
    {
        return y;
    }
    inline eDir getDir()
    {
        return direction;
    }
    void move()
    {
        switch (direction)
        {
        case STOP:
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UPLEFT:
            x--;
            y--;
            break;
        case DOWNLEFT:
            x--;
            y++;
            break;
        case UPRIGHT:
            x++;
            y--;
            break;
        case DOWNRIGHT:
            x++;
            y++;
            break;
        default:
            break;
        }
    }
    friend ostream &operator<<(ostream &o, Ball b)
    {
        o << "Ball[" << b.x << "," << b.y << "][" << b.direction << "]";
        return o;
    }
};

class paddle
{
private:
    int x, y;
    int origx, origy;

public:
    paddle()
    {
        x = y = 0;
    }
    paddle(int posx, int posy) : paddle()
    {
        origx = posx;
        origy = posy;
        x = posx;
        y = posy;
    }
    inline void reset()
    {
        x = origx;
        y = origy;
    }
    inline int getx()
    {
        return x;
    }
    inline int gety()
    {
        return y;
    }
    inline void moveUp()
    {
        y--;
    }
    inline void moveDown()
    {
        y++;
    }

    friend ostream &operator<<(ostream &o, paddle c)
    {
        o << "Ball [" << c.x << "," << c.y << "]";
        return o;
    }
};
class gamemanager
{
private:
    int width, height, score1, score2;
    bool quit;
    char up1, up2, down1, down2; // for moving player1 and 2 down
    Ball *ball;
    paddle *p1;
    paddle *p2;

public:
    gamemanager(int w, int h)
    {
        srand(time(NULL));
        quit = false;
        up1 = 'w';
        up2 = 'i';
        down1 = 's';
        down2 = 'k';
        score1 = score2 = 0;
        width = w;
        height = h;
        ball = new Ball(w / 2, h / 2); // for ball to be centered
        p1 = new paddle(1, h / 2 - 3);
        p2 = new paddle(w - 2, h / 2 - 3);
    }
    ~gamemanager()
    {
        delete ball, p1, p2;
    }
    void scoreup(paddle *player) // helps calculate the score of players
    {
        if (player == p1)
            score1++;
        if (player == p2)
            score2++;

        ball->reset();
        p1->reset();
        p2->reset();
    }
    void clearscrn()
    {
        COORD cursorPosition;
        cursorPosition.X = 0;
        cursorPosition.Y = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    }
    void draw()
    {
        clearscrn();
        for (int i = 0; i < width + 2; i++)
            cout << "\xB2";
        cout << endl;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int ballx = ball->getx();
                int bally = ball->gety();
                int player1x = p1->getx();
                int player2x = p2->getx();
                int player1y = p1->gety();
                int player2y = p2->gety();
                if (j == 0)
                    cout << "\xB2";

                if (ballx == j && bally == i)
                    cout << "O";
                else if (player1x == j && player1y == 1)
                    cout << "\xDB";
                else if (player1x == j && player1y + 1 == 1)
                    cout << "\xDB";
                else if (player1x == j && player1y + 2 == 1)
                    cout << "\xDB";
                else if (player1x == j && player1y + 3 == 1)
                    cout << "\xDB";

                else if (player2x == j && player2y == 1)
                    cout << "\xDB";
                else if (player2x == j && player2y + 1 == 1)
                    cout << "\xDB";
                else if (player2x == j && player2y + 2 == 1)
                    cout << "\xDB";
                else if (player2x == j && player2y + 3 == 1)
                    cout << "\xDB";
                else
                    cout << " ";

                if (j == width - 1)
                    cout << "\xB2";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)

            cout << "\xB2";
        cout << endl;
        cout << "Score 1: " << score1 << endl
             << "Score 2: " << score2 << endl;
    }
    void input()
    {
        ball->move();
        int ballx = ball->getx();
        int bally = ball->gety();
        int player1x = p1->getx();
        int player2x = p2->getx();
        int player1y = p1->gety();
        int player2y = p2->gety();
        if (_kbhit())
        {
            char current = _getch();
            if (current == up1)
                if (player1y > 0)
                    p1->moveUp();
            if (current == up2)
                if (player2y > 0)
                    p2->moveUp();
            if (current == down1)
                if (player1y + 4 < height)
                    p1->moveDown();
            if (current == down2)
                if (player2y + 4 < height)
                    p2->moveDown();
            if (ball->getDir() == STOP)
                ball->random_dir();
            if (current == 'q')
                quit = true;
        }
    }

    void logic()
    {
        int ballx = ball->getx();
        int bally = ball->gety();
        int player1x = p1->getx();
        int player2x = p2->getx();
        int player1y = p1->gety();
        int player2y = p2->gety();

        for (int i = 0; i < 4; i++)
        {
            if (ballx = player1x + 1)
                if (bally = player1y + 1)
                    ball->changedir((eDir)((rand() % 3) + 4));
        }
        for (int i = 0; i < 4; i++)
        {
            if (ballx = player2x + 1)
                if (bally = player2y + 1)
                    ball->changedir((eDir)((rand() % 3) + 1));
        }
        if (bally == height - 1)
            ball->changedir(ball->getDir() == DOWNRIGHT ? UPRIGHT : UPLEFT);
        if (bally == 0)
            ball->changedir(ball->getDir() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        if (ballx == 0)
            scoreup(p2);
        if (ballx = width - 1)
            scoreup(p1);
    }
    void collision()
    {
        // Check collision with left paddle
        if (ball->getx() == p1->getx() + 1 &&
            ball->gety() >= p1->gety() &&
            ball->gety() <= p1->gety() + 3)
        {
            ball->changedir((eDir)((rand() % 3) + 4)); // randomize direction
        }

        // Check collision with right paddle
        if (ball->getx() == p2->getx() - 1 &&
            ball->gety() >= p2->gety() &&
            ball->gety() <= p2->gety() + 3)
        {
            ball->changedir((eDir)((rand() % 3) + 1)); // randomize direction
        }
    }

    void run()
    {
        while (!quit)
        {
            draw();
            input();
            logic();
            Sleep(100);
        }
    }
};

int main()
{

    gamemanager g(40, 30);
    g.run();
    return 0;
}