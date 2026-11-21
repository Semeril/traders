cmake_minimum_required(VERSION 4.4.5)
project(traders CXX)

add_executable(traders src/main.cxx)

include(FetchContent)

FetchContent_Declare(
	scmdr
	GIT_REPOSITORY
	https://github.com/Semeril/scmdr.git
	GIT_TAG
	v1.0
	SYSTEM
)
FetchContent_MakeAvailable(scmdr)

FetchContent_Declare(
	entt
	GIT_REPOSITORY
	https://github.com/skypjack/entt.git
	GIT_TAG
	v3.13.x
	SYSTEM
)
FetchContent_MakeAvailable(entt)

FetchContent_Declare(
	keyboard-plus-plus
	GIT_REPOSITORY
	https://github.com/Semeril/keyboard-plus-plus.git
	GIT_TAG
	main
	SYSTEM
)
FetchContent_MakeAvailable(keyboard-plus-plus)

target_link_libraries(traders
	PRIVATE
		scmdr::scmdr
		EnTT::EnTT
		keyboard-plus-plus
)