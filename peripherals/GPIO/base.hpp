#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>

// xmcu
#include <xmcu/non_constructible.hpp>

#define XMCU_SOC_STM32L010F4P6 17648494870528054
#define XMCU_SOC_STM32L010C6T6 17648494867548454

namespace xmcu::soc::st::arm::m0::l0::rm0451::peripherals {
#if (XMCU_SOC_MODEL == XMCU_SOC_STM32L010F4P6)
#define XMCU_GPIOA_PRESENT
#define XMCU_GPIOB_PRESENT
#define XMCU_GPIOC_PRESENT

struct gpio_base : private non_constructible
{
public:
    enum class A : std::uint8_t
    {
        _0_CK_IN,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,

        _9,
        _10,

        _13,
        _14,
    };
    enum class B : std::uint8_t
    {
        _1,
        _9_BOOT0,
    };
    enum class C : std::uint8_t
    {
        _14_OSC32_IN,
        _15_OSC32_OUT
    };

public:
    friend constexpr bool operator==(gpio_base::A, gpio_base::B)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::A, gpio_base::C)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::B, gpio_base::A)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::B, gpio_base::C)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::C, gpio_base::A)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::C, gpio_base::B)
    {
        return false;
    }
};
#endif
#if (XMCU_SOC_MODEL == XMCU_SOC_STM32L010C6T6)
#define XMCU_GPIOA_PRESENT
#define XMCU_GPIOB_PRESENT
#define XMCU_GPIOC_PRESENT
#define XMCU_GPIOH_PRESENT

struct gpio_base : private non_constructible
{
public:
    enum class A : std::uint8_t
    {
        _0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        _11,
        _12,
        _13,
        _14,
        _15,
    };
    enum class B : std::uint8_t
    {
        _0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        _11,
        _12,
        _13,
        _14,
        _15,
    };
    enum class C : std::uint8_t
    {
        _0,
        _13_ANTI_TAMP,
        _14_OSC32_IN,
        _15_OSC32_OUT
    };
    enum class H : std::uint8_t
    {
        _0_OSC_IN,
        _1_OSC_OUT,
    };

public:
    friend constexpr bool operator==(gpio_base::A, gpio_base::B)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::A, gpio_base::C)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::A, gpio_base::H)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::B, gpio_base::A)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::B, gpio_base::C)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::B, gpio_base::H)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::C, gpio_base::A)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::C, gpio_base::B)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::C, gpio_base::H)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::H, gpio_base::A)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::H, gpio_base::B)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::H, gpio_base::C)
    {
        return false;
    }
};
#endif
} // namespace xmcu::soc::st::arm::m0::l0::rm0451::peripherals