Welcome to the UE4 Compilation Tool.

This tool allows you to cook, package, and upload your UE4 games to Steam. It is quick and rudimentary, but can help you iterate builds and get them up to Steam much faster by automating the process.

For example, for my project Epitasis, I would have to constantly open the project, compile, wait, rename the folder and exe, copy over to some other directorys on my hardrive (a build depository area, or deploy area, and also the Steam content path for building and uploading). This became a redundant and long process. 

This simplifies all of that. With a simple command, your project will compile and upload to Steam automatically (the one exception is having to enter in a 2FA code). The command line also allows you to perform individual tasks rather than all at once. 

To get started, download the source code. You will have to edit the Settings struct to include your own settings. I've included almost all of mine (besides steam user/pass) to give you an idea of how it's used. When you're done editing them, recompile the program and run. You should then be able to compile your game via the tool and have it start the process of uploading to Steam automatically. 

List of commands the project includes:
'compile' : compiles the UE4 project using your pre-defined settings.
'copy_build_to_deploy' : copies the build from the staging area to the deploy path. This will also rename the exe and top level folder if needed (e.g 'WindowsNoEditor' can be changed to 'epitasis').
'copy_build_to_steam' : copies the build from staging area to the steam content builder folder.
'upload' : uploads the build to steam.
'compile_and_upload' : compiles the UE4 project, copies to relevant directories, and then pushes the build to Steam. This is the one the tool is built around.
'view_settings' : displays currently defined settings.
'exit' : exits the UE4 Compilation Tool.

In the future, I plan on changing the Settings into a file to allow users to just download the UE4CompilationTool.exe and load their own settings in via a text file, so they do not have to recompile.

I hope this helps your project in some way. The application is free to download and modify as you see fit. Enjoy!
