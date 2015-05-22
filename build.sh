#!/bin/bash

sudo rm /var/log/istatd.log
make OPT= CXX=clang++-3.7 -j8
sudo /etc/init.d/istatd stop
sudo cp bin/istatd /usr/bin/istatd
sudo /etc/init.d/istatd start
