﻿#ifndef	_SCENE_H_
#define	_SCENE_H_

#include <vector>
#include <typeinfo>

#include "constant.h"
#include "intersection.h"

#include "object/object.h"
#include "object/sphere.h"
#include "object/raymarching_sphere.h"
#include "object/raymarching_menger_sponge.h"
#include "object/raymarching_menger_sponge_loop.h"
#include "object/raymarching_mbox.h"
#include "object/point_light.h"

namespace tsukihi {
	Color backgroundColor = Color(0.0, 0.0, 0.0);

	Vec3 camera_position;
	Vec3 camera_dir;
	Vec3 camera_up;

	std::vector<Object*> objects;
	std::vector<Object*> cast_shadow_objects;
	std::vector<Object*> refraction_objects;
	std::vector<Object*> not_refraction_objects;
	std::vector<PointLight*> lights;

	void setup_sponge() {
		// 全体像
		camera_position = Vec3(50.0, 52.0, 220.0);
		camera_dir = normalize(Vec3(0.0, -0.04, -1.0));
		camera_up = Vec3(0.0, 1.0, 0.0);

		// 中身
		//camera_position = Vec3(50, 60, 80);
		//camera_dir      = normalize(Vec3(-0.1, -1.0, -0.01));
		//camera_up       = Vec3(0.0, -1.0, 0.0);

		// 斜め視点
		//camera_position = Vec3(90.0, 78.0, 130.0);
		//camera_dir = normalize(Vec3(-0.4, -0.5, -0.5));
		//camera_up = Vec3(0.0, 1.0, 0.0);

		objects.push_back(new Sphere(1e5, Vec3(-1e5 + 1, 40.8, 81.6), Color(), Color(0.75, 0.25, 0.25), REFLECTION_TYPE_DIFFUSE)); // 左
		objects.push_back(new Sphere(1e5, Vec3(1e5 + 99, 40.8, 81.6), Color(), Color(0.25, 0.25, 0.75), REFLECTION_TYPE_DIFFUSE)); // 右
		objects.push_back(new Sphere(1e5, Vec3(50, 40.8, -1e5), Color(), Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE));// 奥
		objects.push_back(new Sphere(1e5, Vec3(50, 40.8, 1e5 + 250), Color(), Color(), REFLECTION_TYPE_DIFFUSE));// 手前
		objects.push_back(new Sphere(1e5, Vec3(50, -1e5, 81.6), Color(), Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE)); // 床
		objects.push_back(new Sphere(1e5, Vec3(50, 1e5 + 81.6, 81.6), Color(), Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE)); // 天井

		//objects.push_back(new Sphere(1.0, Vec3(50.0, 90.0 - 10, 81.6), Color(36, 36, 36), Color(), REFLECTION_TYPE_SPECULAR)); //照明
		//objects.push_back(new Sphere(1.0, Vec3(50.0, 20, 120), Color(36, 36, 36), Color(), REFLECTION_TYPE_SPECULAR)); //照明

		//objects.push_back(new Sphere(20,Vec(65, 20, 20),           Color(),       Color(0.99, 0.99, 0.99), REFLECTION_TYPE_SPECULAR)); // 鏡
		//objects.push_back(new Sphere(16.5,Vec(47, 16.5, 117),       Color(),      Color(0.99, 0.199, 0.99), REFLECTION_TYPE_REFRACTION)); // ガラス
		//objects.push_back(new Sphere(15,Vec(73, 15, 100),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_REFRACTION)); //ガラス
		//objects.push_back(new RaymarchingSphere(Color(), Color(0.75, 0.25, 0.25), REFLECTION_TYPE_SPECULAR));

		double scale = 22;
		auto sponge = new RaymarchingMengerSponge(Vec3(50, scale, 70), scale, Color(), Color(0.25, 0.75, 0.25), REFLECTION_TYPE_DIFFUSE);
		objects.push_back(sponge);
		cast_shadow_objects.push_back(sponge);

		lights.push_back(new PointLight(1.0, Vec3(50.0, 90.0 - 10, 81.6), Color(255, 255, 255)));
		lights.push_back(new PointLight(1.0, Vec3(50.0, 20, 120.0), Color(255, 255, 255)));
	}

