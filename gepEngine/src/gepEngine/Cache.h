#ifndef GEPENGINE_CACHE_H
#define GEPENGINE_CACHE_H

#include <memory>
#include <string>
#include <vector>

namespace gepEngine
{
	struct Resource;

	struct Cache
	{
		template <typename T>
		std::shared_ptr<T> load(const std::string& _path)
		{
			for (size_t i = 0; i < m_resources.size(); ++i)
			{
				if (m_resources.at(i)->GetPath() == _path)
				{
					std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(m_resources.at(i));
					return rtn;
				}
			}
			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->m_path = _path;
			rtn->Load();
			m_resources.push_back(rtn);
			return rtn;
		}

	private:
		std::vector<std::shared_ptr<Resource> > m_resources;
	};
}
#endif