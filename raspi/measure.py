import os
import re
import yaml
from serial import Serial
from time import sleep
from datetime import datetime
from subprocess import call
from itertools import count

# may add argparse
## required
num_data = 3
## optional
sleep_sec = 60
baudrate = 115200
serial_port = path.join(os.sep, 'dev'. 'ttyACM0')
save_delta = 5

time_file_name = datetime.now().strftime('-%d-%m-%Y')
save_folder = os.path.join(os.getcwd(), "data")

ser = Serial(serial_port, baudrate)

class ArdString:
    def __init__(self, ard_string, num_data, start_char = '[', end_char = ']'):
        self.ard_string = str(ard_string)
        self.start_char, self.end_char = start_char, end_char
        self.num_data = num_data
    
    @property
    def has_start_end(self):
        if self.start_char not in self.ard_string or self.end_char not in self.ard_string:
            return False
        return True

    @property
    def is_valid_pack(self):
        if not self.has_start_end:
            return False
        if len(self.data_list) != self.num_data:
            return False
        return True
    
    @property
    def data_list(self):
        if not self.has_start_end:
            return []
        between_chars = self.ard_string.split(self.start_char)[1].split(self.end_char)[0]
        return [int(s) for s in re.findall("\\d+", between_chars)]

    @property
    def time_dict(self):
        data_dict = {'S{0}'.format(sensor_no): self.data_list[sensor_no] for sensor_no in range(len(self.data_list))}
        return {datetime.now().strftime('%m/%d/%Y/%H:%M:%S'): data_dict}


get_save_place = lambda: os.path.join(save_folder, "temperature_dump{0}.yaml".format(time_file_name))

#Loop through sensor data
for s in count(0):
    input_arduino = ser.readline() #Read Serial line
    ard_obj = ArdString(input_arduino)

    with open(get_save_place(), "a+") as yaml_file:
        if not ard_obj.is_valid_pack:
            continue
        print(ard_obj.time_dict)
        time_yaml = yaml.dumps(ard_obj.time_dict, indent = 4)
        yaml_file.write(time_yaml + "\n\n")

    if s % save_delta == 0:
        call(["rclone", "copy", save_folder, "grotech:"])

    sleep(sleep_sec)