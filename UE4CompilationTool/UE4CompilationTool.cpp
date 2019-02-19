// UE4CompilationTool.cpp : Defines the entry point for the console application.
// (C) @lucasgovatos + Epitasis Games; 
// (C) Unreal Engine 4 - Epic Games;
// (C) Steam - Valve Corporation;

// Include
#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstring>
#include <Windows.h>
#include <fstream>

using namespace std;

// Settings 
struct Settings {
	Settings() : 

		//Define your settings here in the default values of the struct!

		ue4_runaut_path("E:\\Epic Games\\UE_4.16_Source\\Engine\\Build\\BatchFiles\\RunUAT.bat"), //This is where the RunUAT.bat file is located for your engine.
		project_path("E:\\Epic Games\\UE_4.16_Source\\DistantWorldsCode\\DistantWorldsCode.uproject"), //This is the location and file name of your project.
		actual_project_name("DistantWorldsCode"), //Actual project name minus the .uproject extension!
		project_deploy_path("E:\\EpitasisBuilds\\Windows\\Release"), //The path you want your game copied to after compilation.
		stage_path("E:\\Epic Games\\UE_4.16_Source\\DistantWorldsCode\\Saved\\StagedBuilds\\WindowsNoEditor"), //The staging path (this is where Unreal usually spits out the compiled game after RunUAT is done.)
		renamed_project_directory("epitasis"), //The folder you want your directory renamed to; e.g 'WindowsNoEditor' becomes 'epitasis'
		release(true), //Release build?
		renameEXE(true), //Rename the exe?
		renamed_exe("epitasis"), //What should the exe be renamed to? (do not include .exe extension!)
		app_id("999999"), //Your Steam APP ID
		steam_username("MySteamUsername"), //Steam Username
		steam_password("MyPassword"), //Steam password
		steam_content_path("E:\\steamworks_sdk_142\\sdk\\tools\\ContentBuilder\\content\\windows_content"), //Path to wherever you put your windows content for Steam
		steam_cmd_path("E:\\steamworks_sdk_142\\sdk\\tools\\ContentBuilder\\builder\\steamcmd.exe"), //Location of the Steam CMD app for building your content and uploading. 
		steam_script_file("..\\scripts\\app_build_999999.vdf") //location and name of vdf script to use. Should be in the scripts folder located where steamcmd is!
	{}
	string ue4_runaut_path;
	string project_path;
	string actual_project_name;
	string project_deploy_path;
	string renamed_project_directory;
	string stage_path;
	bool release;
	bool renameEXE;
	string renamed_exe;
	string app_id;
	string steam_content_path;
	string steam_cmd_path;
	string steam_username;
	string steam_password;
	string steam_script_file;
};

//functions
int parseCommand(string command, Settings& settings);
int viewSettings(Settings& current_settings);
int compile(Settings settings);
int upload_to_steam(Settings settings);
int copy_build_to_deploy(Settings settings);
int copy_build_to_steam(Settings settings);
void help();

int main()
{
	

	int exit = 0;
	string command;
	Settings current_settings;

	cout << "Welcome to the UE4 Compilation Tool. Type 'help' for a list of commands.\n" << endl;
	cout << "This is a quickly created tool to allow you to both compile UE4 projects and upload to Steam.\n" << endl;
	while (exit == 0) {
		cout << "UE4 Compile Tool > ";
		cin >> command;
		exit = parseCommand(command, current_settings);
	}

	return 0;
}

int parseCommand(string command, Settings& settings) {
	if (command.compare("compile") == 0) {
		compile(settings);
	}
	else if (command.compare("upload") == 0) {
		upload_to_steam(settings);
	}
	else if (command.compare("compile_and_upload") == 0) {
		if (compile(settings) == 0) {
			upload_to_steam(settings);
		}
	}
	else if (command.compare("copy_build_to_deploy") == 0) {
		copy_build_to_deploy(settings);
	}
	else if (command.compare("copy_build_to_steam") == 0) {
		copy_build_to_steam(settings);
	}
	else if (command.compare("view_settings") == 0) {
		viewSettings(settings);
	}
	else if (command.compare("exit") == 0) {
		return 1;
	}
	else if (command.compare("help") == 0) {
		help();
	}
	else {
		cout << "Unknown command. Type 'help' for a list of commands." << endl;
	}
	return 0;
}

int viewSettings(Settings& current_settings)
{
	cout << "\n---------- UE4 TOOL VIEW SETTINGS ----------\n" << endl;
	cout << "Unreal Engine RunAUT tool path: " << current_settings.ue4_runaut_path << endl;
	cout << "Project path: " << current_settings.project_path << endl;
	cout << "Project name: " << current_settings.actual_project_name << endl;
	cout << "Project deploy path: " << current_settings.project_deploy_path << endl;
	cout << "Is this project a release build?: " << current_settings.release << endl;
	cout << "Should the exe file be renamed after the build is complete?: " << current_settings.renameEXE << endl;
	cout << "New exe file name: " << current_settings.renamed_exe << endl;
	cout << "Steam App ID: " << current_settings.app_id << endl;
	cout << "Steam cmd tool path: " << current_settings.steam_cmd_path << endl;
	cout << "Steam content path: " << current_settings.steam_content_path << endl;
	cout << "Steam username: " << current_settings.steam_username << endl;
	cout << "Steam password: " << current_settings.steam_password << endl;
	cout << "Steam script file: " << current_settings.steam_script_file << endl;
	cout << "\n";
	return 0;
}

