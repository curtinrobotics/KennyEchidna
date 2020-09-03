#ifndef KENNYCPP__SEGMENT_H
#define KENNYCPP__SEGMENT_H

#include <kennycpp/joint.h>

namespace kennycpp
{
	template <int T> class Segment
	{
		private:

		public:
			Segment() { };
			~Segment() { };
			int size() const { return T; }
			Joint joints[T];
	};
}

#endif