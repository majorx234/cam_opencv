cmake_minimum_required(VERSION 2.6)
PROJECT(cam_opencv)

find_package( OpenCV REQUIRED )
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Threads REQUIRED)

QT5_WRAP_CPP( QT_DISPLAY_PARAMETERS_WINDOW_MOCsrcs
              ${CMAKE_CURRENT_SOURCE_DIR}/src/qt_display_parameters_window.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/include/qt_display_parameters_window.h)

QT5_WRAP_CPP(mainMOCsrcs
   ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/qt_display_parameters_window.h
)

QT5_WRAP_CPP(CVMAT2QIMAGE_MOCsrcs
  ${CMAKE_CURRENT_SOURCE_DIR}/src/cvmat2qimage.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/cvmat2qimage.h
)

QT5_WRAP_CPP(QT_IMAGE_VIEW_MOCsrcs
  ${CMAKE_CURRENT_SOURCE_DIR}/src/qt_image_view.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/qt_image_view.h
)

QT5_WRAP_CPP(QT_CAM_OPENCV_CONTROLLER_MOCsrcs
  ${CMAKE_CURRENT_SOURCE_DIR}/src/qt_cam_opencv_controller.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/qt_cam_opencv_controller.h
)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include )


set(CAM_OPENCV_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

)

set(CAM_OPENCV_MVC_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_mvc.cpp

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

set(CVMAT2QIMAGE_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/cvmat2qimage.cpp
)

set(QT_DISPLAY_PARAMETERS_WINDOW_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/qt_display_parameters_window.cpp
)

set(QT_IMAGE_VIEW_SOURCES
 ${CMAKE_CURRENT_SOURCE_DIR}/src/qt_image_view.cpp
)

set(IMAGE_MANIPULATION_MODEL_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/image_manipulation_model.cpp
)

set(QT_CAM_OPENCV_CONTROLLER_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/qt_cam_opencv_controller.cpp
)
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(include)

ADD_LIBRARY(cam
  ${CAM_SOURCES}
)


ADD_LIBRARY(filter
  ${FILTER_SOURCES}
)

ADD_LIBRARY(manipulation
  ${MANIPULATION_SOURCES}
)

ADD_LIBRARY(cvmat2qimage
  ${CVMAT2QIMAGE_MOCsrcs}
  ${CVMAT2QIMAGE_SOURCES}

)

ADD_LIBRARY(QtDisplayParametersWindow
  ${QT_DISPLAY_PARAMETERS_WINDOW_MOCsrcs}
  ${QT_DISPLAY_PARAMETERS_WINDOW_SOURCES}
)

ADD_LIBRARY(qt_image_view
 ${QT_IMAGE_VIEW_MOCsrcs}
 ${QT_IMAGE_VIEW_SOURCES}
)

ADD_LIBRARY(image_manipulation_model
  ${IMAGE_MANIPULATION_MODEL_SOURCES}
)

ADD_LIBRARY(qt_cam_opencv_controller
  ${QT_CAM_OPENCV_CONTROLLER_MOCsrcs}
  ${QT_CAM_OPENCV_CONTROLLER_SOURCES}
)

ADD_EXECUTABLE(qt_cam_opencv
  ${mainMOCsrcs}
  ${CAM_OPENCV_SOURCES}

)

ADD_EXECUTABLE(qt_cam_opencv_mvc
  ${CAM_OPENCV_MVC_SOURCES}

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

TARGET_LINK_LIBRARIES(qt_cam_opencv
  ${OpenCV_LIBS} 
  QtDisplayParametersWindow
  cam
  filter
  manipulation
  cvmat2qimage
  ${CMAKE_THREAD_LIBS_INIT} 
)

TARGET_LINK_LIBRARIES(qt_image_view
  QtDisplayParametersWindow
  manipulation
  ${CMAKE_THREAD_LIBS_INIT} 
)

TARGET_LINK_LIBRARIES(image_manipulation_model
  ${OpenCV_LIBS} 
  cam
  filter
  manipulation
)

TARGET_LINK_LIBRARIES(qt_cam_opencv_controller
  ${OpenCV_LIBS} 
  QtDisplayParametersWindow
  cam
  filter
  manipulation
  cvmat2qimage
  ${CMAKE_THREAD_LIBS_INIT} 
)

TARGET_LINK_LIBRARIES(qt_cam_opencv_mvc
  qt_cam_opencv_controller
  qt_image_view
  image_manipulation_model
)

qt5_use_modules(QtDisplayParametersWindow Core Gui Widgets)
qt5_use_modules(cvmat2qimage Core)
qt5_use_modules(qt_cam_opencv Core)
qt5_use_modules(qt_image_view Core)
qt5_use_modules(qt_cam_opencv_controller Core)