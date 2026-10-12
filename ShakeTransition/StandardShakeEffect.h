#pragma once

#include "ShakeEffectBase.h"

class StandardShakeEffect : public ShakeEffectBase
{
public:
    ShakeOffset Calculate(double frame, const ShakeSettings& settings) const override;
};