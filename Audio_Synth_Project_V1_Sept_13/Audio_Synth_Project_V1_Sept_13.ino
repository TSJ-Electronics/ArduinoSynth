#include "KeyboardNotes.h"

/*
Audio Synth v1.0
Project By: TSJ_Electronics
October 1, 2022
*/

//Declare Recording Function
void recordSong();

//Declare Playback function
void playRecordedSong();

//Declare adjustableSpeedValue function
int getAdjustableSpeedValue();

//Initialize Keyboard class object
KeyboardNotes keyboard = KeyboardNotes();

//These buttons change the octave
const int downOctave = 11;
const int upOctave = 12;

//This switches to a wider array of notes
const int customKeyboardNotes = 13;

const int playbackSpeedInput = A0;

//Speaker Output (piezo buzzer)
const int buzzer = 9;

//This is the recording switch, when active HIGH it records note presses and duration.
int startRecordingSwitch = A2;

//Playback Song Switch
int playbackSongSwitch = A1;

void setup() {
  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);//turn buzzer off
  pinMode(startRecordingSwitch, INPUT);
  pinMode(upOctave, INPUT);
  pinMode(downOctave, INPUT);
  pinMode(playbackSpeedInput, INPUT);
  pinMode(playbackSongSwitch, INPUT);
}

void loop() {


  if(digitalRead(upOctave) == HIGH){
    keyboard.incrementOctave();
    delay(200);
  }

  if(digitalRead(downOctave) == HIGH){
    keyboard.decrementOctave();
    delay(200);
  }

    if(digitalRead(customKeyboardNotes) == HIGH){
    keyboard.setCustomNotes();
    delay(200);
  }

   if (digitalRead(startRecordingSwitch) == HIGH)
    recordSong();

   if (digitalRead(playbackSongSwitch) == HIGH)
    playRecordedSong();
   
   for(int x = 0; x < keyboard.getNumberOfKeys(); x++){
    if(digitalRead(keyboard.key[x]))
      tone(buzzer, keyboard.note[x]);// play note for undetermined amount of time
    while(digitalRead(keyboard.key[x])){
      //do nothing while button is pressed
    }
    noTone(buzzer);// end note
   }
}

int playbackArrayCurrentPosition = 0; //Which note is being played on the playback loop, keeps track of how many notes in array
int playbackNoteArray[100] = {0}; //These are the notes in which we recorded, and are set to play back
int playbackNoteDuration[100] = {0}; // This is the duration of each note in the playback Note array
int delayBetweenNotesArray[100] = {0}; //This is the delay from one note to the next.


//This function reads the adjustable voltage from a potentiometer and reports a value that speeds up or slows down the recorded song playback speed
int getAdjustableSpeedValue(){
  float voltage = analogRead(playbackSpeedInput) * (5.0/1023.0);
  double speedValue = 1.0;
  for(double x = 1.0; x < 5.0; x += 0.2){
    if(voltage < x)
      break;
    else
      speedValue+= 0.2;
  }
  return speedValue;
}


//This is the code to play recording.
void playRecordedSong(){
while((digitalRead(playbackSongSwitch) == HIGH)){
  
 for(int x = 0; x < playbackArrayCurrentPosition; x++){ //iterate through note and duration arrays until there are no more notes to play
    delay(delayBetweenNotesArray[x] / getAdjustableSpeedValue());
    tone(buzzer, playbackNoteArray[x]);
    delay(playbackNoteDuration[x] / getAdjustableSpeedValue());
    noTone(buzzer);
    }
    delay(330);
  }
}

void recordSong(){
  unsigned long noteStartTime = 0;// start time of note pressed
  unsigned long noteEndTime = 0; // end time of note pressed
  unsigned long delayStartTime = 0; //start time of delay between notes
  unsigned long delayEndTime = 0; //end time of delay between notes
  Serial.println("RecordingSong");
  
   while(digitalRead(startRecordingSwitch) == HIGH){ // while recording
     if(digitalRead(upOctave) == HIGH){
      keyboard.incrementOctave();
      delay(100);
    }

    if(digitalRead(downOctave) == HIGH){
      keyboard.decrementOctave();
      delay(100);
    }

    if(digitalRead(customKeyboardNotes) == HIGH){
      keyboard.setCustomNotes();
      delay(100);
    }
    
    for(int x = 0; x < keyboard.getNumberOfKeys(); x++){ // check if any keys are pressed
      if(digitalRead(keyboard.key[x]) == HIGH){ // if a key is pressed
        delayEndTime = millis();// end note delay timer
        if(delayStartTime !=0) // if delay start time == 0 then ignore the first delay call, we want 0 delay for first note
          delayBetweenNotesArray[playbackArrayCurrentPosition] = (delayEndTime - delayStartTime);
        else
          delayBetweenNotesArray[playbackArrayCurrentPosition] = 0;
        
        noteStartTime = millis();// start note duration timer
        playbackNoteArray[playbackArrayCurrentPosition] = keyboard.note[x];//the next note recorded in sequence is:
        if(digitalRead(keyboard.key[x]))
          tone(buzzer, keyboard.note[x]);// play note for undetermined amount of time
        while(digitalRead(keyboard.key[x]) == HIGH){
          //Do nothing but play the note while key is pressed
        }
        noTone(buzzer);
        noteEndTime = millis();
        playbackNoteDuration[playbackArrayCurrentPosition] = (noteEndTime - noteStartTime); //The duration of this note is incremented by 100ms as long as button is pressed

        delayStartTime = millis();
        ++playbackArrayCurrentPosition;
      }   
    }
   }
}
