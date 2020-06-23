/*************************************************
 * MIDI In Buzzer Example
 *
 * Author: James Saunders
 *************************************************/

#include "midiNote2Frequency.h"
#include <MIDI.h>

#define BUZZER_PIN 9

// Created and binds the MIDI interface to the default hardware serial port.
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // Initialize the MIDI Library.
  // OMNI sets it to listen to all channels. MIDI.begin(2) would set it to respond to notes on channel 2 only.
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // This is important!! This command tells the MIDI Library which function you want to call when a NOTE ON command
  // is received. In this case it's "handleNoteOn".
  MIDI.setHandleNoteOn(handleNoteOn);

  // This command tells the MIDI Library to call "handleNoteOff" when a NOTE OFF command is received.
  MIDI.setHandleNoteOff(handleNoteOff);

  // TODO
  MIDI.setHandlePitchBend(handlePitchBend);
}

void loop() {
  // Continuously check if MIDI data has been received.
  MIDI.read();
}

// handleNoteOn() is the function that will be called by the MIDI Library when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Note, and Velocity.
void handleNoteOn(byte channel, byte midiNote, byte velocity) {
  // Lookup pitch from MIDI Note
  int pitch = freqFromMidiNote(midiNote);
  
  // Play Note
  tone(BUZZER_PIN, pitch, 500);
}

// handleNoteOff() is the function that will be called by the MIDI Library when a MIDI NOTE OFF message is received.
// A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message.
// It will be passed bytes for Channel, Note, and Velocity.
void handleNoteOff(byte channel, byte midiNote, byte velocity) {
  // Stop Playing Note
  noTone(BUZZER_PIN);
}

void handlePitchBend(byte channel, int bend) {
  // TODO
  // Handle Pitch Bend
}