//
//  GlobalModel.h
//  ModeCollapse
//
//  Created by lovelace on 6/11/2023.
//

#include "ofMain.h"
#include "ofxFutilities.h"
#include "CocoTypes.h"

#pragma once



class GlobalModel{
    
public:
    
    GlobalModel(){};
    ~GlobalModel(){};
    
    void setup(bool bForceLoad){
        
        if(bForceLoad){
            
            ofJson json = ofLoadJson("/Volumes/Mirzakhani/ACT_DATA/annotations/instances_val2017.json");
            
            for(int i = 0; i < json["images"].size(); ++i){
                ofJson imgJson = json["images"].at(i);
//                fu::debug << imgJson["file_name"] << fu::endl;
                if(imgJson["width"] >= 640 && imgJson["height"] >= 420){
                    COCOImage* img = new COCOImage;
                    img->setup(imgJson["file_name"],
                               imgJson["id"],
                               imgJson["width"],
                               imgJson["height"]);
                    // force creation of map reference so we can easily check if we're segmenting this image
                    cocoAnnotationsByImageIDX[img->imageIDX] = vector<COCOAnnotation>();
                    cocoImages.push_back(img);
                }
            } // images

            fu::info << "Total image files: " << cocoImages.size() << fu::endl;

            for(int i = 0; i < json["categories"].size(); ++i){

                ofJson catJson = json["categories"].at(i);

                COCOCategory cat;
                cat.idx = catJson["id"];
                cat.superCategory = catJson["supercategory"];
                cat.subCategory = catJson["name"];
                
                cocoCategories.push_back(cat.subCategory);
//                cocoSuperCategories.push_back(cat.superCategory);
                cocoCategoriesTypes.push_back(cat);
                
                cocoCategoriesIDXMapping[cat.idx] = cocoCategories.size() - 1;

                vector<string>& subCats = cocoSuperMap[cat.superCategory];
                subCats.push_back(cat.subCategory);

                fu::debug << cat.subCategory << " " << cat.superCategory << fu::endl;

            } // categories

            fu::info << "Total sub categories: " << cocoCategories.size() << fu::endl;
//            fu::info << "Total super categories: " << cocoSuperCategories.size() << fu::endl;
            
            int annotationCount = 0;
            
            for(int i = 0; i < json["annotations"].size(); ++i){
                
                ofJson anotJson = json["annotations"].at(i);
                
                COCOAnnotation annotation;
                annotation.imageIDX = anotJson["image_id"];;
                annotation.categoryIDX = anotJson["category_id"];
                
                // cat ids start at 1 and the id's are not sequential!!! so we need a map from actual id to vector id
                annotation.category = cocoCategories[cocoCategoriesIDXMapping[annotation.categoryIDX]];
                
                int isCrowd = anotJson["iscrowd"];

                if(isCrowd == 0 && cocoAnnotationsByImageIDX.find(annotation.imageIDX) != cocoAnnotationsByImageIDX.end()){
                    
                    //fu::debug << "Segmentation: " << annotation.imageIDX << " for " << annotation.category << fu::endl;

                    annotation.bbox = ofRectangle(anotJson["bbox"][0], anotJson["bbox"][1],
                                                  anotJson["bbox"][2], anotJson["bbox"][3]);
                    
                    annotation.mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
                    for(int j = 0; j < anotJson["segmentation"].at(0).size() - 1; j+=2){ // assuming only one?
                        
                        ofPoint p = ofPoint(anotJson["segmentation"].at(0)[j],
                                            anotJson["segmentation"].at(0)[j+1], 0); // assume poly?
                        
                        annotation.mesh.addVertex(p);
                        
                    }
                    
                    cocoAnnotationsByImageIDX[annotation.imageIDX].push_back(annotation);
                    
                    ++annotationCount;
                    
                    
                }else{
                    //fu::debug << "Discarding annotation: " << annotation.imageIDX << " for " << annotation.category << fu::endl;
                }
                
            } // annotations
            
            for(int i = 0; i < cocoImages.size(); ++i){
                if(cocoAnnotationsByImageIDX.find(cocoImages[i]->imageIDX) != cocoAnnotationsByImageIDX.end()){
                    fu::debug << "Adding annotations to img: " << cocoImages[i]->imageIDX << fu::endl;
                    cocoImages[i]->annotations = cocoAnnotationsByImageIDX[cocoImages[i]->imageIDX];
                    cocoImages[i]->resizeAnnotations();
                }
            }
            
            for(int i = 0; i < cocoImages.size(); ++i){
                const vector<COCOAnnotation>& annotations = cocoImages[i]->annotations;
                for(int j = 0; j < annotations.size(); ++j){
                    string category = annotations[j].category;
                    cocoImagesByCategoryIDX[category].push_back(cocoImages[i]);
                    //fu::debug << category << fu::endl;
                }
            }
            
            for(map< string, vector<COCOImage*> >::iterator it = cocoImagesByCategoryIDX.begin(); it != cocoImagesByCategoryIDX.end(); ++it){
                cocoActualCategories.push_back(it->first);
            }
            
            fu::info << "Total annotations considered: " << json["annotations"].size() << " with " << annotationCount << " included" << fu::endl;
            fu::info << "Total categories considered: " << cocoCategories.size() << " with " << cocoActualCategories.size() << " included" << fu::endl;
            
//            fu::Serializer.saveClass(ofToDataPath("global.conf"), *this, ARCHIVE_BINARY);
            
        }

        
    }
    
    vector<COCOImage*> cocoImages;
    vector<COCOCategory> cocoCategoriesTypes;
    vector<string> cocoCategories;
    map< int, int > cocoCategoriesIDXMapping;
//    vector<string> cocoSuperCategories;
    vector<string> cocoActualCategories;
    map< string, vector<string> > cocoSuperMap;
    map< int, vector<COCOAnnotation> > cocoAnnotationsByImageIDX;
    map< string, vector<COCOImage*> > cocoImagesByCategoryIDX;
    
    
    fu::MIDI::Receiver midiReceiver;
    
    
//    friend class boost::serialization::access;
//
//    template<class Archive>
//    void serialize(Archive & ar, const unsigned int version){
//
//        ar & BOOST_SERIALIZATION_NVP(cocoImages);
//        ar & BOOST_SERIALIZATION_NVP(cocoCategoriesTypes);
//        ar & BOOST_SERIALIZATION_NVP(cocoCategories);
//        ar & BOOST_SERIALIZATION_NVP(cocoSuperCategories);
//        ar & BOOST_SERIALIZATION_NVP(cocoSuperMap);
//        ar & BOOST_SERIALIZATION_NVP(cocoAnnotationsByImageIDX);
//        ar & BOOST_SERIALIZATION_NVP(cocoImagesByCategoryIDX);
//
//    };
    
};

namespace global {
typedef Singleton<GlobalModel> globalModelSingleton;
static GlobalModel& model = globalModelSingleton::Instance();
};
