#pragma once

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "../list/singly_linked_list.h"

#define LINEAR_PROBING (false)
#define QUADRATIC_PROBING (false)
#define DOUBLE_HASHING (true)

namespace hash_table
{
	using namespace singly_linked_list;

	template<typename K, typename V>
	struct linear_hash_table_t {
		K* p_keys;
		V* p_values;

		bool* p_has_values;

		int capacity;

#if DOUBLE_HASHING
		int double_hashing_prime;
#endif /* DOUBLE_HASHING */
	};

	bool is_prime(const int num)
	{
		if (num <= 1) {
			return false;
		}

		if (num == 2 || num == 3) {
			return true;
		}

		for (int i = 2; i * i <= num; ++i) {

			if (num % i == 0) {
				return false;
			}
		}

		return true;
	}

	int get_table_capacity(const int size)
	{
		assert(size > 0);

		int capacity = size * 2;
		while (!is_prime(capacity)) {
			++capacity;
		}

		return capacity;
	}

	template<typename K, typename V>
	linear_hash_table_t<K, V> create_linear_table(const int size)
	{
		assert(size > 0);

		linear_hash_table_t<K, V> ret;

		int capacity = get_table_capacity(size);
		ret.capacity = capacity;

#if DOUBLE_HASHING
		int double_hashing_prime = capacity - 1;
		while (!is_prime(double_hashing_prime)) {
			--double_hashing_prime;
		}
		ret.double_hashing_prime = double_hashing_prime;
#endif /* DOUBLE_HASHING */

		ret.p_keys = static_cast<K*>(malloc(sizeof(K) * capacity));
		ret.p_values = static_cast<V*>(malloc(sizeof(V) * capacity));
		ret.p_has_values = static_cast<bool*>(malloc(sizeof(bool) * capacity));
		assert(ret.p_has_values != nullptr);

		memset(ret.p_has_values, false, sizeof(bool) * capacity);

		return ret;
	}

	template<typename K, typename V>
	void destroy(linear_hash_table_t<K, V>* const p_this)
	{
		assert(p_this != nullptr);

		free(p_this->p_keys);
		p_this->p_keys = nullptr;

		free(p_this->p_values);
		p_this->p_values = nullptr;

		free(p_this->p_has_values);
		p_this->p_has_values = nullptr;

		p_this->capacity = -1;
	}

	constexpr uint32_t get_hash(const void* const p_key, const int byte_size)
	{
		assert(p_key != nullptr);
		assert(byte_size > 0);

		/*constexpr uint32_t FNV_PRIME_32 = 1677619;
		constexpr uint32_t FNV_OFFSET_32 = 216613261u;

		const int8_t* const p_stream = static_cast<const int8_t*>(p_key);

		uint32_t hash = FNV_OFFSET_32;
		for (const int8_t* p = p_stream; p < p_stream + byte_size; ++p) {

			hash *= FNV_PRIME_32;
			hash ^= *p;
		}*/

		const int8_t* const p_stream = static_cast<const int8_t*>(p_key);

		uint32_t hash = 0;
		for (const int8_t* p = p_stream; p < p_stream + byte_size; ++p) {

			hash += *p;
		}

		return hash;
	}

#if DOUBLE_HASHING
	// 대충 다른 해시 함수
	constexpr uint32_t get_hash_secondary(const void* const p_key, const int byte_size)
	{
		assert(p_key != nullptr);
		assert(byte_size > 0);

		const int8_t* const p_stream = static_cast<const int8_t*>(p_key);

		uint32_t hash = 0;
		for (const int8_t* p = p_stream; p < p_stream + byte_size; ++p) {

			hash += *p << 1;
		}

		return hash;
	}

	template<typename K, typename V>
	constexpr uint32_t get_step(const linear_hash_table_t<K, V>* const p_this, const K key)
	{
		assert(p_this != nullptr);

		const uint32_t hash = get_hash_secondary(&key, sizeof(K));
		uint32_t step = p_this->double_hashing_prime - (hash % p_this->double_hashing_prime);

		return step;
	}

	template<typename V>
	constexpr uint32_t get_step(const linear_hash_table_t<const char*, V>* const p_this, const char* const p_key)
	{
		assert(p_this != nullptr);

		const int key_byte_size = static_cast<int>(strlen(p_key));
		const uint32_t hash = get_hash_secondary(p_key, key_byte_size);
		uint32_t step = p_this->double_hashing_prime - (hash % p_this->double_hashing_prime);

		return step;
	}
#endif /* DOUBLE_HASHING */

	template<typename K>
	uint32_t get_index(const int capacity, const K key)
	{
		assert(capacity > 0);

		const uint32_t hash = get_hash(&key, sizeof(key));

		return hash % capacity;
	}

	template<>
	uint32_t get_index(const int capacity, const char* const p_key)
	{
		assert(capacity > 0);
		assert(p_key != nullptr);

		const int key_byte_size = static_cast<int>(strlen(p_key));
		const uint32_t hash = get_hash(p_key, key_byte_size);

		return hash % capacity;
	}

