#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// xmcu
#include <xmcu/Duration.hpp>
#include <xmcu/Non_copyable.hpp>
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>
#include <xmcu/soc/Scoped_guard.hpp>

namespace xmcu {
namespace soc {
namespace m0 {
namespace l0 {
namespace rm0451 {
namespace peripherals {

class option_bytes : private non_constructible
{
public:
    class unlocker : private non_constructible
    {
    public:
        static void unlock();
        static bool unlock(Milliseconds a_timeout);

        static void lock();
    };

    struct secure_flash : private non_constructible
    {
        static std::uint32_t get_start_address();
        static std::uint32_t get_start_address(Milliseconds a_timeout);
    };

    struct BOR : private non_constructible
    {
        enum class Level : std::uint8_t
        {
            disabled = 0,
            _1 = 0x8u,
            _2 = 0x9u,
            _3 = 0xAu,
            _4 = 0xBu,
            _5 = 0xCu
        };

        static bool set(Level a_level);
        static Level get();
    };
    struct USER : private non_constructible
    {
        static std::uint32_t get();
    };

    static void reload();
};

} // namespace peripherals
} // namespace rm0451
} // namespace l0
} // namespace m0
} // namespace soc
} // namespace xmcu

namespace xmcu {
namespace soc {

template<> class Scoped_guard<m0::l0::rm0451::peripherals::option_bytes::unlocker> : private Non_copyable
{
public:
    Scoped_guard()
        : unlocked(false)
    {
        m0::l0::rm0451::peripherals::option_bytes::unlocker::unlock();
        this->unlocked = (false == bit::flag::is(FLASH->PECR, FLASH_PECR_OPTLOCK));
    }

    Scoped_guard(Milliseconds a_timeout)
        : unlocked(m0::l0::rm0451::peripherals::option_bytes::unlocker::unlock(a_timeout))
    {
    }

    ~Scoped_guard()
    {
        m0::l0::rm0451::peripherals::option_bytes::unlocker::lock();
    }

    bool is_unlocked() const
    {
        return this->unlocked;
    }

private:
    bool unlocked;
};

} // namespace soc
} // namespace xmcu
