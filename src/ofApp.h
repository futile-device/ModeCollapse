#pragma once

#include "ofMain.h"
#include "ofxFutilities.h"

#include "GlobalModel.h"

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
    
};


/*
 ofDirectory dir;
 
 vector<int> imageIndexes;
 vector<ofImage> images;
 
 int mW;
 int mH;
 
 int tilesW;
 int tilesH;
 int tilesTotal;
 
 ofFbo fbo;
 fu::PBOPixels pbo;
 
 bool bIsSetup = false;
 
 ofPixels pix;
 bool bSave = false;
 */
