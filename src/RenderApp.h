//
//  RenderApp.h
//  LaserLight
//
//  Created by lovelace on 15/8/2023.
//

#pragma once

#include "ofMain.h"
#pragma once

class RenderApp: public ofBaseApp {
    
public:
    
    void setup(){
        
        ofBackground(0);
        ofSetLogLevel(OF_LOG_VERBOSE);
        ofSetFullscreen(true);
        bVerticalSync = false;
        ofSetVerticalSync(bVerticalSync);
    }

    void update(){

    }

    void draw(){
        
        ofSetColor(255);
        
        if(renderFbo != nullptr){
            renderFbo->draw(0, 0, 1920, 1200);
        }
        
        ostringstream os;
        os << "FPS: " << ofGetFrameRate() << std::endl;
        ofDrawBitmapString(os.str(), 20, 20);
    }

    void toggleFullScreen(){
        ofToggleFullscreen();
    }
    
    void toggleVerticalSync(){
        bVerticalSync = !bVerticalSync;
        ofSetVerticalSync(bVerticalSync);
    }
    
    void setRenderFbo(ofFbo* fbo){
        renderFbo = fbo;
    }
    
    ofFbo* renderFbo = nullptr;
    bool bVerticalSync = false;
    
};
