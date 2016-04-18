#pragma once
#include "Component.h"
#include "Shader.h"
#include <vector>

class MeshComponent : public Component
{
	struct AttributeSet
	{
		glm::vec3 pos;
		glm::vec3 col;

		AttributeSet(glm::vec3 position, glm::vec3 color)
		{
			pos = position;
			col = color;
		}
	};

public:
	MeshComponent();
	~MeshComponent();

	bool Init();
	bool InitShader(const char* vsFile, const char* fsFile);

	void Destroy();

	bool Update();
	void Render();

	GLuint program;

private:
	bool LoadShader(const char* vsFile, const char* fsFile);
	bool LinkShader();
	
	void GenCube();

	shader myShader;

	GLuint vbo;
	//GLuint ibo;
	
	std::vector<AttributeSet> attributes;
	//GLushort elms[36];
	
	GLint attribute_coord3d;
	GLint attribute_colors;
	GLint attribute_transform;
};
