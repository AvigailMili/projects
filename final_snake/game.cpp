/*********************************
 * Author: Avigail Millatiner		
 * File: game.cpp
 * ******************************/
#include <stdlib.h> /* system("clear"), rand, srand */
#include <thread> /* std::thread */
#include <unistd.h> /* sleep*/
#include <ctime> /* time */
#include <curses.h> /* keyboard arrows, printw */
#include <cassert> /* assert */
#include "game.hpp"

/* ******************** free function ********************* */

namespace ilrd
{

static void UpdateDirection(Snake *snake);
static Direction_t GetInput();


static Direction_t GetInput()
{
    Direction_t new_direction = UP;

    int input = getch();
    switch (input) 
    {
        case KEY_UP:
            new_direction = UP;
            break;
        case KEY_DOWN:
            new_direction = DOWN;
            break;
        case KEY_LEFT:
            new_direction = LEFT;
            break;
        case KEY_RIGHT:
            new_direction = RIGHT;
            break;
        default:
            new_direction = BAD_INPUT;
    }
    return new_direction;
}

static void UpdateDirection(Snake *snake)
{
    assert(snake);
    
    Direction_t new_direction = snake->GetCurrDirection();
    while(true)
    {
        new_direction = GetInput();
        snake->SetNextDirection(new_direction);
    }
} 

/* ******************** class Game ********************* */

Game::Game(int board_size, int level): 
        m_board_size(board_size),
        m_snake(Point(m_board_size/2-1, m_board_size/2-1)), 
        m_food(GenFood()),
        m_speed(1000000/level)
        {
            assert(board_size >= 4);
            assert(level >= 1);
            assert(level <= 5);
        }


void Game::Run()
{
    InitDisplay();
    
    int inner_size = (m_board_size-1)*(m_board_size-1);

    std::thread Read_Input(&UpdateDirection,&m_snake);
    Read_Input.detach();

    while(false == CrashFrame() && false == m_snake.EatSelf())
    {
        Display();
        
        usleep(m_speed);

        if(true == SnakeEat())
        {
            m_snake.Grow();
            
            //chack if snake filled board - player win!
            if(m_snake.GetSize() == inner_size) 
            {
                Read_Input.~thread();
                return;
            }
            m_food = GenFood();
        }
        else
        {
            m_snake.Move();
        }
    }
    Read_Input.~thread();
    CleanUpDisplay();
}


void Game::Display()
{
    clear();
    for(int i = 0; i < m_board_size; ++i)
    {
        printw("O");
    }
    printw("\n");

    for(int j = 1; j < m_board_size-1; ++j)
    {
        printw("O");
        for(int i = 1; i < m_board_size-1; ++i)
        {
            if(true == m_snake.IsSnake(Point(i,j)))
            {
                printw("X");
            }
            else  if (Point(i,j) == m_food)
            {
                printw("@");
            }
            else 
            {
                printw(" ");
            }
        }
        printw("O");
        printw("\n");
    }

    for(int i = 0; i < m_board_size; ++i)
    {
        printw("O");
    }
    printw("\n");
    refresh();
} // display


void Game::InitDisplay()
{
    initscr();  // Initialize ncurses
    cbreak();   // Put the terminal into cbreak mode
    noecho();  // Don't echo keystrokes to the screen
    keypad(stdscr, TRUE);   // Enable keyboard arrow keys
}


void Game::CleanUpDisplay()
{
    endwin();   // ncurses cleanup
}


bool Game::CrashFrame()
{
    Point head = m_snake.GetHead();

    if(head.X() != 0 && head.X() != m_board_size -1 && head.Y() != 0 && head.Y() != m_board_size -1)
    {
        return false;
    }
    return true;
} 


bool Game::SnakeEat()
{
    return m_snake.IsHead(m_food);
}


Point Game::RandPosition()
{
    srand(time(NULL));
    Point position = Point(1 + rand() % (m_board_size - 2), 1 + rand() % (m_board_size - 2));

    return position;
}


Point Game::GenFood()
{
    Point position = RandPosition();
    while(m_snake.IsSnake(position))
    {
        position = RandPosition();
    }
    return position;
}
}//namespace ilrd
