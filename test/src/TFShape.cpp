
#include "TFShape.h"

#include <glm/gtx/transform.hpp>

TFShape::TFShape(const std::vector<vec4>& _verts, const GLenum& mode):
	Shape(mode),
	verts(_verts)
{
	vertBuf = genBuffer(verts.size(), 4);
	update();
}

TFShape::TFShape(const std::vector<vec3>& _verts, const GLenum& mode) :
	Shape(mode)
{
	// Reserve space for all vertices
	verts.reserve(_verts.size());

	// Copy the vertices
	for (const vec3& v3 : _verts)
	{
		verts.emplace_back(v3.x, v3.y, v3.z, 1.0f);
	}

	vertBuf = genBuffer(verts.size(), 4);
	update();
}

TFShape::TFShape(const std::vector<vec2>& _verts, const GLenum& mode) :
	Shape(mode)
{
	// Reserve space for all vertices
	verts.reserve(_verts.size());

	// Copy the vertices
	for (const vec2& v2 : _verts)
	{
		verts.emplace_back(v2.x, v2.y, 0.0f, 1.0f);
	}

	vertBuf = genBuffer(verts.size(), 4);
	update();
}

void TFShape::tfInt(const mat4& mat)
{
	for (vec4& v : verts)
	{
		v = mat * v;
	}
	update();
}

void TFShape::tlInt(const vec3& d)
{
	tfInt(glm::translate(glm::mat4(), d));
}
void TFShape::tlInt(const vec2& d)
{
	tfInt(glm::translate(mat4(), vec3(d.x, d.y, 0.0f)));
}

void TFShape::rotInt(const GLfloat& angle, const vec3& axis)
{
	tfInt(glm::rotate(mat4(), angle, axis));
}

void TFShape::tfExt(const bool& rel, const mat4& mat)
{
	if (rel)
		tfMat = tfMat * mat;
	else
		tfMat = mat;
}

void TFShape::tlExt(const bool& rel, const vec3& d)
{
	tfExt(rel, glm::translate(glm::mat4(), d));
}
void TFShape::tlExt(const bool& rel, const vec2& d)
{
	tfExt(rel, glm::translate(mat4(), vec3(d.x, d.y, 0.0f)));
}

void TFShape::rotExt(const bool& rel, const GLfloat& angle, const vec3& axis)
{
	tfExt(rel, glm::rotate(mat4(), angle, axis));
}

void TFShape::update()
{
	// Copy from the vertex array to the float array
	for (size_t v = 0; v < verts.size(); ++v)
	{
		for (size_t i = 0; i < 4; ++i)
		{
#pragma warning(suppress: 4267)
			vertBuf[v * 4 + i] = verts[v][i];
		}
	}

	// Copy from the float array to the buffer
	Shape::update();
}