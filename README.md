# Bullet hell.
## This is
### Description


### How to Install and Run the Project
- Clone this repository
- Create an empty project in Visual Studio
- Download SDL. For Visual Studio, download the "VC" development library. 	https://github.com/libsdl-org/SDL/releases/tag/release-2.30.2)
	![The "VC" development library](/sdl_vc.png)
- Extract the files and move the folder into your project.
	![SDL2 location](/sdl_location.png)
- Open up your project properties.
- Go to VC++ directories, select include directories, and select edit.
- Add the path to the "include" folder in your SDL source folder. $(ProjectDir) is replaced with the path to your .vxproj file.
	Example ```$(ProjectDir)..\SDL2\include```
- Hit OK, then do the same for library directories. Here, add lib/x64 (or lib/x86) from your SDL source folder.
	```$(ProjectDir)..\SDL2\lib\x64```
- Next, expand the linker options and select input. Click on additional dependencies and select edit. 
- Add SDL2.lib and SDL2main.lib. 
	```SDL2.lib;SDL2main.lib```
- Next, go to debugging and edit environment. 
- Add this command. Use the path to the lib/x64 (or lib/x86) folder in your SDL source folder. This allows your program to see the SDL libraries at runtime. To run the executable on its own, you must copy those libraries into the same directory. 
	```PATH=%PATH%;$(ProjectDir)..\SDL2\lib\x64```
- Go to system under linker. Edit subsystem. Select Console.
- From *source_files* folder add all files to Source Files in Visual Studio.
- From *header_files* folder add all filet to Header Files in Visual Studio.
- Replace *images* folder to working directory. The working directory is where your application thinks it is operating. Typically, your working directory is the directory where your executable is at but some programs like Visual Studio change the working directory to where the vcxproj file is located.
- Run
