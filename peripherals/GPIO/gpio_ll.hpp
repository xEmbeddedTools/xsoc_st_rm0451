#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>

// xmcu
#include <xmcu/Non_copyable.hpp>
#include <xmcu/soc/ST/arm/m0/stm32l0/rm0451/peripherals/GPIO/base.hpp>

namespace xmcu {
namespace soc {
namespace m0 {
namespace stm32l0 {
namespace rm0451 {
namespace peripherals {
namespace ll {

struct gpio : public gpio_base
{
#if defined XMCU_GPIOA_PRESENT
    using A = gpio_base::A;
#endif

#if defined XMCU_GPIOB_PRESENT
    using B = gpio_base::B;
#endif

#if defined XMCU_GPIOC_PRESENT
    using C = gpio_base::C;
#endif

#if defined XMCU_GPIOD_PRESENT
    using D = gpio_base::D;
#endif

#if defined XMCU_GPIOE_PRESENT
    using D = gpio_base::E;
#endif

#if defined XMCU_GPIOF_PRESENT
    using F = gpio_base::F;
#endif

#if defined XMCU_GPIOH_PRESENT
    using H = gpio_base::H;
#endif

    struct Port : private Non_copyable
    {
        volatile std::uint32_t moder;   // port mode register
        volatile std::uint32_t otyper;  // port output type register
        volatile std::uint32_t ospeedr; // port output speed register
        volatile std::uint32_t pupdr;   // port pull-up/pull-down register
        volatile std::uint32_t idr;     // port input data register
        volatile std::uint32_t odr;     // port output data register
        volatile std::uint32_t bsrr;    // port bit set/reset  register
        volatile std::uint32_t lckr;    // port configuration lock register
        volatile std::uint32_t afr[2];  // alternate function registers
        volatile std::uint32_t brr;     // bit reset register
    };

    template<typename Port_t> [[nodiscard]] static constexpr Port* port() = delete;

};

#if defined XMCU_GPIOA_PRESENT
template<> [[nodiscard]] constexpr gpio::Port* gpio::port<gpio::A>()
{
    return reinterpret_cast<gpio::Port*>(GPIOA_BASE);
}
#endif
#if defined XMCU_GPIOB_PRESENT
template<> [[nodiscard]] constexpr gpio::Port* gpio::port<gpio::B>()
{
    return reinterpret_cast<gpio::Port*>(GPIOB_BASE);
}
#endif
#if defined XMCU_GPIOC_PRESENT
template<> [[nodiscard]] constexpr gpio::Port* gpio::port<gpio::C>()
{
    return reinterpret_cast<gpio::Port*>(GPIOC_BASE);
}
#endif
#if defined XMCU_GPIOD_PRESENT
template<> [[nodiscard]] constexpr gpio::Port* gpio::port<gpio::D>()
{
    return reinterpret_cast<gpio::Port*>(GPIOD_BASE);
}
#endif
#if defined XMCU_GPIOE_PRESENT
template<> [[nodiscard]] constexpr gpio::Port* gpio::port<gpio::E>()
{
    return reinterpret_cast<gpio::Port*>(GPIOE_BASE);
}
#endif
#if defined XMCU_GPIOF_PRESENT
template<> [[nodiscard]] constexpr gpio::Port* gpio::port<gpio::F>()
{
    return reinterpret_cast<gpio::Port*>(GPIOF_BASE);
}
#endif
#if defined XMCU_GPIOH_PRESENT
template<> [[nodiscard]] constexpr gpio::Port* gpio::port<gpio::H>()
{
    return reinterpret_cast<gpio::Port*>(GPIOH_BASE);
}
#endif


} //namespace ll
} //namespace peripherals
} //namespace rm0451
} //namespace stm32l0
} // namespace m0
} // namespace soc
} // namespace xmcu