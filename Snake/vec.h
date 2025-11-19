#pragma once

#include <cstdint>
#include <random>

struct Vec
{
    Vec() = default;
    Vec(int32_t x_, int32_t y_) 
        : x{x_}
        , y{y_}
    {}

    void Set(const Vec& v)
    {
        x = v.x;
        y = v.y;
    }

    void Set(int32_t x_, int32_t y_)
    {
        x = x_;
        y = y_;
    }

    void SetX(int32_t x_)
    {
        x = x_;
    }

    void SetY(int32_t y_)
    {
        y = y_;
    }

    void Add(Vec v)
    {
        x += v.x;
        y += v.y;
    }

    static Vec RandomVec(int32_t min, int32_t max)
    {
        static std::mt19937 rng{ std::random_device{}() };
        std::uniform_int_distribution<int32_t> dist(min, max);
        int32_t x = dist(rng);
        int32_t y = dist(rng);
        return Vec(x, y);
    }

    int32_t x{};
    int32_t y{};
};