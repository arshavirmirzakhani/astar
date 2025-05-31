#include "object.h"

class Scene {
      public:
	Scene();
	~Scene();

	void add_object(std::string name, Object object);

	std::map<std::string, Object> objects;

	int width;
	int height;

	template <class Archive> void serialize(Archive& archive) { archive(objects, width, height); }
};
