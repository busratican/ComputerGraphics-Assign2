#include "camera.h"
#include "vectors.h"
#include "camera.h"
#include "ray.h"
#include "floatpoint.h"
/* Orthographic Camera */
OrthographicCamera::OrthographicCamera(Vec3f c, Vec3f direction, Vec3f u, float s)
{
    center = c;
    dir = direction; dir.Normalize(); // This is using sqrt, try quake appox?
    // Make orthonormal
    if(u.Dot3(dir) != 0)
    {
        Vec3f t;
        Vec3f::Cross3(t,u,dir);
        Vec3f::Cross3(up,dir,t);
    }
    else
        up = u;

    up.Normalize();
    
    size = s;
    Vec3f::Cross3(horz, dir, up);
    horz.Normalize();
}

OrthographicCamera::~OrthographicCamera() {}

Ray OrthographicCamera::generateRay(Vec2f point)
{
    //0,0 -> 1,1 :: -.5,-.5 -> .5,.5
    //center + y*size*up + x*size*horz;
    Vec3f p(center + (point.y()-.5f)*(size*up) + (point.x()-.5f)*(size*horz));
    return (Ray(p,dir));
}

float OrthographicCamera::getTMin() const
{
    return -FLT_MAX;
    //return log(0); // -&infin
}

/* Perspective Camera */

PerspectiveCamera::PerspectiveCamera(Vec3f &c, Vec3f &direction, Vec3f &u, float a)
{
    center = c;
    dir = direction;
	 dir.Normalize();
    up = u; up.Normalize();
    Vec3f::Cross3(horz, dir, u); 
	horz.Normalize();
    Vec3f::Cross3(up, dir, horz);
    angle = a;
}

PerspectiveCamera::~PerspectiveCamera() {}

Ray PerspectiveCamera::generateRay(Vec2f point)
{
assert(point.x() < 1.0 && point.x() >= 0.0);
	assert(point.y() < 1.0 && point.y() >= 0.0);
	assert(f_unequal(point.x(), 1.0));
	assert(f_unequal(point.y(), 1.0));
	assert(angle != 0);

	Vec3f org(0.0, 0.0, 0.0);
	Vec3f dir;
	Vec3f target;

	// assume distance between origin and image plane is 1
	float hypotenuse = 1 / cos(angle/2);
	float image_plane_size = (hypotenuse * sin(angle/2)) * 2;
	float x_off, y_off;


	x_off = image_plane_size * (point.x() - 0.5);
	y_off = image_plane_size * (point.y() - 0.5);
	cout << x_off << "," << y_off << endl;

	// get the image plane origin
	target = center + this->dir;
	// add x offset
	target.Set(target.x()+x_off, target.y(), target.z());
	// add y offset
	target.Set(target.x(), target.y()+y_off, target.z());

	org = center;

	cout << target << endl;
	// get direction vector
	dir = target - center;
	dir.Normalize();
	Ray r(org, dir);
	cout << "ray: dir correspond to (" << point.x() << "," << point.y() << "), " << dir << endl;
	return r;
}

float PerspectiveCamera::getTMin() const
{
    return 1e-6; // min representable by float close to 0
}
