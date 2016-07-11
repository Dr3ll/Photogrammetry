#include "Observer.h"

namespace Protoone
{

	Observer::Observer(std::function<void(const NotificationArgs* args)> target)
	{
		_target = target;
	}

	Observer::~Observer()
	{
		_target.~function();
	}

	void Observer::Update(const NotificationArgs* args)
	{
		_target(args);
	}

}