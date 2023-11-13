#pragma once

#include <vector>
#include <mutex>
#include <functional>

/*
	Thread-safe generic wrapper for a std::vector
*/

template <typename T>
class ConcurrentVector
{
public:
	// TODO:
	std::vector<T>& Read()
	{
		std::lock_guard<std::mutex> lock { mutex };

		return vector;
	}

	template <typename Func>
	void Modify(Func f)
	{
		std::lock_guard<std::mutex> lock { mutex };
		f(vector);
	}

private:
	std::vector<T> vector;
	mutable std::mutex mutex;
};
