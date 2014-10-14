#include <pihud/Rect.hpp>


bool operator!=(const PiH::FloatRect &l, const PiH::FloatRect &r)
{
    return !(l == r);
}


bool operator==(const PiH::FloatRect &l, const PiH::IntRect &r)
{
    if(l.x == r.x
            && l.y == r.y
            && l.w == r.w
            && l.h == r.h)
    {
        return true;
    }
    return false;
}
