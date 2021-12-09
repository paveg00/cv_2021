# from __future__ import print_function

import numpy as np

from PyMedianFilter import PyMedianFilter

# check correct building of module(just import)

def check_process_easy():
    image = np.array([[0, 2], [0, 3]])
    worker = PyMedianFilter()
    res = np.array(worker.process_easy(image, 1))
    print("MedianFilter: ", res)

check_process_easy()
