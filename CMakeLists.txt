cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(ErysEdits VERSION 1.0.0)

add_library(
	${PROJECT_NAME} SHARED
	src/main.cpp
	
	src/Manager.cpp
	src/Utils.cpp

	src/CCKeyboardDispatcher.cpp
	src/CommentCell.cpp
	src/CreatorLayer.cpp
	src/CustomListView.cpp
	src/EditLevelLayer.cpp
	src/EditorPauseLayer.cpp
	src/EditorUI.cpp
	src/EffectGameObject.cpp
	src/EndLevelLayer.cpp
	src/FMODAudioEngine.cpp
	src/GameManager.cpp
	src/GJBaseGameLayer.cpp
	src/GJGarageLayer.cpp
	src/InfoLayer.cpp
	src/LeaderboardsLayer.cpp
	src/LevelBrowserLayer.cpp
	src/LevelCell.cpp
	src/LevelEditorLayer.cpp
	src/LevelInfoLayer.cpp
	src/LevelLeaderboard.cpp
	src/LevelListLayer.cpp
	src/LevelPage.cpp
	src/LikeItemLayer.cpp
	src/OptionsLayer.cpp
	src/PlayerObject.cpp
	src/PlayLayer.cpp
	src/ProfilePage.cpp
	src/SecretRewardsLayer.cpp
	src/SetIDPopup.cpp
	)

if (NOT DEFINED ENV{GEODE_SDK})
	message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
	message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})