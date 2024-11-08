/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// xmcu
#include <xmcu/bit.hpp>
#include <xmcu/soc/ST/arm/IRQ_config.hpp>
#include <xmcu/soc/ST/arm/m0/nvic.hpp>
#include <xmcu/soc/ST/arm/m0/l0/rm0451/peripherals/GPIO/GPIO.hpp>
#include <xmcu/soc/Scoped_guard.hpp>

// debug
#include <xmcu/assertion.hpp>

namespace {
using namespace xmcu;
using namespace xmcu::soc::m0::l0::rm0451::peripherals;

GPIO::Interrupt::Callback callbacks[3u];

void shared_exti_int_handler(std::uint32_t a_start, std::uint32_t a_end, std::uint32_t a_handler_index)
{
    for (std::uint32_t i = a_start; i <= a_end; ++i)
    {
        std::uint32_t bit_index = i - 1;
        if (true == bit::is(EXTI->PR, bit_index))
        {
            hkm_assert(nullptr != callbacks[a_handler_index].function);
            callbacks[a_handler_index].function(bit_index, callbacks[a_handler_index].p_user_data);
            bit::set(&(EXTI->PR), bit_index);
        }
    }
}

ll::gpio::Registers* cast_to_registers(GPIO* a_p_port)
{
    return static_cast<ll::gpio::Registers*>(*(a_p_port));
}

} // namespace

extern "C" {

void EXTI0_1_IRQHandler()
{
    shared_exti_int_handler(0u, 1u, 0u);
}

void EXTI2_3_IRQHandler()
{
    shared_exti_int_handler(2u, 3u, 1u);
}

void EXTI4_15_IRQHandler()
{
    shared_exti_int_handler(4u, 15u, 2u);
}
}

namespace xmcu::soc::m0::l0::rm0451::peripherals {
using namespace xmcu;
using namespace xmcu::soc::m0::l0::rm0451::sources;
using namespace xmcu::soc::m0::l0::rm0451::system;

void GPIO::In::Pin::set_pull(Pull a_pull)
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    bit::flag::set(&(cast_to_registers(this->p_port)->pupdr),
                   ll::gpio::PUPDR::mask << this->id,
                   static_cast<ll::gpio::PUPDR::Flag>(a_pull) << this->id);
}

GPIO::Level GPIO::In::Pin::get_level() const
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    return static_cast<GPIO::Level>(
        bit::is(cast_to_registers(this->p_port)->idr, Limited<std::uint32_t, 0u, 15u>(this->id)));
}

GPIO::Pull GPIO::In::Pin::get_pull() const
{
    hkm_assert(nullptr != this->p_port && 0xFF != this->id);

    return static_cast<Pull>(
        bit::flag::get(cast_to_registers(this->p_port)->pupdr, ll::gpio::PUPDR::mask << this->id) >> this->id);
}

void GPIO::Out::Pin::set_level(Level a_level)
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    xmcu::bit::flag::set(&(cast_to_registers(this->p_port)->odr),
                         ll::gpio::ODR::mask << this->id,
                         static_cast<ll::gpio::ODR::Flag>(a_level) << this->id);
}

void GPIO::Out::Pin::toggle_level()
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    bit::toggle(&(cast_to_registers(this->p_port)->odr), this->id);
}

void GPIO::Out::Pin::set_type(Type a_type)
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    bit::flag::set(&(cast_to_registers(this->p_port)->otyper),
                   ll::gpio::OTYPER::mask << this->id,
                   static_cast<ll::gpio::OTYPER::Flag>(a_type) << this->id);
}

void GPIO::Out::Pin::set_pull(Pull a_pull)
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    bit::flag::set(&(cast_to_registers(this->p_port)->pupdr),
                   ll::gpio::PUPDR::mask << this->id,
                   static_cast<ll::gpio::PUPDR::Flag>(a_pull) << this->id);
}

