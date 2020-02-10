#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;

    vec3 sum_Id;
    vec3 sum_Is;
    vec3 Ia;


    for (int i =0; i < world.lights.size(); i++){

    	vec3 Id;
    	vec3 Is;
    	vec3 lvec = world.lights[i]->position - intersection_point;
    	vec3 vvec = ray.endpoint - intersection_point;

    	// Id = R*L*max(l*n) 
    	//USE NORMALIZED VECTORS for max(l*n)!!!

    	double dotDiffuse = dot(normal, lvec.normalized());
    	double maxDiffuse = fmax(0.0, dotDiffuse);


    	Id = color_diffuse * world.lights[i]->Emitted_Light(lvec) * maxDiffuse;
    	sum_Id += Id;


    	// Is = R*L*max(v*r)^e 
    	// reflected = -l + 2(l*n)n
    	vec3 reflected = -lvec + 2 * dot(lvec,normal) * normal;

    	double dotSpecular = dot(reflected.normalized(), vvec.normalized());
    	double maxSpecular = fmax(0.0, dotSpecular);
    	double expSpecular = pow(maxSpecular, specular_power);

    	Is = color_specular * world.lights[i]->Emitted_Light(lvec) * expSpecular;
    	sum_Is += Is; 
    }
    //TODO; //determine the color
    // ambient color = r_amb*l_amb

    Ia = color_ambient * world.ambient_color * world.ambient_intensity; 

    color = Ia + sum_Id + sum_Is;
    return color;
}
