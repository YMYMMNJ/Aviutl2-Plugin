#pragma once

#include "ShakeSettings.h"

class ShakeEffectBase
{
public:
    virtual ~ShakeEffectBase() = default;

    virtual ShakeOffset Calculate(double frame, const ShakeSettings& settings) const = 0;
};