#!/bin/sh

GREEN='\033[0;32m'
RESET='\033[0m'

DEPENDENCIES='make libgtest-dev'

install_deps() {
	echo "${GREEN}Installing required dependencies...${RESET}"
	sudo apt-get install ${DEPENDENCIES}
}

build_install_gtest() {
	echo "${GREEN}Setting up Google Test...${RESET}"
	cd /usr/src/gtest
	sudo cmake CMakeLists.txt
	sudo make
	sudo cp *.a /usr/lib
	echo "${GREEN}GTest successfully compiled and installed! You may now compile.${RESET}"
}

main() {
	install_deps
	build_install_gtest
}

main



