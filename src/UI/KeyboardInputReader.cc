/*
 * KeyboardInputReader.cc
 *
 *  Created on: Jan 13, 2019
 *      Author: temp
 */

#include <pthread.h>
#include <unistd.h>

#include "KeyboardInputReader.h"

bool KeyboardInputReader::isKeyPressed(char key) {
}

bool KeyboardInputReader::isKeyHold(char key) {
}

bool KeyboardInputReader::isKeyReleased(char key) {
}

bool KeyboardInputReader::isKeyActive() {
}

char KeyboardInputReader::getActiveKey() {
}

keyState KeyboardInputReader::getActiveKeyState() {
}

float KeyboardInputReader::getActiveKeyHoldTime() {
}

void KeyboardInputReader::StartThread() {



}

void KeyboardInputReader::StopThread() {



}

void* KeyboardInputReader::Thread(void* nothing) {

	while(!m_stopThread)
	{

	}

}
