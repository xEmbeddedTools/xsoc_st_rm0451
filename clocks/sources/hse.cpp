/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// this
#include <xmcu/soc/ST/arm/m0/l0/rm0451/clocks/sources/hse.hpp>

// xmcu
#include <xmcu/Duration.hpp>
#include <xmcu/bit.hpp>
#include <xmcu/soc/ST/arm/m0/l0/rm0451/utils/tick_counter.hpp>
#include <xmcu/soc/ST/arm/m0/l0/rm0451/utils/wait_until.hpp>

namespace {
constexpr std::uint32_t hse_control_unlock_key = 0xCAFECAFEu;
}

namespace xmcu::soc::st::arm::m0::l0::rm0451::clocks::sources {
using namespace xmcu;
using namespace xmcu::soc::st::arm::m0::l0::rm0451::utils;

void hse::enable()
{
    bit::flag::set(&(RCC->CR), RCC_CR_HSEON);

    wait_until::all_bits_are_set(RCC->CR, RCC_CR_HSERDY);
}

bool hse::enable(Milliseconds a_timeout)
{
    const std::uint64_t start = tick_counter<Milliseconds>::get();

    bit::flag::set(&(RCC->CR), RCC_CR_HSEON);

    return wait_until::all_bits_are_set(
        RCC->CR, RCC_CR_HSERDY, a_timeout.get() - (tick_counter<Milliseconds>::get() - start));
}

void hse::disable()
{
    bit::flag::set(&(RCC->CR), RCC_CR_HSEON);
    wait_until::all_bits_are_cleared(RCC->CR, RCC_CR_HSERDY);
}

bool hse::disable(Milliseconds a_timeout)
{
    const std::uint64_t start = tick_counter<Milliseconds>::get();

    bit::flag::set(&(RCC->CR), RCC_CR_HSEON);
    return wait_until::all_bits_are_cleared(
        RCC->CR, RCC_CR_HSERDY, a_timeout.get() - (tick_counter<Milliseconds>::get() - start));
}

} // namespace xmcu::soc::st::arm::m0::l0::rm0451::sources