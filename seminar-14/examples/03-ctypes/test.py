from ctypes import cdll
from ctypes import c_float

lib = cdll.LoadLibrary("./lib_sum_utils.so")
assert 23 + 42 == lib.sum_ints(23, 42)

lib.sum_floats.restype = c_float
lib.sum_floats.argtypes = [c_float, c_float]
assert 23.0 + 42.0 == lib.sum_floats(23, 42)
