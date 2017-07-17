#include "vectors.h"
#include "hit.h"
#include "light.h"
#include "normal.h"

Vec3f NormalShader::shading(Vec3f &output_color,
			   Hit *hit_point, SceneParser *scene)
{
	Vec3f normal = hit_point->getNormal();
	output_color = normal;
	return output_color;
}
