#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second
	ofSetBackgroundAuto(false); //�׸��� �׸��� �׸� �׸��� ��� �����ǵ��� �����Ѵ�
    // We still want to draw on a black background, so we need to draw
    // the background before we do anything with the brush
    ofBackground(255,255,255); //�� ����� ������� ����
    ofSetLineWidth(4); //�β��� 4�� ����
    
    draw_flag = 0; //�׸��� �׸��� �ִ��� Ȯ���ϴ� flag
    load_flag = 0; //������ �ҷ��Դ��� Ȯ���ϴ� flag
    dot_diameter = 20.0f; //dot�� ���� ����
}

//--------------------------------------------------------------
void ofApp::update() {
	if (water_flag == 1) //waterflag�� 1�̶�� ���� �������°� �����Ѵٴ� �ǹ�
	{
		if (ofGetHeight()-40 > water_y2) { //���� ���� ������ y2 ��ǥ�� ofGetHeight-40���� ������ ������ ���� ���������� ����
			if (water_x1 == 0 && water_y1 == 0) { //���� �������� ù �������� �ƴ��� Ȯ�� 
				vertical_flag = 1; //ó�� ���� ���������� �������� ���������ϴ� vertical_flag�� 1�� �д�
				water_x1 = water_dot[check].X; //���� x1,y1,x2,y2 ��ǥ�� ��� ó�� ���� ������ ���� ��ǥ�� �ʱ�ȭ���ش�.
				water_y1 = water_dot[check].Y;
				water_x2 = water_dot[check].X;
				water_y2 = water_dot[check].Y;
			}
			int i = 0;
			for (i = 0; i < num_of_line; i++) //��ü line�� for���� ���� ���� ������ ������ ��� Ž���غ��� 
			{
				if (water_y1 > water_line[i].eY && water_y1 > water_line[i].sY) //���� y1�� ��ǥ�� line�� �� �� y��ǥ���� ũ�ٸ� ��, line�� ���� �������� �������� ���� �ִٴ� �ǹ��̹Ƿ� Ž���� ������ �ʿ� ����
					continue; //continue�� ���� for������ �̵�
				
				if (abs(water_y2 - (water_line[i].slope*(water_x2 - water_line[i].eX) + water_line[i].eY)) < 3) //���� ���� y2��ǥ - (line�Լ��� x2��ǥ�� ���� ��) �� ���밪�� 2���� �۴ٸ�
				{
					if ((water_line[i].sY <= water_y2 && water_y2<= water_line[i].eY) || (water_line[i].eY <= water_y2&&water_y2 <= water_line[i].sY)) { //���� y2�� ��ǥ�� line�� �� �� y��ǥ ���̿� �ִٸ�
						vertical_flag = 0; //verticial flag�� 0���� �ξ� ���� ������ �ƴ� line�� ���� �帣���� ��
						break; //line�� ã������ ���̻� for�� Ž�� �ʿ� ����
					}
					vertical_flag = 1; //�ƴ϶�� ���� �������� ���������� vertical_Flag�� 1�� �� 
				}
				else vertical_flag = 1; //�ƴ϶�� ���� �������� ����������
		
			}
			if (vertical_flag != start_flag) //vertical_flag�� start_flag�� �ٸ��ٸ� ���� ǥ���� line�� ù �������� �ٲ����Ѵٴ� �ǹ�
			{
				water_x1 = water_x2; //ù ������ x��ǥ�� water_x2�� �Ѵ�
				water_y1 = water_y2; //ù ������ y��ǥ�� water_y2�� �Ѵ�
				start_flag = vertical_flag; //startflag�� verticalflag�� ���� �Ͽ� ù �������� �ٲ���ٰ� �˸�
			}
			if (vertical_flag == 1) //vertical_flag�� 1�̶�� ���� �������� ���������ϹǷ�
				water_y2 += 3; //water�� �׸��� line�� �� y2��ǥ�� �Ʒ��� �� �׸����� y2�� ����ġ�� �����ش�
			else {//���� line�� ����� ���� �귯���ϱ� ������
				if (water_line[i].slope > 0) //���� slope�� 0���� ũ�ٸ�
					water_x2 += 3; //water_x2�� ����ġ�� �����ְ�
				else water_x2 -= 3; //slope�� 0���� ������ water_x2�� ����ġ�� ���ش�
				water_y2 = water_line[i].slope*(water_x2 - water_line[i].eX) + water_line[i].eY; //���� line�Լ��� water_x2 ��ǥ�� ���� ���� water_y2�� �Ѵ� 
			}
		}
		else {
			water_flag = 0; //���̻� ���� ������ ���� �����Ƿ� water_flag�� 0���� �ٲ۴�.
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(127,23,31);  // Set the drawing color to brown
    
    // Draw shapes for ceiling and floor
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofSetLineWidth(5);
    
    
    ofSetLineWidth(5); //line�β��� �ǹ��Ѵ�
	if (draw_flag) { //drag_flag�� 1 �̹Ƿ� �׸� �� �ִ�
		int i = 0; //dot�� �׸� �� ����ϴ� index
		while (i != num_of_dot) { //i�� 0���� �����ϹǷ� num_of_dots �������� ���� ������ �ݺ��� ���ƾ���
			if (i == check) ofSetColor(255, 0, 0); //i�� check�� ���ٸ� �� ���� ���� ���;��ϴ� ���̹Ƿ� ���������� ǥ��
			else ofSetColor(0, 0, 0); //�׷��� �ʴٸ� ���������� dot ǥ��
			ofDrawCircle(water_dot[i].X, water_dot[i].Y, dot_diameter / 2); //�ش� ����� ��ǥ�� �̿��� ���� �׸���
			i++;//i 1 ����
		}
		i = 0; //i �� 0���� �ξ� �ٽ� line�� �׸��� ����ϴ� index�� �̿��Ѵ�
		while (i != num_of_line) //i�� 0���� �����ϹǷ� num_of_line �������� ���� ������ �ݺ��� ����
		{
			ofSetColor(127, 23, 31); //������ �ٽ� brown
			ofDrawLine(water_line[i].sX, water_line[i].sY, water_line[i].eX, water_line[i].eY); //ofDrawLine �Լ��� ���� �ش� ��ǥ�� �ش��ϴ� ������ �׷��ش�
			i++; //i 1 ���� �Ͽ� ���� index ����

		}
		/* COMSIL1-TODO 3 : Draw the line segment and dot in which water starts to flow in the screen.
		 Note that after drawing line segment and dot, you have to make selected water start dot colored in red.
		 */

	}
        
        // 2nd week portion.
        ofSetLineWidth(2); //line �β��� �ǹ�
		if (water_flag == 1) //water_flag�� 1�̶�� ���̶������� ���� line���� �׸���
		{
			ofSetLineWidth(5); //�β��� 5�� �����ϰ�
			ofSetColor(0, 0, 255); //������ blue�̴�
			ofDrawLine(water_x1, water_y1, water_x2, water_y2);//water_x1, water_y1�� line�� ������, water_x2,water_y2�� line�� �������� ����ؼ� ��ġ�� �׸���.
		}
	
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'v') {
        // HACK: only needed on windows, when using ofSetAutoBackground(false)
        glReadBuffer(GL_FRONT);
        ofSaveScreen("savedScreenshot_"+ofGetTimestampString()+".png");
    }
    if (key == 'q'){ //q�� ������ flag�� reset �ϰ� �޸� �Ҵ�������� free ���������
        // Reset flags
        draw_flag = 0; //draw_flag�� �ٽ� 0���� ���ش�
		delete[] water_line; //�Ҵ���� water_line �޸� ����
		delete[] water_dot; //�Ҵ���� water_dot �޸� ����
        // Free the dynamically allocated memory exits.
        
        cout << "Dynamically allocated memory has been freed." << endl;
        
        _Exit(0);
    }
    if (key == 'd'){
        if( !load_flag) return; //load_flag�� 0�� ��� ���� L �� �ȴ����� ������ ���� ������ �ٷ� return �Ѵ�
        
		draw_flag = 1; //draw_flag�� 1�� �����Ͽ� ������ ���� �׸� �� �ְ� �Ѵ�
		load_flag = 0; //�ٽ� load_flag �ʱ�ȭ
		water_x1 = 0; water_x2 = 0; water_y1 = 0; water_y2 = 0;//���� �׸� line�� ��ǥ���� 0���� �ʱ�ȭ �����ش�.
        /* COMSIL1-TODO 2: This is draw control part.
        You should draw only after when the key 'd' has been pressed.
        */
    }
    if (key == 's'){//���� �귯���Ѵ�
        // 2nd week portion.
		if (draw_flag == 1) //draw_flag�� 1�̶�� line�� dot �׸��� �׷����ٴ� �ǹ��̹Ƿ� ���� �带 �� �ִ�.
		{
			water_flag = 1;
		} //water_flag�� 1�� �ٲ� update�Լ����� ���� �帣�� ����� �ϵ��� �Ѵ�
		start_flag = 1; //ù start_flag�� 1�� �����Ͽ� ó�� vertical flag�� ������ ���ش�.
		draw_flag = 0; //draw_flag�� �ٽ� 0���� �ٲ��ش�.
		
		//ofSetBackgroundAuto(true);
		ofSetBackgroundAuto(false); //�� line�� ����ؼ� ��ġ�� �׸� �� �ֵ��� ofsetbackgroundauto�� false�� �Ѵ�.
    }
	if (key == 'e') { //���� ���̻� �������� �ȵȴ�
		if (draw_flag == 1 || water_flag == 1) // ���� �׸��� �׷��� �ִٸ� e ������ ���� ������� �Ѵ�
		{
			water_flag = 0; //water_flag�� 0���� �ξ� update�Լ����� ���̻� �� �帣�� ����� ���ϰ� �Ѵ�.
			draw_flag = 1; //draw_flag�� 1�� �ξ� �ٽ� �ٸ� dot���� 's'�� ������ ���� �����ϰ� �Ѵ�.
			water_x1 = 0; water_x2 = 0; water_y1 = 0; water_y2 = 0; //���� �׸� line ��ǥ���� 0���� �ʱ�ȭ�Ѵ�.
			ofSetBackgroundAuto(true); //���� ���̻� �׷����� �ȵǱ� ������ ofsetbackgroundauto�� true�� �Ͽ� ���� �׷������� ���ش�.
		}// 2nd week portion.
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) { //key�� I�� �����ٸ� ������ ���� ������ �ҷ��;��Ѵ�
	if (key == 'l') {
		// Open the Open File Dialog
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a only txt for Waterfall");

		// Check whether the user opened a file
		if (openFileResult.bSuccess) {
			ofLogVerbose("User selected a file");

			// We have a file, so let's check it and process it
			processOpenFileSelection(openFileResult);
			load_flag = 1; //���������� �ҷ������Ƿ� load_flag�� 1�� ������ ���� ������ ������ �˸�
			water_flag = 0; //���� ���� �������� �ȵǱ� ������ water_flag �ʱ�ȭ
			check = 0; //check ����  �ʱ�ȭ
			ofClear(255, 255, 255); //l�� ������ ȭ���� �ѹ� �ʱ�ȭ ���ش� 
		}
	}

	/* COMSIL1-TODO 4: This is selection dot control part.
	 You can select dot in which water starts to flow by left, right direction key (<- , ->).
	 */
	if (water_flag==0&&num_of_dot != 0) { //water_Flag�� 0�̰� dot ������ ���� ���� ����Ű �����̵��� ����
		if (key == OF_KEY_RIGHT) { //������Ű�� �����ٸ� ���� ������ dot�� ���������� ��ĭ �̵��ؾ� �ϹǷ� check�� 1 ������Ų��
			check = check + 1;
			if (check == num_of_dot) //���� check�� num_of_dot �� ���ٸ� �ش� dot�� ���� ���� dot�̹Ƿ� check�� 0���� ����
				check = 0;


			cout << "Selcted Dot Coordinate is (" << water_dot[check].X << ", " << water_dot[check].Y << ")" << endl;
		}//�ش���ġ�� dot X,Y ��ǥ�� ����Ѵ�
		if (key == OF_KEY_LEFT) { //����Ű�� ���ȴٸ� ���� ������ dot�� �������� ��ĭ �̵��ؾ� �ϹǷ� check�� 1 ���ҽ�Ų��
			check = check - 1;
			if (check == -1) //check�� -1 �̶�� �ش� dot�� ���� ������ dot�� �ǹ��ϹǷ�
				check = num_of_dot - 1; //check�� num_of_dot-1�� �����Ѵ�

			cout << "Selcted Dot Coordinate is (" << water_dot[check].X << ", " << water_dot[check].Y << ")" << endl;
		}//�ش���ġ�� dot X,Y��ǥ�� ����Ѵ�
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
 
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) { 
    //Path to the comma delimited file
    //string fileName = "input.txt";
    
    string fileName = openFileResult.getName();
    ofFile file(fileName);
    
    if( !file.exists()) cout << "Target file does not exists." << endl;
    else cout << "We found the target file." << endl;
    //�������������� check�ϰ� �׿� �´� ������ ������ش�
    ofBuffer buffer(file);
    
    /* This variable is for indicating which type of input is being received.
     IF input_type == 0, then work of getting line input is in progress.
     IF input_type == 1, then work of getting dot input is in progress.
     */
    int input_type = 0; //���� ����� �����Ѱ�ó�� input_type�� ���� line�������� dot�������� Ȯ���Ѵ�
    
    
    /* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
     You must maintain those information. But, currently below code is not complete.
     Also, note that all of coordinate should not be out of screen size.
     However, all of coordinate do not always turn out to be the case.
     So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
    */
	bool index = false; //index�� �̿��ϴ� bool flag
	int i = 0; //water_line, water_dot ����ü �迭�� index i�� �ǹ��Ѵ�
    // Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        
        // Split line into strings
        vector<string> words = ofSplitString(line, " ");
        
	


        if( words.size() == 1){ //size�� 1 �̸� line�̳� dot �� ������ �ǹ��Ѵ�
            if( input_type == 0){ // Input for the number of lines.
                num_of_line = atoi(words[0].c_str()); //num_of_line�� int�� �޾ƿ´�
				water_line = new line_water[num_of_line]; //water_line�� num_of_line��ŭ�� �迭�� ���� �޸� �Ҵ��� ���ش�.
                cout << "The number of line is: " << num_of_line << endl;  //���� ���
				
			}

            else{ // Input for the number of dots.
                num_of_dot = atoi(words[0].c_str()); //num_of_dot�� int�� ����
				water_dot = new dot_water[num_of_dot]; //water_dot�� num_of_dot��ŭ�� �迭�� ���� �޸� �Ҵ��� ���ش�
                cout << "The number of dot is: " << num_of_dot << endl;//���� ���
				
            }
			if (num_of_line == 0)
				input_type = 1; //num_of_line�� 0�϶�
        }

		

        else if (words.size() >= 2){//size�� 2���� ũ�ų� ������ ��ǥ�� �ش�
			
			if (i == num_of_line&&index==false)//index i �� num_of_line�� ���� index flag�� false��� line�� �� �޾Ҵٴ� �ǹ��̹Ƿ� ���� i �� water_dot�� ���� index�� �ǰ�
			{
				i = 0; 
			}//0���� �ʱ�ȭ
		

            int x1,y1,x2,y2; //��ǥ�� �޴� ����
			
			


			if (input_type == 0) { // Input for actual information of lines 
					
				if (i + 1 == num_of_line)//���� i+1�� num_of_line�� ���ٸ� ���� for�����ʹ� dot ��ǥ�� �޾ƾ��ϱ� ������
					input_type = 1; //input_type�� 1�� �����Ͽ� �� �̻� water_line�� ���ٸ��ϰ� �Ѵ�
					x1 = atoi(words[0].c_str()); //������� x1,y1,x2,y2 ��ǥ�� �޾ƿ´�
					y1 = atoi(words[1].c_str());
					x2 = atoi(words[2].c_str());
					y2 = atoi(words[3].c_str());
					water_line[i].sX = x1; //water_line ����ü �迭�� ���� x1,y1,x2,y2 ��ǥ�� �����Ѵ�
					water_line[i].sY = y1;
					water_line[i].eX = x2;
					water_line[i].eY = y2;
					water_line[i].slope = double(y2 - y1) / double(x2 - x1); //�� water_line�� ���⸦ ���Ͽ� �����Ѵ�.
				
					i++; //i�� �������� ���� index�� �̵��ϰ� ���ش�

				
			}
            else{ // Input for actual information of dots. //input_type�� 1 �϶��� dot ��ǥ�� �޾ƿ´�
				index = true;
				x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
				water_dot[i].X = x1; //water_dot ����ü �迭�� x1,y1 ��ǥ�� �����Ѵ�
				water_dot[i].Y = y1;

				i++; //i�� �������� ���� index�� �̵��ϰ� ��
            }
        } // End of else if.
    } // End of for-loop (Read file line by line).
    //initializeWaterLines();
}

void ofApp::initializeWaterLines() {
    ;
}


