#
# Copyright 2017 Intel(R) Nervana(TM)
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

set(AEON_SERVICE_SOURCES main.cpp service.cpp)
set(AEON_SERVICE_HEADERS log.hpp pidfile.hpp service.hpp)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(aeon-service ${AEON_SERVICE_SOURCES} ${AEON_SERVICE_HEADERS})
target_link_libraries(aeon-service aeon ${CMAKE_THREAD_LIBS_INIT}
        ${Boost_LIBRARIES} ${CPPREST_LIBRARIES} ${OPENSSL_LIBRARIES})

install(TARGETS aeon-service DESTINATION sbin)
# we need to run ldconfig to make aeon library visible for aeon-service
install(CODE "execute_process(COMMAND ldconfig)")
