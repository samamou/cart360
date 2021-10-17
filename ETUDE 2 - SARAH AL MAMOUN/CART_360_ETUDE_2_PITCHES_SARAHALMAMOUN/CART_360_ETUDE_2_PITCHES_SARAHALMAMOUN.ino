#include "pitches.h" //included the file pitches 

/**********************ETUDE 3 CART 360 2020*******************************
 * WELCOME! 
 * THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (4 KEYS)
 * WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK SINGLE NOTES (NO CHORDS OR TIMING). 
 * THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
 * THERE ARE 5 POSSIBLE MODES
 * 0 ==  reset    ==   led off == also resets
 * 1 ==  live     ==   led BLUE
 * 2 ==  record   ==   led RED
 * 3 ==  play     ==   led GREEN
 * 4 ==  looper   ==   led PURPLE
 * 
 * ADDITIONALLY - WHEN THE USER CHANGES MODE, 
 * THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)

 * PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
 * DO NOT ADD ANY MORE FUNCTION DEFINITIONS 
 * ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
 * THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
 * PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
 * GOOD LUCK!
 */
/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_R 11  // B PIN
#define LED_PIN_G 10 // G PIN
#define LED_PIN_B 9 // R PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// duration for a single played note
const int duration = 200;

// constant for pin to output for buzzer 
#define BUZZER_PIN 3 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes = 0;
int mode = 0; // start at off
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES]; 

/*************************************************************************/


/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
  Serial.begin(115200); //since 115200 band is the fastest
  pinMode(BUTTON_MODE_PIN, INPUT);
}

/**********************LOOP() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change the loop - it establishes the flow of the program
 * We call here 3 functions repeatedly:
 * 1: chooseMode(): this function will determine the mode that your program is in 
 * based on if the button (linked to the BUTTON_MODE_PIN) was pressed
 * 2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
 * 3: selectMode(): will determine which function to call based on the value of the mode variable

**************************************************************************/
void loop()
{
  chooseMode();
  setRGB();
  selectMode();
}
/******************CHOOSEMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Read the value from the Button (linked to the BUTTON_MODE_PIN) and 
 * if is being pressed then change the mode variable.
 * REMEMBER:
 * mode == 0 is reset 
 * mode == 1 is live
 * mode == 2 is record
 * mode == 3 is play
 * mode == 4 is loopMode
 * Every time the user presses the button, the program will go to the next mode,
 * once it reaches 4, it should go back to mode == 0. 
 * (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode(){
  
  //When the user Changes MODE, The RGB LED will change color.
  if (digitalRead(BUTTON_MODE_PIN) == HIGH) { //as user presses the button, mode goes from low to high 
    if(mode == 4) { //reset mode to 0 at 4
      mode = 0;
      delay(300); //give it some time 
    }
    else if (mode!= (mode-1)) {  //if the mode isn't the same as the mode right before
       if(mode == 3){
        mode++;
        delay(300); 
       }
       else if(mode == 2){
       mode++;
       delay(300); 
       }
       else if(mode == 1){
       mode++;
       delay(300); 
       }
       else if(mode == 0){
       mode++;
       delay(300); 
       }   
    } 
  }
}
/******************SETRGB(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Depending on the value of the mode variable:
 * if the mode is 0 - RGB LED IS OFF
 * if the mode is 1 - RGB LED IS BLUE
 * if mode is 2 - RGB LED IS RED
 * if mode is 3 - RGB LED IS GREEN
 * if mode is 4 - RGB LED iS PURPLE
 * YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
void setRGB()
{
  // 0 = all pins low
  // 1 = blue pin high
  // 2 = red pin high
  // 3 = green pin high
  // 4 = blue + red pins high :)
  switch(mode) {
    case 0: 
        digitalWrite(LED_PIN_R, LOW);
        digitalWrite(LED_PIN_G, LOW);
        digitalWrite(LED_PIN_B, LOW);
    break;
    case 1: 
        digitalWrite(LED_PIN_R, LOW);
        digitalWrite(LED_PIN_G, LOW);
        digitalWrite(LED_PIN_B, HIGH);
    break;
    case 2: 
        digitalWrite(LED_PIN_R, HIGH);
        digitalWrite(LED_PIN_G, LOW);
        digitalWrite(LED_PIN_B, LOW);
    break;
    case 3: 
        digitalWrite(LED_PIN_R, LOW);
        digitalWrite(LED_PIN_G, HIGH);
        digitalWrite(LED_PIN_B, LOW);
    break;
    case 4: 
        digitalWrite(LED_PIN_R, HIGH);
        digitalWrite(LED_PIN_G, LOW);
        digitalWrite(LED_PIN_B, HIGH);
    break;
  }
}
/**********************SELECTMODE() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
 * There are 4 possibilities
 * 1: reset(): this function will reset any arrays etc, and will do nothing else
 * 2: live(): this function will play the corresponding notes 
 * to the user pressing the respective buttons. 
 * NOTE:: the notes played are NOT stored
 * 3: record(): this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * 4: play(): this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * 5: loopMode(): this function will playback any notes stored in the array that were recorded, 
 * BUT unlike the previous mode, you can choose in which sequence the notes are played.
 * REQUIRED: only play notes from the array (no live stuff)

******************************************************************************/
void selectMode()
{
  if(mode == 0) { 
    reset();
  }
  else if(mode == 1) {
    live();
  }
  else if(mode == 2) {
    record();
  }
  
  else if(mode == 3) {
    play();
  }
   
   else if(mode == 4) {
    looper();
  }
}
/******************RESET(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function should ensure that any notes recorded are no longer available
**************************************************************************/
void reset()
{
  countNotes = 0;  //set the counter to 0 
  //we also have an array called notes that stores the notes played. 
  for (int i=0; i< MAX_NOTES; i++){ 
    notes[i] = 0; //assign 0s 
  }
  Serial.println("RESET(): ");
}
/******************LIVE(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * NOTE:: the notes played are NOT stored
 * SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * THEN - output the note to the buzzer using the tone() function
**************************************************************************/
void live()
{
    //tone(pin, frequency, duration)
    //https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
    int noteInput = analogRead(NOTE_IN_PIN);  
    if (noteInput == 0) { 
      noTone(BUZZER_PIN);
    }
    else {
      tone(BUZZER_PIN, noteInput, duration);
      Serial.println("LIVE(): We are liiive"); //when a button is pressed
    }
}

