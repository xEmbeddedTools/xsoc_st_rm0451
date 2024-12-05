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
#include <xmcu/soc/ST/arm/IRQ_config.hpp>
#include <xmcu/soc/ST/arm/Systick.hpp>
#include <xmcu/soc/ST/arm/m0/l0/rm0451/rcc.hpp>
#include <xmcu/soc/ST/arm/m0/l0/rm0451/sources/hsi16.hpp>
#include <xmcu/soc/ST/arm/m0/l0/rm0451/system/mcu/mcu.hpp>

namespace xmcu::soc::st::arm::m0::l0::rm0451::utils {
template<typename Period_t> class tick_counter : private non_constructible
{
};

template<> class tick_counter<Milliseconds> : private non_constructible
{
public:
    struct Callback
    {
        using Function = void (*)(std::uint64_t a_cnt, void* a_p_user_data);

        Function function = nullptr;
        void* p_user_data = nullptr;
    };

    template<typename Timer_t, typename Clock_t = void> static void
    enable(Timer_t* a_p_timer, const xmcu::soc::IRQ_config& a_irq_config, std::uint64_t a_start_cnt) = delete;
    template<typename Timer_t> static void disable() = delete;

    template<typename Timer_t> static void start(bool a_call_handler_on_start) = delete;
    template<typename Timer_t> static void stop() = delete;

    static std::uint64_t get();
    static std::uint32_t get_ticks_per_period();
    static std::uint32_t get_current_period_ticks();

    static void register_callback(const Callback& a_callback);

private:
    static void update(void*);

    static inline volatile std::uint64_t cnt = 0u;
    static inline void* p_timer = nullptr;
    static inline std::uint32_t ticks_per_period = 0u;

    static Callback callback;
};

template<> void tick_counter<Milliseconds>::enable<soc::Systick>(soc::Systick* a_p_timer,
                                                                 const soc::IRQ_config& a_irq_config,
                                                                 std::uint64_t a_start_cnt);

template<> void tick_counter<Milliseconds>::disable<soc::Systick>();

template<> void tick_counter<Milliseconds>::start<Systick>(bool a_start_handler_immediately);

template<> void tick_counter<Milliseconds>::stop<Systick>();
} // namespace xmcu::soc::st::arm::m0::l0::rm0451::utils