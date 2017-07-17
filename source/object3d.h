#ifndef _OBJECT3D_H
#define _OBJECT3D_H
#define EPS 1e-4
#include "hit.h"
#include "ray.h"
#include "vectors.h"
class Ray;
class Hit;


class Object3D{

public:

 Object3D(){};

~Object3D(){};

virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;

public:
	
Vec3f color;

};


// ====================================================================
// ====================================================================

#endif
