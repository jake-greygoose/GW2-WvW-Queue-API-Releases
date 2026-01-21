///----------------------------------------------------------------------------------------------------
/// Licensed under the MIT license.
///
/// Name         :  WQAPI.h
/// Description  :  WvW Queue API definitions.
///----------------------------------------------------------------------------------------------------

#ifndef WQAPI_H
#define WQAPI_H

#include <stdint.h>

#define WQAPI_SIG                0x57565751
#define DL_WVW_QUEUE_STATUS      "DL_WVW_QUEUE_STATUS"

#define EV_WVW_QUEUE_JOINED      "EV_WVW_QUEUE_JOINED"      // Payload: QueueEventData*
#define EV_WVW_QUEUE_UPDATED     "EV_WVW_QUEUE_UPDATED"     // Payload: QueueEventData*
#define EV_WVW_QUEUE_POPPED      "EV_WVW_QUEUE_POPPED"      // Payload: QueueEventData*
#define EV_WVW_QUEUE_LEFT        "EV_WVW_QUEUE_LEFT"        // Payload: QueueEventData*
#define EV_WVW_QUEUE_ENTERED     "EV_WVW_QUEUE_ENTERED"     // Payload: QueueEventData*
#define EV_WVW_TOTALS_UPDATED    "EV_WVW_TOTALS_UPDATED"    // Payload: GlobalTotals*

#define WQAPI_INITIALIZED        (1u << 0)
#define WQAPI_IN_QUEUE           (1u << 1)
#define WQAPI_POPPED             (1u << 2)

typedef enum WvwMapId {
    WvwMapId_None                 = 0,
    WvwMapId_EternalBattlegrounds = 38,
    WvwMapId_GreenBorderlands     = 95,
    WvwMapId_BlueBorderlands      = 96,
    WvwMapId_RedBorderlands       = 1099
} WvwMapId;

typedef struct QueueEntry {
    WvwMapId mapId;
    int32_t position;         // -1 = not in queue, 0 = popped, 1+ = waiting
    int32_t initialPosition;
    int64_t joinedAtMs;
} QueueEntry;

typedef struct QueueEventData {
    WvwMapId mapId;
    int32_t position;
    int32_t previousPosition;
} QueueEventData;

typedef struct GlobalTotals {
    int32_t eternalBattlegrounds;
    int32_t redBorderlands;
    int32_t blueBorderlands;
    int32_t greenBorderlands;
} GlobalTotals;

typedef struct WvwQueueDataLink {
    uint32_t signature;       // WQAPI_SIG when valid, 0 when unloaded
    uint32_t flags;

    QueueEntry queue;

    uint32_t popDurationMs;   // Total time to accept, 0 if not popped
    uint32_t popRemainingMs;  // Time left, 0 if not popped

    GlobalTotals totals;
} WvwQueueDataLink;

#endif
