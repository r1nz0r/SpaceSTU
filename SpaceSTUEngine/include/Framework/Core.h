#pragma once
#include <stdio.h>
#include <cassert>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>


namespace SSTU
{
	template<typename T>
	using List = std::vector<T>;

	template<typename Key, typename Value, typename Predicate = std::less<Key>>
	using SortedDictionary = std::map<Key, Value, Predicate>;

	template<typename Key, typename Value, typename Hash = std::hash<Key>>
	using Dictionary = std::unordered_map<Key, Value, Hash>;

	#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}