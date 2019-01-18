#pragma once

struct ray
{
	ray() {}
	ray(vector3 const &origin, vector3 const &direction) : origin(origin), direction(direction) {}
	ray(const ray &ray) : origin(ray.origin), direction(ray.direction) {}

	vector3 origin;
	vector3 direction;
};

