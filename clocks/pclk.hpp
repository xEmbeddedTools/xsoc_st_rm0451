#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// xmcu
#include <xmcu/Duration.hpp>
#include <xmcu/non_constructible.hpp>

// soc
#include <xmcu/soc/ST/arm/m0/l0/rm0451/utils/wait_until.hpp>

// std
#include <cstdint>
#include <cstdlib>

namespace xmcu::soc::st::arm::m0::l0::rm0451::clocks {
template<std::size_t id> class pclk : private non_constructible
{
private:
    constexpr static std::uint32_t dividers[] = { 2u, 4u, 8u, 16u };

    friend class pclk<1u>;
    friend class pclk<2u>;
};

template<> class pclk<1u> : private non_constructible
{
public:
    enum class Prescaler : std::uint32_t
    {
        _1 = 0x0u,
        _2 = RCC_CFGR_PPRE1_2,
        _4 = RCC_CFGR_PPRE1_0 | RCC_CFGR_PPRE1_2,
        _8 = RCC_CFGR_PPRE1_1 | RCC_CFGR_PPRE1_2,
        _16 = RCC_CFGR_PPRE1_0 | RCC_CFGR_PPRE1_1 | RCC_CFGR_PPRE1_2,
    };
    static void set(Prescaler a_prescaler);
    static bool set(Prescaler a_prescaler, Milliseconds a_timeout);
    static Prescaler get_Prescaler();
    static std::uint32_t get_frequency_Hz();
};
template<> class pclk<2u> : private non_constructible
{
public:
    enum class Prescaler : std::uint32_t
    {
        _1 = 0x0u,
        _2 = RCC_CFGR_PPRE2_2,
        _4 = RCC_CFGR_PPRE2_0 | RCC_CFGR_PPRE2_2,
        _8 = RCC_CFGR_PPRE2_1 | RCC_CFGR_PPRE2_2,
        _16 = RCC_CFGR_PPRE2_0 | RCC_CFGR_PPRE2_1 | RCC_CFGR_PPRE2_2,
    };

    static void set(Prescaler a_prescaler);
    static bool set(Prescaler a_prescaler, Milliseconds a_timeout);

    static Prescaler get_Prescaler();
    static std::uint32_t get_frequency_Hz();
};

inline void pclk<1u>::set(Prescaler a_prescaler)
{
    std::uint32_t prescaler_value = static_cast<std::uint32_t>(a_prescaler);
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_PPRE1, static_cast<std::uint32_t>(a_prescaler));
    // RM doesn't tell anything about waiting for changed PCLK but not doing so feels wrong
    utils::wait_until::masked_bits_are_set(RCC->CFGR, RCC_CFGR_PPRE1, prescaler_value);
}
inline bool pclk<1u>::set(Prescaler a_prescaler, Milliseconds a_timeout)
{
    std::uint32_t prescaler_value = static_cast<std::uint32_t>(a_prescaler);
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_PPRE1, prescaler_value);
    // RM doesn't tell anything about waiting for changed PCLK but not doing so feels wrong
    return utils::wait_until::masked_bits_are_set(RCC->CFGR, RCC_CFGR_PPRE1, prescaler_value, a_timeout);
}
inline std::uint32_t pclk<1u>::get_frequency_Hz()
{
    std::uint32_t index = bit::flag::get(RCC->CFGR, RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos;

    if (index >= 4)
    {
        return SystemCoreClock / pclk<0u>::dividers[index - 4];
    }

    return SystemCoreClock;
}

inline void pclk<2u>::set(Prescaler a_prescaler)
{
    std::uint32_t prescaler_value = static_cast<std::uint32_t>(a_prescaler);
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_PPRE2, prescaler_value);
    // RM doesn't tell anything about waiting for changed PCLK but not doing so feels wrong
    utils::wait_until::masked_bits_are_set(RCC->CFGR, RCC_CFGR_PPRE2, prescaler_value);
}
inline bool pclk<2u>::set(Prescaler a_prescaler, Milliseconds a_timeout)
{
    std::uint32_t prescaler_value = static_cast<std::uint32_t>(a_prescaler);
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_PPRE2, prescaler_value);
    // RM doesn't tell anything about waiting for changed PCLK but not doing so feels wrong
    return utils::wait_until::masked_bits_are_set(RCC->CFGR, RCC_CFGR_PPRE2, prescaler_value, a_timeout);
}
inline pclk<2u>::Prescaler pclk<2u>::get_Prescaler()
{
    return Prescaler();
}
inline std::uint32_t pclk<2u>::get_frequency_Hz()
{
    std::uint32_t index = bit::flag::get(RCC->CFGR, RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos;

    if (index >= 4)
    {
        return SystemCoreClock / pclk<0u>::dividers[index - 4];
    }

    return SystemCoreClock;
}
} // namespace xmcu::soc::st::arm::m0::l0::rm0451::clocks