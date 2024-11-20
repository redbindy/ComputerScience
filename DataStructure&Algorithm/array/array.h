#pragma once

#include <cassert>
#include <cstdlib>

template<typename T>
struct array_t {
	T* p_data;
	size_t capacity;
};

template<typename T>
array_t<T> array_create(const size_t capacity)
{
	assert(capacity > 0);

	array_t<T> ret;
	ret.p_data = static_cast<T*>(malloc(sizeof(T) * capacity));
	ret.capacity = capacity;

	return ret;
}

template<typename T>
void array_delete(array_t<T>* p_this)
{
	free(p_this->p_data);
	p_this->p_data = nullptr;

	p_this->capacity = 0;
}

template<typename T>
T array_get(const array_t<T>* p_this, const size_t index)
{
	assert(p_this != nullptr);
	assert(p_this->p_data != nullptr);
	assert(index < p_this->capacity);

	return *(p_this->p_data + index);
}

template<typename T>
void array_set(array_t<T>* p_this, const size_t index, const T value)
{
	assert(p_this != nullptr);
	assert(p_this->p_data != nullptr);
	assert(index < p_this->capacity);

	*(p_this->p_data + index) = value;
}
