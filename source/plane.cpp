#include "plane.h"

Plane::Plane(Vec3f &n, float d, Vec3f &col)
{
    normal = n;
    offset = d;
    color = col;
}

bool Plane::intersect(const Ray &r, Hit &h, float tmin)
{   
    // t = (-d - n.o) / (n.d)
    float a = normal.Dot3(r.getOrigin());
    float b = normal.Dot3(r.getDirection());

    if(b == 0.0f) // parallel
        return false;

    float t = (offset - a) / b;

    if(t<h.getT())
        if(t>=tmin)
        {
            h.set(t, color, normal, r);
            return true;
        }
    return false;
}
