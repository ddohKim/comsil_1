/*

	ofxWinMenu basic example - ofApp.cpp

	Example of using ofxWinMenu addon to create a menu for a Microsoft Windows application.

	Copyright (C) 2016-2017 Lynn Jarvis.

	https://github.com/leadedge

	http://www.spout.zeal.co

	=========================================================================
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
	=========================================================================

	03.11.16 - minor comment cleanup
	21.02.17 - rebuild for OF 0.9.8

*/
#include "ofApp.h"
#include <iostream>
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("Maze Example"); // Set the app name on the title bar
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	ofSetBackgroundAuto(false);//최적경로를 그릴 때 stack과 queue를 pop 시키면서 그리기 때문에 ofsetbackgroundAuto를 끈다
	// Get the window size for image loading
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	isdfs = false; //isdfs를 false 로 초기화하여 dfs경로가 탐색되지 않았음을 알림
	isDFS = 0; //isDFS를 0으로 하여 DFS가 실행되지 않았다.
	isOpen = 0; //아직 파일이 열리지 않았다.
	drawing = 0; //아직 미로가 그려지지 않았다.
	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth() - windowWidth) / 2, (ofGetScreenHeight() - windowHeight) / 2);

	// Load a font rather than the default
	//myFont = new ofTrueTypeFont();
	myFont.loadFont("verdana.ttf", 12, true, true);//font를 추가하였다.

	// Load an image for the example
	//myImage.loadImage("lighthouse.jpg");

	// Window handle used for topmost function
	hWnd = WindowFromDC(wglGetCurrentDC());

	// Disable escape key exit so we can exit fullscreen with Escape (see keyPressed)
	ofSetEscapeQuitsApp(false);

	//
	// Create a menu using ofxWinMenu
	//

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();

	//
	// Create a "File" popup menu
	//
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");

	//
	// Add popup items to the File menu
	//

	// Open an maze file
	menu->AddPopupItem(hPopup, "Open", false, false); // Not checked and not auto-checked

	// Final File popup menu item is "Exit" - add a separator before it
	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);

	//
	// View popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "View");

	bShowInfo = true;  // screen info display on
	menu->AddPopupItem(hPopup, "Show DFS", false, false); // Checked
	bTopmost = false; // app is topmost
	menu->AddPopupItem(hPopup, "Show BFS"); // Not checked (default)
	bFullscreen = false; // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false); // Not checked and not auto-check

	//
	// Help popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check

	hPopup = menu->AddPopupMenu(hMenu, "Toolbar"); //Toolbar  popupmenu 새로 추가를 해줌

	bShowInfo = true;  // screen info display on
	menu->AddPopupItem(hPopup, "Show DFS", false, false); // Checked //popup item에 show DFS 라는 DFS를 그릴 버튼을 추가
	bTopmost = false; // app is topmost
	menu->AddPopupItem(hPopup, "Show BFS"); // Not checked (default) //popup item에 show BFS 라는 BFS를 그릴 버튼을 추가

	// Set the menu to the window
	menu->SetWindowMenu();

} // end Setup


//
// Menu function
//
// This function is called by ofxWinMenu when an item is selected.
// The the title and state can be checked for required action.
// 
void ofApp::appMenuFunction(string title, bool bChecked) {

	ofFileDialogResult result;
	string filePath;
	size_t pos;

	//
	// File menu
	//
	if (title == "Open") {
		ofClear(ofColor::white);
		readFile();
	}
	if (title == "Exit") {
		if (drawing == 1)
			freeMemory();
		ofExit(); // Quit the application
	}

	//
	// Window menu
	//
	if (title == "Show DFS") {
		//bShowInfo = bChecked;  // Flag is used elsewhere in Draw()
		if (isOpen)
		{
			DFS(); //dfs를 실행하여 경로를 탐색한다.
			bShowInfo = bChecked;
		}
		else
			cout << "you must open file first" << endl;

	}

	if (title == "Show BFS") {
		doTopmost(bChecked); // Use the checked value directly

	}

	if (title == "Full screen") {
		bFullscreen = !bFullscreen; // Not auto-checked and also used in the keyPressed function
		doFullScreen(bFullscreen); // But als take action immediately
	}

	//
	// Help menu
	//
	if (title == "About") {
		ofSystemAlertDialog("ofxWinMenu\nbasic example\n\nhttp://spout.zeal.co");
	}

} // end appMenuFunction


