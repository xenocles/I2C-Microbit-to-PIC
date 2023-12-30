// Makecode JS file for Microbit v2 with I2CMicrobitToPicDemo

input.onButtonPressed(Button.A, function () {
    number += -1
    basic.showNumber(number)
})
input.onButtonPressed(Button.AB, function () {
    number = 0
    basic.showNumber(number)
})
input.onButtonPressed(Button.B, function () {
    number += 1
    basic.showNumber(number)
})
input.onLogoEvent(TouchButtonEvent.Pressed, function () {
    pins.i2cWriteNumber(
    i2cAddress,
    number,
    NumberFormat.Int8LE,
    false
    )
})
/**
 * I2C address
 * 
 * (0x30 >> 1) = 24
 */
let temp = 0
let number = 0
let i2cAddress = 0
i2cAddress = 24
number = 0
basic.showNumber(number)
while (true) {
    temp = pins.i2cReadNumber(i2cAddress, NumberFormat.Int8LE, false)
    if (temp > 0) {
        number = temp
        basic.showNumber(number)
    }
    basic.pause(1000)
}
