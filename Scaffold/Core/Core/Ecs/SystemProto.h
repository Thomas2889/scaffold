#pragma once

#include <unordered_map>
#include <string>

#include <entt.hpp>


// This macro is required to be used for every system implementation
#define DEFINE_SYSTEM_PROTO(__type__)			private: __type__##(std::string UID, int priority) : scaffold::ecs::SystemProto(UID, priority) {} friend scaffold::ecs::SystemProto;

#define IMPLEMENT_SYSTEM_PROTO_PRI(__type__, __priority__)	scaffold::ecs::SystemProto* SystemProto_##__type__##_RefPointer = scaffold::ecs::SystemProto::AddPrototype<__type__>(#__type__, __priority__);
#define IMPLEMENT_SYSTEM_PROTO(__type__) IMPLEMENT_SYSTEM_PROTO_PRI(__type__, 0)

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
	private:
		static SystemProto* instance;
		const std::string systemUID;
		const int priority;

		static std::unordered_map<std::string, SystemProto*>* systemMap;
		static std::vector<SystemProto*>* systemList;

	protected:
		SystemProto(std::string uid, int priority);

	public:
		template <typename T>
		static SystemProto* AddPrototype(std::string UID, int priority)
		{
			SystemProto* _p = new T(UID, priority);

			if (systemMap == nullptr)
			{
				systemMap = new std::unordered_map<std::string, SystemProto*>();
				systemList = new std::vector<SystemProto*>();

				systemList->push_back(_p);
			}
			else
			{
				int i = floor(systemList->size() / 2.f);
				int previ = INT_MAX;
				int lefti = 0;
				int righti = systemList->size() - 1;
				while (true)
				{
					if (i == previ)
						break;
					previ = i;

					int refPriority = (*systemList)[i]->priority;

					if (refPriority == priority)
						break;
					else if (refPriority < priority)
					{
						if (i == 0 || (*systemList)[i - 1]->priority >= priority)
							break;
						righti = i;
						i = righti - ceil((righti - lefti) / 2.f);
					}
					else
					{
						if (i == systemList->size() - 1 || (*systemList)[i + 1]->priority <= priority)
						{
							i++;
							break;
						}
						lefti = i;
						i = lefti + ceil((righti - lefti) / 2.f);
					}
				}
				systemList->insert(systemList->begin() + i, _p);
			}

			(*systemMap)[UID] = _p;

			return _p;
		}

		static void Cleanup()
		{
			if (systemMap != nullptr)
			{
				delete systemMap;
				delete systemList;
			}
		}

#pragma region System Functions
		virtual System_Start() {}
		static void RunStart()
		{
			for (SystemProto* system : *systemList)
				system->Start();
		}

		virtual System_End() {}
		static void RunEnd()
		{
			for (SystemProto* system : *systemList)
				system->End();
		}

		virtual System_PreRender() {}
		static void RunPreRender(float dt)
		{
			for (SystemProto* system : *systemList)
				system->PreRender(dt);
		}
		virtual System_Render() {}
		static void RunRender(float dt)
		{
			for (SystemProto* system : *systemList)
				system->Render(dt);
		}
		virtual System_PostRender() {}
		static void RunPostRender(float dt)
		{
			for (SystemProto* system : *systemList)
				system->PostRender(dt);
		}

		virtual System_PreTick() {}
		static void RunPreTick(float dt)
		{
			for (SystemProto* system : *systemList)
				system->PreTick(dt);
		}
		virtual System_Tick() {}
		static void RunTick(float dt)
		{
			for (SystemProto* system : *systemList)
				system->Tick(dt);
		}
		virtual System_PostTick() {}
		static void RunPostTick(float dt)
		{
			for (SystemProto* system : *systemList)
				system->PostTick(dt);
		}
#pragma endregion
	};
}
