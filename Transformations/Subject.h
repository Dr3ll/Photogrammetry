#pragma once

#include "Observer.h";
#include "NotificationArgs.h";
#include <vector>;

namespace Protoone
{
	class Subject
	{
	private:
		std::vector<Observer*> _observer;

	public:
		Subject();

		void Subject::Attach(Observer* obs);
	
		void Subject::Detach(Observer* obs);

		void Subject::Notify(const NotificationArgs* args);

		~Subject();
	};
}