/******************RECORD(): IMPLEMENT **********************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * AND - output the note to the buzzer using the tone() function
 * THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
**************************************************************************/
void record()
{
  int noteReading = analogRead(NOTE_IN_PIN);
  int pitchedNote = 0; //new pitched note  
  if (noteReading > 0) { // as long as there's at least 1
    pitchedNote = getPitch(noteReading); //convert input voltage to a defined note
    tone(BUZZER_PIN, pitchedNote, duration); 
  }
  if (countNotes < MAX_NOTES){ // we already have a variable created for the max notes (16)
      if(noteReading >= 1) { //at least one 
        pitchedNote = getPitch(noteReading); //convert input voltage to a defined note
        notes[countNotes] = pitchedNote;
        //tone(BUZZER_PIN, notes[countNotes], duration);
        delay(duration); // (with pauses)
        countNotes++;
      }
    }  
}
/******************PLAY(): IMPLEMENT ************************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ each value IN ORDER
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void play()
{
   // loop through the array 
  for (int i = 0; i< countNotes; i++) {
    //and play of notes
    tone(BUZZER_PIN, notes[i], duration);
    delay(duration);
  }
}
/******************LOOPMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void looper()
{
   //play()'s it backwards!
   for (int i = countNotes; i > 0; i--) {
    // play through the array of notes
    tone(BUZZER_PIN, notes[i], duration);
    delay(100); //with some fixed delay ~~
  }
}
/**************************************************************************/
 
/******************getPitch(): IMPLEMENT **********************************
// check pdf for documentation
**************************************************************************/
int getPitch(int noteReading)
{
 if(noteReading > 0){
  if (noteReading > 0 && noteReading < 255 ) { 
    return NOTE_E5;
    } else if(noteReading > 255 && noteReading < 510){
      return NOTE_D5;
      } else if (noteReading > 510 && noteReading < 765){
        return NOTE_C5; 
        }
        else if (noteReading > 765 && noteReading < 1020 ){
          return NOTE_F5;
          }
    }
}
