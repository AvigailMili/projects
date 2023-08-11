/*********************************
 * Author: Avigail Millatiner		
 * File: game.hpp
 * ******************************/
#pragma once
#include "point.hpp"
#include "snake.hpp"

namespace ilrd
{
class Game
{
private:
    Point GenFood();

public: 
    explicit Game(int board_size, int level);
    void Run();

private:
    bool CrashFrame();
    bool SnakeEat();
    void InitDisplay();
    void Display();
    void CleanUpDisplay();
    Point RandPosition();

    int m_board_size;
    Snake m_snake;
    Point m_food;
    int m_speed;
}; // class game

}//namespace ilrd
