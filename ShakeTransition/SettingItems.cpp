
#include <windows.h>
#include <memory>
#include <cmath>
#include <algorithm>
#include "filter2.h"
#include "ShakeSettings.h"
#include "StandardShakeEffect.h"

//auto は C#で言う var と同じ
auto intensityItem = FILTER_ITEM_TRACK(L"揺れの強さ", 25.0, 0.0, 500.0, 1.0);
auto speedItem = FILTER_ITEM_TRACK(L"速度", 1.0, 0.1, 5.0, 0.1);
auto zoomItem = FILTER_ITEM_TRACK(L"ズーム", 1.0, 1.0, 5.0, 0.01);
auto enabledItem = FILTER_ITEM_CHECK(L"IsEnabled", true);

void* items[] =
{
    &intensityItem,
    &speedItem,
    &zoomItem,
    &enabledItem,
    nullptr
};

ShakeSettings GetSettings()
{
    ShakeSettings settings;

    settings.ShakeIntensity = intensityItem.value;
    settings.Speed = speedItem.value;
    settings.Zoom = zoomItem.value;

    return settings;
}