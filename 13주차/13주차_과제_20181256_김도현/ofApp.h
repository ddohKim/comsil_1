/*

	ofxWinMenu basic example - ofApp.h

	Copyright (C) 2016-2017 Lynn Jarvis.

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
*/

	#pragma once

#include "ofMain.h"
#include "ofxWinMenu.h" // Menu addon

#include <stack>
#include <queue>


class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key); // Traps escape key if exit disabled
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		bool readFile(); //파일을 읽는 함수
		void freeMemory(); //동적 할당 메모리 해제 하는 함수
		bool DFS(); //DFS 탐색을 하는 함수
		void dfsdraw(); //DFS 탐색을 한 후 이에 해당하는 경로를 그리는 함수
		bool BFS(); //BFS 탐색을 하는 함수
		void bfsdraw(); //BFS 탐색을 한 후 이에 해당하는 경로를 그리는 함수
		void visitedfree(); //DFS,BFS 탐색을 할 때 방문한 visited 2차원 배열 메모리 해제 함수
		void bfs_free(); //bfs에서 경로를 그릴 때 사용하는 parent 2차원 배열 메모리 해제시키는 함수
		bool drawing; //미로가 그려졌는지 안그렸는지 확인하는 flag 

		int HEIGHT;//미로의 높이
		int WIDTH;//미로의 너비
		char** input;//텍스트 파일의 모든 정보를 담는 이차원 배열이다.
		int** visited;//방문여부를 저장할 포인
		
	

		int maze_col;//미로칸의 열의 인덱스를 가리킨다.
		int maze_row;//미로칸의 행의 인덱스를 가리킨다.
		int k;
		int isOpen; //파일이 열렸는지를 판단하는 변수. 0이면 안열렸고 1이면 열렸다.
		int isDFS;//DFS함수를 실행시켰는지 판단하는 변수. 0이면 실행안했고 1이면 실행했다.
		int isBFS;//BFS함수를 실행시켰는지 판단하는 변수. 0이면 실행안했고 1이면 실행했다.
		// Menu
		ofxWinMenu * menu; // Menu object
		void appMenuFunction(string title, bool bChecked); // Menu return function



		// Used by example app
		ofTrueTypeFont myFont;
        ofImage myImage;
		float windowWidth, windowHeight;
		HWND hWnd; // Application window
		HWND hWndForeground; // current foreground window

		// Example menu variables
		bool bShowInfo;
		bool bFullscreen;
		bool bTopmost;
		bool isdfs; //dfs 탐색이 끝났는지 확인하고 경로를 그릴 수 있는지 확인하는 flag
		bool isbfs; //bfs 탐색이 끝났는지 확인하고 경로를 그릴 수 있는 지 확인하는 flag
		// Example functions
 		void doFullScreen(bool bFull);
		void doTopmost(bool bTop);


	
		stack<int> dfs_all_path_x; //dfs에서 모든 경로를 탐색할 때 사용하는 stack, 여기는 x좌표를 저장한다.
		stack<int> dfs_all_path_y;//dfs에서 모든 경로를 탐색할 때 사용하는 stack, 여기는 y좌표를 저장한다.

		stack<int> dfs_path_y;//dfs에서 최적 경로를 탐색할 때 사용하는 stack, 여기는 y좌표를 저장한다.
		stack<int> dfs_path_x;//dfs에서 최적 경로를 탐색할 때 사용하는 stack, 여기는 y좌표를 저장한다.

		queue<int> bfs_path_x; //bfs에서 경로를 탐색할 때 사용하는 queue, 여기는 x좌표를 저장한다.
		queue<int> bfs_path_y; //bfs에서 경로를 탐색할 때 사용하는 queue, 여기는 y좌표를 저장한다.

		queue<int> bfs_all_path_x; //bfs에서 모든 경로를 탐색할 때 사용하는 queue, 여기는 x좌표를 저장한다.
		queue<int> bfs_all_path_y;//bfs에서 모든 경로를 탐색할 때 사용하는 queue, 여기는 x좌표를 저장한다.


		int** bfs_parent_x; //bfs 경로를 그리기 위해서는 해당 좌표의 parent 좌표를 알아야 하기 때문에 2차원 동적배열을 통해 parent x좌표 저장
		int** bfs_parent_y; //bfs 경로를 그리기 위해서는 해당 좌표의 parent 좌표를 알아야 하기 때문에 2차원 동적배열을 통해 parent y좌표 저장
};