//--------------------------------------------------------------
void ofApp::update() {

}


//--------------------------------------------------------------
void ofApp::draw() {

	char str[256];
	//ofBackground(0, 0, 0, 0);
	ofSetColor(100);
	ofSetLineWidth(5);

	// TO DO : DRAW MAZE; 
	// 저장된 자료구조를 이용해 미로를 그린다.
	// add code here
	float x = 0; //미로를 그릴 때의 x좌표를 의미한다.
	float y = 0; //미로르 그릴 떄의 y좌표를 의미한다.

	if (drawing == 1)
	{ //만약 drawing flag가 1이라면 미로를 그려야한다.

		for (int i = 0; i < HEIGHT * 2 + 1; i++)
		{// 전체 미로의 높이만큼 반복
			for (int j = 0; j < WIDTH * 2 + 1; j++)
			{//전체 미로의 가로만큼 반복
				if (input[i][j] == '+')
				{ //모서리를 의미하기 떄문에 아무 것도 그리지 않는다. 
				}
				if (input[i][j] == '-')
				{ //bottom 벽을 의미하기 때문에 x좌표 기준 30만큼 오른쪽으로 그린다.
					ofDrawLine(x, y, x + 30, y);
					x += 30; //실제 x좌표 역시 30을 늘려 다음 미로의 그림을 그리도록 한다.
				}
				if (input[i][j] == '|')
				{//side 벽을 의미하기 때문에 y좌표 기준 30만큼 아래로 그린다.
					ofDrawLine(x, y, x, y + 30);
				}
				if (input[i][j] == ' ')
				{ //비었다는 것은 방이거나 빈 벽이기 때문에
					if (j % 2 == 1) //j가 2로 나누었을 때 나머지가 1이면 방이라는 의미로
						x += 30; //x좌표를 30 만큼 늘린다.
				}
			}
			x = 0; //가로 for문을 모두 돌면 다시 다음 행을 출력해야 하기 때문에 x좌표를 0으로 둔다.
			if (i % 2 == 1) //만약 i가 2로 나누었을 때 나머지가 1이면 실제 미로의 한 행을 그린것이기 때문에 y좌표를 30 늘려 다음 행을 그릴 준비를 한다.
				y += 30;
		}
	}
	if (isdfs)
	{ //만약 isdfs가 true 이면(dfs 탐색이 끝났다면)
		ofSetLineWidth(5);
		if (isOpen) //만약 file이 열려있다면
			dfsdraw(); //dfs로 탐색한 미로를 그린다.
		else
			cout << "You must open file first" << endl;
	}
	if (bShowInfo) {
		// Show keyboard duplicates of menu functions
		sprintf(str, " comsil project");
		myFont.drawString(str, 15, ofGetHeight() - 20);
	}

} // end Draw


void ofApp::doFullScreen(bool bFull)
{
	// Enter full screen
	if (bFull) {
		// Remove the menu but don't destroy it
		menu->RemoveWindowMenu();
		// hide the cursor
		ofHideCursor();
		// Set full screen
		ofSetFullscreen(true);
	}
	else {
		// return from full screen
		ofSetFullscreen(false);
		// Restore the menu
		menu->SetWindowMenu();
		// Restore the window size allowing for the menu
		ofSetWindowShape(windowWidth, windowHeight + GetSystemMetrics(SM_CYMENU));
		// Centre on the screen
		ofSetWindowPosition((ofGetScreenWidth() - ofGetWidth()) / 2, (ofGetScreenHeight() - ofGetHeight()) / 2);
		// Show the cursor again
		ofShowCursor();
		// Restore topmost state
		if (bTopmost) doTopmost(true);
	}

} // end doFullScreen


