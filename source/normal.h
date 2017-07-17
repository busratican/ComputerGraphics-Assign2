#include "shader.h"

class NormalShader : public Shader {

public:
	NormalShader() {};
	~NormalShader() {};
	Vec3f shading(Vec3f &pixel_color,
		     Hit *hit_point, SceneParser *Scene);
private:
};
