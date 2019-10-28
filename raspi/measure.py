import os
import time
import serial
from time import sleep
from datetime import datetime
from subprocess import call
import re
import json

time_file_name = datetime.now().strftime('-%d-%m-%Y')
curr_dir = os.getcwd()
save_folder = os.path.join(curr_dir, "data")
save_place = os.path.join(save_folder, "temperature_dump{0}.json".format(time_file_name))
json_file = open(save_place, "a+")

ser = serial.Serial('/dev/ttyACM0', 115200) #Arduino Serial Port

#ser.write(b'8')
#while not ser.in_waiting:
#    ser.write(b'8')

class ArdString:
    def __init__(self, ard_string):
        self.ard_string = str(ard_string)
    
    @property
    def valid_pack(self, required_chars = ['[', ']'], num_data = 3):
        for char in required_chars:
            if char not in self.ard_string:
                return False
        arduino_ints = self.get_arduino_ints(start_char = required_chars[0], end_char = required_chars[-1])
        if len(arduino_ints) != num_data:
            print(arduino_ints)
            return False
        return True
    
    def get_arduino_ints(self, start_char = '[', end_char = ']'):
        after_start = self.ard_string.split(start_char)[1]
        before_end = after_start.split(end_char)[0]
        int_list = [int(s) for s in re.findall("\\d+", before_end)]
        return int_list

def get_time_dict(temp_list):
    temp_list = ard_obj.get_arduino_ints()
    temp_dict = {'S1': temp_list[0], 'S2': temp_list[1], 'S3': temp_list[2]}
    return {current_time.strftime('%m/%d/%Y/%H:%M:%S'): temp_dict}

#Loop through sensor data
while True:
    current_time = datetime.now() #Get Time
    input_arduino = ser.readline() #Read Serial line
    ard_obj = ArdString(input_arduino)
    if ard_obj.valid_pack:
        json_file = open(save_place, "a+")
        temp_list = ard_obj.get_arduino_ints()
        time_dict = get_time_dict(temp_list)
        print(time_dict)
        time_json = json.dumps(time_dict, indent = 4)
        json_file.write(time_json + "\n\n")
        json_file.close()
        call(["rclone", "copy", save_folder, "grotech:"])
    time.sleep(60) #grab data every min