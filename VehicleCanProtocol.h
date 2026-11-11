#pragma once

#include <cstdint>

namespace VehicleCanProtocol
{
inline constexpr std::uint32_t SpeedFrameId= 0x100;
inline constexpr int SpeedPayloadBytes = 2;

inline constexpr int SpeedCountsPerKph = 100;

constexpr double decodeSpeedKph(std::uint8_t lowByte, std::uint8_t highByte) noexcept
{
    const auto raw = static_cast<std::uint16_t>(std::uint16_t{lowByte} | (std::uint16_t{highByte} << 8));

    return static_cast<double>(raw) / SpeedCountsPerKph;
}

}
