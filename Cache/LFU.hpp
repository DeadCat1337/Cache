#ifndef CACHE_LFU_HPP
#define CACHE_LFU_HPP

#include <list>
#include <unordered_map>
#include <iostream>

namespace cache {

	template<typename T, typename KeyT>
	class LFU {
	public:
		LFU(size_t size) : size_(size) {}

		bool full() const {
			return size_ <= cache_.size();
		}

		bool lookup(KeyT key) {
			auto hit = hash_.find(key);

			if (hit == hash_.end()) {
				//not in cache
				if (full()) {
					cache_.sort([](const fpage_t& first, const fpage_t& second) {
						return first.freq > second.freq;
					});
					auto iter = hash_.find(cache_.back().key);
					hash_.erase(iter);
					cache_.pop_back();
					std::cout << "deleted least feaquent" << std::endl;
				}

				struct fpage_t fpg;
				fpg.key = key;
				fpg.data = long_get_elem(key);
				fpg.freq = 1;
				cache_.push_back(fpg);
				hash_.insert(std::make_pair(key, --cache_.end()));
				std::cout << "added new" << std::endl;
				std::cout << *(fpg.data) << std::endl;
				//return fpg.data;
				return false;
			}
			else {
				//already in cache
				hit->second->freq++;
				std::cout << "freq increased" << std::endl;
				std::cout << *(hit->second->data) << std::endl;
				//return hit->second->data;
				return true;
			}

		}

	private:
		struct fpage_t {
			KeyT key;
			T* data;
			int freq = 0;
		};

		T* long_get_elem(KeyT key) {
			return new T(key*key);
		}

		size_t size_;
		std::list<fpage_t> cache_;
		std::unordered_map<KeyT, typename std::list<fpage_t>::iterator> hash_;
	};

}

#endif // !CACHE_LFU_HPP

