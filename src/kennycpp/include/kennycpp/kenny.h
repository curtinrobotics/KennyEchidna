#ifndef KENNYCPP__KENNY_H
#define KENNYCPP__KENNY_H

#include <sstream>
#include <kennycpp/segment.h>

namespace kennycpp
{
	class Kenny
	{
		private:
		public:
			Kenny();
			~Kenny();

			Segment<2> base;
			Segment<3> arm;
			Segment<2> camera;

			Joint getJoint(std::string jointName);
			void setJoint(tr1cpp::Joint joint);
	};
}

#endif