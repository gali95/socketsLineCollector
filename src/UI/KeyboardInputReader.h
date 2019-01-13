/*
 * KeyboardInputReader.h
 *
 *  Created on: Jan 10, 2019
 *      Author: temp
 */

#ifndef UI_KEYBOARDINPUTREADER_H_
#define UI_KEYBOARDINPUTREADER_H_

enum keyState
{
	pressed,
	hold,
	released
};

class KeyboardInputReader
{
public:
	static bool isKeyPressed(char key);
	static bool isKeyHold(char key);
	static bool isKeyReleased(char key);

	static bool isKeyActive();
	static char getActiveKey();
	static keyState getActiveKeyState();
	static float getActiveKeyHoldTime();

	static void StartThread();
	static void StopThread();
private:

	void* Thread(void *nothing);
	bool m_stopThread;

};

#endif /* UI_KEYBOARDINPUTREADER_H_ */
