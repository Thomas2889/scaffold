#pragma once

#include <unordered_map>
#include <string>

#include <entt.hpp>


// These two macros are used to define and implement some prototype data to enable the class as a true ECS system.
#define DEFINE_SYSTEM_PROTO(__type__)	private: static scaffold::ecs::SystemProto* SystemProto_##__type__; \
										public: static const std::string systemUID;

#define IMPLEMENT_SYSTEM_PROTO(__type__)	scaffold::ecs::SystemProto* __type__##::SystemProto_##__type__ = scaffold::ecs::SystemProto::AddPrototype(new __type__(), #__type__); \
											const std::string __type__##::systemUID = #__type__;

#pragma region FunctionDefines
#define System_Start() void Start()
#define System_End() void End()

#define System_PreRender(__dt__) void PreRender(float __dt__)
#define System_Render(__dt__) void Render(float __dt__)
#define System_PostRender(__dt__) void PostRender(float __dt__)

#define System_PreTick(__dt__) void PreTick(float __dt__)
#define System_Tick(__dt__) void Tick(float __dt__)
#define System_PostTick(__dt__) void PostTick(float __dt__)
#pragma endregion


namespace scaffold::ecs
{
	class SystemProto
	{
	public:
		static std::unordered_map<std::string, SystemProto*>* systems;

		static SystemProto* AddPrototype(SystemProto* _p, std::string UID)
		{
			if (systems == nullptr)
				systems = new std::unordered_map<std::string, SystemProto*>;
			(*systems)[UID] = _p;
			return _p;
		}

		static void Cleanup()
		{
			if (systems != nullptr)
				delete systems;
		}

#pragma region System Functions
		virtual System_Start() {}
		virtual System_End() {}

		virtual System_PreRender() {}
		virtual System_Render() {}
		virtual System_PostRender() {}

		virtual System_PreTick() {}
		virtual System_Tick() {}
		virtual System_PostTick() {}
#pragma endregion
	};
}
