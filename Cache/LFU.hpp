#ifndef CACHE_LFU_HPP
#define CACHE_LFU_HPP

#include <list>
#include <unordered_map>
#include <iostream>

struct page_t {
	int id;
	//double data; 
};

namespace cache {

	template<typename T, typename KeyT>
	class LFU{
	public:
		LFU(size_t size) : size_(size) {}

		~LFU() {
			for (auto elem : cache_) {
				if(elem.data) delete elem.data; //free used data
			}
		}

		bool full() const {
			return size_ <= cache_.size();
		}

		bool lookup(KeyT key) {
			if (size_ == 0) return false;

			auto hit = hash_.find(key);

			if (hit == hash_.end()) {
				//not in cache
				if (full()) {
					//cache full
					delete_less_frequent();
				}

				//there is free space
				struct fpage_t fpg;
				fpg.key = key;
				fpg.data = long_get_elem(key);
				fpg.freq = 1;
				cache_.push_back(fpg);
				hash_.insert(std::make_pair(key, --cache_.end()));
				return false;
			}
			else 
			{
				//already in cache
				hit->second->freq++;
				if (hit->second != cache_.begin()) {
					// move element up, if needed
					typename std::list<fpage_t>::iterator it = hit->second;
					it--;
					for (; it != cache_.begin(); --it) {
						if (it->freq > hit->second->freq) break;
					}
					it++;
					auto temp = *it;
					*it = *(hit->second);
					*(hit->second) = temp;
				}
				return true;
			}
		}

	private:
		struct fpage_t {
			KeyT key;
			T* data;
			int freq = 0;
		};

		//some function to get data by key
		//for example lets return squared key 
		//(we use only int as keys and doubles as data)
		T* long_get_elem(KeyT key) {
			return new T(key*key);
		}

		//special function to free used memory
		void release_last_elem() {
			if (cache_.back().data) delete cache_.back().data;
		}

		void delete_less_frequent() {
			release_last_elem();
			auto iter = hash_.find(cache_.back().key);
			hash_.erase(iter);
			cache_.pop_back();
		}

		size_t size_;
		std::list<fpage_t> cache_;
		std::unordered_map<KeyT, typename std::list<fpage_t>::iterator> hash_;
	};

}

#endif // !CACHE_LFU_HPP

