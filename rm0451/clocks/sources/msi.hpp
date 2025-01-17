#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// externals
#include <stm32l0xx.h>

// xmcu
#include <xmcu/Duration.hpp>
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>

namespace xmcu::soc::st::arm::m0::l0::rm0451::clocks::sources {
class msi : private non_constructible
{
public:
    enum class Frequency : std::uint32_t
    {
        _65_kHz = RCC_ICSCR_MSIRANGE_0,  // ~65.536 kHz
        _131_kHz = RCC_ICSCR_MSIRANGE_1, // ~131.072 kHz
        _262_kHz = RCC_ICSCR_MSIRANGE_2, // ~262.144 kHz
        _524_kHz = RCC_ICSCR_MSIRANGE_3, // ~524.288 kHz
        _1_MHz = RCC_ICSCR_MSIRANGE_4,   // ~1.048 MHz
        _2_MHz = RCC_ICSCR_MSIRANGE_5,   // ~2.097 MHz (reset value)
        _4_MHz = RCC_ICSCR_MSIRANGE_6,   // ~4.194 MHz
    };

    static void enable(Frequency a_frequency);
    static bool enable(Frequency a_frequency, Milliseconds a_timeout);

    static void disable();
    static bool disable(Milliseconds a_timeout);

    static std::uint32_t get_frequency_Hz();

    static bool is_enabled()
    {
        return bit::flag::is(RCC->CR, RCC_CR_MSIRDY);
    }
};
} // namespace xmcu::soc::st::arm::m0::l0::rm0451::clocks::sources