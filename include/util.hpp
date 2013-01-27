#pragma once

#include "sequencer.hpp"
#include <functional>
#include <queue>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace heart
{

bool segment_intersects_rectangle(const sf::FloatRect& rect, const sf::Vector2f& a, const sf::Vector2f& b);

template<class T>
sf::Vector2<T> unit_vector_from_angle(float degrees)
{
    return sf::Vector2<T>(
            (T)std::cos(degrees*3.14159265359f/180.0f),
            (T)std::sin(degrees*3.14159265359f/180.0f));
}

template<class T>
T dot_product(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
{
    return a.x * b.x + a.y * b.y;
}

template<class T>
T signum(T x)
{
    return x >= 0 ? 1 : -1;
}

template<class T>
T clamp(T val, T low, T high)
{
    return val < low ? low :
           val > high ? high :
           val;
}

template<class T>
bool intersecting_range(const T& min1, const T& max1, const T& min2, const T& max2)
{
    return (min1 <= min2 && max1 >= min2) ||
        (min1 >= min2 && min1 <= max2);
}

template<class Container, class T>
static bool element_of(const T& elm, const Container& c)
{
    return std::find(c.cbegin(),c.cend(),elm) != c.cend();
}

void log_message(const std::string& msg);

template<class T>
float vector_magnitude(const sf::Vector2<T>& v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

template<class T>
sf::Vector2<T> vector_LERP(const sf::Vector2<T>& a, const sf::Vector2<T>& b, float c)
{
    return a + (c * (b - a));
}

template<class T>
sf::Vector2<T> rect_size(const sf::Rect<T>& r)
{
    return sf::Vector2<T>(r.GetWidth(),r.GetHeight());
}
template<class T>
sf::Vector2f rect_center(const sf::Rect<T>& r)
{
    return sf::Vector2f((r.Left + r.Right)/2.f,(r.Top + r.Bottom)/2.f);
}

template<class T>
sf::Vector2<T> rect_topleft(const sf::Rect<T>& r)
{
    return sf::Vector2f(r.Left,r.Top);
}

inline sf::Color color_LERP(const sf::Color& start, const sf::Color& end, float c)
{
    return sf::Color( (end.r-start.r)*c, (end.g-start.g)*c, (end.b-start.b)*c, (end.a-start.a)*c );
}

inline std::function<bool ()> not_function(const std::function<bool ()>& f)
{
    return [f]{ return !f(); };
}

class FunctionSeqItem : public SequencerItem
{
public:
    FunctionSeqItem(const std::function<void ()>& f);
    void init();
private:
    const std::function<void ()> f_;
};

class ColorTweenSeqItem : public SequencerItem
{
public:
    ColorTweenSeqItem(const sf::Color& start, const sf::Color& end, sf::Color& current, sf::Uint32 duration);
    void init();
    void update(sf::Uint32 dt);
    void exit();
private:
    sf::Color start_;
    sf::Color end_;
    sf::Color& current_;
    sf::Uint32 duration_;
    sf::Uint32 time_accumulator_;
};

class DrawableColorTweenSeqItem : public SequencerItem
{
public:
    DrawableColorTweenSeqItem(const sf::Color& start, const sf::Color& end, sf::Uint32 duration, sf::Drawable& tweened);
    void update(sf::Uint32 dt);
private:
    sf::Color color_;
    Sequencer fade_seq_;
    sf::Drawable& tweened_;
};

class WaitUntilSeqItem : public SequencerItem
{
public:
    WaitUntilSeqItem(const std::function<bool ()>& cond);
    void init();
    void update(sf::Uint32 dt);
private:
    const std::function<bool ()> cond_;
};


template<class T>
std::ostream& operator<<(std::ostream& os, const sf::Rect<T>& r)
{
    os << "{ L:" << r.Left << " T:" << r.Top
        << " R:" << r.Right << " B:" << r.Bottom << " }";
    return os;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& v)
{
    os << "{ " << v.x << ", " << v.y << " }";
    return os;
}

}
