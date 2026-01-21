# GW2-WvW-Queue-API-Releases

WQAPI provides real-time WvW queue position data.

If this information gets added to RTAPI then I will likely archive / not maintain this project. 

If you are building something cool or find a bug, let me know on discord @__unreal

## Using WQAPI
The primary object `WvwQueueDataLink` can be obtained using Nexus' DataLink API. The name of the data link is defined in the header `DL_WVW_QUEUE_STATUS`.

As Nexus allows for hot-loading and as such this addon can be unloaded at runtime, you must check that the data has not gone stale. If `WvwQueueDataLink->signature == 0`, the provider was unloaded.

It is recommended to also listen to `EV_ADDON_LOADED` and `EV_ADDON_UNLOADED`, and check against `WQAPI_SIG` to refresh your pointer.

### Example (addon load events)
```cpp
void OnAddonLoaded(int* aSignature)
{
  if (!aSignature) { return; }
  if (*aSignature == WQAPI_SIG)
  {
    G::WvwQueue = (WvwQueueDataLink*)G::APIDefs->DataLink_Get(DL_WVW_QUEUE_STATUS);
  }
}
void OnAddonUnloaded(int* aSignature)
{
  if (!aSignature) { return; }
  if (*aSignature == WQAPI_SIG)
  {
    G::WvwQueue = nullptr;
  }
}
```

## Queue Events
The following events are provided. The payload is `QueueEventData*`.

```cpp
#define EV_WVW_QUEUE_JOINED    "EV_WVW_QUEUE_JOINED"
#define EV_WVW_QUEUE_UPDATED   "EV_WVW_QUEUE_UPDATED"
#define EV_WVW_QUEUE_POPPED    "EV_WVW_QUEUE_POPPED"
#define EV_WVW_QUEUE_LEFT      "EV_WVW_QUEUE_LEFT"
#define EV_WVW_QUEUE_ENTERED   "EV_WVW_QUEUE_ENTERED"
#define EV_WVW_TOTALS_UPDATED  "EV_WVW_TOTALS_UPDATED" // Payload is GlobalTotals*
```

## Notes
- During loading screens, the addon will keep the last non-zero DataLink values for up to ~2s to avoid flicker.
- Queue's are abandoned when entering character select / DC'ing, the addon uses a 15 second timeout to detect this state.
