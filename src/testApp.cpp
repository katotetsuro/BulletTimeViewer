#include "testApp.h"
#include "ofxXmlSettings.h"

using namespace nistetsurooy;

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(0);
    
    ofDirectory dir;
    int length = dir.listDir("images");
    for (int i=0; i<length; ++i) {
        ofPtr<Image> pImage(new Image());
        if (pImage->loadImage(dir.getFile(i)) ) {
            images.push_back(pImage);
        }
    }
    
    load();
    
    iterator = images.begin();
    
    showPreviousImage = false;
    
    screenRecorder.setup();
    
    ofSetWindowShape((*iterator)->getWidth(), (*iterator)->getHeight());
    screen.allocate((*iterator)->getWidth(), (*iterator)->getHeight(), OF_IMAGE_COLOR);
    
}

//--------------------------------------------------------------
void testApp::update(){
    if (screenRecorder.getIsRecording()) {
        screen.grabScreen(0, 0, screen.width, screen.height);
        screenRecorder.addFrame(screen.getPixelsRef());
        screenRecorder.update();
    }
}

//--------------------------------------------------------------
void testApp::draw() {
    
    if (showPreviousImage) {
        ImageIterator previous = iterator;
        if (previous == images.begin()) {
            previous = images.end();
        }
        --previous;
        
        ofPushStyle();
        ofEnableAlphaBlending();
        ofSetColor(ofColor::blue, 125);
        (*previous)->draw();
        ofSetColor(ofColor::red, 125);
        (*iterator)->draw();
        ofPopStyle();
    } else {
        (*iterator)->draw();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
        case OF_KEY_LEFT:
            if (iterator == images.begin()) {
                iterator = images.end();
            }
            --iterator;
            break;
            
        case OF_KEY_RIGHT:
            if (++iterator == images.end()) {
                iterator = images.begin();
            }
            break;
        
        case 'a':
            showPreviousImage = !showPreviousImage;
            break;
            
        case 'h':
            (*iterator)->pos.x--;
            break;
            
        case 'j':
            (*iterator)->pos.y++;
            break;
            
        case 'k':
            (*iterator)->pos.y--;
            break;
            
        case 'l':
            (*iterator)->pos.x++;
            break;
            
        case 'r':
            if (screenRecorder.getIsRecording()) {
                screenRecorder.finishMovie();
            } else {
                screenRecorder.startNewRecording();
            }
            
            break;
            
        case 's':
            save();
            break;
            
        default:
            break;
    }
}

void testApp::save() {
    ofxXmlSettings xml;
    for (int i=0; i<images.size(); ++i) {
        xml.addTag("position");
        xml.addAttribute("position", "x", images[i]->pos.x, i);
        xml.addAttribute("position", "y", images[i]->pos.y, i);
    }
    xml.saveFile("positions.xml");
}

void testApp::load() {
    ofxXmlSettings xml;
    if (xml.loadFile("positions.xml")) {
        int length = min (xml.getNumTags("position"), static_cast<int>(images.size()));
        for (int i=0; i<length; ++i) {
            images[i]->pos.x = xml.getAttribute("position", "x", 0.0f, i);
            images[i]->pos.y = xml.getAttribute("position", "y", 0.0f, i);
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}