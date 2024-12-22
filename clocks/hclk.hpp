#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// xmcu
#include <xmcu/Duration.hpp>
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>

// soc
#include <xmcu/soc/ST/arm/m0/l0/rm0451/utils/wait_until.hpp>

// CMSIS
#include <stm32l0xx.h>

// std
#include <cstdint>
#include <cstdlib>

namespace xmcu::soc::st::arm::m0::l0::rm0451::clocks {
template<std::size_t id> struct hclk : private non_constructible
{
private:
    static constexpr std::uint32_t dividers[] = { 1u, 3u, 5u, 1u,  1u,  6u,   10u,  32u,
                                                  2u, 4u, 8u, 16u, 64u, 128u, 256u, 512u };

    friend class hclk<1u>;
};

template<> class hclk<1u> : private non_constructible
{
public:
    enum class Prescaler : std::uint32_t
    {
        _1 = RCC_CFGR_HPRE_DIV1,
        _2 = RCC_CFGR_HPRE_DIV2,
        _4 = RCC_CFGR_HPRE_DIV4,
        _8 = RCC_CFGR_HPRE_DIV8,
        _16 = RCC_CFGR_HPRE_DIV16,
        _64 = RCC_CFGR_HPRE_DIV64,
        _128 = RCC_CFGR_HPRE_DIV128,
        _256 = RCC_CFGR_HPRE_DIV256,
        _512 = RCC_CFGR_HPRE_DIV512,
    };
    static void set(Prescaler a_prescaler);
    static bool set(Prescaler a_prescaler, Milliseconds a_timeout);
    static Prescaler get_Prescaler();
    static std::uint32_t get_frequency_Hz();
};

inline void hclk<1u>::set(Prescaler a_prescaler)
{
    std::uint32_t prescaler_value = static_cast<std::uint32_t>(a_prescaler);
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_HPRE, prescaler_value);
    utils::wait_until::all_bits_are_set(RCC->CFGR, prescaler_value);
}
inline bool hclk<1u>::set(Prescaler a_prescaler, Milliseconds a_timeout)
{
    std::uint32_t prescaler_value = static_cast<std::uint32_t>(a_prescaler);
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_HPRE, prescaler_value);
    return utils::wait_until::masked_bits_are_set(RCC->CFGR, RCC_CFGR_HPRE, prescaler_value, a_timeout);
}
inline hclk<1u>::Prescaler hclk<1u>::get_Prescaler()
{
    return Prescaler();
}
inline std::uint32_t hclk<1u>::get_frequency_Hz()
{
    return SystemCoreClock / hclk<0u>::dividers[bit::flag::get(RCC->CFGR, RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos];
}
} // namespace xmcu::soc::st::arm::m0::l0::rm0451::clocks