	template<typename K, typename V>
	bool try_add(linear_hash_table_t<K, V>* const p_this, const K key, const V value)
	{
		assert(p_this != nullptr);

		const int start = get_index(p_this->capacity, key);

		int i = start;

		int increment = 1;
#if DOUBLE_HASHING
		increment = get_step(p_this, key);
#endif /* DOUBLE_HAHSING */

		while (p_this->p_has_values[i]) {

			if (p_this->p_keys[i] == key) {
				break;
			}

#if LINEAR_PROBING || DOUBLE_HASHING
			i = (i + increment) % p_this->capacity;
#endif /* LINEAR_PROBING */

#if QUADRATIC_PROBING
			// (start + inc * inc) % TABLE_SIZE
			i = (i + increment) % p_this->capacity;
			increment += 2;
#endif /* QUADRATIC_PROBING*/

			if (i == start) {
				return false;
			}
		}

		p_this->p_keys[i] = key;
		p_this->p_values[i] = value;
		p_this->p_has_values[i] = true;

		return true;
	}

	template<typename V>
	bool try_add(linear_hash_table_t<const char*, V>* const p_this, const char* const p_key, const V value)
	{
		assert(p_this != nullptr);
		assert(p_key != nullptr);

		const int start = get_index(p_this->capacity, p_key);

		int i = start;

		int increment = 1;
#if DOUBLE_HASHING
		increment = get_step(p_this, p_key);
#endif /* DOUBLE_HAHSING */

		while (p_this->p_has_values[i]) {

			if (strcmp(p_this->p_keys[i], p_key) == 0) {
				break;
			}

#if LINEAR_PROBING || DOUBLE_HASHING
			i = (i + increment) % p_this->capacity;
#endif /* LINEAR_PROBING */

#if QUADRATIC_PROBING
			// (start + inc * inc) % TABLE_SIZE
			i = (i + increment) % p_this->capacity;
			increment += 2;
#endif /* QUADRATIC_PROBING*/

			if (i == start) {
				return false;
			}
		}

		p_this->p_keys[i] = p_key;
		p_this->p_values[i] = value;
		p_this->p_has_values[i] = true;

		return true;
	}

	template<typename K, typename V>
	int find_key_index(const linear_hash_table_t<K, V>* const p_this, const K key)
	{
		assert(p_this != nullptr);

		const int start = get_index(p_this->capacity, key);

		int i = start;

		int increment = 1;
#if DOUBLE_HASHING
		increment = get_step(p_this, key);
#endif /* DOUBLE_HAHSING */

		while (!p_this->p_has_values[i] || p_this->p_keys[i] != key) {
#if LINEAR_PROBING || DOUBLE_HASHING
			i = (i + increment) % p_this->capacity;
#endif /* LINEAR_PROBING */

#if QUADRATIC_PROBING
			i = (i + increment) % p_this->capacity;
			increment += 2;
#endif /* QUADRATIC_PROBING*/

			if (i == start) {
				return -1;
			}
		}

		return i;
	}

	template<typename V>
	int find_key_index(const linear_hash_table_t<const char*, V>* const p_this, const char* const p_key)
	{
		assert(p_this != nullptr);
		assert(p_key != nullptr);

		const int start = get_index(p_this->capacity, p_key);

		int i = start;

		int increment = 1;
#if DOUBLE_HASHING
		increment = get_step(p_this, p_key);
#endif /* DOUBLE_HAHSING */

		while (!p_this->p_has_values[i] || strcmp(p_this->p_keys[i], p_key) != 0) {

#if LINEAR_PROBING || DOUBLE_HASHING
			i = (i + increment) % p_this->capacity;
#endif /* LINEAR_PROBING */

#if QUADRATIC_PROBING
			// (start + inc * inc) % TABLE_SIZE
			i = (i + increment) % p_this->capacity;
			increment += 2;
#endif /* QUADRATIC_PROBING*/

			if (i == start) {
				return -1;
			}
		}

		return i;
	}

	template<typename K, typename V>
	bool try_get_value(const linear_hash_table_t<K, V>* const p_this, const K key, V* const p_out_value)
	{
		assert(p_this != nullptr);
		assert(p_out_value != nullptr);

		const int index = find_key_index(p_this, key);

		if (index == -1) {
			return false;
		}

		*p_out_value = p_this->p_values[index];

		return true;
	}

	template<typename K, typename V>
	void remove_key(linear_hash_table_t<K, V>* const p_this, const K key)
	{
		assert(p_this != nullptr);

		const int index = find_key_index(p_this, key);

		if (index == -1) {
			return;
		}

		p_this->p_has_values[index] = false;
	}

	template<typename K, typename V>
	struct element_t {
		K key;
		V value;
	};

	template<typename K, typename V>
	struct chained_hash_table_t {
		node_t<element_t<K, V>>** pp_pairs;

		int capacity;
	};

