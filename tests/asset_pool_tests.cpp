#ifndef SMARTIN3D_ASSETPOOL_TESTS_H
#define SMARTIN3D_ASSETPOOL_TESTS_H

#include "test_hints.h"

#include "base/Actor.h"
#include "utils/AssetPool.h"

TEST_CASE("Garbage collection in asset pool", "[require]") {
    smartin::utils::AssetPool<smartin::base::Actor> pool;
    std::string actorName = "actor1";

    {
        auto actor = std::make_shared<smartin::base::Actor>();
        REQUIRE_EQ(actor.use_count(), 1);

        pool.Add(actorName, actor);
        REQUIRE_EQ(actor.use_count(), 3);

        pool.CollectGarbage();
        REQUIRE_EQ(actor.use_count(), 3);
    }

    pool.Remove(pool.Get(actorName));
    pool.CollectGarbage();
    REQUIRE_EQ(pool.Get(actorName), nullptr);
}

#endif // SMARTIN3D_ASSETPOOL_TESTS_H