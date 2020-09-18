#! /bin/bash
mkdir build
cd build

if [ -n "$1" ]; then
    if [[ "$1" == "bupt" ]]; then
        echo "Enable BUPT Login"
        cmake .. -DBUPT_LOGIN=ON
    fi
else
    cmake ..
fi

make
sudo make install

cat>raspip.service<<EOF
[Unit]
Description=Raspip Client Service
After=multi-user.target

[Service]
ExecStart=raspip

[Install]
WantedBy=multi-user.target
EOF

sudo mv raspip.service /lib/systemd/system/
sudo systemctl daemon-reload
sudo systemctl enable raspip.service