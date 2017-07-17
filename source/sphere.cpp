#include "sphere.h"
#include "vectors.h"
#include "ray.h"
#include "hit.h"
#include "floatpoint.h"


 Sphere::Sphere( Vec3f center, float radius,
		Vec3f color)
	{
		this->center = center;
		this->radius = radius;
		this->color = color;
	};
	
#if 0
// Algebraic solution

	
bool Sphere::intersect(const Ray &r, Hit &h, float tmin)
{

	//
	// The intersection point can be obtained via following methold:
	//
	//     For a given point P on the ray, if P satisfies:
	//         (Length of P and origin) - radius = 0,
	//     we can say, P is on the sphere
	//
	//     P can be represented by P(t) = o + d*t, where o is 
	//     origin, and d is the direction vector of the Ray
	//     t is unknown.
	//
	//     To get t, we should solve the equaltion:
	//        (P - center)^2 = radius^2
	//     => P^2 - 2*P*center + center^2 = radius^2
	//     => (o + d*t)^2 - 2*(o + d*t)*center + center^2 = radius^2
	//     => o^2 + 2*d*o*t + d^2*t^2 - 2*o*center - 2*d*center*t + center^2
	//           - radius^2 = 0
	//     => (d^2)*t^2 + 2*d*(o-center)*t + (o^2 - 2*o*center +
	//           center^2 - radius^2) = 0
	//     => (d^2)*t^2 + 2*d*(o-center)*t + ((o-center)^2 - radius^2) = 0
	//
	//     Solution t = -B +(or -) sqrt(B^2 -4*A*C) / 2*A
	//        Where A = (d^2)
	//              B = 2*d*(o-center)
	//              C = ((o-center)^2 - radius^2)
	//
	//	Note: the * operator of two vectors is Dot product

	float t, discriminant;
	Vec3f d = r.getDirection();
	Vec3f o = r.getOrigin();

	discriminant = 4*d.Dot3(o-center)*d.Dot3(o-center) - 
		4*d.Dot3(d)*((o-center).Dot3(o-center)-radius*radius);
	if (discriminant < 0)
		return false;
	if (f_equal(discriminant, 0.0f))
		return false;

	// choice smaller solution
	t = (-2*d.Dot3(o-center) - sqrt(discriminant)) / 2*d.Dot3(d);

	if (t > tmin || f_equal(t, tmin)) {
		if (t < h.getT())
			h.set(t, material, r);
		return true;
	}
	else 
		return false;
}
#endif

#if 1
// Geometric solution
bool Sphere::intersect(const Ray &r, Hit &h, float tmin)
{
#define INSIDE   0
#define ONSPHERE 1
#define OUTSIDE  2

	Vec3f d = r.getDirection();
	Vec3f o = r.getOrigin();
	Vec3f co = o-center;
	Vec3f n;
	int state;
	float tp, sd2, t1, t;
	float radius2 = radius*radius;

	// Firstly, we should decide ray origin, said o, is inside,
	// outside or on the sphere:
	//    inside:  (co)^2 < radius^2
	//    on:      (co)^2 = radius^2
	//    outside: (co)^2 > radius^2
	//
	// where co is the vector from sphere center to ray origin

	if (co.Dot3(co) < radius2)
		state = INSIDE;
	else if (f_equal(co.Dot3(co), radius2))
		state = ONSPHERE;
	else
		state = OUTSIDE;

	// Then, find the closest point on the ray, said cp,
	// to sphere origin, the distance between closest point
	// cp and ray origin is tp:
	//   tp = -(o-center) * d
	// where d is direction vector input ray r
	tp = -co.Dot3(d);

	// Then, find the squared distance sd between ray and center
	// sd^2 = (o-center)^2 - tp^2  (Pythagoras' Theorem)
	//
	//    - if sd^2 > r^2 => no hit
	sd2 = co.Dot3(co) - tp*tp;
	if (sd2 > radius2)
		return false;

	// to omit glitch on the cutedge of the sphere
	// TODO: should have better solution
	if (f_equal(sd2, radius2))
		return false;

	// Find distance t1 from closest point cp to correct
	// intersection point
	//   t1^2 = radius^2 - sd^2 (Pythagoras' Theorem)
	t1 = sqrt(radius2 - sd2);

	// Finally, we can get:
	if (state == ONSPHERE && tp > 0.0f)
		t = 0.0f;
	else if (state == ONSPHERE && tp < 0.0f)
		t = 2.0f*tp;
	else if (state == OUTSIDE && tp < 0.0f)
		t = -(-tp + t1);
	else if (state == OUTSIDE)
		t = tp - t1;
	else if (state == INSIDE && (tp > 0.0f || f_equal(tp, 0.0f)))
		t = -(tp + t1);
	else if (state == INSIDE)
		t = -(-t1 - tp);
	else
		assert(0);

	// get normal vector
	n = (o + t*d) - center;

	if (t > tmin || f_equal(t, tmin)) {
		if (t < h.getT())
			h.set(t, color, n, r);
		return true;
	}
	else
		return false;
}
#endif

