#!/usr/bin/env python
# vim: set fileencoding=utf-8 :
# Andre Anjos <andre.anjos@idiap.ch>
# Mon  7 Apr 09:25:43 2014 CEST
#
# Copyright (C) 2011-2014 Idiap Research Institute, Martigny, Switzerland

"""Tests some drawing on images
"""

import numpy
import nose.tools

from . import point, try_point, line#, box

def test_gray_point():

  # Tests single point drawing using gray-scaled images
  image = numpy.ndarray((100, 100), 'uint8')
  image.fill(0)

  # Draws a white point on the middle
  point(image, (50, 50), 255)
  nose.tools.eq_(image[50, 50], 255)

def test_does_not_raise_gray():

  image = numpy.ndarray((100, 100), 'uint8')
  image.fill(0)
  imcopy = image.copy()
  try_point(imcopy, (100, 100), 255)
  assert  numpy.array_equal(image, imcopy)  # no change is made

@nose.tools.raises(RuntimeError)
def test_raises_gray():

  image = numpy.ndarray((100, 100), 'uint8')
  point(image, (100, 100), 255)

def test_color_point():

  # color
  white = (255, 255, 255) #rgb
  a1    = numpy.ndarray((3,), 'uint8')
  a1.fill(255) #a comparision array

  # Tests single point drawing using gray-scaled images
  image = numpy.ndarray((3, 100, 100), 'uint8')
  image.fill(0)

  # Draws a white point on the middle
  point(image, (50, 50), white)
  assert numpy.array_equal(image[:,50, 50],a1)

def test_does_not_raise_color():

  image = numpy.ndarray((3, 100, 100), 'uint8')
  image.fill(0)
  imcopy = image.copy()
  try_point(imcopy, (100, 100), (255, 255, 255))
  assert numpy.array_equal(image, imcopy) # no change is made

@nose.tools.raises(RuntimeError)
def test_raises_color():

  image = numpy.ndarray((3, 100, 100), 'uint8')
  point(image, (100, 100), (255, 255, 255))

def test_line():

  # draws a gray line, test to see if works; note the same algorithm is used
  # for color line plotting, so we only test the gray one.

  image = numpy.ndarray((100, 100), 'uint8')
  image.fill(0)

  # Draws a white line on the middle (horizontal)
  line(image, (50, 50), (70, 50), 255)
  for k in range(50,70):
    nose.tools.eq_(image[k,50], 255)

  # Draws a white line on the middle (vertical)
  line(image, (50, 50), (50, 70), 230)
  for k in range(50,70):
    nose.tools.eq_(image[50,k], 230)

  # Draws a white line on the middle (horizontal, backwards)
  line(image, (70, 50), (50, 50), 128)
  for k in range(50,70):
    nose.tools.eq_(image[k,50], 128)

  # Draws a white line on the middle (vertical, backwards)
  line(image, (50, 70), (50, 50), 65)
  for k in range(50,70):
    nose.tools.eq_(image[50,k], 65)

def test_box():

  # draws a box on the image, only test gray as color uses the same
  # algorithm.

  image = numpy.ndarray((100, 100), 'uint8')
  image.fill(0)

  # Draws a white line on the middle (horizontal)
  box(image, 50, 50, 20, 20, 255)

  for k in range(50,70):
    nose.tools.eq_(image[k,50], 255)
    nose.tools.eq_(image[50,k], 255)
    nose.tools.eq_(image[k,70], 255)
    nose.tools.eq_(image[70,k], 255)
