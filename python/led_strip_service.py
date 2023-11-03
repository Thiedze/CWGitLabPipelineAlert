import board
import neopixel


class LedStripeService:

    def __init__(self):
        self.led_counter = 30
        self.brightness = 80
        self.pixels = neopixel.NeoPixel(board.D18, self.led_counter)

    def update_led_failed_status(self):
        if self.pixels[0] == [self.brightness, 0, 0]:
            self.pixels.fill([0, 0, 0])
        else:
            self.pixels.fill([self.brightness, 0, 0])
        return 0.5

    def update_led_success_status(self):
        self.pixels.fill([0, self.brightness, 0])
        return 10

    def update_led_waiting_status(self, fade_in_counter, direction):
        fade_in_counter += 1 * direction

        if fade_in_counter <= 0 or fade_in_counter >= self.brightness:
            direction *= -1

        self.pixels.fill([0, 0, fade_in_counter])
        return 0.04, fade_in_counter, direction

    def update_led_unknown_status(self, led_counter, direction):
        led_counter += 1 * direction

        if led_counter < 0 or led_counter > self.led_counter:
            direction *= -1

        for index in range(0, self.led_counter):
            if index < led_counter:
                self.pixels[index] = [self.brightness, self.brightness, 0]
            else:
                self.pixels[index] = [0, 0, 0]
        return 0, led_counter, direction

    def update_led_all_other_status(self):
        self.pixels.fill([0, self.brightness, self.brightness])
        return 10
