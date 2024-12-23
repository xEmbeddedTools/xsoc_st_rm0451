/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// this
#include <rm0451/clocks/sources/msi.hpp>

// xmcu
#include <rm0451/utils/tick_counter.hpp>
#include <rm0451/utils/wait_until.hpp>
#include <xmcu/Frequency.hpp>

namespace {
constexpr std::uint32_t msi_frequency_hz_lut[] = { 100_kHz, 200_kHz, 400_kHz, 800_kHz, 1_MHz,  2_MHz,
                                                   4_MHz,   8_MHz,   16_MHz,  24_MHz,  32_MHz, 48_MHz };
}

namespace xmcu::soc::st::arm::m0::l0::rm0451::clocks::sources {
using namespace xmcu;
using namespace xmcu::soc::st::arm::m0::l0::rm0451::utils;

void msi::enable(Frequency a_frequency)
{
    bit::flag::clear(&(RCC->CR), RCC_CR_MSION);
    wait_until::all_bits_are_cleared(RCC->CR, RCC_CR_MSIRDY);

    bit::flag::set(&(RCC->ICSCR), RCC_ICSCR_MSIRANGE, static_cast<std::uint32_t>(a_frequency));
    bit::flag::set(&(RCC->CR), RCC_CR_MSION);

    wait_until::all_bits_are_set(RCC->CR, RCC_CR_MSIRDY);

    bit::flag::clear(&(RCC->ICSCR), RCC_ICSCR_MSITRIM);

    wait_until::all_bits_are_set(RCC->CR, RCC_CR_MSIRDY);
}

bool msi::enable(Frequency a_frequency, Milliseconds a_timeout)
{
    const std::uint64_t start = tick_counter<Milliseconds>::get();

    bit::flag::clear(&(RCC->CR), RCC_CR_MSION);
    if (true == wait_until::all_bits_are_cleared(
                    RCC->CR, RCC_CR_MSIRDY, a_timeout.get() - (tick_counter<Milliseconds>::get() - start)))
    {
        bit::flag::set(&(RCC->ICSCR), RCC_ICSCR_MSIRANGE, static_cast<std::uint32_t>(a_frequency));
        bit::flag::set(&(RCC->CR), RCC_CR_MSION);

        if (true == wait_until::all_bits_are_set(
                        RCC->CR, RCC_CR_MSIRDY, a_timeout.get() - (tick_counter<Milliseconds>::get() - start)))
        {
            bit::flag::clear(&(RCC->ICSCR), RCC_ICSCR_MSITRIM);

            return wait_until::all_bits_are_set(
                RCC->CR, RCC_CR_MSIRDY, a_timeout.get() - (tick_counter<Milliseconds>::get() - start));
        }
    }

    return false;
}

void msi::disable()
{
    bit::flag::clear(&(RCC->CR), RCC_CR_MSION);
    wait_until::all_bits_are_cleared(RCC->CR, RCC_CR_MSIRDY);
}

bool msi::disable(Milliseconds a_timeout)
{
    const std::uint64_t start = tick_counter<Milliseconds>::get();

    bit::flag::clear(&(RCC->CR), RCC_CR_MSION);
    return wait_until::all_bits_are_cleared(
        RCC->CR, RCC_CR_MSIRDY, a_timeout.get() - (tick_counter<Milliseconds>::get() - start));
}

std::uint32_t msi::get_frequency_Hz()
{
    if (true == is_enabled())
    {
        return msi_frequency_hz_lut[bit::flag::get(RCC->ICSCR, RCC_ICSCR_MSIRANGE) >> RCC_ICSCR_MSIRANGE_Pos];
    }

    return 0u;
}
} // namespace xmcu::soc::st::arm::m0::l0::rm0451::clocks::sources