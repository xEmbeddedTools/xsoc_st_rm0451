#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// xmcu
#include <xmcu/Duration.hpp>
#include <xmcu/non_constructible.hpp>

namespace xmcu::soc::st::arm::m0::l0::rm0451::utils {
class delay : private xmcu::non_constructible
{
public:
    static void wait(xmcu::Milliseconds a_time);
    static void wait(xmcu::Seconds a_time);
    static void wait(xmcu::Microseconds a_time);
};
} // namespace xmcu::soc::st::arm::m0::l0::rm0451::utils
