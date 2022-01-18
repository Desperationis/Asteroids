# Asteroids
![Asteroids GIF](preview/Asteroids.gif)

A fun little game based on the original Asteroids. Features PS4 controller support, a ECS System, and a few levels.


## Keyboard Controls

  * MOVEMENT - FWD-Arrow (Throttle) Left-Arrow (Turn Left) Right-Arrow (Turn Right)
  * SHOOT - Space
  * HIGHLIGHT PLAYER - L-Shift
  * ESC - Exit the program; You can call this whenever, where ever.

## Controller controls

  * MOVEMENT - Left Analog Stick (turning) L2 (Throttle)
  * SHOOT - X


# Compiling on Linux (Debian-based)
This project uses CMake in order to generate a make file. Install CMake through whatever means necessary, though the easiest would be using `sudo apt-get install cmake` on the command line. 

In addition to this, you must install the dev versions of [SDL2](https://www.libsdl.org/), [SDL2_image](https://www.libsdl.org/projects/SDL_image/), and [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/). On Debian, this can be done by calling `sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev`. 

Then, run `installDependencies.bash` to download other dependencies onto the project directory. After that, you can compile this project by simply running `compile.bash` to compile an executable into `executable/`. It's as easy as that! 

# Compiling on Arch Linux
To install everything that was said above (and the compilation tools necessary, the command is `pacman -S cmake sdl2 sdl2_image sdl2_ttf base-devel wget`. After that, follow the same steps as Debian to compile.

# Compiling on Windows
## Requirements
Installing prerequisites on Windows is a bit more complicated. First, download the binary executable of [CMake](https://cmake.org/) and install it. Be sure to install the executable that matches your system architecture.

After that, create a folder named `Dependencies`. In that folder, create a folder titles `SDL_FULL` and put two folders named `include` and `x86` inside it; Here is where you put the header files of SDL2, SDL2_image, and SDL_tff in `include` and their x86 .lib files into `x86`. After that, follow these steps
* Get the `SDL2-devel-2.0.x` archive from [here](https://www.libsdl.org/release/)
* Get the `SDL2_image-devel-2.0.x` archive from [here](https://www.libsdl.org/projects/SDL_image/release/)
* Get the `SDL2_ttf-devel-2.0.x` archive from [here](https://www.libsdl.org/projects/SDL_ttf/release/)
* For each archive, unzip the contents of their `include` folder into `Dependencies/SDL_FULL/include` and `lib/x86` folder into `Dependencies/SDL_FULL/x86`
* Move all the .dll files into a separate folder at the root of the project; This is where your executable will run. 

This project also requires the use of two open-source libraries [nlohmann/json](https://github.com/nlohmann/json) and [Tessil/hopscotch-map](https://github.com/Tessil/hopscotch-map). Download the `include.zip` file in [nlohmann/json](https://github.com/nlohmann/json) and put its contents in a folder titled `json` in `Dependencies/`, and clone / download the source code of [Tessil/hopscotch-map](https://github.com/Tessil/hopscotch-map) and rename the folder for the project as `hopscotch-map` and put it in `Dependencies/`. After that, you're all set!

## Compiling
To compile this project, you need to use CMake and your prefered compiler to generate a x86 (32-bit) version of your solution / executable. 

After this, the compiled executable must be put into ANY folder in the root directory of the project along with the aforementioned .dll files of SDL2. After this, you can run the game :)