	void setup_sponge2() {
		// 全体を覆う光源
		backgroundColor = Color(1, 1, 1);

		// 全体像
		//camera_position = Vec3(50.0, 52.0, 220.0);
		//camera_dir = normalize(Vec3(0.0, -0.04, -1.0));
		//camera_up = Vec3(0.0, 1.0, 0.0);

		// 中身
		//camera_position = Vec3(50, 60, 80);
		//camera_dir      = normalize(Vec3(-0.1, -1.0, -0.01));
		//camera_up       = Vec3(0.0, -1.0, 0.0);

		// 斜め視点
		camera_position = Vec3(90.0, 78.0, 130.0);
		camera_dir = normalize(Vec3(-0.4, -0.5, -0.5));
		camera_up = Vec3(0.0, 1.0, 0.0);

		//objects.push_back(new Sphere(1e5, Vec3(-1e5 + 1, 40.8, 81.6), Color(), Color(0.75, 0.25, 0.25), REFLECTION_TYPE_DIFFUSE)); // 左
		//objects.push_back(new Sphere(1e5, Vec3(1e5 + 99, 40.8, 81.6), Color(), Color(0.25, 0.25, 0.75), REFLECTION_TYPE_DIFFUSE)); // 右
		//objects.push_back(new Sphere(1e5, Vec3(50, 40.8, -1e5), Color(), Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE));// 奥
		//objects.push_back(new Sphere(1e5, Vec3(50, 40.8, 1e5 + 250), Color(), Color(), REFLECTION_TYPE_DIFFUSE));// 手前
		objects.push_back(new Sphere(1e5, Vec3(50, -1e5, 81.6), Color(), Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE)); // 床
		//objects.push_back(new Sphere(1e5, Vec3(50, 1e5 + 81.6, 81.6), Color(), Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE)); // 天井

		double scale = 22;
		auto sponge = new RaymarchingMengerSponge(Vec3(50, scale, 70), scale, Color(), Color(0.25, 0.75, 0.25), REFLECTION_TYPE_DIFFUSE);
		objects.push_back(sponge);
		cast_shadow_objects.push_back(sponge);

		lights.push_back(new PointLight(1.0, Vec3(50.0, 90.0 - 10, 81.6), Color(255, 255, 255)));
		//lights.push_back(new PointLight(1.0, Vec3(50.0, 20, 120.0), Color(255, 255, 255)));
	}

	void setup_sponge_inside() {
		camera_position = Vec3(0, 0, 80);
		camera_dir = normalize(Vec3(-3, -1, -10));
		camera_up = Vec3(0.0, 1.0, 0.0);

		double scale = 30;
		auto sponge = new RaymarchingMengerSpongeLoop(Vec3(0, 0, 0), scale, Color(), Color(0.25, 0.75, 0.3), REFLECTION_TYPE_DIFFUSE);
		objects.push_back(sponge);
		cast_shadow_objects.push_back(sponge);

		double r = 2.5;
		auto glass = new Sphere(r, Vec3(-5, -10 + r, 42), Color(), Color(1.0, 1.0, 1.0), REFLECTION_TYPE_REFRACTION);
		//auto glass = new RaymarchingSphere(Vec3(-4, -10 + r, 42), r, Color(), Color(1.0, 1.0, 1.0), REFLECTION_TYPE_REFRACTION);
		objects.push_back(glass);
		cast_shadow_objects.push_back(glass);
		refraction_objects.push_back(glass);

		//r = 2.0;
		auto mirror = new Sphere(r, Vec3(-12, -10 + r, 62.5), Color(), Color(1.0, 1.0, 1.0), REFLECTION_TYPE_SPECULAR);
		objects.push_back(mirror);
		cast_shadow_objects.push_back(mirror);

		double s = 1.0;
		//s = 2.5;
		double inv_pow_s = 1.0 / (s*s);
		//lights.push_back(new PointLight(1.0*s, Vec3(0, 10, -150), Color(0, 0, 35) * inv_pow_s));
		//lights.push_back(new PointLight(1.0*s, Vec3(0, 10, -90), Color(35, 35, 35) * inv_pow_s));
		lights.push_back(new PointLight(1.0*s, Vec3(0, 9.7, -30), Color(35, 0, 0) * inv_pow_s));
		lights.push_back(new PointLight(1.0*s, Vec3(0, 9.7, 30), Color(70, 70, 70) * inv_pow_s));
		lights.push_back(new PointLight(1.0*s, Vec3(-2, 0, 82), Color(35, 35, 35) * inv_pow_s));
	}

	void setup_mbox() {
		camera_position = Vec3(1.373, 2.741, 0.026);
		camera_dir = normalize(Vec3(-0.8, -0.5, 0.001));
		camera_up = Vec3(0.0, 1.0, 0.0);

		auto mbox = new RaymarchingMbox(Vec3(0.0, 0.0, 0.0), 1.0, Color(), Color(0.25, 0.75, 0.25), REFLECTION_TYPE_DIFFUSE);
		objects.push_back(mbox);
		cast_shadow_objects.push_back(mbox);

		lights.push_back(new PointLight(1.0, camera_position - camera_dir * 1 + Vec3(0, -2.0, 0), Color(5, 5, 5)));
		//lights.push_back(new PointLight(1.0, Vec3(50.0, 20, 120.0), Color(255, 255, 255)));
	}

	void setup() {
		//setup_mbox();
		//setup_sponge();
		//setup_sponge2();
		setup_sponge_inside();

		for (auto object : objects) {
			auto itr = std::find(refraction_objects.begin(), refraction_objects.end(), object);
			if (itr == refraction_objects.end()) {
				not_refraction_objects.push_back(object);
			}
		}
	}

	// シーンとの交差判定関数
	inline bool intersect_scene(const Ray &ray, Intersection *intersection) {
		// 初期化
		intersection->hitpoint.distance = kINF;
		intersection->object = nullptr;

		// 線形探索
		for (auto object : objects) {
			Hitpoint hitpoint;
			if (object->intersect(ray, &hitpoint)) {
				if (hitpoint.distance < intersection->hitpoint.distance) {
					intersection->hitpoint = hitpoint;
					intersection->object = object;
				}
			}
		}

		for (auto light : lights) {
			Hitpoint hitpoint;
			if (light->intersect(ray, &hitpoint)) {
				if (hitpoint.distance < intersection->hitpoint.distance) {
					intersection->hitpoint = hitpoint;
					intersection->object = light;
				}
			}
		}

		return (intersection->object != nullptr);
	}
};

#endif