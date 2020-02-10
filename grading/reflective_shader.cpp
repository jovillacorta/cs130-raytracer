#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const {

    vec3 color;

    color = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
    // reflected = d-2(d-n)n;


    if (recursion_depth < world.recursion_depth_limit){ // if within recursion limit, calculate reflected color

		vec3 d = ray.direction;
		Ray reflected;
		reflected.endpoint = intersection_point;
		reflected.direction = d - 2 * dot(d,normal) * normal;
		
		return ((1 - reflectivity) * color + reflectivity * world.Cast_Ray(reflected, recursion_depth+1));
	}
    

    return (1 - reflectivity) * color; // reach recursion limit = return color without a reflected ray casted
}

