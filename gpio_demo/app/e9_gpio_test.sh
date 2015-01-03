#!/bin/sh

pin_no=$1

while :
do
echo $pin_no  > /sys/devices/platform/e9_gpio_output/gpio_high
sleep 1
echo $pin_no > /sys/devices/platform/e9_gpio_output/gpio_low
sleep 1
done