	template<typename K, typename V>
	chained_hash_table_t<K, V> create_chained_table(const int size)
	{
		assert(size > 0);

		chained_hash_table_t<K, V> ret;

		int capacity = get_table_capacity(size);
		ret.capacity = capacity;

		ret.pp_pairs = static_cast<node_t<element_t<K, V>>**>(malloc(sizeof(node_t<element_t<K, V>>*) * capacity));

		for (node_t<element_t<K, V>>** pp = ret.pp_pairs; pp < ret.pp_pairs + capacity; ++pp) {
			*pp = nullptr;
		}

		return ret;
	}

	template<typename K, typename V>
	void destroy(chained_hash_table_t<K, V>* const p_this)
	{
		assert(p_this != nullptr);

		const node_t<element_t<K, V>>* const* const pp_end = p_this->pp_pairs + p_this->capacity;
		for (node_t<element_t<K, V>>** pp = p_this->pp_pairs; pp < pp_end; ++pp) {
			singly_linked_list::destroy(pp);
		}

		free(p_this->pp_pairs);
		p_this->pp_pairs = nullptr;

		p_this->capacity = -1;
	}

	template<typename K, typename V>
	void add(chained_hash_table_t<K, V>* const p_this, const K key, const V value)
	{
		assert(p_this != nullptr);

		const int index = get_index(p_this->capacity, key);

		node_t<element_t<K, V>>* p_node = p_this->pp_pairs[index];
		if (p_node == nullptr) {
			p_this->pp_pairs[index] = create_singly_node_malloc<element_t<K, V>>({ key, value });

			return;
		}

		while (p_node->p_next != nullptr) {

			element_t<K, V> e = p_node->data;

			if (e.key == key) {
				p_node->data.value = value;

				return;
			}
		}

		p_node->p_next = create_singly_node_malloc<element_t<K, V>>({ key, value });
	}

	template<typename V>
	void add(chained_hash_table_t<const char*, V>* const p_this, const char* const p_key, const V value)
	{
		assert(p_this != nullptr);
		assert(p_key != nullptr);

		const int index = get_index(p_this->capacity, p_key);

		node_t<element_t<const char*, V>>* p_node = p_this->pp_pairs[index];
		if (p_node == nullptr) {
			p_this->pp_pairs[index] = create_singly_node_malloc<element_t<const char*, V>>({ p_key, value });

			return;
		}

		while (p_node->p_next != nullptr) {

			element_t<const char*, V> e = p_node->data;

			if (strcmp(e.key, p_key) == 0) {
				p_node->data.value = value;

				return;
			}

			p_node = p_node->p_next;
		}

		p_node->p_next = create_singly_node_malloc<element_t<const char*, V>>({ p_key, value });
	}

	template<typename K, typename V>
	bool try_get_value(const chained_hash_table_t<K, V>* const p_this, const K key, V* const p_out_value)
	{
		assert(p_this != nullptr);
		assert(p_out_value != nullptr);

		const int index = get_index(p_this->capacity, key);

		node_t<element_t<K, V>>* p_node = p_this->pp_pairs[index];

		while (p_node != nullptr) {

			element_t<K, V> e = p_node->data;

			if (e.key == key) {
				*p_out_value = e.value;

				return true;
			}

			p_node = p_node->p_next;
		}

		return false;
	}

	template<typename V>
	bool try_get_value(const chained_hash_table_t<const char*, V>* const p_this, const char* const p_key, V* const p_out_value)
	{
		assert(p_this != nullptr);
		assert(p_out_value != nullptr);

		const int index = get_index(p_this->capacity, p_key);

		const node_t<element_t<const char*, V>>* p_node = p_this->pp_pairs[index];
		while (p_node != nullptr) {

			const element_t<const char*, V> e = p_node->data;

			if (strcmp(e.key, p_key) == 0) {
				*p_out_value = e.value;

				return true;
			}

			p_node = p_node->p_next;
		}

		return false;
	}

	template<typename K, typename V>
	void remove_key(const chained_hash_table_t<K, V>* const p_this, const K key)
	{
		assert(p_this != nullptr);

		const int index = get_index(p_this->capacity, key);

		node_t<element_t<K, V>>** pp_node = p_this->pp_pairs + index;

		while (*pp_node != nullptr) {

			element_t<K, V> e = (*pp_node)->data;

			if (e.key == key) {

				node_t<element_t<K, V>>* p_next = (*pp_node)->p_next;

				free(*pp_node);

				*pp_node = p_next;

				break;
			}

			pp_node = &((*pp_node)->p_next);
		}
	}

	template<typename V>
	void remove_key(const chained_hash_table_t<const char*, V>* const p_this, const char* const p_key)
	{
		assert(p_this != nullptr);
		assert(p_key != nullptr);

		const int index = get_index(p_this->capacity, p_key);

		node_t<element_t<const char*, V>>** pp_node = p_this->pp_pairs + index;

		while (*pp_node != nullptr) {

			element_t<const char*, V> e = (*pp_node)->data;

			if (strcmp(e.key, p_key) == 0) {

				node_t<element_t<const char*, V>>* p_next = (*pp_node)->p_next;

				free(*pp_node);

				*pp_node = p_next;

				break;
			}

			pp_node = &((*pp_node)->p_next);
		}
	}
}