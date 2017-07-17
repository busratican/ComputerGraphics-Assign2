#ifndef _HIT_H
#define _HIT_H

#include "vectors.h"
#include "ray.h"

//class Material



// ====================================================================
// ====================================================================

class Hit {
  
public:

  // CONSTRUCTOR & DESTRUCTOR
  Hit(float _t, Vec3f c, Vec3f n) { t = _t; color = c; normal = n; }
  Hit(const Hit &h) { t = h.t; color = h.color; normal = h.normal; intersectionPoint = h.intersectionPoint;}
  ~Hit() {}

  // ACCESSORS
  float getT() const { return t; }
  Vec3f getColor() const { return color; }
  Vec3f getNormal() const { return normal; }
   Vec3f getIntersectionPoint() const { return intersectionPoint; }
    // ACCESSORS
  virtual Vec3f getDiffuseColor() const { return diffuseColor; }
  // MODIFIER
  void set(float _t, Vec3f c, Vec3f n,const Ray &ray) 
  { t = _t; 
  color = c; 
  normal = n;
   intersectionPoint = ray.pointAtParameter(t); }

   
protected: 

  // REPRESENTATION
  float t;
  Vec3f color;
  //Material *material;
  Vec3f normal;
  Vec3f intersectionPoint;

  // REPRESENTATION
  Vec3f diffuseColor;
};

inline ostream &operator<<(ostream &os, const Hit &h) {
  os << "Hit <" <<h.getT()<<", "<<h.getColor()<<", "<<h.getNormal()<<">";
  return os;
}
// ====================================================================
// ====================================================================

#endif
