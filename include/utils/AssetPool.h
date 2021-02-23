#ifndef SMARTIN3D_ASSETPOOL_H
#define SMARTIN3D_ASSETPOOL_H

#include <map>
#include <string>
#include <vector>

#include "utils/Log.h"

namespace smartin::utils {
    template<class T>
    class AssetPool {
    public:
        AssetPool() {}

        T* Get(const std::string& name) {
            if (items.find(name) != items.end())
                return items[name];
            return nullptr;
        }

        std::vector<T*> GetAll() const { return itemsArray; }

        bool Add(const std::string& name, T* item) {
            if (items.find(name) != items.end()) {
                smartin::utils::log::E("AssetPool", "Asset already exists: " + name);
                return false;
            }

            items[name] = item;
            itemsArray.push_back(item);
            return true;
        }

        void Remove(const std::string& name) {
            T* item = items[name];
            if (item != nullptr) {
                for (int i = 0; i < itemsArray.size(); i++) {
                    if (itemsArray[i] == item)
                        itemsArray[i] = nullptr;
                }

                items[name] = nullptr;

                delete item;
            }
        }

        ~AssetPool() {
            for (T* item : itemsArray)
                delete item;

            itemsArray.clear();
            items.clear();
        }

    private:
        std::map<std::string, T*> items;
        std::vector<T*> itemsArray;
    };
}

#endif //SMARTIN3D_ASSETPOOL_H
