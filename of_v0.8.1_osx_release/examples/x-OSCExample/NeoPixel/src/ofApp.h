#pragma once

#include "ofMain.h"
#include "oscpack/osc/OscOutboundPacketStream.h"
#include "oscpack/ip/UdpSocket.h"

class ofApp : public ofBaseApp{
	
	public:
        ofApp() : transmitSocket( IpEndpointName( "169.254.1.1", 9000) )
    {}
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		
		ofVideoGrabber 		vidGrabber;
		unsigned char * 	videoInverted;
		ofTexture			videoTexture;
		int 				camWidth;
		int 				camHeight;
    
private:
    static const int BufferSize = 2048;
    char buffer[BufferSize];
    UdpTransmitSocket transmitSocket;
};
