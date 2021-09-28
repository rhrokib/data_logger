import os
import requests
import serial
import time


writeAPIkey = "FMADOBAT0J1G28C5"
channelID = "1518679"
url = "https://api.thingspeak.com/update?api_key=FMADOBAT0J1G28C5"


def get_data():
    ser = serial.Serial('COM3', 9600, timeout=1)
    while True:
        x = ser.readline().decode('ascii')
        if len(x) > 0:
            try:
                data = x.split(',')

                distance = float(data[0])
                temperature = float(data[1])
                humidity = float(data[2])
                light_intensity = float(data[3])

                return [int(distance), int(float(temperature)), int(float(humidity)), int(float(light_intensity))]

            except Exception as e:
                print(e)


def send_to_cloud():
    writeURL = url
    data = get_data()

    for i, d in enumerate(data):
        writeURL += f'&field{i+1}={d}'

    # print(writeURL)
    r = requests.get(writeURL)
    if r.status_code == 200:
        print('[200 OK] UPLOADED')
    else:
        print('[ERROR] Really?')


if __name__ == '__main__':
    while True:
        send_to_cloud()
        time.sleep(20)