//compiles your project and automatically copies to relevant directories so they are up to date.
int compile(Settings settings) {

	cout << "\n---------- Compile Started ---------- \n" << settings.project_path << "......\n" << endl;
	cout << "Starting UAT.....\n" << endl;

	//check settings to see if release or dev
	string config;
	if (settings.release == true) {
		config = "Shipping";
	}
	else {
		config = "Development";
	}

	//Build Command. Adjust as needed
	string commandTemp = "\"\"" + settings.ue4_runaut_path + //build tool location
		"\" -ScriptsForProject=\"" + settings.project_path + //scripts (project path)
		"\" BuildCookRun" +  //required
		" -project=\"" + settings.project_path + //project path
		"\" -cook -stage -archive -archiveddirectory=\"\"" + settings.project_deploy_path + //archive directory (does not seem to work?)
		"\"\" -package -clientconfig=" + config + //shipping status
		" -ue4exe=UE4Editor-Cmd.exe -pak -prereqs -nodebuginfo -targetplatform=Win64 -build -utf8output\""; //define or change build settings here

	//builds game
	system(commandTemp.c_str());

	cout << "\n---------- Project Compiled. Beginning Copy Commands. ---------- \n " << endl;

	//copies to the deploy path
	copy_build_to_deploy(settings);

	//copies to the steam content builder path
	copy_build_to_steam(settings);

	cout << "\n---------- Compile Command Finished. ---------- \n " << endl;
	return 0;
}

//renames the exe and copies to deploy folder
int copy_build_to_deploy(Settings settings) {

	cout << "\n---------- Copy Build to Deploy Directory Started ----------\n" << endl;

	cout << "Copying files to the deploy directory..." << endl;

	//remove previously renamed file, if it exists... (rename function does not overwrite)
	remove(("" + settings.stage_path + "\\" + settings.renamed_exe + ".exe").c_str());
	
	//rename the exe if needed... (original is based of of project name)
	if (settings.renameEXE == true) {
		if (rename(("" + settings.stage_path + "\\" + settings.actual_project_name + ".exe").c_str(), ("" + settings.stage_path + "\\" + settings.renamed_exe + ".exe").c_str()) == 0) {
			cout << "Renamed to " + settings.renamed_exe + ".exe" << endl;
		}
		else {
			cout << ("" + settings.stage_path + "\\DistantWorldsCode.exe").c_str() << endl;
			cout << ("" + settings.stage_path + "\\" + settings.renamed_exe + ".exe").c_str() << endl;
			cout << "Renaming failed!" << endl;
		}
	}

	//create steam_appid.txt in folder with your app id
	ofstream file_;
	file_.open(settings.stage_path + "\\" + settings.actual_project_name + "\\Binaries\\Win64\\steam_appid.txt");
	file_ << settings.app_id;
	file_.close();
	
	//now copy
	
	string copyDir = "\"xcopy \"" + settings.stage_path + "\" \"" + settings.project_deploy_path + "\\" + settings.renamed_project_directory + "\\\" /Y /E /H /K /O /X \"";
	cout << copyDir.c_str() << endl;
	system(copyDir.c_str());

	cout << "\n---------- Copy Build to Deploy Directory Finished ---------- \n" << endl;

	return 0;
}

int copy_build_to_steam(Settings settings) {

	cout << "\n---------- Copy Build to Steam Started ----------\n" << endl;

	//now copy
	cout << "WARNING: Always do copy_build_to_deploy before copying to steam content folder! Your exe may not be named correctly before copying! (If you did, or ran compile, ignore this message)" << endl;
	
	string copyDir = "\"xcopy \"" + settings.stage_path + "\" \"" + settings.steam_content_path + "\\" + settings.renamed_project_directory + "\\\" /Y /E /H /K /O /X \"";
	cout << copyDir.c_str() << endl;
	system(copyDir.c_str());

	cout << "\n---------- Copy Build to Steam Finished ---------- \n" << endl;

	return 0;
}

int upload_to_steam(Settings settings) {

	cout << "\n---------- Upload to Steam Started ---------- \n" << endl;
	cout << "Beginning upload to Steam... please be ready with 2FA code..." << endl;

	//should look like this
	//builder\steamcmd.exe +login account password +run_app_build_http ..\scripts\app_build_1000.vdf +quit

	//hardcoded here
	string commandTemp = "" + settings.steam_cmd_path + " +login " + settings.steam_username + " " + settings.steam_password + " +run_app_build_http " + settings.steam_script_file + " +quit";

	//open steam cmd
	system(commandTemp.c_str());

	cout << "\n---------- !!Remember to push build live at steamgames.com!! ---------- " << endl;
	cout << "---------- Upload to Steam Finished! ---------- \n" << endl;

	return 0;
}

void help() {
	cout << "\n---------- UE4 COMPILATION TOOL - HELP ---------- \n" << endl;
	cout << "Valid commands are as follows:\n" << endl;
	cout << "'compile' : compiles the UE4 project using your pre-defined settings." << endl;
	cout << "'copy_build_to_deploy' : copies the build from the staging area to the deploy path." << endl;
	cout << "'copy_build_to_steam' : copies the build from staging area to the steam content builder folder" << endl;
	cout << "'upload' : uploads the build to steam. " << endl;
	cout << "'compile_and_upload' : compiles the UE4 project, copies to relevant directories, and then pushes the build to Steam." << endl;
	cout << "'view_settings' : displays currently defined settings." << endl;
	cout << "'exit' : exits the UE4 Compilation Tool.\n" << endl;
	cout << "\nCheck the source code to see how the settings are used, along with defining them. (Coming soon: a settings file...)\n" << endl;
	cout << "\nUE4 Compilation Tool created by @lucasgovatos. Unreal Engine and Steam are property of their respective owners.\n" << endl;
}
