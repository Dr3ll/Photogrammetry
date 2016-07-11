#pragma once

#include <vector>;
#include <functional>;
#include "NotificationArgs.h";

namespace Protoone
{
	class Observer
	{
	private:
		std::function<void(const NotificationArgs* args)> _target;

	public:
		Observer(std::function<void(const NotificationArgs* args)> target);
		~Observer();

		void Update(const NotificationArgs* args);
	};
}