void GPIO::Out::Pin::set_speed(Speed a_speed)
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    bit::flag::set(&(cast_to_registers(this->p_port)->ospeedr),
                   ll::gpio::OSPEEDR::mask << this->id,
                   static_cast<ll::gpio::OSPEEDR::Flag>(a_speed) << this->id);
}

GPIO::Level GPIO::Out::Pin::get_level() const
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    return static_cast<GPIO::Level>(
        bit::is(cast_to_registers(this->p_port)->idr, Limited<std::uint32_t, 0u, 15u>(this->id)));
}

GPIO::Type GPIO::Out::Pin::get_type() const
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    return static_cast<Type>(
        bit::flag::get(cast_to_registers(this->p_port)->otyper, ll::gpio::OTYPER::mask << this->id) >> this->id);
}

GPIO::Pull GPIO::Out::Pin::get_pull() const
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    return static_cast<Pull>(
        bit::flag::get(cast_to_registers(this->p_port)->pupdr, ll::gpio::PUPDR::mask << this->id) >> this->id);
}

GPIO::Speed GPIO::Out::Pin::get_speed() const
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    return static_cast<Speed>(
        bit::flag::get(cast_to_registers(this->p_port)->ospeedr, ll::gpio::OSPEEDR::mask << this->id) >> this->id);
}

void GPIO::Analog::Pin::set_pull(Pull a_pull)
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    bit::flag::set(&(cast_to_registers(this->p_port)->pupdr),
                   ll::gpio::PUPDR::mask << this->id,
                   static_cast<ll::gpio::PUPDR::Flag>(a_pull) << this->id);
}

GPIO::Pull GPIO::Analog::Pin::get_pull() const
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    return static_cast<Pull>(
        bit::flag::get(cast_to_registers(this->p_port)->pupdr, ll::gpio::PUPDR::mask << this->id) >> this->id);
}

void GPIO::Alternate_function::Pin::set_type(Type a_type)
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    bit::flag::set(&(cast_to_registers(this->p_port)->otyper),
                   ll::gpio::OTYPER::mask << this->id,
                   static_cast<ll::gpio::OTYPER::Flag>(a_type) << this->id);
}

void GPIO::Alternate_function::Pin::set_pull(Pull a_pull)
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    bit::flag::set(&(cast_to_registers(this->p_port)->pupdr),
                   ll::gpio::PUPDR::mask << this->id,
                   static_cast<ll::gpio::PUPDR::Flag>(a_pull) << this->id);
}

void GPIO::Alternate_function::Pin::set_speed(Speed a_speed)
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    bit::flag::set(&(cast_to_registers(this->p_port)->ospeedr),
                   ll::gpio::OSPEEDR::mask << this->id,
                   static_cast<ll::gpio::OSPEEDR::Flag>(a_speed) << this->id);
}

GPIO::Type GPIO::Alternate_function::Pin::get_type() const
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    return static_cast<Type>(
        bit::flag::get(cast_to_registers(this->p_port)->otyper, ll::gpio::OTYPER::mask << this->id) >> this->id);
}

GPIO::Pull GPIO::Alternate_function::Pin::get_pull() const
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    return static_cast<Pull>(
        bit::flag::get(cast_to_registers(this->p_port)->pupdr, ll::gpio::PUPDR::mask << this->id) >> this->id);
}

GPIO::Speed GPIO::Alternate_function::Pin::get_speed() const
{
    hkm_assert(nullptr != this->p_port && 0xFFu != this->id);

    return static_cast<Speed>(
        bit::flag::get(cast_to_registers(this->p_port)->ospeedr, ll::gpio::OSPEEDR::mask << this->id) >> this->id);
}

