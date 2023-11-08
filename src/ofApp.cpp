#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundColor(0);
    ofSetVerticalSync(true);
    
    fu::SetLogLevel(FU_DEBUG);
    fu::SetLogWithTime(true);
    
    
    
    blurEffect.setup(640, 420);
    blurEffect.setName("Blur FX");
    blurEffect.setParameters(4,4);
    
    
    imageFbo.allocate(640, 420, GL_RGBA);
    
    
    global::model.setup(true);
    global::model.midiReceiver.setup("MPK mini 3");
    
    ndi.setup("ModeCollapseNDI", 1920 * 3, 1080);
    
    fu::setupGui();
}

//--------------------------------------------------------------
void ofApp::update(){

    global::model.midiReceiver.update();
    
    ofDisableArbTex();
    
    fu::gui.begin();
    {
        
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        ImGui::Begin("ModeCollapse");
        ImGui::PushID("ModeCollapse");
        {
            ImGuiContext& g = *GImGui;
            ImGuiIO& io = g.IO;
            ImGui::Text("FPS %.3f ms/f (%.1f fps", 1000.0f / io.Framerate, io.Framerate);
            
            ndi.gui();
            
            global::model.midiReceiver.gui(false);
            
            fu::Console.gui();
        }
        ImGui::PopID();
        ImGui::End();
        
    }
    fu::gui.end();
    
    ofEnableArbTex();
    
}



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

    
    if(currentCocoImage != nullptr) {
        
        imageFbo.begin();
        {
            ofPushMatrix();
            ofPushStyle();
//            ofClear(0);
//            ofFill();
            ofSetColor(255);
            
            currentCocoImage->img.draw(0, 0);
            ofPopMatrix();
            ofPopStyle();
        }
        imageFbo.end();
        
        blurEffect.process(imageFbo);
        
        ofFbo& renderFbo = ndi.getRender();
        renderFbo.begin();
        {
            blurEffect.getRender().draw(0, 0);
            imageFbo.draw(640, 0);
            ofNoFill();
            for(int i = 0; i < bboxs.size(); ++i){
                ofDrawRectangle(bboxs[i]);
                meshes[i].draw();
                ofDrawBitmapString(cats[i], bboxs[i].x, bboxs[i].y);
            }
        }
        renderFbo.end();
        ndi.publish();
//        renderFbo.draw(0,0);

    }
//    ofDrawBitmapString(os.str().c_str(), 20, ofGetHeight() - 20);
    
    fu::gui.draw();
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    fu::gui.exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
//    if(key == 'f') renderApp->toggleFullScreen();
//    if(key == 'v') renderApp->toggleVerticalSync();
    
    if(key == ' '){
        catIDX++;
        if(catIDX == global::model.cocoActualCategories.size()) catIDX = 0;
        bLoadNext = true;
    }

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
