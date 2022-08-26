#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second
    
    // We still want to draw on a black background, so we need to draw
    // the background before we do anything with the brush
    ofBackground(255,255,255); //뒤 배경을 흰색으로 설정
    ofSetLineWidth(4); //두께는 4로 설정
    
    draw_flag = 0; //그림을 그릴수 있는지 확인하는 flag
    load_flag = 0; //파일을 불러왔는지 확인하는 flag
    dot_diameter = 20.0f; //dot의 지름 설정
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(127,23,31);  // Set the drawing color to brown
    
    // Draw shapes for ceiling and floor
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofSetLineWidth(5);
    
    
    ofSetLineWidth(5); //line두께를 의미한다
    if( draw_flag ){ //drag_flag가 1 이므로 그릴 수 있다
		int i=0; //dot을 그릴 때 사용하는 index
		while (i != num_of_dot) { //i는 0부터 시작하므로 num_of_dots 개수보다 작을 때까지 반복문 돌아야함
			if (i == check) ofSetColor(255, 0, 0); //i랑 check가 같다면 그 점이 물이 나와야하는 점이므로 빨간색으로 표시
			else ofSetColor(0, 0, 0); //그렇지 않다면 검은색으로 dot 표시
			ofDrawCircle(water_dot[i].X, water_dot[i].Y, dot_diameter/2); //해당 저장된 좌표를 이용해 원을 그린다
			i++;//i 1 증가
		}
		i = 0; //i 를 0으로 두어 다시 line을 그릴때 사용하는 index로 이용한다
		while (i != num_of_line) //i는 0부터 시작하므로 num_of_line 개수보다 작을 때까지 반복문 돈다
		{
			ofSetColor(127, 23, 31); //색깔을 다시 brown
			ofDrawLine(water_line[i].sX, water_line[i].sY, water_line[i].eX, water_line[i].eY); //ofDrawLine 함수를 통해 해당 좌표에 해당하는 선분을 그려준다
			i++; //i 1 증가 하여 다음 index 접근

		}
        /* COMSIL1-TODO 3 : Draw the line segment and dot in which water starts to flow in the screen.
         Note that after drawing line segment and dot, you have to make selected water start dot colored in red.
         */

        
        
        // 2nd week portion.
        ofSetLineWidth(2); //line 두께를 의미
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'v') {
        // HACK: only needed on windows, when using ofSetAutoBackground(false)
        glReadBuffer(GL_FRONT);
        ofSaveScreen("savedScreenshot_"+ofGetTimestampString()+".png");
    }
    if (key == 'q'){ //q를 누르면 flag를 reset 하고 메모리 할당받은것을 free 시켜줘야함
        // Reset flags
        draw_flag = 0; //draw_flag를 다시 0으로 해준다
		delete[] water_line; //할당받은 water_line 메모리 해제
		delete[] water_dot; //할당받은 water_dot 메모리 해제
        // Free the dynamically allocated memory exits.
        
        cout << "Dynamically allocated memory has been freed." << endl;
        
        _Exit(0);
    }
    if (key == 'd'){
        if( !load_flag) return; //load_flag가 0이 라면 아직 L 이 안눌러져 정보가 없기 때문에 바로 return 한다
        
		draw_flag = 1; //draw_flag를 1로 설정하여 직선과 선을 그릴 수 있게 한다
		load_flag = 0; //다시 load_flag 초기화
        /* COMSIL1-TODO 2: This is draw control part.
        You should draw only after when the key 'd' has been pressed.
        */
    }
    if (key == 's'){
        // 2nd week portion.
    }
    if (key == 'e'){
        // 2nd week portion.
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) { //key를 I로 눌렀다면 파일을 열어 정보를 불러와야한다
	if (key == 'l') {
		// Open the Open File Dialog
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a only txt for Waterfall");

		// Check whether the user opened a file
		if (openFileResult.bSuccess) {
			ofLogVerbose("User selected a file");

			// We have a file, so let's check it and process it
			processOpenFileSelection(openFileResult);
			load_flag = 1; //파일정보를 불러왔으므로 load_flag를 1로 설정해 파일 정보가 있음을 알림
			check = 0; //check 변수  초기화
		}
	}

	/* COMSIL1-TODO 4: This is selection dot control part.
	 You can select dot in which water starts to flow by left, right direction key (<- , ->).
	 */
	if (num_of_dot != 0) { //dot 개수가 있을 때만 방향키 움직이도록 설정
		if (key == OF_KEY_RIGHT) { //오른쪽키를 누른다면 물이 떨어질 dot이 오른쪽으로 한칸 이동해야 하므로 check를 1 증가시킨다
			check = check + 1;
			if (check == num_of_dot) //만약 check와 num_of_dot 이 같다면 해당 dot은 가장 왼쪽 dot이므로 check를 0으로 설정
				check = 0;


			cout << "Selcted Dot Coordinate is (" << water_dot[check].X << ", " << water_dot[check].Y << ")" << endl;
		}//해당위치의 dot X,Y 좌표를 출력한다
		if (key == OF_KEY_LEFT) { //왼쪽키가 눌렸다면 물이 떨어질 dot이 왼쪽으로 한칸 이동해야 하므로 check를 1 감소시킨다
			check = check - 1;
			if (check == -1) //check가 -1 이라면 해당 dot은 가장 오른쪽 dot을 의미하므로
				check = num_of_dot - 1; //check를 num_of_dot-1로 설정한다

			cout << "Selcted Dot Coordinate is (" << water_dot[check].X << ", " << water_dot[check].Y << ")" << endl;
		}//해당위치의 dot X,Y좌표를 출력한다
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
    //파일존재유무를 check하고 그에 맞는 정보를 출력해준다
    ofBuffer buffer(file);
    
    /* This variable is for indicating which type of input is being received.
     IF input_type == 0, then work of getting line input is in progress.
     IF input_type == 1, then work of getting dot input is in progress.
     */
    int input_type = 0; //위에 영어로 설명한거처럼 input_type을 통해 line정보인지 dot정보인지 확인한다
    
    
    /* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
     You must maintain those information. But, currently below code is not complete.
     Also, note that all of coordinate should not be out of screen size.
     However, all of coordinate do not always turn out to be the case.
     So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
    */
	bool index = false; //index에 이용하는 bool flag
	int i = 0; //water_line, water_dot 구조체 배열의 index i를 의미한다
    // Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        
        // Split line into strings
        vector<string> words = ofSplitString(line, " ");
        
	


        if( words.size() == 1){ //size가 1 이면 line이나 dot 의 개수를 의미한다
            if( input_type == 0){ // Input for the number of lines.
                num_of_line = atoi(words[0].c_str()); //num_of_line을 int로 받아온다
				water_line = new line_water[num_of_line]; //water_line에 num_of_line만큼의 배열을 가진 메모리 할당을 해준다.
                cout << "The number of line is: " << num_of_line << endl;  //정보 출력
				
			}

            else{ // Input for the number of dots.
                num_of_dot = atoi(words[0].c_str()); //num_of_dot을 int로 받음
				water_dot = new dot_water[num_of_dot]; //water_dot에 num_of_dot만큼의 배열을 가진 메모리 할당을 해준다
                cout << "The number of dot is: " << num_of_dot << endl;//정보 출력
				
            }
			if (num_of_line == 0)
				input_type = 1; //num_of_line이 0일때
        }

		

        else if (words.size() >= 2){//size가 2보다 크거나 같으면 좌표에 해당
			
			if (i == num_of_line&&index==false)//index i 가 num_of_line과 같고 index flag가 false라면 line을 다 받았다는 의미이므로 이제 i 는 water_dot에 관한 index가 되고
			{
				i = 0; 
			}//0으로 초기화
		

            int x1,y1,x2,y2; //좌표를 받는 변수
			
			


			if (input_type == 0) { // Input for actual information of lines 
					
				if (i + 1 == num_of_line)//만약 i+1이 num_of_line과 같다면 다음 for문부터는 dot 좌표를 받아야하기 때문에
					input_type = 1; //input_type을 1로 설정하여 더 이상 water_line에 접근못하게 한다
					x1 = atoi(words[0].c_str()); //순서대로 x1,y1,x2,y2 좌표를 받아온다
					y1 = atoi(words[1].c_str());
					x2 = atoi(words[2].c_str());
					y2 = atoi(words[3].c_str());
					water_line[i].sX = x1; //water_line 구조체 배열에 각각 x1,y1,x2,y2 좌표를 저장한다
					water_line[i].sY = y1;
					water_line[i].eX = x2;
					water_line[i].eY = y2;
					i++; //i를 증가시켜 다음 index로 이동하게 해준다

				
			}
            else{ // Input for actual information of dots. //input_type이 1 일때는 dot 좌표를 받아온다
				index = true;
				x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
				water_dot[i].X = x1; //water_dot 구조체 배열에 x1,y1 좌표를 저장한다
				water_dot[i].Y = y1;
				i++; //i를 증가시켜 다음 index로 이동하게 함
            }
        } // End of else if.
    } // End of for-loop (Read file line by line).
    //initializeWaterLines();
}

void ofApp::initializeWaterLines() {
    ;
}


