import json
import time
import threading

from gitlab_service import GitLabService
from led_strip_service import LedStripeService
from status import Status


def get_status():
    while True:
        gitlab_service.set_pipeline_status()
        time.sleep(30)


def update_led_stripe():
    fade_in_counter = 1
    fade_in_direction = 1
    brightness = 80
    while True:
        if gitlab_service.status in [Status.CREATED, Status.RUNNING, Status.SCHEDULED]:
            sleep_timer = 0.04
            if fade_in_counter >= brightness or fade_in_counter <= 0:
                fade_in_direction *= -1
            fade_in_counter += 1 * fade_in_direction

            led_stripe_service.pixels.fill([0, 0, fade_in_counter])
        elif gitlab_service.status == Status.SUCCESS:
            sleep_timer = 10
            led_stripe_service.pixels.fill([0, brightness, 0])
        elif gitlab_service.status == Status.FAILED:
            sleep_timer = 0.5
            if led_stripe_service.pixels[0] == [brightness, 0, 0]:
                led_stripe_service.pixels.fill([0, 0, 0])
            else:
                led_stripe_service.pixels.fill([brightness, 0, 0])
        else:
            sleep_timer = 10
            led_stripe_service.pixels.fill([brightness, brightness, 0])
        time.sleep(sleep_timer)


if __name__ == '__main__':
    file = open('/home/pi/CWGitLabPipelineAlert/python/config.json')
    config = json.load(file)

    gitlab_service = GitLabService(config['base_url'], config['access_token'], config['project_id'])
    led_stripe_service = LedStripeService()

    get_status_thread = threading.Thread(target=get_status)
    get_status_thread.start()

    update_led_stripe_thread = threading.Thread(target=update_led_stripe)
    update_led_stripe_thread.start()
