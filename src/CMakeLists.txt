include_directories(${BACKUPCAMERA_SOURCE_DIR}/src)
link_directories(${BACKUPCAMERA_BINARY_DIR}/src)

add_library(graphics graphics_handler.cpp)
add_library(video videoStream.cpp)
add_library(camera backup_camera.cpp)

target_link_libraries(camera video graphics)
target_link_libraries(video ${OpenCV_LIBS})

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(BackupCamera main.cpp)
target_link_libraries(BackupCamera ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${OpenCV_LIBS} graphics video camera  -lpthread)
