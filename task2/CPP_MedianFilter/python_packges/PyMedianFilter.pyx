# distutils: language = c++
# distutils: sources = ../lib/MedianFilter.cpp

# Cython interface file for wrapping the object
#
#

from libcpp.vector cimport vector

# c++ interface to cython
cdef extern from "../lib/MedianFilter.h" namespace "my_cv":
  cdef cppclass MedianFilter:
        MedianFilter() except +
        vector[vector[int]] process_easy(vector[vector[int]], int)
        vector[vector[int]] process_medium(vector[vector[int]], int)
        vector[vector[int]] process_hard(vector[vector[int]], int)
        vector[vector[int]] process(vector[vector[int]])

# creating a cython wrapper class
cdef class PyMedianFilter:
    cdef MedianFilter *thisptr      # hold a C++ instance which we're wrapping
    def __cinit__(self):
        self.thisptr = new MedianFilter()
    def __dealloc__(self):
        del self.thisptr
    def help(self):
        return '''
        This is class to process Median filter 
        with 3 different algorithms
        '''
    def process_easy(self, image, r):
        return self.thisptr.process_easy(image, r)
    def process_medium(self, image, r):
        return self.thisptr.process_medium(image, r)
    def process_hard(self, image, r):
        return self.thisptr.process_hard(image, r)
