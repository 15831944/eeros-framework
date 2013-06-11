#pragma once

#include "Sequence.hpp"

/** Dies ist eine Beispielklasse f�r den Anwender. Damit wird gezeigt, wie dieser Sequnecer verwendet wird
  *
  */
class MySequence : public Sequence
{
public:
	MySequence(double period, string name);

	//Destruktor muss virtual sein, damit er automatisch aufgerufen wird.
	virtual ~MySequence(void);

	/**eigene Steps f�llen, Init wird automatisch immer hinzugef�gt von Sequence
	 * der n�chste sollte Initialising sein, Rest spielt keine Rolle
	 */
	void fillSequencerSteps();
};

