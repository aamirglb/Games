#pragma once

#include "vec.h"
#include "food.h"

#include <iostream>
#include <format>
#include <cstdint>
#include <random>
#include <raylib.h>

class Snake
{
public:
    Snake(int32_t rows, int32_t cols, int32_t sz) 
        : m_Rows{rows}
        , m_Cols{cols}
        , m_CellSize{sz}
        , m_Length{1}
    {
        m_Pos.Set(Vec::RandomVec(0, m_Rows-1));
    }

    void Print()
    {
        std::cout << std::format("Snake Position: ({}, {})\n", m_Pos.y, m_Pos.x);
    }

    void Draw()
    {
        DrawRectangle((m_Pos.x * m_CellSize)+1, (m_Pos.y * m_CellSize)+1, m_CellSize-2, m_CellSize-2, RED);
    }

    Vec Pos() 
    {
        return m_Pos;
    }

    int32_t Len()
    {
        return m_Length;
    }

    bool Eat(std::shared_ptr<Food> food)
    {
        Vec pos = food->Pos();
        if(pos.x == m_Pos.x && pos.y == m_Pos.y) {
            m_Length += 1;
            std::cout << std::format("Snake eat the food at position ({}, {})\n", pos.y, pos.x);
            return true;
        } else {
            return false;
        }
    }

    void Update(Vec dir)
    {
        m_Pos.Add(dir);

        if(m_Pos.x < 0) { m_Pos.x = m_Cols-1; }
        if(m_Pos.x >= m_Cols) { m_Pos.x = 0; }
        if(m_Pos.y < 0) { m_Pos.y = m_Rows -1; }
        if(m_Pos.y >= m_Rows) { m_Pos.y = 0; }
    }

private:
    int32_t m_Rows;
    int32_t m_Cols;
    int32_t m_CellSize;
    int32_t m_Length;
    Vec m_Pos;
};