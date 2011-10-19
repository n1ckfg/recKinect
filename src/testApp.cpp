#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	w = 640;
	h = 480;
	fps = 48;
	
	ofSetFrameRate(fps);
	ofBackground(250, 250, 250);

	kinect.init();
	kinect.setVerbose(false); //what does this do?
	kinect.enableDepthNearValueWhite(true);  //false makes a negative image
	kinect.open();

	//colorImage.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height,OF_IMAGE_GRAYSCALE);
	
	angle = 0;
	kinect.setCameraTiltAngle(angle);
	
	drawPC = false;  //what does this do?
	counter = 1;
	shot = 1;
	fileName = "foo";
	fileType = "raw";
	useName = false;
	record = false;
	fullscreen=false;
	timestampInterval=1000;
}

//--------------------------------------------------------------
void testApp::update(){

	kinect.update();
	kinect.getDepthPixels();

	
	
	depthArray = kinect.getDepthPixels();
    /*
	 depthArrayRaw = kinect.getRawDepthPixels();
		
	for(int i=0;i<w*h;i++) {
		float p = ofMap(depthArrayRaw[i],1040,530,255,0);
		depthArray[i] = (unsigned char) p;
	}

	grayImage.setFromPixels(depthArray, kinect.width, kinect.height);	
	 */

	
	if(record){
		int timestamp = ofGetElapsedTimeMillis(); //%timestampInterval;
		if(!useName){
			//sayText = "shot" + ofToString(shot) + "_frame" + ofToString(counter) + "_timestamp" + ofToString(timestamp) + "." + fileType;
			sayText = "shot" + ofToString(shot) + "_frame" + ofToString(counter) + "." + fileType;
		}else{
			sayText = fileName + "_" + sayText;
		}
		//ofSaveScreen(sayText);
		outfile.open(ofToDataPath(sayText).c_str(), ios::binary | ios::trunc);
		outfile.write ((char*)&timestamp,4);
		outfile.write ((char*)kinect.getRawDepthPixels(),2 * kinect.width * kinect.height);
		outfile.close();
		
		sayText="REC " + sayText;
		counter++;
	}else{
		sayText = "READY shot " + ofToString(shot);
	}
}

//--------------------------------------------------------------
void testApp::draw(){

	ofBackground(0, 0, 0);
	kinect.drawDepth(4, 0);
	//grayImage.draw(4,0);

	
	ofDrawBitmapString(sayText,40,35);
	showfps = ofGetFrameRate();
	ofDrawBitmapString(ofToString(showfps) + " fps", w-60,35);

 //rec dot
	
	 ofFill();
	if(record&&(counter%2!=0)) {
		ofSetColor(255,0,0);
	} 
	else {
		ofSetColor(35,0,0);
	}
	ofCircle(20,30,10);
	
	//safe
	ofNoFill();
	ofSetColor(255,255,255);	
	ofRect(3,59,633,360);
	ofLine((w/2)-10,(h/2),(w/2)+10,(h/2));
	ofLine((w/2),(h/2)-10,(w/2),(h/2)+10);
	
}

//--------------------------------------------------------------
void testApp::exit(){
	kinect.close();
}

//--------------------------------------------------------------
void testApp::keyPressed (int key){

	switch (key){

		case ' ':
			if(record){
				record=false;
				shot++;
				counter=1;
			}else{
				frame = 0;
				record=true;
			}
			break;
		
		/*
		 case 'f':
			if(fullscreen){
				fullscreen=false;
				ofToggleFullscreen();
			}else{
				fullscreen=true;
				ofToggleFullscreen();
			}
			break;
		 */
		
		/*
		 case 'w':
			kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
			break;
		 */
			
		case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;

		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
	}
}

