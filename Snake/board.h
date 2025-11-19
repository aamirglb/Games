#pragma once

#include <cstdint>
#include <vector>
#include <format>
#include <string>
#include <ranges>
#include <raylib.h>

class Board
{
public:
    using Grid = std::vector<std::vector<int32_t>>;
    Board(int32_t rows, int32_t cols, int32_t sz)
        : m_Rows{rows}
        , m_Cols{cols}
        , m_CellSize{sz}
    {
        m_Board.resize(m_Rows);
        for(int32_t i = 0; i < m_Rows; ++i) {
            m_Board[i].resize(m_Cols);
        }

        for(int32_t r = 0; r < m_Rows; ++r) {
            for(int32_t c = 0; c < m_Cols; ++c) {
                m_Board[r][c] = 0;
            }
        }
    }

    void Print()
    {
        std::string line(3*20, '-');
        std::cout << "    | "; // << std::endl;
        for(int32_t r = 0; r < m_Rows; ++r) {
            std::cout << std::format("{:<3}", r);
        }
        std::cout << std::endl;
        std::cout << "---+ " << line << std::endl;
        // std::cout << "   | " << std::endl;
        for(int32_t r = 0; r < m_Rows; ++r) {
            std::cout << std::format("{:>3} |", r);
            for(int32_t c = 0; c < m_Cols; ++c) {
                std::cout << std::format("{:2} ", m_Board[r][c]);
            }
            std::cout << std::endl;
        }
    }

    void DrawGrid()
    {
        for(int32_t c = 0; c <= m_Cols; ++c) {
            DrawLine(c*m_CellSize + offset, 5, c*m_CellSize + offset, 605, ColorAlpha(WHITE, 0.3f));
            // DrawRectangle((c * m_CellSize)+1, (r * m_CellSize)+1, m_CellSize-2, m_CellSize-2, WHITE);
        }
        for(int32_t r = 0; r <= m_Rows; ++r) {
            DrawLine(5, r * m_CellSize + offset, 605, r * m_CellSize + offset, ColorAlpha(WHITE, 0.3f));
        }
    }

    void Draw(int32_t headLen, bool showNum, bool showLen)
    {
        // int32_t head = std::ranges::max_element(m_Board);
        for(int32_t r = 0; r < m_Rows; ++r) {
            for(int32_t c = 0; c < m_Cols; ++c) {
                if(m_Board[r][c] >= 1) {
                    // DrawRectangle((c * m_CellSize)+1, (r * m_CellSize)+1, m_CellSize-2, m_CellSize-2, RED);
                    if(m_Board[r][c] != headLen) {
                        DrawRectangle((c * m_CellSize) + offset, (r * m_CellSize) + offset, m_CellSize, m_CellSize, PURPLE);
                    } else {
                        DrawRectangle((c * m_CellSize) + offset, (r * m_CellSize) + offset, m_CellSize, m_CellSize, RED);
                        if(showLen) {
                            DrawText(std::to_string(m_Board[r][c]).c_str(), (c*m_CellSize) + m_CellSize/2, (r*m_CellSize) + m_CellSize/2, 8, WHITE);
                        }
                    }
                }
                else if(m_Board[r][c] == -1) {
                    // DrawRectangle((c * m_CellSize)+1, (r * m_CellSize)+1, m_CellSize-2, m_CellSize-2, ORANGE);
                    DrawRectangle((c * m_CellSize) + offset, (r * m_CellSize) + offset, m_CellSize, m_CellSize, ORANGE);
                }

                if(showNum && m_Board[r][c] != 0)
                {
                    DrawText(std::to_string(m_Board[r][c]).c_str(), (c*m_CellSize) + m_CellSize/2, (r*m_CellSize) + m_CellSize/2, 8, WHITE);
                }
            }
        }
    }

    void SetCell(const Vec& v, int32_t val)
    {
        m_Board[v.y][v.x] = val;
    }

    int32_t Cell(const Vec& v)
    {
        return m_Board[v.y][v.x];
    }

    void UpdateBoard()
    {
        for(int32_t r = 0; r < m_Rows; ++r) {
            for(int32_t c = 0; c < m_Cols; ++c) {
                if(m_Board[r][c] > 0) {
                    // std::cout << std::format("({}, {}) is {}\n", r, c, m_Board[r][c]);
                    m_Board[r][c] -= 1;
                }
            }
        }
    }

    void UpdateSnakeTail(int32_t length)
    {
        for(int32_t r = 0; r < m_Rows; ++r) {
            for(int32_t c = 0; c < m_Cols; ++c) {
                if(m_Board[r][c] > 0 && m_Board[r][c] < length) {
                    m_Board[r][c] += 1;
                }
            }
        }
    }

    bool IsAvailable(const Vec& v)
    {
        return m_Board[v.y][v.x] == 0;
    }

private:
    int32_t m_Rows;
    int32_t m_Cols;
    int32_t m_CellSize;
    Grid m_Board;
    constexpr inline static int32_t offset = 5;
};