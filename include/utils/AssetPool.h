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

        std::shared_ptr<T> Get(const std::string& name) {
            if (items.find(name) != items.end())
                return items[name];
            return nullptr;
        }

        std::vector<std::shared_ptr<T>> GetAll() const {
            std::vector<std::shared_ptr<T>> result;

            for (auto& item : itemsList)
                result.push_back(item);

            return result;
        }

        bool Add(const std::string& name, std::shared_ptr<T> item) {
            if (items.find(name) != items.end()) {
                smartin::utils::log::E("AssetPool", "Asset already exists: " + name);
                return false;
            }

            items[name] = item;
            itemsList.push_back(item);
            return true;
        }

        void Remove(std::shared_ptr<T> item) {
            if (item != nullptr) {
                itemsList.remove(item);

                for (const auto& [name, _item] : items) {
                    if (item == _item) {
                        items[name] = nullptr;
                        break;
                    }
                }
            }
        }

        ~AssetPool() {
            itemsList.clear();
            items.clear();
        }

    private:
        std::map<std::string, std::shared_ptr<T>> items;
        std::list<std::shared_ptr<T>> itemsList;
    };
}

#endif //SMARTIN3D_ASSETPOOL_H
