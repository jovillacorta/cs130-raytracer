#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color; //TODO; //determine the color

    vec3 sum_Id; //summation of all lights' i_diffuse
    vec3 sum_Is; //summation off all lights' i_specular
    vec3 Ia;	 //ambient light
 	Ia = color_ambient * world.ambient_color * world.ambient_intensity; // ambient color = r_amb*l_amb

 	color = Ia;


    for (int i =0; i < world.lights.size(); i++){ 
    //first find if in shadow
    	vec3 lvec = world.lights[i]->position - intersection_point;
    	Ray sRay(intersection_point,lvec); //cast a shadow ray from intersect towards the light

    	Hit shadowObj = world.Closest_Intersection(sRay); //check: does the shadow ray hit anything?

    if (!shadowObj.object){
    //for each light find their diffuse and specular intensities

    	vec3 Id;
    	vec3 Is;

    	// Id = R*L*max(l*n) 
    	// l = light, n = normal
    	// l = light pos - intersect
    	//USE NORMALIZED VECTORS for max(l*n)!!!
    	

    	double dotDiffuse = dot(normal, lvec.normalized());
    	double maxDiffuse = fmax(0.0, dotDiffuse);


    	Id = color_diffuse * world.lights[i]->Emitted_Light(lvec) * maxDiffuse;
    	sum_Id += Id;


    	// Is = R*L*max(v*r)^e  *note NORMALIZED 
    	// r = reflected, v = view
    	// reflected = -l + 2(l*n)n
    	// view = ray end - intersect 

    	vec3 vvec = ray.endpoint - intersection_point;
    	vec3 rvec = -lvec + 2 * dot(lvec,normal) * normal;

    	double dotSpecular = dot(rvec.normalized(), vvec.normalized());
    	double maxSpecular = fmax(0.0, dotSpecular);
    	double expSpecular = pow(maxSpecular, specular_power);

    	Is = color_specular * world.lights[i]->Emitted_Light(lvec) * expSpecular;
    	sum_Is += Is; 

    	color += sum_Id + sum_Is;  
    }
	}


    return color;
}
