#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    /* WaterFall-related member variables Regions */
    
    // flag variables
    int draw_flag; //그림을 그릴 수 있는지 판단하는 flag
    int load_flag; //파일을 load했는지 판단하는 flag
	int water_flag; //물이 떨어지는지 안떨어지는지 판단하는 flag
	int vertical_flag; //물이 수직으로 떨어지는지 확인하는 flag
	int start_flag; //물이 이동할 때 기울기가 변할때 시작점을 바꿔주는 flag

	int check=0; //물이 떨어질 dot 좌표 이동시키는 check 변수, 0이 가장 왼쪽을 의미하고 오른쪽으로 하나씩 이동할수록 1씩 증가
	float water_x1, water_y1; //물이 떨어질 곳의 시작 좌표
	float water_x2, water_y2; //물이 떨어질 곳의 끝 좌표
	struct line_water{ //line을 그리는 struct 구조체
		int sX; //시작의 X 좌표를 의미
		int sY; //시작의 Y 좌표를 의미
		int eX; //끝의 X 좌표를 의미
		int eY; //끝의 Y 좌표를 의미
		float slope; //기울기를 의미

	};
	line_water * water_line; //line구조체를 water_line 로 이용
	struct dot_water{ //dot을 그리는 struct 구조체
		int X; //dot의 X좌표
		int Y; //dot의 Y좌표
	};
	dot_water * water_dot; //dot 구조체를  water_dot으로 이용



    // Line segment and dot related variables
    int num_of_line, num_of_dot;
    float dot_diameter;
    
    /* WaterFall-related member functions */
    
    void processOpenFileSelection(ofFileDialogResult openFileResult);
    void initializeWaterLines(); // 2nd week portion.
		
};
