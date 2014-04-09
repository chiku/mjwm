#!/bin/sh

ls -hal mjwm
strip -sxXv mjwm
ls -hal mjwm
upx -9 --ultra-brute -v mjwm
ls -hal mjwm
