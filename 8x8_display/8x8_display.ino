/**
 * This is an Arduino code to show pretty much what you can fit in a 8x8 display.
 * I have used this display https://www.adafruit.com/product/1821 -- datasheet link on the page.
 * I am pretty sure there are better libraries out there, and easier ways to wire it (as the tutorials by adafruit show)
 * I just felt like building it from the ground up as a learning exercise.
 * @author Nigini Oliveira - dev@nigini.me
 * @licence CC BY-NC-SA https://creativecommons.org/licenses/by-nc-sa/4.0/
 */

// ROWS
#define R1 A0
#define R2 0
#define R3 12
#define R4 1
#define R5 6
#define R6 2
#define R7 3
#define R8 4
#define ROWS_SIZE 8
byte rows[] = {R1, R2, R3, R4, R5, R6, R7, R8};

//COLUMNS
#define C1 A4
#define C2 11
#define C3 5
#define C4 A1
#define C5 13
#define C6 A2
#define C7 A3
#define C8 A5
#define COLS_SIZE 8
byte columns[] = {C1, C2, C3, C4, C5, C6, C7, C8};

//TODO: Refactor the USE functions into one - they are too similar
void useRow(int rowNumber) {
  for (byte row=1; row <= ROWS_SIZE; row++) {
    if(rowNumber == row) {
      digitalWrite(rows[row-1], LOW);
    } else {
      digitalWrite(rows[row-1], HIGH);
    }
  }
}

void useColumn(int colNumber) {
  for (byte col=1; col <= COLS_SIZE; col++) {
    if(colNumber == col) {
      digitalWrite(columns[col-1], HIGH);
    } else {
      digitalWrite(columns[col-1], LOW);
    } 
  }
}

void byteToBits(byte theByte, bool *bitsArray) {
  for (byte i = 0; i < 8; i++) {
    bitsArray[7 - i] = bitRead(theByte, i);
  }
}

void showLine(byte line, bool *bits) {
  digitalWrite(rows[line-1], LOW);
  for(byte bit=0; bit < 8; bit++) {
    digitalWrite(columns[bit], bits[bit]);
    //delay(100);
  }
  digitalWrite(rows[line-1], HIGH);
}

void showCharacter(byte *character, byte SHOW_FOR) {
    bool currentLine[8] = {0};
    for (int time=0; time <= SHOW_FOR; time++) {
      for(byte line=1; line<= 8; line++) {
        byteToBits(character[line-1], currentLine);
        showLine(line, currentLine);
        delay(10);
      }
    }

}

void cleanScreen() {
  for (byte col=1; col <= COLS_SIZE; col++) {
    pinMode(columns[col-1], OUTPUT);
    digitalWrite(columns[col-1], LOW); //OFF
  }
  for (byte row=1; row <= ROWS_SIZE; row++) {
    pinMode(rows[row-1], OUTPUT);
    digitalWrite(rows[row-1], HIGH); //OFF
  }
}

/** 
 * FONT DEFINITION
 * Characters source: https://github.com/idispatch/raster-fonts/blob/master/font-8x8.c 
**/

byte letterC[] = {
    0x7C,  /* 01111100 */
    0xC6,  /* 11000110 */
    0xC0,  /* 11000000 */
    0xC0,  /* 11000000 */
    0xC0,  /* 11000000 */
    0xC6,  /* 11000110 */
    0x7C,  /* 01111100 */
    0x00,  /* 00000000 */
};

byte letterD[] = {
    0xF8,  /* 11111000 */
    0xCC,  /* 11001100 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xCC,  /* 11001100 */
    0xF8,  /* 11111000 */
    0x00,  /* 00000000 */
};

byte letterE[] = {
    0xFE,  /* 11111110 */
    0xC0,  /* 11000000 */
    0xC0,  /* 11000000 */
    0xF8,  /* 11111000 */
    0xC0,  /* 11000000 */
    0xC0,  /* 11000000 */
    0xFE,  /* 11111110 */
    0x00,  /* 00000000 */
};

byte letterH[] = {
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xFE,  /* 11111110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0x00,  /* 00000000 */
};

byte letterI[] = {
    0x7E,  /* 01111110 */
    0x18,  /* 00011000 */
    0x18,  /* 00011000 */
    0x18,  /* 00011000 */
    0x18,  /* 00011000 */
    0x18,  /* 00011000 */
    0x7E,  /* 01111110 */
    0x00,  /* 00000000 */
};

byte letterL[] = {
    0xC0,  /* 11000000 */
    0xC0,  /* 11000000 */
    0xC0,  /* 11000000 */
    0xC0,  /* 11000000 */
    0xC0,  /* 11000000 */
    0xC0,  /* 11000000 */
    0xFE,  /* 11111110 */
    0x00,  /* 00000000 */
};

byte letterM[] = {
    0xC6,  /* 11000110 */
    0xEE,  /* 11101110 */
    0xFE,  /* 11111110 */
    0xFE,  /* 11111110 */
    0xD6,  /* 11010110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0x00,  /* 00000000 */
};

byte letterO[] = {
    0x7C,  /* 01111100 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0x7C,  /* 01111100 */
    0x00,  /* 00000000 */
};

byte letterU[] = {
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xFE,  /* 11111110 */
    0x00,  /* 00000000 */
};

byte letterV[] = {
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0xC6,  /* 11000110 */
    0x7C,  /* 01111100 */
    0x38,  /* 00111000 */
    0x00,  /* 00000000 */
};

byte symbolSpace[] = {
    0x00,  /* 00000000 */
    0x00,  /* 00000000 */
    0x00,  /* 00000000 */
    0x00,  /* 00000000 */
    0x00,  /* 00000000 */
    0x00,  /* 00000000 */
    0x00,  /* 00000000 */
    0x00,  /* 00000000 */
};

byte symbolExclamation[] = {
    0x18,  /* 00011000 */
    0x18,  /* 00011000 */
    0x18,  /* 00011000 */
    0x18,  /* 00011000 */
    0x00,  /* 00000000 */
    0x00,  /* 00000000 */
    0x18,  /* 00011000 */
    0x18,  /* 00011000 */
};

void bootAnimation() {
  int SHOW_FOR = 200;
  for (byte row=1; row <= ROWS_SIZE; row++) {
    useRow(row);
    for(int time=0; time<SHOW_FOR; time++) {
      for(byte col=1; col<= COLS_SIZE; col++) {
        useColumn(col);
      }
    }
    cleanScreen();
    delay(200);
  }
}

void setup() {
  cleanScreen();
  bootAnimation();
}

void loop() {
  int SHOW_FOR = 1000;
  byte *message[] = {letterM, letterH, letterC, letterI, letterD, symbolExclamation, symbolSpace, symbolExclamation, symbolSpace, symbolExclamation, symbolSpace, symbolSpace, symbolSpace};
  byte MESG_LENGTH = 13;
  for (byte letter=0; letter<MESG_LENGTH; letter++) {
    showCharacter(message[letter], SHOW_FOR);
    cleanScreen();
    delay(SHOW_FOR/2);
  }

}


























