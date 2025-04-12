# nRF Connect SDK - LED Control with Button Interrupt

This project demonstrates how to use **GPIO interrupt handling** using the **nRF Connect SDK**. When the button is pressed, an LED toggles its state.

## 🔧 Tools & Environment

- **Board Used:** [nRF52840 DK]
- **SDK:** nRF Connect SDK (v2.90)
- **IDE:** Visual Studio Code with nRF Connect Extension
- **Toolchain:** 2.90


## 🚀 How It Works

- Configures a GPIO pin as input for the button.
- Configures another GPIO pin as output for the LED.
- On button press (falling edge), an interrupt is triggered.
- In the ISR, the LED is toggled.

## 🧠 What I Learned

- Setting up an nRF Connect SDK project in VS Code
- Configuring GPIO with Zephyr
- Writing and registering interrupt service routines (ISRs)
- Using `devicetree` and `gpio_dt_spec` in Zephyr

Check out the demo video: [Demo on Google Photos](https://photos.app.goo.gl/GDo9bxfGxcSJ9TUg6)
