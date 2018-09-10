#!/bin/bash

arduino --board arduino:avr:leonardo --pref build.path=./build --verify ArduMuni.ino && ProjectABE build/ArduMuni.ino.hex 
