/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// this
<<<<<<<< HEAD:rm0451/clocks/sources/hsi16.cpp
#include <rm0451/clocks/sources/hsi16.hpp>
========
#include <xmcu/soc/ST/arm/m0/l0/rm0451/clocks/sources/hsi16.hpp>
>>>>>>>> main:clocks/sources/hsi16.cpp

// xmcu
#include <rm0451/utils/tick_counter.hpp>
#include <rm0451/utils/wait_until.hpp>
#include <xmcu/bit.hpp>

namespace xmcu::soc::st::arm::m0::l0::rm0451::clocks::sources {
using namespace xmcu;
using namespace xmcu::soc::st::arm::m0::l0::rm0451::utils;

void hsi16::enable()
{
    bit::flag::set(&(RCC->CR), RCC_CR_HSION, RCC_CR_HSION);
    wait_until::all_bits_are_set(RCC->CR, RCC_CR_HSIRDY);
}
bool hsi16::enable(Milliseconds a_timeout)
{
    const std::uint64_t start = tick_counter<Milliseconds>::get();

    bit::flag::set(&(RCC->CR), RCC_CR_HSION, RCC_CR_HSION);
    return wait_until::all_bits_are_set(
        RCC->CR, RCC_CR_HSIRDY, a_timeout.get() - (tick_counter<Milliseconds>::get() - start));
}
void hsi16::disable()
{
    bit::flag::clear(&(RCC->CR), RCC_CR_HSION);
    wait_until::all_bits_are_cleared(RCC->CR, RCC_CR_HSIRDY);
}
bool hsi16::disable(Milliseconds a_timeout)
{
    const std::uint64_t start = tick_counter<Milliseconds>::get();

    bit::flag::clear(&(RCC->CR), RCC_CR_HSION);
    return wait_until::all_bits_are_cleared(
        RCC->CR, RCC_CR_HSIRDY, a_timeout.get() - (tick_counter<Milliseconds>::get() - start));
}
} // namespace xmcu::soc::st::arm::m0::l0::rm0451::clocks::sources