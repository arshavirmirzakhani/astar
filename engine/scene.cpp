#include "scene.h"

Scene::Scene() {
	this->width  = 1;
	this->height = 1;
}

Scene::~Scene() {}

void Scene::add_object(std::string name, Object object) { this->objects[name] = object; }