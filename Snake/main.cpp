#include <iostream>
#include <cstdint>
#include <raylib.h>
#include <memory>
#include <chrono>
#include <deque>

#include "vec.h"
#include "board.h"
#include "snake.h"
#include "food.h"
#include "fixq.h"

double LastUpdateTime{};

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if(currentTime - LastUpdateTime >= interval)
    {
        LastUpdateTime = currentTime;
        return true;
    }
    return false;
}

enum class Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

Vec dir(1, 0);
Direction currDir = Direction::RIGHT;
bool pause{};
bool nextFrame{};
bool printBoard{};
bool showNum{};
bool showSnakeLen{true};
bool showGrid{true};
bool gameOver{};
int32_t flash{};

constexpr int32_t Rows{30};
constexpr int32_t Cols{30};
constexpr int32_t CellSize{20};

int32_t frameRate{10};

void HandleInput()
{
    int32_t keyPressed = GetKeyPressed();
    switch(keyPressed)
    {
        case KEY_LEFT:
            if(currDir != Direction::RIGHT) {
                dir.Set(-1, 0);
                currDir = Direction::LEFT;
            } else {
                std::cout << "LEFT turn not allowed\n";
            }
        break;
        case KEY_RIGHT:
            if(currDir != Direction::LEFT) {
                dir.Set(1, 0);
                currDir = Direction::RIGHT;
            } else {
                std::cout << "RIGHT turn not allowed\n";
            }
        break;
        case KEY_UP:
            if(currDir != Direction::DOWN) {
                dir.Set(0, -1);
                currDir = Direction::UP;
            } else {
                std::cout << "UP turn not allowed\n";
            }
        break;
        case KEY_DOWN:
            if(currDir != Direction::UP) {
                dir.Set(0, 1);
                currDir = Direction::DOWN;
            } else {
                std::cout << "DOWN turn not allowed\n";
            }
        break;
        case KEY_SPACE:
            std::cout << "GAME is PAUSED!!\n";
            std::cout << "Press 'n' key to move to next frame\n";
            pause = !pause;
        break;
        case KEY_N:
            if(pause) {
                nextFrame = true;
            }
        break;
        case KEY_P:
            printBoard = true;
        break;
        case KEY_L:
            showSnakeLen = !showSnakeLen;
        break;
        case KEY_D:
            showNum = !showNum;
        break;
        case KEY_G:
            showGrid = !showGrid;
        break;
        case KEY_PAGE_UP:
            // Increase frame rate
            frameRate += 1;
            SetTargetFPS(frameRate);
            std::cout << "FrameRate Set To: " << frameRate << std::endl;
        break;
        case KEY_PAGE_DOWN:
            // Decrease frame rate
            frameRate -= 1;
            SetTargetFPS(frameRate);
            std::cout << "FrameRate Set To: " << frameRate << std::endl;
        break;
    }
}

constexpr uint64_t MSEC_IN_HOURS {1000 * 60 * 60};
constexpr uint64_t SEC_IN_MIN {1000 * 60};

std::string GetFormattedTime(uint64_t ms)
{
    uint64_t hours = ms / MSEC_IN_HOURS;
    ms %= MSEC_IN_HOURS;

    uint64_t minutes = ms / SEC_IN_MIN;
    ms %= SEC_IN_MIN;

    uint64_t seconds = ms / 1000;
    uint64_t millis = ms % 1000;

    return std::format("{:02}:{:02}:{:02}.{:03}", hours, minutes, seconds, millis);
}

int main()
{
    const int32_t GridWidth = 600;
    const int32_t GridHeight = 600;
    const int32_t offset = 10;
    const int32_t scoreWindow = 190;

    const int32_t width = {GridWidth + offset + scoreWindow};
    const int32_t height {GridHeight + offset * 2};

    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
    //std::deque<std::string> lapTimes;
    FixQ<std::string, 6> lapTimes;
    std::string formattedTime;

    InitWindow(width, height, "Snake Game");

    SetTargetFPS(frameRate);

    // Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    Font font = LoadFontEx("font/tuffy.ttf", 64, 0, 0);

    std::unique_ptr<Board> board = std::make_unique<Board>(Rows, Cols, CellSize);
    auto snake = std::make_shared<Snake>(Rows, Cols, CellSize);
    snake->Print();

    auto food = std::make_shared<Food>(Rows, Cols);
    food->Print();
    //int32_t flash{};

    start = std::chrono::steady_clock::now();
    auto gameStart = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point loopTime;

    while(WindowShouldClose() == false)
    {
        HandleInput();
        BeginDrawing();
        ClearBackground(BLACK);

        if(showGrid) {
            board->DrawGrid();
        }
        DrawRectangleLines(5, 5, 600, 600, ColorAlpha(WHITE, 0.7f));

        if(gameOver) {
            flash += 1;
            if(flash < 5)
            {
                DrawTextEx(font, "GAME OVER", {250, 250}, 38, 2, RED);
            }
            else if(flash > 10)
            {
                flash = 0;
            }
            board->Draw(snake->Len(), showNum, showSnakeLen);
        }
        else {
            if(!gameOver && (!pause || nextFrame)) {
                snake->Update(dir);
            } 

            if(board->Cell(snake->Pos()) > 0)
            {
                std::cout << "GAME OVER!!" << std::endl;
                gameOver = true;
            }
            board->SetCell(snake->Pos(), snake->Len()+1);

            if(snake->Eat(food)) {
                end = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                std::cout << "Elapsed: " << elapsed.count() << " ms\n";
                int32_t idx = snake->Len() - 2;
                //if(snake->Len() > 11) {
                //    //lapTimes.pop_back();
                //    lapTimes.Push()
                //}    
                lapTimes.Push(std::format("LAP-{:02}: {}", idx+1, GetFormattedTime(elapsed.count())));

                while(true) {
                    auto v = Vec::RandomVec(0, 19);
                    if(board->IsAvailable(v)) {
                        food->SetPos(v);
                        break;
                    }
                }
                board->UpdateSnakeTail(snake->Len());
                board->SetCell(snake->Pos(), snake->Len()+1);
                start = std::chrono::steady_clock::now();
            }

            board->SetCell(food->Pos(), -1);

            if(!pause || nextFrame) {
                board->UpdateBoard();
            } 

            board->Draw(snake->Len(), showNum, showSnakeLen);

            if(nextFrame) {
                board->Print();
                nextFrame = false;
            }

            if(printBoard) {
                board->Print();
                printBoard = false;
            }
            loopTime = std::chrono::high_resolution_clock::now();
            auto dur = std::chrono::duration_cast<std::chrono::milliseconds>( loopTime - gameStart );
            formattedTime = GetFormattedTime( dur.count() );
        }


        DrawTextEx( font, formattedTime.c_str(), { 620, 10 }, 16, 1, WHITE );

        int32_t i{1};
        for(const auto& lap : lapTimes) {
            if(!lap.empty()) {
                Vector2 v{620, 10+(i*24)};
                DrawTextEx(font, lap.c_str(), v, 16, 2, WHITE);
            }
            ++i;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}