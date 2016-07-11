#pragma once

#include <functional>

namespace Protoone
{
	class MouseSubscription
	{
	private:
		std::function<void(int button, int state, int x, int y)> _target;

	public:
		explicit MouseSubscription(std::function<void(int button, int state, int x, int y)> target)
		{
			_target = target;
		}

		~MouseSubscription(void) { }
	};
}
