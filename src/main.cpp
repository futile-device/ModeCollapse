
#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

    ofGLWindowSettings settings;
    //settings.setGLVersion(2, 1);  // Fixed pipeline
    settings.setGLVersion(3, 3);  // Programmable pipeline
    settings.setSize(1920, 1080);

    ofCreateWindow(settings);
    if (!ofGLCheckExtension("GL_ARB_geometry_shader4") && !ofGLCheckExtension("GL_EXT_geometry_shader4") && !ofIsGLProgrammableRenderer()) {
        ofLogFatalError() << "geometry shaders not supported on this graphics card";
        return 1;
    }

    //ofSetupOpenGL(1920, 1080 ,OF_WINDOW);            // <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

}


//#include "ofMain.h"
//#include "ofApp.h"
//
////========================================================================
//int main( ){
//
//    ofGLFWWindowSettings settings;
//
//    settings.setGLVersion(3, 3);
//    settings.setSize(1920, 1080);
//    settings.setPosition(glm::vec2(0, 0));
//    settings.resizable = true;
//    //    settings.multiMonitorFullScreen = true;
//    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
//
//    settings.setGLVersion(3, 3);
//    settings.setSize(1920, 1080);
//    settings.setPosition(glm::vec2(0, 0));
//    settings.resizable = true;
//    settings.multiMonitorFullScreen = true;
//    settings.shareContextWith = mainWindow;
//    shared_ptr<ofAppBaseWindow> renderWindow = ofCreateWindow(settings);
//
//
//    if (!ofGLCheckExtension("GL_ARB_geometry_shader4") && !ofGLCheckExtension("GL_EXT_geometry_shader4") && !ofIsGLProgrammableRenderer()) {
//        ofLogFatalError() << "geometry shaders not supported on this graphics card";
//        return 1;
//    }
//
//    shared_ptr<ofApp> mainApp(new ofApp);
//    shared_ptr<RenderApp> renderApp(new RenderApp);
//    mainApp->renderApp = renderApp;
//
//    ofRunApp(renderWindow, renderApp);
//    ofRunApp(mainWindow, mainApp);
//    ofRunMainLoop();
//
//
//}
/*
 ofGLWindowSettings settings;
 //settings.setGLVersion(2, 1);  // Fixed pipeline
 settings.setGLVersion(3, 3);  // Programmable pipeline
 settings.setSize(1920, 1080);
  
 ofCreateWindow(settings);
 if (!ofGLCheckExtension("GL_ARB_geometry_shader4") && !ofGLCheckExtension("GL_EXT_geometry_shader4") && !ofIsGLProgrammableRenderer()) {
     ofLogFatalError() << "geometry shaders not supported on this graphics card";
     return 1;
 }
 
 //ofSetupOpenGL(1920, 1080 ,OF_WINDOW);            // <-------- setup the GL context
 
 // this kicks off the running of my app
 // can be OF_WINDOW or OF_FULLSCREEN
 // pass in width and height too:
 ofRunApp(new ofApp());
*/




//#include "ofMain.h"
//#include "ofApp.h"
//
////========================================================================
//int main( ){
//
//    ofGLWindowSettings settings;
//    //settings.setGLVersion(2, 1);  // Fixed pipeline
//    settings.setGLVersion(3, 3);  // Programmable pipeline
//    settings.setSize(1920 * 2, 1080);
//
//    ofCreateWindow(settings);
//    if (!ofGLCheckExtension("GL_ARB_geometry_shader4") && !ofGLCheckExtension("GL_EXT_geometry_shader4") && !ofIsGLProgrammableRenderer()) {
//        ofLogFatalError() << "geometry shaders not supported on this graphics card";
//        return 1;
//    }
//
//    //ofSetupOpenGL(1920, 1080 ,OF_WINDOW);            // <-------- setup the GL context
//
//    // this kicks off the running of my app
//    // can be OF_WINDOW or OF_FULLSCREEN
//    // pass in width and height too:
//    ofRunApp(new ofApp());
//
//}
