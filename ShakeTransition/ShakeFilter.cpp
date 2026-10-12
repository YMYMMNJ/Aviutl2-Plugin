
#include <windows.h>
#include <memory>
#include <cmath>
#include <algorithm>
#include "filter2.h"
#include "ShakeSettings.h"
#include "StandardShakeEffect.h"
#include "TrackItems.cpp"

namespace
{

    StandardShakeEffect standardShake;
    ShakeEffectBase* shakeEffect = &standardShake;

    // { get; set; } プロパティはない
    bool IsEnabled()
    {
        return enabledItem.value && intensityItem.value > 0.0;
    }

    bool func_proc_video(FILTER_PROC_VIDEO* video)
    {
        if (video == nullptr ||
            video->object == nullptr ||
            video->get_image_data == nullptr ||
            video->set_image_data == nullptr)
        {
            return false;
        }

        if (!IsEnabled())
            return true;

        const int width = video->object->width;
        const int height = video->object->height;

        if (width <= 0 || height <= 0)
            return false;

        const size_t pixelCount =
            static_cast<size_t>(width) * static_cast<size_t>(height);

        auto source = std::make_unique<PIXEL_RGBA[]>(pixelCount);
        auto output = std::make_unique<PIXEL_RGBA[]>(pixelCount);

        video->get_image_data(source.get());

        const ShakeSettings settings = GetSettings();
        const double frame = static_cast<double>(video->object->frame);

        const ShakeOffset offset = shakeEffect->Calculate(frame, settings);

        const double scale = settings.Zoom > 1.0 ? settings.Zoom : 1.0;

        const double pivotX = settings.CenterX * (width - 1);
        const double pivotY = settings.CenterY * (height - 1);

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                const double sourceX =
                    (x - pivotX - offset.X) / scale + pivotX;

                const double sourceY =
                    (y - pivotY - offset.Y) / scale + pivotY;

                const int sx = static_cast<int>(std::round(sourceX));
                const int sy = static_cast<int>(std::round(sourceY));

                const size_t index =
                    static_cast<size_t>(y) * width + x;

                if (sx >= 0 && sx < width &&
                    sy >= 0 && sy < height)
                {
                    const size_t sourceIndex =
                        static_cast<size_t>(sy) * width + sx;

                    output[index] = source[sourceIndex];
                }
                else
                {
                    output[index] = { 0, 0, 0, 0 };
                }
            }
        }

        video->set_image_data(output.get(), width, height);
        return true;
    }
}

FILTER_PLUGIN_TABLE filter_plugin_table = 
{
    FILTER_PLUGIN_TABLE::FLAG_VIDEO,
    L"Shake",
    L"Shake",
    L"Shake Filter",
    items,
    func_proc_video,
    nullptr
};

EXTERN_C __declspec(dllexport) bool InitializePlugin(DWORD version)
{
    return true;
}

EXTERN_C __declspec(dllexport) void UninitializePlugin()
{}

EXTERN_C __declspec(dllexport) FILTER_PLUGIN_TABLE* GetFilterPluginTable(void)
{
    return &filter_plugin_table;
}
