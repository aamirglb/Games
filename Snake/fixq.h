#pragma once

#include <iostream>
#include <cstdint>
#include <array>

template<typename T, int32_t N>
class FixQ
{
public:
	FixQ() = default;

	void Push( T value )
	{
		if ( m_Size < m_Array.size() )
		{
			// Push the elements from the end of the array
			auto idx = ( m_Array.size() - 1 ) - m_Size;
			m_Array[idx] = value;
			m_Size += 1;
		}
		else
		{
			// array is full, pop the last element and insert the new element at the begining
			for ( size_t i = m_Array.size() - 1; i > 0; --i )
			{
				m_Array[i] = m_Array[i - 1];
			}
			m_Array[0] = value;
		}
	}

	size_t size() const
	{
		return m_Size;
	}

	auto begin()
	{
		return m_Array.begin();
	}

	auto end()
	{
		return m_Array.end();
	}

private:
	std::array<T, N> m_Array{};
	size_t m_Size{};
};