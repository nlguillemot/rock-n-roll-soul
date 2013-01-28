#include "util.hpp"
#include <cmath>

namespace heart
{

sf::Vector2f unit_vector_from_angle(float degrees)
{
    return sf::Vector2f(
            std::cos(degrees*3.14159265359f/180.0f),
            std::sin(degrees*3.14159265359f/180.0f));
}

bool segment_intersects_rectangle(const sf::FloatRect& rect, const sf::Vector2f& a, const sf::Vector2f& b)
{
    // Find min and max X for the segment
    float minX = a.x;
    float maxX = b.x;

    if (a.x > b.x)
    {
      minX = b.x;
      maxX = a.x;
    }

    // Find the intersection of the segment's and rectangle's x-projections
    if (maxX > rect.Right)
    {
      maxX = rect.Right;
    }

    if (minX < rect.Left)
    {
      minX = rect.Left;
    }

    if (minX > maxX) // If their projections do not intersect return false
    {
      return false;
    }

    // Find corresponding min and max Y for min and max X we found before
    float minY = a.y;
    float maxY = b.y;

    float dx = b.x - a.x;

    if (std::fabs(dx) > 0.0000001)
    {
      float c = (b.y - a.y) / dx;
      float d = a.y - c * a.x;
      minY = c * minX + d;
      maxY = c * maxX + d;
    }

    if (minY > maxY)
    {
      float tmp = maxY;
      maxY = minY;
      minY = tmp;
    }

    // Find the intersection of the segment's and rectangle's y-projections
    if (maxY > rect.Bottom)
    {
      maxY = rect.Bottom;
    }

    if (minY < rect.Top)
    {
      minY = rect.Top;
    }

    if (minY > maxY) // If Y-projections do not intersect return false
    {
      return false;
    }

    return true;
}

static time_t first_time = std::time(NULL);
void log_message(const std::string& msg)
{
    time_t sec = std::time(NULL) - first_time;
    time_t min = sec/60;
    time_t hr = min/60;
    min = min - hr * 60;
    sec = sec - min * 60;
    std::cout << hr << "h" << min << "m" << sec << "s: " << msg << std::endl;
}

}
