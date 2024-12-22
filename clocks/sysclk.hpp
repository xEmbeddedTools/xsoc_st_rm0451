#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// xmcu
#include <xmcu/Duration.hpp>
#include <xmcu/assertion.hpp>
#include <xmcu/non_constructible.hpp>

// soc
#include <xmcu/soc/ST/arm/m0/l0/rm0451/clocks/sources/hse.hpp>
#include <xmcu/soc/ST/arm/m0/l0/rm0451/clocks/sources/hsi16.hpp>
#include <xmcu/soc/ST/arm/m0/l0/rm0451/clocks/sources/msi.hpp>
#include <xmcu/soc/ST/arm/m0/l0/rm0451/utils/tick_counter.hpp>
#include <xmcu/soc/ST/arm/m0/l0/rm0451/utils/wait_until.hpp>

// std
#include <cstdlib>

namespace xmcu::soc::st::arm::m0::l0::rm0451::clocks {
template<std::size_t id> struct sysclk : private non_constructible
{
};

template<> class sysclk<1u> : private non_constructible
{
public:
    template<typename Source_t> static void set_source() = delete;
    template<typename Source_t> static bool set_source(Milliseconds a_timeout) = delete;
    static bool set_source(Milliseconds a_timeout) = delete;
    template<typename Source_t> static bool is_source() = delete;
    template<typename Source> void set_wakeup_source() = delete;
    static std::uint32_t get_frequency_Hz();
};

template<> inline void sysclk<1u>::set_source<sources::msi>()
{
    hkm_assert(true == sources::msi::is_enabled());

    bit::flag::set(&(RCC->CFGR), RCC_CFGR_SW, RCC_CFGR_SW_MSI);
    utils::wait_until::masked_bits_are_set(RCC->CFGR, RCC_CFGR_SWS, RCC_CFGR_SWS_MSI);

    SystemCoreClock = sources::msi::get_frequency_Hz();
}
template<> inline bool sysclk<1u>::set_source<sources::msi>(Milliseconds a_timeout)
{
    hkm_assert(true == sources::msi::is_enabled());

    const std::uint64_t start = utils::tick_counter<Milliseconds>::get();

    bit::flag::set(&(RCC->CFGR), RCC_CFGR_SW, RCC_CFGR_SW_MSI);
    if (true ==
        utils::wait_until::masked_bits_are_set(RCC->CFGR,
                                               RCC_CFGR_SWS,
                                               RCC_CFGR_SWS_MSI,
                                               a_timeout.get() - (utils::tick_counter<Milliseconds>::get() - start)))
    {
        SystemCoreClock = sources::msi::get_frequency_Hz();
        return true;
    }

    return false;
}
template<> inline bool sysclk<1u>::is_source<sources::msi>()
{
    return RCC_CFGR_SWS_MSI == bit::flag::get(RCC->CFGR, RCC_CFGR_SWS);
}

template<> inline void sysclk<1u>::set_source<sources::hsi16>()
{
    hkm_assert(true == sources::hsi16::is_enabled());

    bit::flag::set(&(RCC->CFGR), RCC_CFGR_SW, RCC_CFGR_SW_HSI);
    utils::wait_until::masked_bits_are_set(RCC->CFGR, RCC_CFGR_SWS, RCC_CFGR_SWS_HSI);

    SystemCoreClock = sources::hsi16::get_frequency_Hz();
}
template<> inline bool sysclk<1u>::set_source<sources::hsi16>(Milliseconds a_timeout)
{
    hkm_assert(true == sources::hsi16::is_enabled());

    const std::uint64_t start = utils::tick_counter<Milliseconds>::get();

    bit::flag::set(&(RCC->CFGR), RCC_CFGR_SW, RCC_CFGR_SW_HSI);
    if (true ==
        utils::wait_until::masked_bits_are_set(RCC->CFGR,
                                               RCC_CFGR_SWS,
                                               RCC_CFGR_SWS_HSI,
                                               a_timeout.get() - (utils::tick_counter<Milliseconds>::get() - start)))
    {
        SystemCoreClock = sources::hsi16::get_frequency_Hz();
        return true;
    }

    return false;
}
template<> inline bool sysclk<1u>::is_source<sources::hsi16>()
{
    return RCC_CFGR_SWS_HSI == bit::flag::get(RCC->CFGR, RCC_CFGR_SWS);
}

template<> inline void sysclk<1u>::set_source<sources::hse>()
{
    hkm_assert(true == sources::hse::is_enabled());

    bit::flag::set(&(RCC->CFGR), RCC_CFGR_SW, RCC_CFGR_SW_HSE);
    utils::wait_until::masked_bits_are_set(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_HSE);

    SystemCoreClock = sources::hse::get_frequency_Hz();
}

template<> inline bool sysclk<1u>::is_source<sources::hse>()
{
    return RCC_CFGR_SWS_HSE == bit::flag::get(RCC->CFGR, RCC_CFGR_SWS);
}

inline std::uint32_t sysclk<1u>::get_frequency_Hz()
{
    return SystemCoreClock;
}

template<> inline void sysclk<1u>::set_wakeup_source<sources::msi>()
{
    bit::flag::clear(&(RCC->CFGR), RCC_CFGR_STOPWUCK);
}
template<> inline void sysclk<1u>::set_wakeup_source<sources::hsi16>()
{
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_STOPWUCK, RCC_CFGR_STOPWUCK);
}
} // namespace xmcu::soc::st::arm::m0::l0::rm0451::clocks