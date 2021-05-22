set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

cmake_minimum_required(VERSION 3.5)

project(Asteroids VERSION 1.3.1)

link_directories(${CMAKE_SOURCE_DIR}/Dependencies/SDL_FULL/x86/) # Call before to make sure VS detects it

add_executable(output)

target_include_directories(output 
		PUBLIC 
		./
		./Dependencies/SDL_FULL/include/
		./Dependencies/json/single_include/nlohmann
		./Dependencies/hopscotch-map/include/
		)

target_sources(output 
		PUBLIC 
		Game/Systems/HealthDamageSystem/HealthDamageSystem.cpp
		Game/Systems/CameraSystem/CameraSystem.cpp
		Game/Systems/LevelSystem/LevelSystem.cpp
		Game/Systems/FontSystem/FontSystem.cpp
		Game/Systems/AISystem/AISystem.cpp
		Game/Systems/InputSystem/InputSystem.cpp
		Game/Systems/BulletSystem/BulletSystem.cpp
		Game/Systems/MovementSystem/MovementSystem.cpp
		Game/Systems/MeteorSystem/MeteorSystem.cpp
		Game/Systems/DeathSystem/DeathSystem.cpp
		Game/Systems/ScoreSystem/ScoreSystem.cpp
		Game/Systems/CollisionSystem/CollisionSystem.cpp
		Game/Systems/UFOSystem/UFOSystem.cpp
		Game/Systems/RenderingSystem/RenderingSystem.cpp
		Game/Scenes/InGameControllerSwitch/Switch.cpp
		Game/Scenes/SceneManager/SceneManager.cpp
		Game/Scenes/ButtonSystem.cpp
		Game/Scenes/Menu/Menu.cpp
		Game/Entities/EntityManager.cpp
		Game/Game/main.cpp
		Game/Game/Game.cpp
		Game/stdafx.cpp
		Tools/TM.cpp
	
		)

target_link_libraries(output 
		SDL2main
		SDL2_image
		SDL2
		SDL2_ttf
		)
