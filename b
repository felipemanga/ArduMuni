#!/bin/bash

arduino --board arduino:avr:leonardo --pref build.path=./build --verify muni.ino && ProjectABE build/muni.ino.hex 
