/*********************************
 * Author: Avigail Millatiner		
 * File: snake.cpp
 * ******************************/
#include <curses.h> /* keyboard arrows */
#include <cassert>
#include "snake.hpp"

namespace ilrd
{
/* ******************** class snake ********************* */

Snake::Snake(Point head) : m_curr_direction(UP), m_next_direction(UP)
{
    m_body.push_back(head);
}


//check if direction is valid and set next direction
void Snake::SetNextDirection(Direction_t direction) 
{
    Direction_t OPPOSITE_LUT[] = {DOWN, UP, RIGHT, LEFT, BAD_INPUT};
    if(direction != BAD_INPUT && (direction != OPPOSITE_LUT[GetCurrDirection()] || GetSize() == 1))
    {
        m_next_direction = direction;
    }
}


void Snake::Grow()
{
    Point head = GetHead();
    Point new_head = head;
    switch(m_curr_direction)
    {
        case UP:
        {
            new_head = Point(head - Point(0,1));
            break;
        }
        case DOWN:
        {
            new_head = Point(head + Point(0,1));
            break;
        }
        case LEFT:
        {
            new_head = Point(head - Point(1,0));
            break;
        }
        case RIGHT:
        {
            new_head = Point(head + Point(1,0));
            break;
        }
        default:
        {
            assert(false);
        }
    }
    m_body.push_front(new_head);
    m_curr_direction = m_next_direction;
}


void Snake::Move()
{
    Grow();
    m_body.pop_back();
}


bool Snake::IsBody(Point point) 
{
    int snake_size = m_body.size();
    std::list<Point>::iterator iter = m_body.begin();
    ++iter; // Skip head
    for(iter; iter != m_body.end(); ++iter)
    {
        if(*iter == point)
        {
            return true;
        }
    }
    return false;
}


bool Snake::IsSnake(Point point)
{
    return IsBody(point) || IsHead(point);
}


bool Snake::IsHead(Point point)
{
    return GetHead() == point;
}


//check if head is equal to any body part
bool Snake::EatSelf() 
{
    return IsBody(GetHead());
}
}//namespace ilrd

