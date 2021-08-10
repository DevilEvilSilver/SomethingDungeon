#pragma once
#include <memory>

template <class T>
class Singleton
{
private:
	
	static std::shared_ptr<T> s_instance;
	
public:
	

	static std::shared_ptr<T> GetInstance()
	{
		if (s_instance == 0)
			s_instance = std::make_shared<T>();

			
		return s_instance;
	}

	void ResetInstance() {
		s_instance.reset();
	}

};

template <class T> std::shared_ptr<T> Singleton<T>::s_instance = nullptr;


