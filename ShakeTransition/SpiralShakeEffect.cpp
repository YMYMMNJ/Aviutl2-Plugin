
#include "SpiralShakeEffect.h"
#include <cmath>

ShakeOffset SpiralShakeEffect::Calculate(
    double frame,
    const ShakeSettings& settings) const
{
    const double phase = frame * settings.Speed * 0.35;
    const double radius = settings.ShakeIntensity;

    ShakeOffset offset;

    offset.X = std::cos(phase) * radius;
    offset.Y = std::sin(phase) * radius;

    return offset;
}
