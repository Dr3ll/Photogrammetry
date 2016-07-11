#pragma once

#include <functional>

namespace Protoone
{
	class MouseMotionSubscription
	{
	private:
		std::function<void(int x, int y)> _target;

	public:
		explicit MouseMotionSubscription(std::function<void(int x, int y)> target)
		{
			_target = target;
		}

		~MouseMotionSubscription(void) { }
	};
}
