#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
    ofAppGlutWindow window;
	
	//---------anti-aliasing---------
	//window.setGlutDisplayString("rgba double samples>=4 depth");  //mac
	//window.setGlutDisplayString("rgb double depth alpha samples>=4"); //pc 

	ofSetupOpenGL(&window, 640, 480, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
