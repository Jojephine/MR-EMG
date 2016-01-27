/* Monostable multivibrator, non-retriggerable                            
 *                                                           
 * This sketch listens for a rising edge on a specific 
 * input pin and generates a square pulse on an output  
 * pin. It then enters a nonretriggerable state until   
 * the input stays constant (i.e. the interrupt is not  
 * triggered) for an amount of time specified by        
 * OFFPERIOD                                            
 * Copyright (c) 2015:                                      
 *  Francesco Santini <francesco.santini@unibas.ch>     
 *  Xeni Deligianni   <xeni.deligianni@unibas.ch>       */
 
/*  
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



#define OUTPUTPIN 13
#define INPUTPIN 2
#define INPUTINTERRUPT 0 // this has to be consistent with the previous. See board documentation
#define PULSEDURATION 100
#define OFFPERIOD 200 // Run another pulse only if the input has been low for long enough

volatile bool runPulse = false;
long lastPulse = millis();

void setup() {
  pinMode(INPUTPIN,INPUT);
  attachInterrupt(INPUTINTERRUPT, pulseReceivedInterrupt, RISING);
  pinMode(OUTPUTPIN, OUTPUT);
  digitalWrite(OUTPUTPIN, LOW);
}

void loop() {
  if (runPulse)
  {
    // this means that an interrupt was called
    if (millis() - lastPulse >= OFFPERIOD)
    { 
     // run the pulse only if the last seen interrupt happened >= OFFPERIOD ms before.
     // Otherwise, don't run the pulse, but still record that an interrupt was triggered
      digitalWrite(OUTPUTPIN, HIGH);
      delay(PULSEDURATION);
      digitalWrite(OUTPUTPIN, LOW);
    }
    lastPulse = millis();
    runPulse = false;
  }
  
  
  
}

void pulseReceivedInterrupt()
{
  
  if (!runPulse)
  {
    runPulse = true;
  }
}
