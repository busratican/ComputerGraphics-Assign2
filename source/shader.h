#ifndef _SHADER_H_
#define _SHADER_H_

class Vec3f;
class Hit;
class SceneParser;

class Shader {

public:
	Shader() {};
	~Shader() {};

	// calculate the pixel color - must be implemented
	virtual Vec3f shading(Vec3f &output_color,
			     Hit *hit_point, SceneParser *scene) = 0;
private:
};

#endif
