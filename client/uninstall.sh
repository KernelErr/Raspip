#! /bin/bash
sudo systemctl disable raspip.service
sudo rm /usr/local/bin/raspip
sudo rm /lib/systemd/system/raspip.service
sudo systemctl daemon-reload