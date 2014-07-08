#include "ofApp.h"
#include "stdlib.h"



typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}Pixel;

//--------------------------------------------------------------
void ofApp::setup(){
	
	camWidth 		= 24;	// try to grab at this size.
	camHeight 		= 16;
	
    //we can now get back a list of devices. 
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
	
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName; 
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl; 
        }
	}
    
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	videoInverted 	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);	
	ofSetVerticalSync(true);
}


//--------------------------------------------------------------
void ofApp::update(){
	
	ofBackground(100,100,100);
	
	vidGrabber.update();
	
	if (vidGrabber.isFrameNew()){
		int totalPixels = camWidth*camHeight;
		unsigned char * pixels = vidGrabber.getPixels();
		
        Pixel* pixArray = (Pixel*) vidGrabber.getPixels();
        
        Pixel* destArray = (Pixel*) videoInverted;
        for (int i = 0; i < totalPixels; i++)
        {
            //destArray[i] = pixArray[i];
            int row = i / 24;
            int column = i - (row * 24);
            int block = column / 8;
            int blockPos = column % 8;
        
            int destPos;
            if (row < 8)
                destPos = block * 64 + blockPos + 8 * row;
            else
                destPos = block * 64 + blockPos + 8 * (row - 8) + 192;

            
            destArray[destPos].r = pixArray[i].r * 0.10;
            destArray[destPos].g = pixArray[i].g * 0.10;
            destArray[destPos].b = pixArray[i].b * 0.10;
            
            
		}
        //std::exit(0);
        osc::OutboundPacketStream p( buffer, BufferSize );
        
        p << osc::BeginMessage( "/outputs/rgb/16" )
        << osc::Blob( videoInverted, totalPixels * 3 )
        << osc::EndMessage;
 
        transmitSocket.Send( p.Data(), p.Size() );
//        std::cout << ".";
        
		videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
	}
    
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetHexColor(0xffffff);
	vidGrabber.draw(0,0, 240*6, 160*6);
    //videoTexture.draw(20,20, 240*6, 160*6);
	//videoTexture.draw(20+camWidth,20,camWidth*10,camHeight*10);
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	// Video settings no longer works in 10.7
	// You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343        
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
