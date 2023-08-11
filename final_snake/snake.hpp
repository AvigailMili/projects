/*********************************
 * Author: Avigail Millatiner		
 * File: snake.hpp
 * ******************************/
#pragma once

#include <list>
#include "point.hpp"

namespace ilrd
{

enum Direction_t{UP,DOWN,LEFT,RIGHT,BAD_INPUT};


/* ********** class snake ********** */
class Snake
{
public:
    explicit Snake(Point head);
    bool IsSnake(Point point);
    bool IsHead(Point point);
    void Move();
    void Grow();
    bool EatSelf();
    int GetSize();
    Point GetHead();
    Direction_t GetCurrDirection();
    void SetNextDirection(Direction_t direction);

private:
    std::list<Point> m_body;
    Direction_t m_curr_direction;
    Direction_t m_next_direction;
    bool IsBody(Point point);
}; // class snake

inline int Snake::GetSize()
{
    return m_body.size();
}

inline Direction_t Snake::GetCurrDirection()
{
    return m_curr_direction;
}

inline Point Snake::GetHead()
{
    return m_body.front();
}

}//namespace ilrd



















