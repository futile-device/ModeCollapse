//
//  CocoTypes.h
//  ModeCollapse
//
//  Created by lovelace on 6/11/2023.
//

#include "ofMain.h"
#include "ofxFutilities.h"

#pragma once

static string cocoImgPath = "/Volumes/Mirzakhani/ACT_DATA/val2017/";

struct COCOCategory{
    int idx;
    string subCategory;
    string superCategory;
};

struct COCOAnnotation{
    
    int imageIDX;
    int categoryIDX;
    string category;
    ofMesh mesh;
    ofRectangle bbox;
    
};

class COCOImage{
    
public:
    
    COCOImage(){};
    
    ~COCOImage(){

    };
    
    inline void setup(const string& fileName,
                      const int& idx,
                      const int& width,
                      const int& height){
        
        imageName = fileName;
        imagePath = cocoImgPath + fileName;
        imageIDX = idx;
        originalWidth = width;
        originalHeight = height;
        
        cropX = ceil((originalWidth - 640) / 2.0);
        cropY = ceil((originalHeight - 420) / 2.0);
        
        
    }
    
    inline void load(){
        if(img.getWidth() == 0 && img.getHeight() == 0){
            img.load(imagePath);
            img.crop(cropX, cropY, 640, 420);
        }
    }
    
    inline void resizeAnnotations(){
        
        for(COCOAnnotation& an : annotations){
            
            an.bbox.x -= cropX;
            an.bbox.y -= cropY;
            an.bbox.x = CLAMP(an.bbox.x, 0, an.bbox.x);
            an.bbox.y = CLAMP(an.bbox.y, 0, an.bbox.y);
            
            int x2 = an.bbox.x + an.bbox.width;
            int y2 = an.bbox.y + an.bbox.height;
            
            x2 = CLAMP(x2, 0, 640);
            y2 = CLAMP(y2, 0, 420);
            
            an.bbox.width = x2 - an.bbox.x;
            an.bbox.height = y2 - an.bbox.y;
            
            for(glm::vec3& v : an.mesh.getVertices()){
                v.x -= cropX;
                v.y -= cropY;
                v.x = CLAMP(v.x, 0, 640);
                v.y = CLAMP(v.y, 0, 420);
            }
            
        }
        
    }
    
    vector<COCOAnnotation> annotations;
    
    int imageIDX = -1;
    
    string imageName = "";
    string imagePath = "";
    
    ofImage img;
    
    int originalWidth;
    int originalHeight;
    
    int cropY = 0;
    int cropX = 0;
    
};
