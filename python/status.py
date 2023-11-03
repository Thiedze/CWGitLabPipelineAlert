from enum import Enum


class Status(Enum):
    UNKNOWN = 0
    CREATED = 1
    WAITING_FOR_RESOURCE = 2
    PREPARING = 3
    PENDING = 4
    RUNNING = 5
    SUCCESS = 6
    FAILED = 7
    CANCELED = 8
    SKIPPED = 9
    MANUAL = 10
    SCHEDULED = 11
