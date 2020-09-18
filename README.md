# Raspip
This is a simple tool for getting Raspberry Pi's IP address. The server side would listen on specific port and waiting for client to send its IP address, and it's written in Node.js. While the client side would be register as a system service to send IP to server.

## Requirements

- Node.js v12+ (Server)
- CMake 3.10+ (Client)

## Installation

### Server

```bash
$ npm i
$ node index.js
```

Then, you can visit `http://localhost:3000/` and wait for client.

### Client

First, you need to modify `raspip.cc` to change the value of `remoteServer`.

```bash
$ bash install.sh
```

Then, our binary file will be placed at `/usr/local/bin/raspip` and register as a service. If you reboot your Raspberry Pi, it would automatically run.

## For BUPT Students

We support login to school Wi-Fi, the difference with normal installation steps is showed below:

You should not only modify the remote server, but also change the definition of WIFIUSER and WIFIPASSWD in the first lines. Then, run following command instead.

```bash
$ bash install.sh bupt
```

## Thanks

- [HTTPRequest](https://github.com/elnormous/HTTPRequest)