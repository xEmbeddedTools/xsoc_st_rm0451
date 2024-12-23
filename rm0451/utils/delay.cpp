/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// this
#include <rm0451/utils/delay.hpp>

// externals
#include <stm32l0xx.h>

// xmcu
#include <rm0451/rcc.hpp>
#include <rm0451/system/mcu/mcu.hpp>
#include <rm0451/utils/tick_counter.hpp>

// debug
#include <xmcu/assertion.hpp>

namespace xmcu::soc::st::arm::m0::l0::rm0451::utils {
using namespace xmcu;
using namespace xmcu::soc::st::arm::m0::l0::rm0451::system;

using tick = tick_counter<Milliseconds>;

void delay::wait(Milliseconds a_time)
{
    const std::uint64_t start = tick::get();
    while (tick::get() - start <= a_time.get()) continue;
}

void delay::wait(Seconds a_time)
{
    const std::uint64_t start = tick::get();
    while (tick::get() - start <= a_time.get_in<Milliseconds>().get()) continue;
}

void delay::wait(Microseconds a_time)
{
    std::uint32_t now_ticks = tick::get_current_period_ticks();
    std::uint32_t ticks_per_period = tick::get_ticks_per_period();
    std::uint32_t ticks_per_us = ticks_per_period / 1000u;
    std::uint32_t ticks_to_wait = a_time.get() * ticks_per_us;
    if (ticks_to_wait >= now_ticks)
    {
        // In this scenario, period counter will underflow, so wait two times: one for underflow, one for remaining
        // ticks after it.
        std::uint32_t end_ticks = ticks_per_period + now_ticks - ticks_to_wait;
        while (tick::get_current_period_ticks() < now_ticks) continue;
        while (tick::get_current_period_ticks() >= end_ticks) continue;
    }
    else
    {
        // If the end_ticks value is close to 0, exit condition might be lost, because read interval is long.
        // Also check if tick counter haven't underflown.
        std::uint32_t end_ticks = now_ticks - ticks_to_wait;
        std::uint32_t act;
        while ((act = tick::get_current_period_ticks()) >= end_ticks && act < now_ticks) continue;
    }
}
} // namespace xmcu::soc::st::arm::m0::l0::rm0451::utils