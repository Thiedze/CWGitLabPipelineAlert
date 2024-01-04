import json
import time
import threading
import datetime

from gitlab_service import GitLabService
from led_strip_service import LedStripeService
from status import Status

def get_status():
    while True:
        try:
            gitlab_service.set_pipeline_status()
            time.sleep(30)
        except:
            print("Error")


def update_led_stripe():
    now = datetime.datetime.now()
    today8am = now.replace(hour=8, minute=0, second=0, microsecond=0)
    today630pm = now.replace(hour=16, minute=30, second=0, microsecond=0)

    fade_in_counter = 0
    led_counter = 0
    direction = 1
    while True:
        now = datetime.datetime.now()
        if now > today8am and now < today630pm:
            if gitlab_service.status in [Status.CREATED, Status.RUNNING, Status.SCHEDULED]:
                sleep_timer, fade_in_counter, direction = (
                    led_stripe_service.update_led_waiting_status(fade_in_counter, direction))
            elif gitlab_service.status == Status.SUCCESS:
                sleep_timer = led_stripe_service.update_led_success_status()
            elif gitlab_service.status == Status.FAILED:
                sleep_timer = led_stripe_service.update_led_failed_status()
            elif gitlab_service.status == Status.UNKNOWN:
                sleep_timer, led_counter, direction = led_stripe_service.update_led_unknown_status(led_counter, direction)
            else:
                sleep_timer = led_stripe_service.update_led_all_other_status()
        else:
            sleep_timer = led_stripe_service.night_mode()
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
