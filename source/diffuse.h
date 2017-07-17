#include "shader.h"

class DiffuseShader : public Shader {

public:
	DiffuseShader() {};
	~DiffuseShader() {};
	Vec3f shading(Vec3f &output_color,
		     Hit *hit_point, SceneParser *scene);
private:
};
