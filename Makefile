#OBJS = files to compile
OBJS = src/main.cpp src/threadClass.hpp src/videoStream.cpp src/backup_camera.cpp src/graphics_handler.cpp


#CC = compiler used
CC = g++

#COMPLIE_FLAGS = additional flags
COMPILE_FLAGS = -g -std=c++0x -Wall

LINK_FLAGS = `sdl2-config --cflags` `sdl2-config --libs` `pkg-config opencv --cflags` `pkg-config opencv --libs` -lSDL2_image -pthread


#OUTPUT_NAME = final name
OUTPUT_NAME = BackupCamera

#INCLUDE FLAGS
INCLUDE_FLAGS = -Ilib -Iinclude

all :
	 $(CC) $(OBJS) $(INCLUDE_FLAGS) $(LINK_FLAGS) $(COMPILE_FLAGS) -o $(OUTPUT_NAME) -pthread

clean :
	rm BackupCamera

