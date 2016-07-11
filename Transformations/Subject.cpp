#include "Subject.h"

namespace Protoone
{
	Subject::Subject()
	{
	}

	void Subject::Attach(Observer* obs)
	{
		_observer.push_back(obs);
	}

	Subject::~Subject()
	{
	}
	
	void Subject::Detach(Observer* obs)
	{
		for(int i=0; i<_observer.size(); ++i)
		{
			if(_observer[i] != obs)
				continue;
			_observer.erase(_observer.begin()+i);
		}
	}

	void Subject::Notify(const NotificationArgs* args)
	{
		for(int i=0; i<_observer.size(); ++i)
		{
			_observer[i]->Update(args);
		}
	}

}