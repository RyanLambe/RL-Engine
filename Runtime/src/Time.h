#pragma once

#include <Windows.h>
#include <vector>

namespace Core {
	static class Time {
	public:

		class Timer {
		public:
			void start();
			float getTime();

		private:
			DWORD startFrame;
		};

		Time();
		void update();

		static float getTime();
		static float deltaTime();

	private:

		static void addTimer(Timer* timer);

		static DWORD startFrame;
		static DWORD prevFrame;

		static std::vector<Timer*> timers;
	};
}