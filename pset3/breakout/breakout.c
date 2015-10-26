//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// height and width of paddle in pixels
#define PADDLE_HEIGHT 10
#define PADDLE_WIDTH 60

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // ball's initial velocity
    double velocityX = (drand48() / 20.0) + 0.05;
    double velocityY = 0.1;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if there's an event
        if (event != NULL)
        {
            // if there's movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // move paddle
                double x = getX(event) - getWidth(paddle) / 2;

                double min = 0;
                double max = WIDTH - getWidth(paddle);
                // keep paddle within window
                if (x < min)
                {
                    x = min;
                }
                else if (x > max)
                {
                    x = max;
                }
                setLocation(paddle, x, getY(paddle));
            }
        }

        // move the ball
        move(ball, velocityX, velocityY);

        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocityX = -velocityX;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            velocityX = -velocityX;
        }

        // detect collision with paddle and bricks
        GObject object = detectCollision(window, ball);

        // bounce off paddle
        if (object == paddle)
        {
            velocityY = -velocityY;
        }

        // bounce off bricks and update score
        else if (object && (strcmp(getType(object), "GRect") == 0))
        {
            --bricks;
            updateScoreboard(window, label, (COLS * ROWS) - bricks);
            removeGWindow(window, object);
            velocityY = -velocityY;
        }

        // lose a life and wait for click if ball hits the bottom edge of the window
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            if (--lives)
            {
                waitForClick();
                removeGWindow(window, ball);
                ball = initBall(window);
            }
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    static const string COLORS[] = {
        "RED",
        "ORANGE",
        "YELLOW",
        "GREEN",
        "BLUE",
    };

    // starting position for first row of bricks
    static const int START_X = 2;
    static const int START_Y = 50;

    // spacing between each brick
    static const int HORIZ_SPACE = 4;
    static const int VERT_SPACE = 5;

    // height and width for each brick
    static const int BRICK_HEIGHT = 10;
    static const int BRICK_WIDTH = (WIDTH - (HORIZ_SPACE * COLS)) / COLS;

    // create bricks
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLS; ++col)
        {
            int x = START_X + (col * (HORIZ_SPACE + BRICK_WIDTH));
            int y = START_Y + (row * (VERT_SPACE + BRICK_HEIGHT));
            GRect brick = newGRect(x, y, BRICK_WIDTH, BRICK_HEIGHT);
            setFilled(brick, true);
            setColor(brick, COLORS[row]);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    int diameter = RADIUS * 2;
    int x = (WIDTH - diameter) / 2;
    int y = (HEIGHT - diameter) / 2;
    GOval ball = newGOval(x, y, diameter, diameter);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    int x = (WIDTH - PADDLE_WIDTH) / 2;
    GRect paddle = newGRect(x, 540, PADDLE_WIDTH, PADDLE_HEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel scoreboard = newGLabel("0");
    setFont(scoreboard, "SansSerif-48");
    setColor(scoreboard, "Gray");

    // center label in window
    double x = (getWidth(window) - getWidth(scoreboard)) / 2;
    double y = (getHeight(window) - getHeight(scoreboard)) / 2;
    setLocation(scoreboard, x, y);
    add(window, scoreboard);
    return scoreboard;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
