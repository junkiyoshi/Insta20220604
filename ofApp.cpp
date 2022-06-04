#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofNoFill();
	ofSetCircleResolution(36);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 180 < 5) {

		this->random_seed = ofRandom(1000);
	}

	ofSeedRandom(this->random_seed);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	//// Day 
	vector<ofColor> color_palette;
	color_palette.push_back(ofColor(134, 179, 224));
	color_palette.push_back(ofColor(251, 218, 205));
	color_palette.push_back(ofColor(234, 96, 148));

	this->draw_circle_packing(glm::vec2(), 340, color_palette);

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::draw_circle_packing(glm::vec2 location, float radius, vector<ofColor> color_palette) {

	auto number_of_sphere = radius * 1.2;
	vector<glm::vec2> location_list;
	vector<float> radius_list;

	while (location_list.size() < number_of_sphere) {

		auto tmp_location_radius = ofRandom(1, radius * 0.75);
		auto tmp_deg = ofRandom(0, 360);
		auto tmp_location = glm::vec2(location.x + tmp_location_radius * cos(tmp_deg * DEG_TO_RAD), location.y + tmp_location_radius * sin(tmp_deg * DEG_TO_RAD));
		auto tmp_radius = ofRandom(radius * 0.003, radius * 0.3);

		bool flag = true;
		for (int i = 0; i < location_list.size(); i++) {

			if (glm::distance(tmp_location, location_list[i]) < tmp_radius + radius_list[i] + 1) {

				flag = false;
				break;
			}
		}

		if (flag) {

			location_list.push_back(tmp_location);
			radius_list.push_back(tmp_radius);

			ofSetColor(color_palette[ofRandom(color_palette.size())]);

			ofPushMatrix();
			ofTranslate(tmp_location);
			ofRotateZ(ofRandom(360) + ofGetFrameNum() * ofRandom(0.5, 1.5));
			ofRotateY(ofRandom(360) + ofGetFrameNum() * ofRandom(0.5, 1.5));
			ofRotateX(ofRandom(360) + ofGetFrameNum() * ofRandom(0.5, 1.5));

			ofDrawCircle(glm::vec2(), tmp_radius);

			if (tmp_radius > 15) {

				this->draw_circle_packing(glm::vec2(), tmp_radius, color_palette);
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}