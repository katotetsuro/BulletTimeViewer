#pragma once

#include "ofMain.h"
#include "ofxQTKitAVScreenRecorder.h"

/*
 * Simple Class
 * ofImage + position
 */

namespace nistetsurooy {
    class Image : public ofImage {
    public:
        Image() : ofImage(), pos(0,0) { }
        ofVec2f pos;
        void draw() { ofImage::draw(pos); }
    };
}

typedef vector<ofPtr<nistetsurooy::Image> > ImageArray;
typedef ImageArray::iterator ImageIterator;

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit() { save(); }

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        void save();
        void load();
    
    ImageArray images;
    ImageIterator iterator;
    bool showPreviousImage;
    ofxQTKitAVScreenRecorder screenRecorder;
    ofImage screen;
};
