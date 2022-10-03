#include <memory>

#define Shared std::shared_ptr

namespace gepEngine
{
	struct Core
	{
		static Shared<Core> initialize();

	private:
		int m_dummy;
	};
}