void GPIO::In::enable(Limited<std::uint32_t, 0, 15> a_id, Pull a_pull, Pin* a_p_pin)
{
    hkm_assert(false == this->p_port->is_pin_taken(a_id));

    ll::gpio::Registers* p_port = cast_to_registers(this->p_port);

    bit::flag::set(&(p_port->pupdr), ll::gpio::PUPDR::mask << a_id, static_cast<ll::gpio::PUPDR::Flag>(a_pull) << a_id);
    bit::flag::clear(&(p_port->moder), ll::gpio::MODER::mask << a_id);

    this->p_port->take_pin(a_id);

    if (nullptr != a_p_pin)
    {
        a_p_pin->id = a_id;
        a_p_pin->p_port = this->p_port;
    }
}

void GPIO::In::disable(Limited<std::uint32_t, 0, 15> a_id)
{
    hkm_assert(false == this->p_port->is_pin_taken(a_id));

    ll::gpio::Registers* p_port = cast_to_registers(this->p_port);

    bit::flag::set(&(p_port->moder), ll::gpio::MODER::mask << a_id);
    bit::flag::clear(&(p_port->pupdr), ll::gpio::PUPDR::mask << a_id);

    this->p_port->give_pin(a_id);
}
void GPIO::In::disable(Pin* p_pin)
{
    this->disable(p_pin->get_id());

    p_pin->p_port = nullptr;
    p_pin->id = 0xFFu;
}

void GPIO::Out::enable(Limited<std::uint32_t, 0, 15> a_id, const Enable_config& a_config, Pin* a_p_pin)
{
    hkm_assert(various::get_enum_incorrect_value<Pull>() != a_config.pull);
    hkm_assert(various::get_enum_incorrect_value<Speed>() != a_config.speed);
    hkm_assert(various::get_enum_incorrect_value<Type>() != a_config.type);

    hkm_assert(false == this->p_port->is_pin_taken(a_id));

    ll::gpio::Registers* p_port = cast_to_registers(this->p_port);

    bit::flag::set(&(p_port->ospeedr),
                   ll::gpio::OSPEEDR::mask << a_id,
                   static_cast<ll::gpio::OSPEEDR::Flag>(a_config.speed) << a_id);
    bit::flag::set(
        &(p_port->pupdr), ll::gpio::PUPDR::mask << a_id, static_cast<ll::gpio::PUPDR::Flag>(a_config.pull) << a_id);
    bit::flag::set(&(p_port->moder), ll::gpio::MODER::mask << a_id, ll::gpio::MODER::output << a_id);
    bit::flag::set(
        &(p_port->otyper), ll::gpio::OTYPER::mask << a_id, static_cast<ll::gpio::OTYPER::Flag>(a_config.type) << a_id);

    this->p_port->take_pin(a_id);

    if (nullptr != a_p_pin)
    {
        a_p_pin->id = a_id;
        a_p_pin->p_port = this->p_port;
    }
}

void GPIO::Out::disable(Limited<std::uint32_t, 0, 15> a_id)
{
    hkm_assert(false == this->p_port->is_pin_taken(a_id));

    ll::gpio::Registers* p_port = cast_to_registers(this->p_port);

    bit::flag::set(&(p_port->moder), ll::gpio::MODER::mask << a_id);
    bit::flag::clear(&(p_port->ospeedr), ll::gpio::OSPEEDR::mask << a_id);
    bit::flag::clear(&(p_port->pupdr), ll::gpio::PUPDR::mask << a_id);

    this->p_port->give_pin(a_id);
}
void GPIO::Out::disable(Pin* p_pin)
{
    this->disable(p_pin->get_id());

    p_pin->p_port = nullptr;
    p_pin->id = 0xFFu;
}

void GPIO::Analog::enable(Limited<std::uint32_t, 0, 15> a_id, Pull a_pull, Pin* a_p_out_pin)
{
    hkm_assert(false == this->p_port->is_pin_taken(a_id));

    ll::gpio::Registers* p_port = cast_to_registers(this->p_port);

    bit::flag::set(&(p_port->pupdr), ll::gpio::PUPDR::mask << a_id, static_cast<ll::gpio::PUPDR::Flag>(a_pull) << a_id);
    bit::flag::set(&(p_port->moder), ll::gpio::MODER::mask << a_id, ll::gpio::MODER::analog << a_id);

    this->p_port->take_pin(a_id);

    if (nullptr != a_p_out_pin)
    {
        a_p_out_pin->id = a_id;
        a_p_out_pin->p_port = this->p_port;
    }
}

