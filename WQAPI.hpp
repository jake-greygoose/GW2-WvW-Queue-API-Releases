///----------------------------------------------------------------------------------------------------
/// Licensed under the MIT license.
///
/// Name         :  WQAPI.hpp
/// Description  :  WvW Queue API definitions.
///----------------------------------------------------------------------------------------------------

#ifndef WQAPI_HPP
#define WQAPI_HPP

#include <cstdint>

#define WQAPI_SIG                0x57565751
#define DL_WVW_QUEUE_STATUS      "DL_WVW_QUEUE_STATUS"

#define EV_WVW_QUEUE_JOINED      "EV_WVW_QUEUE_JOINED"      // Payload: WvwQueue::QueueEventData*
#define EV_WVW_QUEUE_UPDATED     "EV_WVW_QUEUE_UPDATED"     // Payload: WvwQueue::QueueEventData*
#define EV_WVW_QUEUE_POPPED      "EV_WVW_QUEUE_POPPED"      // Payload: WvwQueue::QueueEventData*
#define EV_WVW_QUEUE_LEFT        "EV_WVW_QUEUE_LEFT"        // Payload: WvwQueue::QueueEventData*
#define EV_WVW_QUEUE_ENTERED     "EV_WVW_QUEUE_ENTERED"     // Payload: WvwQueue::QueueEventData*
#define EV_WVW_TOTALS_UPDATED    "EV_WVW_TOTALS_UPDATED"    // Payload: WvwQueue::GlobalTotals*

#define WQAPI_INITIALIZED        (1u << 0)
#define WQAPI_IN_QUEUE           (1u << 1)
#define WQAPI_POPPED             (1u << 2)

namespace WvwQueue {

    enum class MapId : int32_t {
        None                 = 0,
        EternalBattlegrounds = 38,
        GreenBorderlands     = 95,
        BlueBorderlands      = 96,
        RedBorderlands       = 1099
    };

    struct QueueEntry {
        MapId mapId = MapId::None;
        int32_t position = -1;          // -1 = not in queue, 0 = popped, 1+ = waiting
        int32_t initialPosition = -1;
        int64_t joinedAtMs = 0;
    };

    struct QueueEventData {
        MapId mapId = MapId::None;
        int32_t position = -1;
        int32_t previousPosition = -1;
    };

    struct GlobalTotals {
        int32_t eternalBattlegrounds = 0;
        int32_t redBorderlands = 0;
        int32_t blueBorderlands = 0;
        int32_t greenBorderlands = 0;
    };

    struct WvwQueueDataLink {
        uint32_t signature = WQAPI_SIG;  // 0 when unloaded
        uint32_t flags = 0;

        QueueEntry queue = {};

        uint32_t popDurationMs = 0;   // Total time to accept, 0 if not popped
        uint32_t popRemainingMs = 0;  // Time left, 0 if not popped

        GlobalTotals totals = {};
    };

}

#endif
