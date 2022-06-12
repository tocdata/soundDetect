import RPi.GPIO as GPIO
import time
import urllib.request
import json
import datetime
from datetime import datetime

pin = 10
soundTrigger = 15

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(pin,GPIO.OUT)

try:
    while True:
        Feed1 = urllib.request.urlopen("https://api.thingspeak.com/channels/1694055/feeds.json?api_key=F5CQ7PVDE1TWRY58&results=1")
        data1 = json.load(Feed1)
        value = float(data1["feeds"][0]["field1"])
        createDate = data1["feeds"][0]["created_at"]
        date = createDate
        datetime_date = datetime.strptime(date, "%Y-%m-%dT%H:%M:%SZ")
        
        if (value > soundTrigger):
            print(datetime_date)
            print('sound detected, alarm triggered')
            for x in range(5):
                GPIO.output(pin, GPIO.HIGH)
                time.sleep(0.25)
                GPIO.output(pin, GPIO.LOW)
                time.sleep(0.25)
        time.sleep(5.25)
except KeyboardInterrupt:
    GPIO.cleanup()
exit()
GPIO.cleanup()
