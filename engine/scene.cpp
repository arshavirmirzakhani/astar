#include "scene.h"

Scene::Scene(/* args */) {
}

Scene::~Scene() {
}

void Scene::add_object(Object object){
    this->objects.push_back(object);
}