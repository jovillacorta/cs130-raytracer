#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
   //TODO;
	Hit intersect;

	double checkIntersect;

	//t = (n * (e - p)) / n * u
	
	checkIntersect = dot(this->normal, ray.direction);

	if (checkIntersect == 0) { 
	// if n*u ==0, no intersection

		intersect.object = NULL;
		intersect.dist = 0;
		intersect.part = part;

	}

	else {
	// find t; if t > 0, record intersect
		double t;

		t = (dot(normal, (this->x1 - ray.endpoint))) / checkIntersect;

		if (t > 0) {
			intersect.object = this;
			intersect.dist = t;
			intersect.part = part;
		}
		else{
			intersect = {NULL, 0, -1};
		}

	}

    return intersect;
}

vec3 Plane::Normal(const vec3& point, int part) const
{
    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}
