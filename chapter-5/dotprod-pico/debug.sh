#!/bin/bash

openocd -f $PICO_SDK_PATH/../openocd/tcl/interface/raspberrypi-swd.cfg -f $PICO_SDK_PATH/../openocd/tcl/target/rp2040.cfg 

