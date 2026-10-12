#include "StandardShakeEffect.h"
#include <cmath>

namespace
{
    // フレーム番号から位相を進める速度の倍率
    constexpr double PhaseSpeedMultiplier = 0.35;

    // 横揺れに使用する主波・副波の周波数
    constexpr double HorizontalFrequencyPrimary = 2.17;
    constexpr double HorizontalFrequencySecondary = 3.73;

    // 縦揺れに使用する主波・副波の周波数
    constexpr double VerticalFrequencyPrimary = 1.83;
    constexpr double VerticalFrequencySecondary = 4.13;

    // 主波と副波の合成時の重み付け（合計 1.0）
    constexpr double PrimaryWaveWeight = 0.65;
    constexpr double SecondaryWaveWeight = 0.35;

    // 縦揺れの各波に適用する位相のずれ
    constexpr double VerticalPrimaryPhaseOffset = 1.7;
    constexpr double VerticalSecondaryPhaseOffset = 0.4;
}

ShakeOffset StandardShakeEffect::Calculate(double frame, const ShakeSettings& settings) const
{
    const double phase = frame * settings.Speed * PhaseSpeedMultiplier;

    ShakeOffset offset;

    offset.X = settings.ShakeIntensity *
        (std::sin(phase * HorizontalFrequencyPrimary) * PrimaryWaveWeight +
            std::sin(phase * HorizontalFrequencySecondary) * SecondaryWaveWeight);

    offset.Y = settings.ShakeIntensity *
        (std::sin(phase * VerticalFrequencyPrimary + VerticalPrimaryPhaseOffset) * PrimaryWaveWeight +
            std::sin(phase * VerticalFrequencySecondary + VerticalSecondaryPhaseOffset) * SecondaryWaveWeight);

    return offset;
}