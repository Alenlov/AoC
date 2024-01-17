import numpy as np
from scipy.optimize import fsolve
import sys

with open(sys.argv[1]) as f:
    lines = f.read().splitlines()

for i in range(3):
    