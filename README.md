# UE4 Compilation Tool

Welcome to the UE4 Compilation Tool.

This tool allows you to cook, package, and upload your UE4 games to Steam. It is quick and rudimentary, but can help you iterate builds and get them up to Steam much faster by automating the process.

## Getting Started

The general idea is that this tool is your one stop hub for:
* Compiling your UE4 project.
* Copying it from the UE4 staging area to a seperate folder (maybe you have a special location on your harddrive just for builds of your game).
* Copying it to your Steamworks Content Builder folder.
* Uploading your project to Steam.
* Automating this entire process by the use of one command. 

To get started, download the source code. You will have to edit the Settings struct inside UE4CompilationTool.cpp to include your own settings. I've included almost all of my original settings as an example (besides steam user/pass) to give you a better idea of how it's used. 

When you're done editing them, recompile the program and run. You should then be able to compile your game via the tool and have it start the process of uploading to Steam automatically. For a list of the commands the tool accepts, see below. 

### Commands

* 'compile' : compiles the UE4 project using your pre-defined settings.
* 'copy_build_to_deploy' : copies the build from the staging area to the deploy path. This will also rename the exe and top level folder if needed (e.g 'WindowsNoEditor' can be changed to 'epitasis').
* 'copy_build_to_steam' : copies the build from staging area to the steam content builder folder.
* 'upload' : uploads the build to steam.
* 'compile_and_upload' : compiles the UE4 project, copies to relevant directories, and then pushes the build to Steam. This is the one the tool is built around.
* 'view_settings' : displays currently defined settings.
* 'exit' : exits the UE4 Compilation Tool.

'compile_and_upload' is the bread and butter of this tool. It will compile your project, copy them to relevant directories, and then upload to Steam. The only reason this is possible is by the tools already provided in Unreal and Steamworks - again, this application simplies automates the process. 

## Acknowledgments

* Epic Games for Unreal Engine 4.
* Valve Corporation for Steamworks and Steam.
* This tool was built by Lucas Govatos.
