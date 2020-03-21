#!/bin/bash

rm -rf ~/work/qmk_firmware/keyboards/fan90
cp -aurf ~/work/fan90/fan90 ~/work/qmk_firmware/keyboards
cd ~/work/qmk_firmware
make fan90:default:avrdude

