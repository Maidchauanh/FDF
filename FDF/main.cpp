#include<iostream> 
#include<string>
#include<Windows.h>
#include <io.h>
#include <fcntl.h>

std::wstring getPath(LPCWSTR fileName) {
	TCHAR** lppPart = { NULL };
	TCHAR  buffer[4096] = TEXT("");
	if (!GetFullPathNameW(fileName, 4096, buffer, lppPart)) {
		std::cerr << "Can not get full path\n";
		std::cerr << "Error: " << GetLastError() << '\n';
	}
	return (std::wstring)buffer;
}

void printPath(LPCWSTR fileName) {
	std::wcout << getPath(fileName) << '\n';
}

std::wstring concat(LPCWSTR base, LPCWSTR top) {
	std::wstring mywstring = base;
	std::wstring mywstring1 = top;
	mywstring.pop_back();
	std::wstring concatted_stdstr = mywstring + mywstring1;
	return concatted_stdstr;
}

// TODO: allow indentation
void printFilesRecursively(LPCWSTR dirPath, int width = 10) {

	WIN32_FIND_DATAW findFileData;
	HANDLE hfindFile = FindFirstFileW(dirPath, &findFileData);
	
	if (hfindFile != INVALID_HANDLE_VALUE) {
		while (FindNextFileW(hfindFile, &findFileData)) {
			// not print the dot 
			std::wstring fileName = findFileData.cFileName;
			bool notADot = !(fileName[0] == '.');
			if (notADot) {
				// FILE_ATTRIBUTE_DIRECTORY		
				if (findFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
					int indent = 10;
					std::wcout.width(width);
					std::wcout << L"dir: " << fileName << '\n';
					std::wstring path = concat(dirPath, fileName.c_str()) + L"\\*";
					LPCWSTR concattedPath =  path.c_str();
					std::wcout << path << '\n';
					indent += 4;
					printFilesRecursively(concattedPath);

				} else {
					std::wcout.width(width);
					std::wcout << L"file: ";
					std::wcout << fileName << '\n';
				}
			}
		}
	}

	FindClose(hfindFile);
}

int main(int argc, char **argv) {
	// TODO: open folder and search recursively 
		// FindFirstFile
		// FindNextFile 
		// FindClose
		// GetFullPathName

	// TODO: hashing the files and build a database
	// TODO: checking the duplications using the database
	_setmode(_fileno(stdout), _O_U16TEXT); // make terminal display Unicode
	LPCWSTR dirPath = L"*";
	printPath(dirPath);
	printFilesRecursively(dirPath);
	system("pause");
	return 0;
}