#pragma once

namespace Protoone
{
	class NotificationArgs
	{
	private:
		bool _dead;		

	public:
		static NotificationArgs* Empty() 
		{
			return new NotificationArgs(true);
		}

		NotificationArgs(bool dead) { _dead = true; }

		NotificationArgs() { _dead = false; }
		~NotificationArgs() { }

		bool Dead()
		{
			return _dead;
		}
	};
}
