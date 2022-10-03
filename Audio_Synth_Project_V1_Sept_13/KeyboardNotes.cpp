#include "KeyboardNotes.h"
#include <Arduino.h>
#include <Math.h>

    void KeyboardNotes::setNotes(){
      for(int x = 0; x < numberOfKeys; x++)
        note[x] = baseFrequencyArray[x] * pow(2, octave); // each note has a base frequency, to get scales multiply base frequency by octave
    }
    
    KeyboardNotes::KeyboardNotes(){
      pinMode(C_Note_Pin, INPUT);
      pinMode(D_Note_Pin, INPUT);
      pinMode(E_Note_Pin, INPUT);
      pinMode(F_Note_Pin, INPUT);
      pinMode(G_Note_Pin, INPUT);
      pinMode(A_Note_Pin, INPUT);
      pinMode(B_Note_Pin, INPUT);
      setNotes();
    }

    void KeyboardNotes::incrementOctave(){
      if(octave < 8){
        ++octave;
        setNotes();
      }
    }
    
    void KeyboardNotes::decrementOctave(){
      if(octave > 1){
        --octave;
        setNotes();
      }
    }

    void KeyboardNotes::setCustomNotes(){
      int startingFrequency = 250;
      int frequencyIncrement = 250;
          for(int x = 0; x < numberOfKeys; x++)
            note[x] = startingFrequency + (frequencyIncrement * x);
    }
