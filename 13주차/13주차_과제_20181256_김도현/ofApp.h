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
		bool readFile(); //������ �д� �Լ�
		void freeMemory(); //���� �Ҵ� �޸� ���� �ϴ� �Լ�
		bool DFS(); //DFS Ž���� �ϴ� �Լ�
		void dfsdraw(); //DFS Ž���� �� �� �̿� �ش��ϴ� ��θ� �׸��� �Լ�
		bool BFS(); //BFS Ž���� �ϴ� �Լ�
		void bfsdraw(); //BFS Ž���� �� �� �̿� �ش��ϴ� ��θ� �׸��� �Լ�
		void visitedfree(); //DFS,BFS Ž���� �� �� �湮�� visited 2���� �迭 �޸� ���� �Լ�
		void bfs_free(); //bfs���� ��θ� �׸� �� ����ϴ� parent 2���� �迭 �޸� ������Ű�� �Լ�
		bool drawing; //�̷ΰ� �׷������� �ȱ׷ȴ��� Ȯ���ϴ� flag 

		int HEIGHT;//�̷��� ����
		int WIDTH;//�̷��� �ʺ�
		char** input;//�ؽ�Ʈ ������ ��� ������ ��� ������ �迭�̴�.
		int** visited;//�湮���θ� ������ ����
		
	

		int maze_col;//�̷�ĭ�� ���� �ε����� ����Ų��.
		int maze_row;//�̷�ĭ�� ���� �ε����� ����Ų��.
		int k;
		int isOpen; //������ ���ȴ����� �Ǵ��ϴ� ����. 0�̸� �ȿ��Ȱ� 1�̸� ���ȴ�.
		int isDFS;//DFS�Լ��� ������״��� �Ǵ��ϴ� ����. 0�̸� ������߰� 1�̸� �����ߴ�.
		int isBFS;//BFS�Լ��� ������״��� �Ǵ��ϴ� ����. 0�̸� ������߰� 1�̸� �����ߴ�.
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
		bool isdfs; //dfs Ž���� �������� Ȯ���ϰ� ��θ� �׸� �� �ִ��� Ȯ���ϴ� flag
		bool isbfs; //bfs Ž���� �������� Ȯ���ϰ� ��θ� �׸� �� �ִ� �� Ȯ���ϴ� flag
		// Example functions
 		void doFullScreen(bool bFull);
		void doTopmost(bool bTop);


	
		stack<int> dfs_all_path_x; //dfs���� ��� ��θ� Ž���� �� ����ϴ� stack, ����� x��ǥ�� �����Ѵ�.
		stack<int> dfs_all_path_y;//dfs���� ��� ��θ� Ž���� �� ����ϴ� stack, ����� y��ǥ�� �����Ѵ�.

		stack<int> dfs_path_y;//dfs���� ���� ��θ� Ž���� �� ����ϴ� stack, ����� y��ǥ�� �����Ѵ�.
		stack<int> dfs_path_x;//dfs���� ���� ��θ� Ž���� �� ����ϴ� stack, ����� y��ǥ�� �����Ѵ�.

		queue<int> bfs_path_x; //bfs���� ��θ� Ž���� �� ����ϴ� queue, ����� x��ǥ�� �����Ѵ�.
		queue<int> bfs_path_y; //bfs���� ��θ� Ž���� �� ����ϴ� queue, ����� y��ǥ�� �����Ѵ�.

		queue<int> bfs_all_path_x; //bfs���� ��� ��θ� Ž���� �� ����ϴ� queue, ����� x��ǥ�� �����Ѵ�.
		queue<int> bfs_all_path_y;//bfs���� ��� ��θ� Ž���� �� ����ϴ� queue, ����� x��ǥ�� �����Ѵ�.


		int** bfs_parent_x; //bfs ��θ� �׸��� ���ؼ��� �ش� ��ǥ�� parent ��ǥ�� �˾ƾ� �ϱ� ������ 2���� �����迭�� ���� parent x��ǥ ����
		int** bfs_parent_y; //bfs ��θ� �׸��� ���ؼ��� �ش� ��ǥ�� parent ��ǥ�� �˾ƾ� �ϱ� ������ 2���� �����迭�� ���� parent y��ǥ ����
};
