# CMake generated Testfile for 
# Source directory: /home/bcloud/shelf
# Build directory: /home/bcloud/shelf/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[appstreamtest]=] "/usr/bin/cmake" "-DAPPSTREAMCLI=/usr/bin/appstreamcli" "-DINSTALL_FILES=/home/bcloud/shelf/build/install_manifest.txt" "-P" "/usr/share/ECM/kde-modules/appstreamtest.cmake")
set_tests_properties([=[appstreamtest]=] PROPERTIES  _BACKTRACE_TRIPLES "/usr/share/ECM/kde-modules/KDECMakeSettings.cmake;173;add_test;/usr/share/ECM/kde-modules/KDECMakeSettings.cmake;191;appstreamtest;/usr/share/ECM/kde-modules/KDECMakeSettings.cmake;0;;/home/bcloud/shelf/CMakeLists.txt;13;include;/home/bcloud/shelf/CMakeLists.txt;0;")
