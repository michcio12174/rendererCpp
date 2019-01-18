#pragma once

struct vertex
{
public:
	vertex(vector3 position, vector3 normal, vector3 uv): //TO OPT przekazywaæ poprzez const float3& position
		position(position), 
		normal(normal),
		uv(uv){}
	vertex(vertex const &other) :
		position(other.position),
		normal(other.normal),
		uv(other.uv){}
	vertex(vector3 position) : //debug constructor
		position(position),
		normal(vector3()),
		uv(vector3()) {}

	vector3 position;
	vector3 normal;
	vector3 uv;
	vector3 color;
};

