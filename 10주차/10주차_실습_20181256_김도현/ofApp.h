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
    int draw_flag; //�׸��� �׸� �� �ִ��� �Ǵ��ϴ� flag
    int load_flag; //������ load�ߴ��� �Ǵ��ϴ� flag
	int water_flag; //���� ���������� �ȶ��������� �Ǵ��ϴ� flag
	int vertical_flag; //���� �������� ���������� Ȯ���ϴ� flag
	int start_flag; //���� �̵��� �� ���Ⱑ ���Ҷ� �������� �ٲ��ִ� flag

	int check=0; //���� ������ dot ��ǥ �̵���Ű�� check ����, 0�� ���� ������ �ǹ��ϰ� ���������� �ϳ��� �̵��Ҽ��� 1�� ����
	float water_x1, water_y1; //���� ������ ���� ���� ��ǥ
	float water_x2, water_y2; //���� ������ ���� �� ��ǥ
	struct line_water{ //line�� �׸��� struct ����ü
		int sX; //������ X ��ǥ�� �ǹ�
		int sY; //������ Y ��ǥ�� �ǹ�
		int eX; //���� X ��ǥ�� �ǹ�
		int eY; //���� Y ��ǥ�� �ǹ�
		float slope; //���⸦ �ǹ�

	};
	line_water * water_line; //line����ü�� water_line �� �̿�
	struct dot_water{ //dot�� �׸��� struct ����ü
		int X; //dot�� X��ǥ
		int Y; //dot�� Y��ǥ
	};
	dot_water * water_dot; //dot ����ü��  water_dot���� �̿�



    // Line segment and dot related variables
    int num_of_line, num_of_dot;
    float dot_diameter;
    
    /* WaterFall-related member functions */
    
    void processOpenFileSelection(ofFileDialogResult openFileResult);
    void initializeWaterLines(); // 2nd week portion.
		
};
