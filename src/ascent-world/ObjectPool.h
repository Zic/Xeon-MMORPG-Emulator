// Original implementation:
// Object Pooling for Generic C++ classes
// By Thomas George

#ifndef __OBJPOOL_H
#define __OBJPOOL_H

class Mutex;

template <class T > class ObjectPool
{
public:

	ObjectPool() {}
	virtual ~ObjectPool() {}

	static Mutex& get_lock()
	{
		static Mutex m_lock;
		return m_lock;
	}

	static std::vector<T* >& get_list()
	{
		static std::vector<T* > m_free;
		return m_free;
	}
	
	static void init()
	{
		for (int i = 0; i < 1; ++i)
		{
			T* p = ::new T;
			T::get_list().push_back(p);
		}
	}

	inline void *operator new( size_t stAllocateBlock)
	{
		get_lock().Acquire();
		if (T::get_list().size() <= 0)
		{
			T::init();
		}
		T* p = T::get_list().back();
		T::get_list().pop_back();
		get_lock().Release();
		return p;
	}

	inline void operator delete( void *p )
	{
		get_lock().Acquire();
		T::get_list().push_back((T*)p);
		get_lock().Release();
	}

	static void destroy()
	{
		typename vector<T* >::iterator first = T::get_list().begin();
		typename vector<T* >::iterator last = T::get_list().end();
		while (first != last)
		{
			T* p = *first; ++first;
			::delete p;
		}
		T::get_list().erase(T::get_list().begin(), T::get_list().end());
	}
};

#endif
