import os
import math
import random
from tqdm import tqdm
import matplotlib.pyplot as plt

import fastf1
from fastf1.mvapi.api import get_circuit

YEAR = 2024

def fetch_calendar(year: int):
    """Fetches the F1 calendar for the specified year."""
    calendar = fastf1.get_event_schedule(year, include_testing=False)
    return calendar

def rotate_point(point, angle):
    x, y = point
    radians = math.radians(angle)
    x_rotated = x * math.cos(radians) - y * math.sin(radians)
    y_rotated = x * math.sin(radians) + y * math.cos(radians)
    return (x_rotated, y_rotated)

def outputCircuit(year: int, round: int, circuit_key: str):

    circuit = get_circuit(year=year, circuit_key=circuit_key)
    x = circuit.get('x', {})
    y = circuit.get('y', {})
    rotation = circuit.get('rotation', 0)

    output_config = (
        ('tiny', 50),
        ('small', 20),
        ('medium', 10),
        ('large', 5),
        ('huge', 1)
    )
    
    pos = list(zip(x, y))
    pos = [rotate_point(p, rotation) for p in pos]

    for size, step in tqdm(output_config, leave=False):

        if not os.path.exists(f'{size}'):
            os.makedirs(f'{size}')   

        sampled_pos = pos[::step]
        random.shuffle(sampled_pos)

        with open(f'{size}/{circuit_key}.txt', 'w+') as f:

            for i, (x, y) in enumerate(sampled_pos):
                f.write(f"{i+1} {int(x * 100)} {int(y * 100)}\n")
    

if __name__ == "__main__":
    
    fastf1.set_log_level('WARNING')

    calender = fetch_calendar(YEAR)

    for round in tqdm(range(1, calender.shape[0] + 1)):

        session = fastf1.get_session(YEAR, round, 'R')
        session.load(laps=False, telemetry=False, weather=False, messages=False)
        session_info = session.session_info
        circuit_key = session_info.get('Meeting', {}).get('Circuit', {}).get('Key', None)

        outputCircuit(YEAR, round, circuit_key)

