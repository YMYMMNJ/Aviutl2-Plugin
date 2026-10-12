
#pragma once

#include "ShakeSettings.h"

class SpiralShakeEffect
{
public:
    ShakeOffset Calculate(double frame, const ShakeSettings& settings) const;
};
