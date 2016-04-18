#include "MeshComponent.h"
#include "GameObject.h"
#include "HelperFunctions.h"
#include "GameManager.h"

#include <glm/gtc/type_ptr.hpp>

MeshComponent::MeshComponent()
{
}

MeshComponent::~MeshComponent()
{
}

bool MeshComponent::Init()
{
	myShader = shader();

	if (!InitShader("vsDefault.glsl", "fsDefault.glsl"))
		return false;

	glm::vec3 pos = glm::vec3();
	glm::vec3 col = glm::vec3();

	pos.x = 0.0f;
	pos.y = 0.8f;

	col.r = 1.0f;
	col.g = 1.0f;
	col.b = 0.0f;

	attributes.push_back(AttributeSet(pos, col));

	pos.x = -0.8f;
	pos.y = -0.8f;

	col.r = 0.0f;
	col.g = 0.0f;
	col.b = 1.0f;

	attributes.push_back(AttributeSet(pos, col));

	pos.x = 0.8f;
	pos.y = -0.8f;

	col.r = 1.0f;
	col.g = 0.0f;
	col.b = 0.0f;

	attributes.push_back(AttributeSet(pos, col));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, attributes.size() * sizeof(AttributeSet), &attributes.front(), GL_STATIC_DRAW);

	return true;
}

bool MeshComponent::InitShader(const char* vsFile, const char* fsFile)
{
	if (!LoadShader(vsFile, fsFile))
		return false;

	if (!LinkShader())
		return false;

	return true;
}

bool MeshComponent::LoadShader(const char* vsFile, const char* fsFile)
{
	GLint compiled = GL_FALSE;

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const char *vs_source = GetFileContents(vsFile);

	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);

	glGetShaderiv(vs, GL_COMPILE_STATUS, &compiled);

	if (!compiled) {
		std::cerr << "Error in vertex shader" << std::endl;
		return false;
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	const char* fs_source = GetFileContents(fsFile);

	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		std::cerr << "Error in fragment shader" << std::endl;
		return false;
	}

	myShader.vertexShader = vs;
	myShader.fragmentShader = fs;

	return true;
}

bool MeshComponent::LinkShader()
{
	GLint linked = GL_FALSE;

	program = glCreateProgram();

	glAttachShader(program, myShader.vertexShader);
	glAttachShader(program, myShader.fragmentShader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (!linked) {
		std::cerr << "Error in glLinkProgram" << std::endl;
		return false;
	}

	const char* attribute_name = "coord3d";
	attribute_coord3d = glGetAttribLocation(program, attribute_name);

	if (attribute_coord3d == -1)
	{
		std::cerr << "Could not bind attribute " << attribute_name << std::endl;
		return false;
	}

	attribute_name = "v_color";
	attribute_colors = glGetAttribLocation(program, attribute_name);

	if (attribute_colors == -1)
	{
		std::cerr << "Could not bind attribute " << attribute_name << std::endl;
		return false;
	}

	attribute_name = "transformation";
	attribute_transform = glGetUniformLocation(program, attribute_name);

	if (attribute_transform == -1)
	{
		std::cerr << "Could not bind attribute " << attribute_name << std::endl;
		return false;
	}

	return true;
}

void MeshComponent::Destroy()
{
	glDeleteProgram(program);
	glDeleteBuffers(1, &vbo);
}

bool MeshComponent::Update()
{
	glUseProgram(program);
	glUniformMatrix4fv(attribute_transform, 1, GL_FALSE, glm::value_ptr(gameObject->transform->matrix));

	return true;
}

void MeshComponent::Render()
{
	glUseProgram(program);

	glEnableVertexAttribArray(attribute_coord3d);
	glEnableVertexAttribArray(attribute_colors);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(attribute_coord3d, 3, GL_FLOAT, GL_FALSE, sizeof(struct AttributeSet), 0);
	glVertexAttribPointer(attribute_colors, 3, GL_FLOAT, GL_FALSE, sizeof(struct AttributeSet), (GLvoid*) offsetof(struct AttributeSet, col));

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(attribute_coord3d);
	glDisableVertexAttribArray(attribute_colors);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}