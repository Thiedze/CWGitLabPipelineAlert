import board
import neopixel


class LedStripeService:

    def __init__(self):
        self.pixels = neopixel.NeoPixel(board.D18, 30)