void ofApp::doTopmost(bool bTop)
{
	if (bTop) {
		// get the current top window for return
		hWndForeground = GetForegroundWindow();
		// Set this window topmost
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
	}
	else {
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
		// Reset the window that was topmost before
		if (GetWindowLong(hWndForeground, GWL_EXSTYLE) & WS_EX_TOPMOST)
			SetWindowPos(hWndForeground, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		else
			SetWindowPos(hWndForeground, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
} // end doTopmost


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// Escape key exit has been disabled but it can be checked here
	if (key == VK_ESCAPE) {
		// Disable fullscreen set, otherwise quit the application as usual
		if (bFullscreen) {
			bFullscreen = false;
			doFullScreen(false);
		}
		else {
			ofExit();
		}
	}

	// Remove or show screen info
	if (key == ' ') {
		bShowInfo = !bShowInfo;
		// Update the menu check mark because the item state has been changed here
		menu->SetPopupItem("Show DFS", bShowInfo);
	}

	if (key == 'f') {
		bFullscreen = !bFullscreen;
		doFullScreen(bFullscreen);
		// Do not check this menu item
		// If there is no menu when you call the SetPopupItem function it will crash
	}

} // end keyPressed

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
bool ofApp::readFile()
{
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select .maz file");
	string filePath;
	size_t pos;
	// Check whether the user opened a file
	if (openFileResult.bSuccess) {
		ofLogVerbose("User selected a file");

		//We have a file, check it and process it
		string fileName = openFileResult.getName();
		//string fileName = "maze0.maz";
		//printf("file name is %s\n", fileName);
		cout << "file name is " << fileName << "\n" << endl;
		filePath = openFileResult.getPath();
		cout << "Open\n" << endl;
		//printf("Open\n");
		pos = filePath.find_last_of(".");
		if (pos != string::npos && pos != 0 && filePath.substr(pos + 1) == "maz") {

			ofFile file(fileName);

			if (!file.exists()) {
				cout << "Target file does not exists." << endl;
				return false;
			}
			else {
				cout << "We found the target file." << endl;
				isOpen = 1;
			}

			string num_line; //num_line에 .maz 파일의 정보를 한줄 씩 받아온다. 
			// TO DO
			// .maz 파일을 input으로 받아서 적절히 자료구조에 넣는다
			if (drawing) //만약 이미 미로가 그려져 있다면
			{
				freeMemory(); //input 동적할당받은 메모리를 해제시킨다.
			}
			HEIGHT = 0; //미로의 높이 초기화
			WIDTH = 0; //미로의 가로 초기화
			while (getline(file, num_line)) //while문을 통해 getline을 이용하여 한줄 씩 num_line에 받아온다
			{
				HEIGHT++;  //높이를 1씩 증가시켜 미로의 높이를 받아온다.

			}
			input = new char*[HEIGHT]; //미로를 저장할 input 동적할당 2차원 배열을 만든다.
			for (int i = 0; i < HEIGHT; i++)
			{
				input[i] = new char[num_line.length()];
			}
			WIDTH = (num_line.length()) / 2; //실제 미로의 가로의 길이는 num_line.length에 1을 뺀 후 2로 나눈 수이다.
			HEIGHT = HEIGHT / 2; //실제 미로의 높이 역시 HEIGHT에 1을 뺀 후 2로 나눈 수이다. 


			string word; //실제 파일의 내용을 word string에 받아온다.

			ofFile file2(fileName); //ofFile 을 통해 다시 file2에 .maz를 받아온다.


			for (int i = 0; i < HEIGHT * 2 + 1; i++) // 전체 미로의 높이 만큼
			{
				getline(file2, word); //getline을 통해 한줄씩 word string에 저장
				for (int j = 0; j < WIDTH * 2 + 1; j++) //전체 미로의 가로 만큼
				{
					input[i][j] = word[j]; //input 동적할당배열에 word 속 한글자씩 저장한다.
				}
			}
			drawing = 1; //drawing flag를 1로 바꾸어 미로 출력이 가능하도록 한다.
		}
		else { //그렇지 않다면
			printf("  Needs a '.maz' extension\n"); //.maz 확장자가 필요함을 알린다.
			return false;
		}
	}
}
void ofApp::freeMemory() {

	for (int i = 0; i < HEIGHT * 2 + 1; i++) //input 2차원 동적할당 배열을 메모리 해제시킨다.
	{
		delete[] input[i];
	}
	delete[] input;

	if (isDFS == 1) { //만약 isDFS 가 1이라면 visited 동적 할당 메모리를 해제시켜 다시 dfs를 통해 다른 미로 경로 탐색을 할 수 있도록 준비한다.
		for (int i = 0; i < HEIGHT * 2 + 1; i++)
		{
			delete[] visited[i];
		}
		delete[] visited;
		cout << "visited memory free" << endl;
		isDFS = 0; //isDFS를 0으로 둬서 성공적으로 다음 미로를 받을 준비가 되었다.
	}
	//TO DO
	// malloc한 memory를 free해주는 함수
	cout << "Memory Free Success!!" << endl;
}

bool ofApp::DFS()//DFS탐색을 하는 함수
{
	//TO DO
	//DFS탐색을 하는 함수 ( 3주차)
	isdfs = 1; //dfs를 통해 미로 탐색 완료 후 그림을 그릴 때 사용하는 flag
	isDFS = 1; //메모리 해제에 사용되는 flag

	visited = new int*[HEIGHT * 2 + 1]; //visted 2차원 동적할당배열은 해당 공간이 이미 방문했는지 안했는지 판단할 때 쓰인다. 
	for (int i = 0; i < HEIGHT * 2 + 1; i++) //new를 통해 동적할당 받는다.
	{
		visited[i] = new int[WIDTH * 2 + 1];
	}

	for (int i = 0; i < HEIGHT * 2 + 1; i++) //visited 배열 초기화. 전체 미로의 높이 즉 HEIGHT*2+1 만큼
	{
		for (int j = 0; j < WIDTH * 2 + 1; j++) //전체 미로의 가로 즉 WIDTH*2+1 만큼
		{
			if (input[i][j] == ' ')visited[i][j] = 0; //만약 input 배열이 비어있다면 visited 역시 비워둔다.
			else visited[i][j] = 1; //그렇지 않다면 1을 두어 벽임을 미리 저장해 놓는다.
		}
	}
	dfs_path_x.push(1); //첫 노드인 (1,1)부터 시작 
	dfs_path_y.push(1);

	dfs_all_path_x.push(1); //첫 노드인 (1,1) 부터 시작
	dfs_all_path_y.push(1);

	visited[1][1] = 1; //해당 (1,1)은 방문하였다.

	while (!dfs_path_x.empty() && !dfs_path_y.empty())
	{ //stack에 x,y 좌표가 모두 비지 않을 때 까지 반복

		if (dfs_path_x.top() == WIDTH * 2 - 1 && dfs_path_y.top() == HEIGHT * 2 - 1) //만약 stack의 x좌표와 y좌표가 우리가 탐색을 원하는 최종 경로의 좌표라면
			break; //while문을 멈춘다.
		int x = dfs_path_x.top(); //stack_x의 top을 x에 넣는다.
		int y = dfs_path_y.top(); //stack_y의 top을 y에 넣는다.
		if (!visited[y + 1][x]) { //만약 현재 기준 아래 공간에 방문하지 않았다면
			dfs_all_path_x.push(x); //전체경로의 stack에 (x,y+1)을 넣는다.
			dfs_all_path_y.push(y + 1); 

			dfs_path_x.push(x); //최적경로의 stack에 (x,y+1)을 넣는다.
			dfs_path_y.push(y + 1);
			visited[y + 1][x] = 1; //visited 역시 방문함을 알려 더이상 이 공간에 접근하지 않도록 한다. 
			continue;
		}
		else if (!visited[y - 1][x]) {//만약 현재 기준 윗 공간에 방문하지 않았다면
			dfs_all_path_x.push(x);//전체경로의 stack에 (x,y-1)을 넣는다.
			dfs_all_path_y.push(y - 1);

			dfs_path_x.push(x);//최적경로의 stack에 (x,y-1)을 넣는다.
			dfs_path_y.push(y - 1);
			visited[y - 1][x] = 1;//visited 역시 방문함을 알려 더이상 이 공간에 접근하지 않도록 한다. 
			continue;
		}
		else if (!visited[y][x + 1]) {//만약 현재 기준 오른쪽 공간에 방문하지 않았다면

			dfs_all_path_x.push(x + 1);//전체경로의 stack에 (x+1,y)을 넣는다.
			dfs_all_path_y.push(y);

			dfs_path_x.push(x + 1);//최적경로의 stack에 (x+1,y)을 넣는다.
			dfs_path_y.push(y);
			visited[y][x + 1] = 1;//visited 역시 방문함을 알려 더이상 이 공간에 접근하지 않도록 한다. 
			continue;
		}
		else if (!visited[y][x - 1]) {//만약 현재 기준 왼쪽 공간에 방문하지 않았다면
			dfs_all_path_x.push(x - 1);//전체경로의 stack에 (x-1,y)을 넣는다.
			dfs_all_path_y.push(y);

			dfs_path_x.push(x - 1);//최적경로의 stack에 (x-1,y)을 넣는다.
			dfs_path_y.push(y);
			visited[y][x - 1] = 1;//visited 역시 방문함을 알려 더이상 이 공간에 접근하지 않도록 한다. 
			continue;
		}
		else { //인접한 모든 공간에 이미 방문했다면 이 좌표는 최적 경로가 아니다.
			dfs_path_x.pop(); //최적 경로stack의 가장 top을 pop 한다. 
			dfs_path_y.pop();
			int return_x = dfs_path_x.top(); //전체경로 역시 다시 돌아가야 하기 때문에 pop 한 이후의 좌표를 
			int return_y = dfs_path_y.top();
			dfs_all_path_x.push(return_x); //전체 경로의 stack에 넣는다.
			dfs_all_path_y.push(return_y);
		}
	}
	return 1;
}
void ofApp::dfsdraw()
{
	int path_size = dfs_all_path_x.size(); //반목문이 돌아갈 size를 전체 경로의 stack 크기로 한다.
	ofSetColor(255, 0, 0, 200);//색깔과 투명도를 따로 지정하였다.
	for (int i = 0; i < path_size - 1; i++)//path_size-1 동안 반복문이돌아간다. 
	{//순차적으로 경로를 탐색한 x,y 좌표를 가져오며 pop을 해준다.
		int x1 = dfs_all_path_x.top();//x1은 전체경로의 시작 x좌표
		int y1 = dfs_all_path_y.top();//y1은 전체경로의 시작 y좌표
		dfs_all_path_x.pop();//전체 경로 stack 을 pop 해주어 다음 좌표를 받을 수 있게 한다.
		dfs_all_path_y.pop();
		int x2 = dfs_all_path_x.top();//x2는 전체경로의 끝 x좌표
		int y2 = dfs_all_path_y.top();//y2는 전체경로의 끝 y좌표
		ofDrawLine(15 * x1, 15 * y1, 15 * x2, 15 * y2);
	}//경로는 미로의 가운데에 그려야하기 때문에 각 좌표에 15만큼 곱해주어 그리면 된다.(미로 한방의 가로, 높이 길이는 30이다.)
	dfs_all_path_x.pop();  //최종적으로 전체경로 stack의 마지막 원소가 하나 남는데 이 역시 pop 하여 새로운 미로를 그릴 때 메모리 이상이 없도록 한다.
	dfs_all_path_y.pop();

	path_size = dfs_path_x.size(); //반목문이 돌아갈 size를 최적 경로의 stack의 크기로 한다.
	ofSetColor(0, 0, 255, 200); //색깔과 투명도를 따로 지정하였다.
	for (int i = 0; i < path_size - 1; i++) //path_size-1 동안 반복문이돌아간다. 
	{ //순차적으로 경로를 탐색한 x,y 좌표를 가져오며 pop을 해준다.
		int x1 = dfs_path_x.top(); //x1은 최적경로의 시작 x좌표
		int y1 = dfs_path_y.top(); //y1은 최적경로의 시작 y좌표
		dfs_path_x.pop(); //최적 경로 stack 을 pop 해주어 다음 좌표를 받을 수 있게 한다.
		dfs_path_y.pop();
		int x2 = dfs_path_x.top(); //x2는 최적경로의 끝 x좌표
		int y2 = dfs_path_y.top(); //y2는 최적겨올의 끝 y좌표
		ofDrawLine(15 * x1, 15 * y1, 15 * x2, 15 * y2); //경로는 미로의 가운데에 그려야하기 때문에 각 좌표에 15만큼 곱해주어 그리면 된다.(미로 한방의 가로, 높이 길이는 30이다.)
	}
	dfs_path_x.pop(); //최종적으로 최적경로 stack의 마지막 원소가 하나 남는데 이 역시 pop 하여 새로운 미로를 그릴 때 메모리 이상이 없도록 한다.
	dfs_path_y.pop();
	isdfs = 0; //isdfs를 0으로 하여 더이상 draw에서 그림을 그리기 못하도록 한다.( 이미 stack들이 pop 되었기 때문)
}

