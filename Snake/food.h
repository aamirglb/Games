#pragma once

#include "vec.h"

#include <iostream>
#include <format>
#include <cstdint>
#include <string>

class Food
{
public:
    Food(int32_t rows, int32_t cols)
        : m_Rows{rows}
        , m_Cols{cols}
    {
        m_Pos.Set(Vec::RandomVec(0, m_Rows-1));
    }

    void SetPos(const Vec& v)
    {
        m_Pos = v;
    }

    Vec Pos()
    {
        return m_Pos;
    }

    void Print()
    {
        std::cout << std::format("Food Position: ({}, {})\n", m_Pos.y, m_Pos.x);
    }

private:
    int32_t m_Rows;
    int32_t m_Cols;
    Vec m_Pos;
};