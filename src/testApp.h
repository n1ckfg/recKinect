#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxKinect.h"

class testApp : public ofBaseApp
{

	public:

		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed  (int key);
	
		ofxKinect kinect;

		//ofxCvColorImage		colorImage;
		//ofxCvGrayscaleImage 	grayImage;
	    ofImage grayImage;
	
		int w;
		int h;
		int fps;
		int showfps;
	
		bool drawPC;
		int	angle;
		int counter;
		int shot;

		string fileName;
		string fileType;
		bool useName;
		bool record;
		string sayText;
		bool fullscreen;
	
		unsigned short int * depthArrayRaw;	
		unsigned char * depthArray;
	
		ofstream outfile;
		int frame;
		int timestampInterval;
};

#endif
