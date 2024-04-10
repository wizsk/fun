#!/bin/sh

ls | grep '.ppm' | sed 's/.ppm//' | xargs -Ixx convert xx.ppm -quality 80 xx.jpg
ls | grep '.ppm' | sed 's/.ppm//' | xargs -Ixx convert xx.ppm xx.png