void GPIO::Analog::disable(Limited<std::uint32_t, 0, 15> a_id)
{
    bit::flag::clear(&(cast_to_registers(this->p_port)->pupdr), (ll::gpio::PUPDR::mask << a_id));

    this->p_port->give_pin(a_id);
}
void GPIO::Analog::disable(Pin* p_pin)
{
    this->disable(p_pin->get_id());

    p_pin->p_port = nullptr;
    p_pin->id = 0xFFu;
}

void GPIO::Alternate_function::disable(Limited<std::uint32_t, 0, 15> a_id)
{
    ll::gpio::Registers* p_port = cast_to_registers(this->p_port);

    bit::flag::set(&(p_port->moder), ll::gpio::MODER::mask << a_id);
    bit::flag::clear(&(p_port->ospeedr), ll::gpio::OSPEEDR::mask << a_id);
    bit::flag::clear(&(p_port->pupdr), ll::gpio::PUPDR::mask << a_id);

    this->p_port->give_pin(a_id);
}
void GPIO::Alternate_function::disable(Pin* p_pin)
{
    this->disable(p_pin->get_id());

    p_pin->p_port = nullptr;
    p_pin->id = 0xFFu;
}

void GPIO::Alternate_function::enable(Limited<std::uint32_t, 0, 15> a_id,
                                      const Enable_config& a_config,
                                      std::uint32_t a_function,
                                      Pin* a_p_pin)
{
    hkm_assert(false == this->p_port->is_pin_taken(a_id));

    hkm_assert(various::get_enum_incorrect_value<Pull>() != a_config.pull);
    hkm_assert(various::get_enum_incorrect_value<Speed>() != a_config.speed);
    hkm_assert(various::get_enum_incorrect_value<Type>() != a_config.type);

    ll::gpio::Registers* p_port = cast_to_registers(this->p_port);

    bit::flag::set(&(p_port->ospeedr),
                   ll::gpio::OSPEEDR::mask << a_id,
                   static_cast<ll::gpio::OSPEEDR::Flag>(a_config.speed) << a_id);
    bit::flag::set(
        &(p_port->pupdr), ll::gpio::PUPDR::mask << a_id, static_cast<ll::gpio::PUPDR::Flag>(a_config.pull) << a_id);
    bit::flag::set(
        &(p_port->otyper), ll::gpio::OTYPER::mask << a_id, static_cast<ll::gpio::OTYPER::Flag>(a_config.type) << a_id);

    const std::uint32_t index = a_id >> 3u;
    const std::uint32_t shift = a_id - (index * 8u);

    hkm_assert(various::countof(p_port->afr) > index);

    bit::flag::set(
        &(p_port->afr[index]), ll::gpio::AFR::mask << shift, static_cast<ll::gpio::AFR::Flag>(a_function) << shift);
    bit::flag::set(&(p_port->moder), ll::gpio::MODER::mask << a_id, ll::gpio::MODER::af << a_id);

    this->p_port->take_pin(a_id);

    if (nullptr != a_p_pin)
    {
        a_p_pin->id = a_id;
        a_p_pin->p_port = this->p_port;
        a_p_pin->function = a_function;
    }
}

void GPIO::Interrupt::enable(const Callback& a_callback, const IRQ_config& a_irq_config)
{
    hkm_assert(std::numeric_limits<decltype(this->idx)>::max() != this->idx);

    NVIC_SetPriority(
        this->irqn,
        NVIC_EncodePriority(NVIC_GetPriorityGrouping(), a_irq_config.preempt_priority, a_irq_config.sub_priority));
    NVIC_EnableIRQ(this->irqn);

    callbacks[this->idx] = a_callback;
}

