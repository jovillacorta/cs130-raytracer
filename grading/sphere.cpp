#include "sphere.h"
#include "ray.h"
#include <cmath>

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
	Hit intersect;
    //TODO;
    double A, B, C, discriminant;
    
    // A= d*d = d^2
    A = ray.direction.magnitude_squared();
    // B = 2d(e-c)
    B = 2 * dot(ray.direction, (ray.endpoint - this->center));
    //C = (e-c) * (e-c) - R^2
    C = (ray.endpoint - this->center).magnitude_squared() - (this->radius * this->radius);
    
    //discriminant = B^2 - 4*A*C
    discriminant = (B*B) - (4*A*C);

    if (discriminant < 0){
    	intersect.object = NULL;
    	intersect.dist = 0;
    	intersect.part = part;
    }

    else {
    	// Find t using quadratic formula
    	double t1, t2;
    	t1 = (-B + sqrt(discriminant)) / (2 * A); //plus
    	t2 = (-B - sqrt(discriminant)) / (2 * A); //minus

    	if (t1 <= t2){
    		intersect.object = this;
    		intersect.dist = t1;
    		intersect.part = part;
    	}

    	else if (t2 < t1) {
    		intersect.object = this;
    		intersect.dist = t2;
    		intersect.part = part;
    	}

    }

    return intersect;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;

    //TODO; // compute the normal direction
    
    //n= 2(p-c)
    normal = (point - this->center);
    return normal.normalized();
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
