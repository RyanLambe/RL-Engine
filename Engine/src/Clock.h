#pragma once

#include <Windows.h>
#include <vector>

namespace rl {
	class Clock {
	public:

		class Timer {
		public:
			void start();
			float getTime();

		private:
			DWORD startFrame;
		};

		Clock();
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