void GPIO::Interrupt::disable()
{
    hkm_assert(std::numeric_limits<decltype(this->idx)>::max() != this->idx);

    NVIC_DisableIRQ(this->irqn);

    callbacks[this->idx] = { nullptr, nullptr };
}

void GPIO::Interrupt::attach(const GPIO& a_port, std::uint32_t a_pin, Trigger_flag a_trigger, Type a_type)
{
    hkm_assert(std::numeric_limits<decltype(this->idx)>::max() != this->idx);

    volatile std::uint32_t* p_register = &(SYSCFG->EXTICR[a_pin / 4u]);
    std::uint32_t pos = ((static_cast<std::uint32_t>(a_pin) % 4u) * 4u);

#if defined(HKM_ASSERT_ENABLED)
    const bool f = bit::flag::is(*p_register, (a_port.idx) << pos);
    hkm_assert((0u == a_port.idx && true == f) || (0u != a_port.idx && false == f));
    hkm_assert((0u == this->idx && 0u == a_pin) || (1u == this->idx && 1u == a_pin) ||
               (2u == this->idx && 2u == a_pin) || (3u == this->idx && 3u == a_pin) ||
               (4u == this->idx && 4u == a_pin) || (5u == this->idx && (a_pin >= 5u && a_pin <= 9u)) ||
               (6u == this->idx && (a_pin >= 10u && a_pin <= 15u)));
#endif

    Scoped_guard<nvic> guard;

    bit::flag::set(p_register, 0x3u << pos, a_port.idx << pos);

    bit::clear(&(EXTI->RTSR), a_pin);
    bit::clear(&(EXTI->FTSR), a_pin);

    switch (a_type)
    {
        case Type::event: {
            bit::set(&(EXTI->EMR), a_pin);
        }
        break;

        case Type::interrupt: {
            bit::set(&(EXTI->IMR), a_pin);
        }
        break;
    }

    switch (a_trigger)
    {
        case Trigger_flag::rising: {
            bit::set(&(EXTI->RTSR), a_pin);
        }
        break;

        case Trigger_flag::falling: {
            bit::set(&(EXTI->FTSR), a_pin);
        }
        break;

        default: {
            if ((Trigger_flag::rising | Trigger_flag::falling) == a_trigger)
            {
                bit::set(&(EXTI->RTSR), a_pin);
                bit::set(&(EXTI->FTSR), a_pin);
            }
        }
    }
}
void GPIO::Interrupt::attach(const GPIO::In::Pin& a_pin, Trigger_flag a_trigger, Type a_type)
{
    this->attach(*(a_pin.get_port()), a_pin.get_id(), a_trigger, a_type);
}
void GPIO::Interrupt::attach(const GPIO::Out::Pin& a_pin, Trigger_flag a_trigger, Type a_type)
{
    this->attach(*(a_pin.get_port()), a_pin.get_id(), a_trigger, a_type);
}
void GPIO::Interrupt::attach(const GPIO::Alternate_function::Pin& a_pin, Trigger_flag a_trigger, Type a_type)
{
    this->attach(*(a_pin.get_port()), a_pin.get_id(), a_trigger, a_type);
}

void GPIO::Interrupt::deattach(const GPIO& a_port, std::uint32_t a_pin)
{
    hkm_assert(std::numeric_limits<decltype(this->idx)>::max() != this->idx);

    Scoped_guard<nvic> guard;

    bit::clear(&(EXTI->RTSR), a_pin);
    bit::clear(&(EXTI->FTSR), a_pin);

    bit::clear(&(EXTI->EMR), a_pin);
    bit::clear(&(EXTI->IMR), a_pin);

    bit::flag::clear(&(SYSCFG->EXTICR[a_pin / 4u]), a_port.idx << ((static_cast<std::uint32_t>(a_pin) % 4u) * 4u));

    callbacks[this->idx] = { nullptr, nullptr };
}
void GPIO::Interrupt::deattach(const GPIO::In::Pin& a_pin)
{
    this->deattach(*(a_pin.get_port()), a_pin.get_id());
}
void GPIO::Interrupt::deattach(const GPIO::Out::Pin& a_pin)
{
    this->deattach(*(a_pin.get_port()), a_pin.get_id());
}
void GPIO::Interrupt::deattach(const GPIO::Alternate_function::Pin& a_pin)
{
    this->deattach(*(a_pin.get_port()), a_pin.get_id());
}

