#include "vectors.h"
#include "scene_parser.h"
#include "hit.h"
#include "light.h"
#include "diffuse.h"

Vec3f DiffuseShader::shading(Vec3f &output_color,
			    Hit *hit_point, SceneParser *scene)
{
	int light_idx, num_lights;
	Vec3f obj_color = hit_point->getColor();
	Vec3f light_dir, light_color;
	Vec3f ambient = scene->getAmbientLight();
	num_lights = scene->getNumLights();

	output_color = obj_color*ambient;

	// shading the pixel
	for (light_idx = 0; light_idx < num_lights; light_idx++) {
		float d;
		Light *light = scene->getLight(light_idx);
		light->getIllumination(
			hit_point->getIntersectionPoint(),
			light_dir, light_color);

		d = hit_point->getNormal().Dot3(light_dir); 
		if (d < 0) d = 0;

		output_color += (obj_color*light_color*d);
		
		return output_color;
	}
}
