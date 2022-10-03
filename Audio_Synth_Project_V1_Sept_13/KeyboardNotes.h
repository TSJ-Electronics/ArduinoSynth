#pragma once
#ifndef KEYBOARDNOTES_H
#define KEYBOARDNOTES_H
class KeyboardNotes{
  private:
    void setNotes();

    // there are octaves 1 - 8
    int octave = 5;

    //number of playable keys
    const int numberOfKeys = 7;

    //These are corresponding arduinio pins that play notes in this order (C,D,E,F,G,A,B)
    const int C_Note_Pin = 2;
    const int D_Note_Pin = 3;
    const int E_Note_Pin = 4;
    const int F_Note_Pin = 5;
    const int G_Note_Pin = 6;
    const int A_Note_Pin = 7;
    const int B_Note_Pin = 8;
    
    //These are base frequencys of a standard scale (C,D,E,F,G,A,B)
    const int A_Base_Frequency = 55;
    const int B_Base_Frequency = 62;
    const int C_Base_Frequency = 33;
    const int D_Base_Frequency = 37;
    const int E_Base_Frequency = 41;
    const int F_Base_Frequency = 44;
    const int G_Base_Frequency = 49;
    
    const int baseFrequencyArray[7] = {C_Base_Frequency, D_Base_Frequency, E_Base_Frequency, F_Base_Frequency, 
    G_Base_Frequency, A_Base_Frequency, B_Base_Frequency};

  public:
    //Playable Notes - there are 7 notes with 8 octives. Note frequency is handled in "setNotes()" function
    int note[7];

    //These are the input pins. If a key is presssed one of these pins will be high, putting them in an array makes them easily iterated to check for key press
    int key[7] = {C_Note_Pin, D_Note_Pin, E_Note_Pin, F_Note_Pin, G_Note_Pin, A_Note_Pin, B_Note_Pin};
    
    KeyboardNotes();
    void incrementOctave();
    void decrementOctave();
    void setCustomNotes();
    void eightBitSynth();
    inline int getNumberOfKeys(){ return numberOfKeys;};
};
#endif
