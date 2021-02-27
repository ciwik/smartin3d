#ifndef SMARTIN3D_ASSETPOOL_H
#define SMARTIN3D_ASSETPOOL_H

#include <map>
#include <string>
#include <list>

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

        std::vector<T*> GetAll() const {
            std::vector<T*> result;

            for (T* item : itemsList)
                result.push_back(item);

            return result;
        }

        bool Add(const std::string& name, T* item) {
            if (items.find(name) != items.end()) {
                smartin::utils::log::E("AssetPool", "Asset already exists: " + name);
                return false;
            }

            items[name] = item;
            itemsList.push_back(item);
            return true;
        }

        void Remove(T* item) {
            if (item != nullptr) {
                itemsList.remove(&(*item));

                for (const auto& [name, _item] : items) {
                    if (item == _item) {
                        items[name] = nullptr;
                        break;
                    }
                }

                delete item;
            }
        }

        ~AssetPool() {
            itemsList.clear();
            items.clear();
        }

    private:
        std::map<std::string, T*> items;
        std::list<T*> itemsList;
    };
}

#endif //SMARTIN3D_ASSETPOOL_H
