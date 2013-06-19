#pragma once

#include <eeros/sequencer/Sequence.hpp>

/** Dies ist eine Beispielklasse f�r den Anwender. Damit wird gezeigt, wie dieser Sequnecer verwendet wird
  *
  */
class MySubSequence : public Sequence
{
public:
	MySubSequence(double period, string name);

	//Destruktor muss virtual sein, damit er automatisch aufgerufen wird.
	virtual ~MySubSequence(void);

	/**eigene Steps f�llen, Init wird automatisch immer hinzugef�gt von Sequence
	 * der n�chste sollte Initialising sein, Rest spielt keine Rolle
	 */
	void fillSequencerSteps();
};

