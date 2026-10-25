#include <stdint.h>

#define RCC_AHB2ENR (*(volatile uint32_t *)0x4002104CUL)
#define GPIOA_MODER (*(volatile uint32_t *)0x48000000UL)
#define GPIOA_BSRR  (*(volatile uint32_t *)0x48000018UL)
#define GPIOC_MODER (*(volatile uint32_t *)0x48000800UL)
#define GPIOC_PUPDR (*(volatile uint32_t *)0x4800080CUL)
#define GPIOC_IDR   (*(volatile uint32_t *)0x48000810UL)
#define SYST_CSR    (*(volatile uint32_t *)0xE000E010UL)
#define SYST_RVR    (*(volatile uint32_t *)0xE000E014UL)
#define SYST_CVR    (*(volatile uint32_t *)0xE000E018UL)

#define USER_LED_PIN 5U
#define USER_BUTTON_PIN 13U

static volatile uint32_t milliseconds;

void SysTick_Handler(void)
{
    ++milliseconds;
}

int main(void)
{
    RCC_AHB2ENR |= (1U << 0) | (1U << 2);
    (void)RCC_AHB2ENR;

    GPIOA_MODER = (GPIOA_MODER & ~(3U << (USER_LED_PIN * 2U)))
        | (1U << (USER_LED_PIN * 2U));
    GPIOA_BSRR = 1U << (USER_LED_PIN + 16U);

    GPIOC_MODER &= ~(3U << (USER_BUTTON_PIN * 2U));
    GPIOC_PUPDR = (GPIOC_PUPDR & ~(3U << (USER_BUTTON_PIN * 2U)))
        | (2U << (USER_BUTTON_PIN * 2U));

    SYST_RVR = 16000U - 1U;
    SYST_CVR = 0U;
    SYST_CSR = 7U;

    uint32_t last_sample = 0U;
    uint32_t candidate_since = 0U;
    uint8_t candidate_pressed = 0U;
    uint8_t button_pressed = 0U;
    uint8_t blinking = 1U;
    uint8_t led_on = 0U;
    uint32_t last_led_toggle = 0U;

    for (;;) {
        uint32_t now = milliseconds;

        if ((uint32_t)(now - last_sample) >= 10U) {
            last_sample = now;
            uint8_t sampled_pressed =
                (GPIOC_IDR & (1U << USER_BUTTON_PIN)) != 0U;

            if (sampled_pressed != candidate_pressed) {
                candidate_pressed = sampled_pressed;
                candidate_since = now;
            } else if (candidate_pressed != button_pressed
                && (uint32_t)(now - candidate_since) >= 20U) {
                button_pressed = candidate_pressed;
                if (button_pressed) {
                    blinking = !blinking;
                    led_on = 0U;
                    GPIOA_BSRR = 1U << (USER_LED_PIN + 16U);
                    last_led_toggle = now;
                }
            }
        }

        if (blinking && (uint32_t)(now - last_led_toggle) >= 100U) {
            last_led_toggle = now;
            led_on = !led_on;
            GPIOA_BSRR = led_on
                ? (1U << USER_LED_PIN)
                : (1U << (USER_LED_PIN + 16U));
        }

        __asm volatile("wfi");
    }
}
