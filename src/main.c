#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* Get the device tree identifiers for button and LED */
#define LED0_NODE DT_ALIAS(led0)
#define BUTTON0_NODE DT_ALIAS(sw0)

/* GPIO descriptors */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(BUTTON0_NODE, gpios);

/* Button callback structure */
static struct gpio_callback button_cb_data;

/* Interrupt Service Routine */
void button_pressed(const struct device *dev, struct gpio_callback *cb,
                    uint32_t pins)
{
    gpio_pin_toggle_dt(&led);
    
    /* Optional: Add software debounce delay */
    k_msleep(50);
}

void main(void)
{
    int ret;

    /* Configure LED as output and turn it off initially */
    if (!device_is_ready(led.port)) {
        return;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        return;
    }

    /* Configure button as input with pull-up */
    if (!device_is_ready(button.port)) {
        return;
    }

    ret = gpio_pin_configure_dt(&button, GPIO_INPUT | GPIO_PULL_UP);
    if (ret < 0) {
        return;
    }

    /* Configure interrupt on falling edge (button press) */
    ret = gpio_pin_interrupt_configure_dt(&button,
                                         GPIO_INT_EDGE_FALLING);
    if (ret < 0) {
        return;
    }

    /* Initialize and register the callback */
    gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
    gpio_add_callback(button.port, &button_cb_data);

    /* Main loop does nothing - everything happens in interrupts */
    while (1) {
        /* Put CPU to sleep to save power */
        k_msleep(SLEEP_TIME_MS);
    }
}