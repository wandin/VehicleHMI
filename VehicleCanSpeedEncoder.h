#pragma once

#include "VehicleCanProtocol.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <limits>

namespace VehicleCanProtocol
{
// The simulator slider selects whole km/h. The wire format is in hundredths.
constexpr std::array<std::uint8_t, SpeedPayloadBytes> encodeWholeSpeedKph(int kph) noexcept
{
    static_assert(SpeedPayloadBytes == 2);
    constexpr int maxWholeKph = std::numeric_limits<std::uint16_t>::max() / SpeedCountsPerKph;
    const int boundedKph = std::clamp(kph, 0, maxWholeKph);
    const auto raw = static_cast<std::uint16_t>(boundedKph * SpeedCountsPerKph);
    return {static_cast<std::uint8_t>(raw & 0xffu), static_cast<std::uint8_t>(raw >> 8)};
}
}
