include_directories(${QUADCOPTER_SOURCE_DIR}/include)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -O3 -std=gnu11")
add_library(I2CDEVICE GY80.c PCA9685PW.c I2CControl.c)
add_library(RF24WT RF24.cpp spi.cpp compatibility.c RF24_Interface.cpp MCP3008.c SPIControl.c)
link_directories(${QUADCOPTER_SOURCE_DIR}/src)
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
SET(BUILD_SHARED_LIBRARIES OFF)
SET(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(QUADCOPTER Common.c Calibration.c main.c Device.c PID.c Filter_Digital.c AHRS.c Filter_Kalman.c)
#add_executable(QUADCOPTER Common.c main.c)
target_link_libraries(QUADCOPTER RF24WT I2CDEVICE -lbcm2835 -lgsl -lgslcblas -lrt -lm -lpthread)
