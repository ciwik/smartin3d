#ifndef SMARTIN3D_ASSETPOOL_H
#define SMARTIN3D_ASSETPOOL_H

#include "precompiled.h"

#include "utils/Log.h"

namespace smartin::utils {
    template<class T>
    class AssetPool final {
    public:
        AssetPool(bool _autoCollect = false) : autoCollect(_autoCollect) { }

        std::shared_ptr<T> Get(const std::string& name) const {
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
            if (item != nullptr)
                toCollect.push_back(item);
        }

        void CollectGarbage() {
            if (autoCollect) {
                for (auto const &item : itemsList) {
                    if (item.use_count() == 2)  // if object is referenced only in pool
                        toCollect.push_back(item);
                }
            }

            for (auto const& item : toCollect) {
                itemsList.remove(item);

                std::string name= "";
                for (const auto& [_name, _item] : items) {
                    if (item == _item) {
                        name = _name;
                        break;
                    }
                }

                if (!name.empty())
                    items.erase(name);
            }

            toCollect.clear();
        }

        void DebugPrintContent(std::string tag) const {
            std::stringstream stream;

            stream << "\n";
            for (const auto& [name, item] : items)
                stream << std::setw(24) << name << std::setw(12) << &item << "\n";

            utils::log::I(tag, stream.str());
        }

        ~AssetPool() {
            itemsList.clear();
            items.clear();
        }

    private:
        mutable std::map<std::string, std::shared_ptr<T>> items;
        std::list<std::shared_ptr<T>> itemsList;
        std::vector<std::shared_ptr<T>> toCollect;

        bool autoCollect;
    };
}

#endif //SMARTIN3D_ASSETPOOL_H
