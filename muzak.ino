//       Note  Period     Frequency
#define  c     3830    // 261 Hz 
#define  C     3600    // 
#define  d     3400    // 294 Hz 
#define  D     3200    // 
#define  e     3038    // 329 Hz 
#define  f     2864    // 349 Hz 
#define  F     2700    //  
#define  g     2550    // 392 Hz 
#define  G     2400    //  
#define  a     2272    // 440 Hz 
#define  A     2100    //  
#define  b     2028    // 493 Hz 
#define  B     1912    // 
#define  R     0       // rest
// From: http://www.soundoctor.com/freq.htm


// SETUP
int piezoPin = 9;

// SMOKE ON THE WATER
int melody[]    = {  e,  g,  a,  e,  R,  g,  R,  A,  a,  e,  g,  a,  g,  R,  e };
double beats[]  = {  4,  4,  2,  8,  8,  8,  8,  8,  2,  4,  4,  2,  8,  8,  1 }; 
double beatNoteType = 4;  // 4th note takes up 1 beat
double bpm = 112; // Set overall tempo


int melodyLength = sizeof(melody)/sizeof(melody[0]);
double bps = bpm / 60;
double beatLengthInSeconds = 1/bps;
double beatLengthInMicroseconds = beatLengthInSeconds * 1000000;
int pause = 1000; // Set length of pause between notes

// Pulse the speaker to play a pitch for a particular duration in usecs
// (c) 2005 D. Cuartielles for K3
void playPitch(int pitch, long duration) {
  long elapsedTime = 0;

  if (pitch != R) { //  pitch is not a rest
    while (elapsedTime < duration) {

      // UP
      digitalWrite(piezoPin,HIGH);
      delayMicroseconds(pitch / 2);

      // DOWN
      digitalWrite(piezoPin, LOW);
      delayMicroseconds(pitch / 2);

      elapsedTime += (pitch);
    } 

  } else { // Rest
    while (elapsedTime < duration) {
      delayMicroseconds(pause);
      elapsedTime += (pause);
    } 
  }                                 
}

void setup() { 
  pinMode(piezoPin, OUTPUT);

  Serial.begin(9600);
  Serial.print("BPM: ");Serial.println(bpm);
  Serial.print("BPS: ");Serial.println(bps);
  Serial.print("BeathLengthInSecs: ");Serial.println(beatLengthInSeconds);
  Serial.print("BeathLengthInMicrosecs: ");Serial.println(beatLengthInMicroseconds);
  Serial.println();
}

void loop() {
  for (int i = 0; i < melodyLength; i++) {
    int pitch = melody[i];
    long duration = (beatNoteType / beats[i]) * beatLengthInMicroseconds; // Set up timing

    playPitch(pitch, duration); 
    delayMicroseconds(pause); // Pause between notes

  }

  Serial.println("END OF TUNE");
}

