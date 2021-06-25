#pragma once

#include <glm/glm.hpp>


namespace powd::input
{
	class InputEntry
	{
	public:
		virtual ~InputEntry() {};
		virtual bool ProcessBool(bool val) { return val; }
		virtual int ProcessInt(int val) { return val; }
		virtual float ProcessFloat(float val) { return val; }
		virtual glm::vec2 ProcessVec2(glm::vec2 val) { return val; }
		virtual glm::vec3 ProcessVec3(glm::vec3 val) { return val; }
	};
}