template<> void GPIO::mco::enable<hse>(Divider a_divider)
{
    bit::flag::set(&(RCC->CFGR), static_cast<std::uint32_t>(a_divider));
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_MCOSEL, RCC_CFGR_MCOSEL_2);
}

template<> void GPIO::mco::enable<hsi16>(Divider a_divider)
{
    bit::flag::set(&(RCC->CFGR), static_cast<std::uint32_t>(a_divider));
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_MCOSEL, RCC_CFGR_MCOSEL_0 | RCC_CFGR_MCOSEL_1);
}

template<> void GPIO::mco::enable<rcc<mcu<1u>>>(Divider a_divider)
{
    bit::flag::set(&(RCC->CFGR), static_cast<std::uint32_t>(a_divider));
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_MCOSEL, RCC_CFGR_MCOSEL_0);
}

template<> void GPIO::mco::enable<msi>(Divider a_divider)
{
    bit::flag::set(&(RCC->CFGR), static_cast<std::uint32_t>(a_divider));
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_MCOSEL, RCC_CFGR_MCOSEL_1);
}

void GPIO::mco::disable()
{
    bit::flag::clear(&(RCC->CFGR), RCC_CFGR_MCOPRE);
    bit::flag::clear(&(RCC->CFGR), RCC_CFGR_MCOSEL);
}

} // namespace xmcu::soc::m0::l0::rm0451::peripherals

namespace xmcu::soc::m0::l0::rm0451 {
using namespace xmcu::soc::m0::l0::rm0451::system;

template<> void rcc<GPIO, 1>::enable(bool a_enable_in_lp)
{
    bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIOAEN);

    if (true == a_enable_in_lp)
    {
        bit::flag::set(&(RCC->IOPSMENR), RCC_IOPSMENR_GPIOASMEN);
    }
    else
    {
        bit::flag::clear(&(RCC->IOPSMENR), RCC_IOPSMENR_GPIOASMEN);
    }
}
template<> void rcc<GPIO, 1>::disable()
{
    bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIOAEN);
}

template<> void rcc<GPIO, 2>::enable(bool a_enable_in_lp)
{
    bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIOBEN);

    if (true == a_enable_in_lp)
    {
        bit::flag::set(&(RCC->IOPSMENR), RCC_IOPSMENR_GPIOBSMEN);
    }
    else
    {
        bit::flag::clear(&(RCC->IOPSMENR), RCC_IOPSMENR_GPIOBSMEN);
    }
}
template<> void rcc<GPIO, 2>::disable()
{
    bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIOBEN);
}

template<> void rcc<GPIO, 3>::enable(bool a_enable_in_lp)
{
    bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIOCEN);

    if (true == a_enable_in_lp)
    {
        bit::flag::set(&(RCC->IOPSMENR), RCC_IOPSMENR_GPIOCSMEN);
    }
    else
    {
        bit::flag::clear(&(RCC->IOPSMENR), RCC_IOPSMENR_GPIOCSMEN);
    }
}
template<> void rcc<GPIO, 3>::disable()
{
    bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIOCEN);
}

template<> void GPIO::Alternate_function::enable<GPIO::mco>(Limited<std::uint32_t, 0, 15> a_id,
                                                            const Enable_config& a_config,
                                                            Pin* a_p_pin)
{
    hkm_assert((0u == this->p_port->idx && 8u == a_id) || (1u == this->p_port->idx && 6u == a_id));

    this->enable(a_id, a_config, 0x0u, a_p_pin);
}

} // namespace xmcu::soc::m0::l0::rm0451