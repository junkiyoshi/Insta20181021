#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);

	int font_size = 600;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", font_size, true, true, true);

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
	this->fbo.begin();
	ofClear(0);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	string word = "C";
	font.drawString(word, font.stringWidth(word) * -0.5, font.stringHeight(word) * 0.5);

	this->fbo.end();

	ofPixels pixels;
	this->fbo.readToPixels(pixels);

	int span = 20;
	for (int x = 0; x < this->fbo.getWidth(); x += span) {

		for (int y = 0; y < this->fbo.getHeight(); y += span) {

			if (pixels.getColor(x, y) != ofColor(0, 0)) {

				this->locations.push_back(ofPoint(x - ofGetWidth() * 0.5, y - ofGetHeight() * 0.5));
			}
		}
	}

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", span, true, true, true);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofColor color;
	for (ofPoint& point : this->locations) {
		
		ofPushMatrix();
		ofTranslate(point);
		ofRotate(ofNoise(point.x * 0.01, point.y * 0.01, ofGetFrameNum() * 0.008) * 720);

		this->font.drawString("C", this->font.getSize() * -0.5, this->font.getSize() * 0.5);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}