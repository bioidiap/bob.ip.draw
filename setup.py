#!/usr/bin/env python
# vim: set fileencoding=utf-8 :
# Andre Anjos <andre.anjos@idiap.ch>
# Thu 30 Jan 08:45:49 2014 CET

from setuptools import setup, find_packages, dist
dist.Distribution(dict(setup_requires=['bob.blitz']))
from bob.blitz.extension import Extension

packages = ['boost']
version = '2.0.0a0'

setup(

    name='bob.ip.draw',
    version=version,
    description='Line and Box drawing utilities',
    url='http://github.com/bioidiap/bob.ip.draw',
    license='BSD',
    author='Andre Anjos',
    author_email='andre.anjos@idiap.ch',

    long_description=open('README.rst').read(),

    packages=find_packages(),
    include_package_data=True,

    install_requires=[
      'setuptools',
      'bob.blitz',
    ],

    namespace_packages=[
      "bob",
      "bob.ip",
      ],

    ext_modules = [
      Extension("bob.ip.draw.version",
        [
          "bob/ip/draw/version.cpp",
          ],
        version = version,
        packages = packages,
        ),
      Extension("bob.ip.draw._library",
        [
          "bob/ip/draw/point.cpp",
          "bob/ip/draw/try_point.cpp",
          "bob/ip/draw/line.cpp",
          "bob/ip/draw/cross.cpp",
          "bob/ip/draw/box.cpp",
          "bob/ip/draw/main.cpp",
          ],
        packages = packages,
        version = version,
        ),
      ],

    classifiers = [
      'Development Status :: 3 - Alpha',
      'Intended Audience :: Developers',
      'License :: OSI Approved :: BSD License',
      'Natural Language :: English',
      'Programming Language :: Python',
      'Programming Language :: Python :: 3',
      'Topic :: Software Development :: Libraries :: Python Modules',
      ],

    )
