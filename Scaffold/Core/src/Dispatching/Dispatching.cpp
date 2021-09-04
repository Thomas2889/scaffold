#include "Dispatching.h"

#include <chrono>
#include <atomic>
#include <thread>
#include <cstdint>

#include "Utils/Math.h"
#include "Ecs/SystemProtoFunctions.h"
#include "Window/WindowManager.h"
#include "Debugging/CPUProfiler.h"


#define TIMEPOINT_VARS(__name__)	std::chrono::steady_clock::time_point __name__; \
									std::chrono::steady_clock::time_point __name__##Last;


namespace scaffold::dispatch
{
	namespace
	{
		struct TimepointData
		{
			TIMEPOINT_VARS(tick);
			TIMEPOINT_VARS(render);
		};

		std::atomic<bool> running = false;

		const uint32_t tickFrequency = 30;
		const uint32_t renderFrequency = 60;
		TimepointData timepoints;

		float GetDeltaTime(std::chrono::steady_clock::time_point _now, std::chrono::steady_clock::time_point _last)
		{
			return (float)(_now - _last).count() / (float)1000000000;
		}
	}

	void StopCoreLoop()
	{
		running = false;
	}

	void CoreLoop()
	{
		if (running)
			return;
		running = true;

		std::chrono::steady_clock::time_point nextUpdate = std::chrono::steady_clock::now();

		uint32_t cycleFrequency = math::lcm(tickFrequency, renderFrequency);

		std::chrono::steady_clock::time_point* pointsStrt = (std::chrono::steady_clock::time_point*)&timepoints;
		for (uint32_t i = 0; i < sizeof(timepoints) / sizeof(std::chrono::steady_clock::time_point); i++)
		{
			*pointsStrt = std::chrono::steady_clock::now();
			pointsStrt++;
		}

		std::chrono::nanoseconds timerIncrement(1000000000 / cycleFrequency);
		std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point currentTime;
		float dt;

		const std::chrono::milliseconds roughness(2); // thread waiting isn't precise and therefor we need some roughness to our time

		ecs::system::RunSystems_Start();
		while (running)
		{
			profiling::intern::StartFrame();

			nextUpdate += timerIncrement;

			currentTime = std::chrono::steady_clock::now();

			profiling::StartSectionProfile("Window Event Flushing");
			window::FlushEvents();
			profiling::StopSectionProfile();

			if (!running)
				break;

			if (currentTime >= timepoints.tick - roughness)
			{
				profiling::StartSectionProfile("Tick Loop");
				while (currentTime >= timepoints.tick - roughness)
				{
					ecs::system::RunSystems_PreTick(1.f / tickFrequency);
					ecs::system::RunSystems_Tick(1.f / tickFrequency);
					ecs::system::RunSystems_PostTick(1.f / tickFrequency);

					timepoints.tick += std::chrono::nanoseconds(1000000000 / tickFrequency);
				}
				profiling::StopSectionProfile();
			}

			if (currentTime >= timepoints.render - roughness)
			{
				profiling::StartSectionProfile("Render Loop");
				dt = GetDeltaTime(currentTime, timepoints.renderLast);

				ecs::system::RunSystems_PreRender(dt);
				ecs::system::RunSystems_Render(dt);
				ecs::system::RunSystems_PostRender(dt);

				timepoints.renderLast = currentTime;
				timepoints.render = currentTime + std::chrono::nanoseconds(1000000000 / renderFrequency);
				profiling::StopSectionProfile();
			}


			lastTime = currentTime;
			profiling::StartSectionProfile("Idle");
			std::this_thread::sleep_until(nextUpdate - roughness);

			while (std::chrono::steady_clock::now() < nextUpdate);

			profiling::StopSectionProfile();

			profiling::StopSectionProfile(); // end of frame
		}
		ecs::system::RunSystems_End();
	}
}
