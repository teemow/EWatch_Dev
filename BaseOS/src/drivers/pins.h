// Central pin map for EWatch v2 (ESP32-S3FH4R2).
// Every pin number here was verified against EWatch_Final.net (rev 2.0).
#pragma once

// ============================================================================
// Waveshare ESP32-S3-Touch-LCD-1.69 (build with -DEWATCH_BOARD_WS169=1,
// env:ws169). Same ST7789 240x280 panel and CST816 touch as the EWatch, so
// only the wiring differs. Pins from https://docs.waveshare.com/ESP32-S3-Touch-LCD-1.69
// The IMU (QMI8658 @0x6B) and RTC (PCF85063 @0x51) are different chips from
// the EWatch's MMA8451/RV-3028; their drivers will not find them and the
// firmware runs without motion wake and without RTC time.
// ============================================================================
#if defined(EWATCH_BOARD_WS169) && EWATCH_BOARD_WS169

#define PIN_LDO_LATCH    41   // SYS_EN: HIGH holds the battery power path on
#define PIN_BTN           0   // BOOT key (active-low); SYS_OUT/GPIO40 reads high while powered
#define BTN_ACTIVE_LEVEL LOW

#define PIN_I2C_SDA      11
#define PIN_I2C_SCL      10
#define I2C_FREQ_HZ  400000

#define PIN_DISP_SCK      6
#define PIN_DISP_MOSI     7
#define PIN_DISP_MISO    -1
#define PIN_DISP_DC       4
#define PIN_DISP_CS       5
#define PIN_DISP_RST      8
#define PIN_DISP_BL      15   // HIGH = backlight on

#define PIN_TOUCH_RST    13
#define PIN_TOUCH_INT    14

// No vibration motor on this board: route the haptic PWM to the buzzer so
// taps still give feedback; EN goes to a free pin.
#define PIN_MOTOR_EN     21
#define PIN_MOTOR_PWM    42

#define PIN_BAT_MON_EN   16   // free pin; the board's divider is always on
#define PIN_BAT_MON_ADC   1   // BAT_ADC, ADC1_CH0

#define PIN_RTC_INT      39
#define PIN_MMA_INT1     38   // QMI8658 INT1 (not an MMA8451; driver stays idle)
#define PIN_MMA_INT2     17   // free pin

#define I2C_ADDR_RV3028     0x52
#define I2C_ADDR_MMA8451_A  0x1C
#define I2C_ADDR_MMA8451_B  0x1D
#define I2C_ADDR_TOUCH      0x15

#else  // ---- EWatch v2 (custom board) --------------------------------------

// ---- Power -------------------------------------------------------------
#define PIN_LDO_LATCH    17   // drives D3 -> LDO_EN; HIGH keeps watch on
#define PIN_BTN          18   // SW2; HIGH while user is pressing
#define BTN_ACTIVE_LEVEL HIGH

// ---- I2C bus (shared: RTC + accel + touch) -----------------------------
#define PIN_I2C_SDA       8
#define PIN_I2C_SCL       9
#define I2C_FREQ_HZ  400000

// ---- Display (ST7789 240x280 IPS over FSPI) ----------------------------
#define PIN_DISP_SCK     10
#define PIN_DISP_MOSI    11
#define PIN_DISP_MISO    -1   // not used (write-only)
#define PIN_DISP_DC       6
#define PIN_DISP_CS       7
#define PIN_DISP_RST     12
#define PIN_DISP_BL      21   // drives S8050 NPN base -> HIGH = backlight ON

// ---- Touch (CST816S, INT/RST private; data over the shared I2C bus) ----
#define PIN_TOUCH_RST    13
#define PIN_TOUCH_INT    14

// ---- Haptic (DRV2603) --------------------------------------------------
#define PIN_MOTOR_EN     38   // EN: HIGH enables driver
#define PIN_MOTOR_PWM    37   // IN: PWM signal becomes vibration

// ---- Battery monitor ---------------------------------------------------
// NOTE: GPIO34 on the schematic is not ADC-capable on the ESP32-S3. A bodge
// wire reroutes the divider tap from GPIO34 -> GPIO5 (ADC1_CH4 on S3).
#define PIN_BAT_MON_EN   33   // HIGH enables the divider (saves quiescent)
#define PIN_BAT_MON_ADC   5   // bodge wire from GPIO34; ADC1_CH4 on S3

// ---- Peripheral interrupts --------------------------------------------
#define PIN_RTC_INT       2   // RV-3028 INT (active low)
#define PIN_MMA_INT1      3   // ⚠ also JTAG strap; MMA defaults inactive at boot
#define PIN_MMA_INT2      4

// ---- I2C addresses -----------------------------------------------------
#define I2C_ADDR_RV3028     0x52
#define I2C_ADDR_MMA8451_A  0x1C   // MMA8451 SA0 = 0
#define I2C_ADDR_MMA8451_B  0x1D   // MMA8451 SA0 = 1
#define I2C_ADDR_TOUCH      0x15   // CST816S

#endif  // EWATCH_BOARD_WS169
