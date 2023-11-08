#include "ofApp.h"

int catIDX = 0;
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    global::model.setup(true);
    
}

//--------------------------------------------------------------
void ofApp::update(){


    
}

COCOImage* currentCocoImage = nullptr;
vector<ofRectangle> bboxs;
vector<ofMesh> meshes;
vector<string> cats;
ostringstream os;
bool bLoadNext = true;
//--------------------------------------------------------------
void ofApp::draw(){
    
    if(bLoadNext){
        
        bLoadNext = false;
        
        bboxs.clear();
        cats.clear();
        meshes.clear();
        
        ostringstream clr;
        os.swap(clr);
        
        string category = global::model.cocoActualCategories[catIDX];
        
        const vector<COCOImage*>& images = global::model.cocoImagesByCategoryIDX[category];
        int idx = (int)ofRandom(0, images.size());
        
        
        currentCocoImage = global::model.cocoImages[catIDX];//images[idx];
        currentCocoImage->load();
        
        for(int i = 0; i < currentCocoImage->annotations.size(); ++i){
            
            bboxs.push_back(currentCocoImage->annotations[i].bbox);
            cats.push_back(currentCocoImage->annotations[i].category);
            meshes.push_back(currentCocoImage->annotations[i].mesh);
            
        }
        
        os << category << " " << idx << " of " << images.size() << " =?= " << endl;
        
    }
    
    ofSetColor(255);
    if(currentCocoImage != nullptr) {
        currentCocoImage->img.draw(0, 0);
        ofNoFill();
        for(int i = 0; i < bboxs.size(); ++i){
            ofDrawRectangle(bboxs[i]);
            meshes[i].draw();
            ofDrawBitmapString(cats[i], bboxs[i].x, bboxs[i].y);
        }
    }
    ofDrawBitmapString(os.str().c_str(), 20, ofGetHeight() - 20);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    catIDX++;
    if(catIDX == global::model.cocoActualCategories.size()) catIDX = 0;
    bLoadNext = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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



/*
 
 
 int rW = 64 * 2;
 int rH = 42 * 2;
 
 //--------------------------------------------------------------
 void ofApp::setup(){

     
     
     
     
 //    dir.allowExt("jpg");
 //    dir.listDir("/Volumes/Kovalevskaya/MACHINE-LISTENING/VISUAL/val2017");
 //
 //
 //
 //    tilesW = 50;
 //    tilesH = 50;
 //    tilesTotal = tilesW * tilesH;
 //
 //    fbo.allocate(tilesW * rW, tilesH * rH, GL_RGBA);
 //    pbo.allocate(tilesW * rW, tilesH * rH, GL_RGBA, 2, fu::PBOPixels::PBO_READ);
 //    pix.allocate(tilesW * rW, tilesH * rH, OF_IMAGE_COLOR_ALPHA);
     
 }

 //--------------------------------------------------------------
 void ofApp::update(){

 //    if(!bIsSetup){
 //
 //        bIsSetup = true;
 //
 //        fu::debug << "START TILING" << fu::endl;
 //
 //        images.clear();
 //        imageIndexes.clear();
 //
 //        fu::vecutils::uniqueRandomIndex(imageIndexes, (int)dir.size());
 //
 //        for(int i =0; i < dir.size(); ++i){
 //
 //            if(images.size() == tilesTotal) {
 //                fu::debug << "FINISHED!" << fu::endl;
 //                break;
 //            }
 //
 //            ofImage img;
 //            img.load(dir.getFile(imageIndexes[i]).getAbsolutePath());
 //
 //            if(img.getWidth() == 640 && img.getHeight() >= 420){
 //
 //                fu::debug << "Found image: " << img.getWidth() << " x " << img.getHeight() << fu::endl;
 //
 //                int cropY = ceil((img.getHeight() - 420) / 2.0);
 //                img.crop(0, cropY, 640, 420);
 //
 //                fu::debug << "Cropped image: " << img.getWidth() << " x " << img.getHeight() << fu::endl;
 //                fu::debug << "Number of Images: " << images.size() << " of " << tilesTotal << fu::endl;
 //                img.resize(rW, rH);
 //
 //                images.push_back(img);
 //
 //            }
 //
 //        }
 //
 //        fbo.begin();
 //        {
 //
 //            ofClear(0, 0, 0, 255);
 //            ofSetColor(255);
 //
 //            for(int yLine = 0; yLine < tilesH; ++yLine){
 //                for(int xLine = 0; xLine < tilesW; ++xLine){
 //                    int tileN = yLine * tilesW + xLine;
 //                    images[tileN].draw(xLine * rW, yLine * rH, rW, rH);
 //                    fu::debug << xLine * rW << " :: " << yLine * rH << fu::endl;
 //                }
 //            }
 //
 //        }
 //        fbo.end();
 //
 //
 //    }
     
 }

 //--------------------------------------------------------------
 void ofApp::draw(){
     
 //    pbo.readPixels(fbo, pix);
 //
 //    ofImage sImage;
 //    sImage.setFromPixels(pix);
 //    sImage.update();
 //
 //    if(bSave){
 //
 //        bSave = false;
 //
 //
 //        sImage.save(ofToDataPath("node.png"));
 //    }
 //
 //    ofSetColor(255);
 //
 //    sImage.draw(0, 0, ofGetWidth(), ofGetHeight());
     
 }

 //--------------------------------------------------------------
 void ofApp::keyPressed(int key){
 //    if(key == 's') bSave = true;
 }
 */
