#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>

// xmcu
#include <xmcu/Duration.hpp>
#include <xmcu/non_constructible.hpp>

namespace xmcu {
namespace soc {
namespace m0 {
namespace stm32l0 {
namespace rm0451 {
namespace utils {

struct wait_until : private non_constructible
{
    static void all_bits_are_set(volatile const std::uint32_t& a_register, std::uint32_t a_mask);
    static void any_bit_is_set(volatile const std::uint32_t& a_register, std::uint32_t a_mask);
    static void
    masked_bits_are_set(volatile const std::uint32_t& a_register, std::uint32_t a_mask, std::uint32_t a_value);

    static void all_bits_are_cleared(volatile const std::uint32_t& a_register, std::uint32_t a_mask);
    static void any_bit_is_cleared(volatile const std::uint32_t& a_register, std::uint32_t a_mask);

    static bool
    all_bits_are_set(volatile const std::uint32_t& a_register, std::uint32_t a_mask, Milliseconds a_timeout);
    static bool
    any_bit_is_set(volatile const std::uint32_t& a_register, std::uint32_t a_mask, Milliseconds a_timeout);
    static bool masked_bits_are_set(volatile const std::uint32_t& a_register,
                                    std::uint32_t a_mask,
                                    std::uint32_t a_value,
                                    Milliseconds a_timeout);

    static bool all_bits_are_cleared(volatile const std::uint32_t& a_register,
                                     std::uint32_t a_mask,
                                     Milliseconds a_timeout);
    static bool
    any_bit_is_cleared(volatile const std::uint32_t& a_register, std::uint32_t a_mask, Milliseconds a_timeout);
};

} // namespace utils
} // namespace rm0451
} // namespace stm32l0
} // namespace m0
} // namespace soc
} // namespace xmcu
