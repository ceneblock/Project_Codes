# Concurrent Data Acquisition On-Board a Raspberry Pi

## Description

This project design, implement and evaluate a system software framework, written in C++, for collecting sensor data concurrently from a Raspberry Pi. 

This repository includes 2 folders and 20 files. The main code of this project is in the Concurrent_Data_Acquisition folder, which is used to display videos by the LED matrix, 
collect data concurrently from the SenseHAT Board and capture images by Raspberry Pi camera. The code in the Plots folder is used to plot figures of sensed values and latency.

## Built With

[SenseHat](https://github.com/PhilippeSimier/SenseHat) - offers a C ++ class for the SenseHat on Raspberry pi

[RTIMULib](https://github.com/RPi-Distro/RTIMULib) - a versatile C++ IMU library

[RaspiCam](https://github.com/rmsalinas/raspicam) - provides class RaspiCam for easy and full control of the camera

[matplotlib-cpp](https://github.com/Cryoris/matplotlib-cpp) - a simplest C++ plotting library

## Getting Started

### Prerequisites

```bash
sudo apt-get install i2c-tools
sudo apt-get install cmake
sudo apt-get install python3 python3-dev
sudo pip3 install matplotlib
```

### Installation

Build and install the RTIMULib library:

```bash
git clone https://github.com/RPi-Distro/RTIMULib.git
cd RTIMULib
mkdir build
cd build
cmake ..
make -j4
sudo make install
sudo ldconfig
```

Build and install the SenseHat library:

```bash
git clone https://github.com/PhilippeSimier/SenseHat.git
cd SenseHat/
make
sudo make install
make clean
```

Build and install the RaspiCam:

```bash
git clone https://github.com/rmsalinas/raspicam.git
cd raspicam
mkdir build
cd build
cmake ..
```

## How To Compile

Compile the main.cpp in the Concurrent_Data_Acquisition folder:

```bash
g++ main.cpp -std=c++11 -Wno-psabi -l SenseHat -l RTIMULib -lpthread -lraspicam -o main
```

Compile the plot_value.cpp/plot_latency.cpp in the Plots folder:

```bash
g++ plot_value.cpp/plot_latency.cpp -std=c++11 -I/usr/include/python2.7 -lpython2.7 -Wno-psabi -l SenseHat -l RTIMULib -lpthread -lraspicam -o plot_value/plot_latency
```

## Test Result

Run the main program in the Concurrent_Data_Acquisition and the result of it meets our expectations. I use all hardware to test.

1. LED Matrix displays like a progress bar
2. All sensors on the SenseHAT Board are initialized
3. Print out the average value and collecting duration of sensors' data
4. Save a image the raspberry pi camera captures

## License

[GNU General Public License, version 2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)
