cmake_minimum_required(VERSION 2.6)
PROJECT(cam_opencv)

find_package( OpenCV REQUIRED )


set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include )
set(CAM_OPENCV_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

)

set(CAM_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/cam.cpp

)

set(FILTER_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/filter.cpp

)

set(MANIPULATION_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/manipulation.cpp

)

include_directories(${PROJECT_INCLUDE_DIR})

ADD_LIBRARY(cam
  ${CAM_SOURCES}
)

ADD_LIBRARY(filter
  ${FILTER_SOURCES}
)

ADD_LIBRARY(manipulation
  ${MANIPULATION_SOURCES}
)

ADD_EXECUTABLE(cam_opencv
  ${CAM_OPENCV_SOURCES}
)

TARGET_LINK_LIBRARIES(filter
  ${OpenCV_LIBS} 
)

TARGET_LINK_LIBRARIES(manipulation
  ${OpenCV_LIBS}
)

TARGET_LINK_LIBRARIES(cam
  ${OpenCV_LIBS} 
)

TARGET_LINK_LIBRARIES(cam_opencv
  ${OpenCV_LIBS} 
  cam
  filter
  manipulation
)
