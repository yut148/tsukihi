﻿#ifndef	_RAYMARCHINNG_OBJECT_H_
#define	_RAYMARCHINNG_OBJECT_H_

#include <cmath>

#include "vec.h"
#include "ray.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"
#include "object.h"

namespace edupt {

struct RaymarchingObject : public Object {
public:
	static const int kREP = 64 * 2;

	RaymarchingObject(const Color &emission, const Color &color, const ReflectionType reflection_type) : Object(emission, color, reflection_type) {
	}

	double distanceFunction(const Vec &position) const {
		return (position - Vec(77, 16.5, 78)).length() - 16.5;
	}

	Vec calcNormal(const Vec &position) const {
		return normalize(Vec(
			distanceFunction(position + Vec( kEPS, 0.0, 0.0 ) ) - distanceFunction(position + Vec( -kEPS, 0.0, 0.0 ) ),
			distanceFunction(position + Vec( 0.0, kEPS, 0.0 ) ) - distanceFunction(position + Vec( 0.0, -kEPS, 0.0 ) ),
			distanceFunction(position + Vec( 0.0, 0.0, kEPS ) ) - distanceFunction(position + Vec( 0.0, 0.0, -kEPS ) )
		));
	}

	bool intersect(const Ray &ray, Hitpoint *hitpoint) const;
};

bool RaymarchingObject::intersect(const Ray &ray, Hitpoint *hitpoint) const {
	double d;
	double distance = 0.0;
	Vec p = ray.org;
	for (int i = 0; i < kREP; i++) {
		d = distanceFunction(p);
		distance += d;
		p = ray.org + distance * ray.dir;
		if (abs(d) < kEPS) break;
	}

	if (abs(d) < kEPS) {
		hitpoint->normal = calcNormal(p);
		hitpoint->position = p + hitpoint->normal * kEPS * 100;
		hitpoint->distance = distance;
		return true;
	} else {
		return false;
	}
}

};

#endif