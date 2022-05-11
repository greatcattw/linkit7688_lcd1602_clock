#!/bin/sh
echo -e -n "\r1234567890" > /proc/LCDI2C
sleep 1

echo -e -n "      abcde" > /proc/LCDI2C
sleep 1

sleep 1
echo -e -n "\r123456789012345678901234567890ab" > /proc/LCDI2C

sleep 1
echo -e -n "\rabcdefghijklmnopqrstuvwxyz123456" > /proc/LCDI2C

echo -e -n "\rABCDEFGHIJKLMNOPQRSTUVWXYZ123456" > /proc/LCDI2C
sleep 1

#off backlight
echo -e -n "\b" > /proc/LCDI2C
sleep 1

#on backlight
echo -e -n "\a" > /proc/LCDI2C
sleep 1

