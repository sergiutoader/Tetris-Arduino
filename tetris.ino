#include "Ucglib.h"
#define MOVEL_BTN 4
#define MOVER_BTN 3
#define ROTATEL_BTN 7
#define ROTATER_BTN 6
#define START_BTN 12
#define LEN 8
#define SQUARE_COUNT 4

#define T_PIECE 0
#define O_PIECE 1
#define I_PIECE 2
#define S_PIECE 3
#define Z_PIECE 4
#define J_PIECE 5
#define L_PIECE 6

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 160
#define INIT_X 56

#define SQR_W (SCREEN_WIDTH / LEN)
#define SQR_H (SCREEN_HEIGHT / LEN)


/* ================= Buzzer part ================ */


int tempo=144;
int buzzer = 5;


int melody[] = {
  
  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,
 
};


int notes = sizeof(melody)/sizeof(melody[0])/2; 

// this calculates the duration of a whole note in ms (60s/tempo)*4 beats
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;


void play_theme() {
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
 
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
 
    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration*0.9);
 
    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzer);
  }

}


void play_change_position_note() {
  divider = melody[1];
  if (divider > 0) {
    // regular note, just proceed
    noteDuration = (wholenote) / divider;
  } else if (divider < 0) {
    // dotted notes are represented with negative durations!!
    noteDuration = (wholenote) / abs(divider);
    noteDuration *= 1.5; // increases the duration in half for dotted notes
  }
  tone(buzzer, melody[0], noteDuration*0.1);
  delay(noteDuration);
  noTone(buzzer);
}

void play_line_complete_tune() {
   for (int thisNote = 2; thisNote <= 6; thisNote = thisNote + 2) {
 
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
 
    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration*0.4);
 
    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}


/* ============================================== */

byte rgb_map[SQR_H][SQR_W];
bool square_map[SQR_H][SQR_W];

class RGB {
public:
  byte r, g, b;
  RGB(){}
  RGB(byte r, byte g, byte b) {
    this->r = r;
    this->g = g;
    this->b = b;
  }
};

struct square {
  RGB rgb;
  byte x, y;
};

class Piece {
  // squares array
public:
  struct square squares[4];

  byte color_code;
  // type
  byte type;

  // rotation and inAir properties
  int rotation;
  RGB rgb;

  Piece() {
    this->rotation = 0;

    byte red = 0, green = 0, blue = 0;

    byte color_mask = random(1, 7);
    this->color_code = color_mask;
    if(color_mask & 1) {
      red = 255;
    }
     if(color_mask & 2) {
      green = 255;
    }
     if(color_mask & 4) {
      blue = 255;
    }

    RGB rgb = RGB(red, green, blue);
    this->rgb = rgb;

    // generate random piece type
    byte piece_type =  random(0, 7);

    this->type = piece_type;

    switch(piece_type) {
    case T_PIECE: // T piece
      squares[0] = init_square(INIT_X,      0,  rgb);
      squares[1] = init_square(INIT_X+LEN,  0,  rgb);
      squares[2] = init_square(INIT_X-LEN,  0,  rgb);
      squares[3] = init_square(INIT_X,    LEN,  rgb);
      break;
    case O_PIECE: // O type
      squares[0] = init_square(INIT_X,        0,  rgb);
      squares[1] = init_square(INIT_X+LEN,    0,  rgb);
      squares[2] = init_square(INIT_X,      LEN,  rgb);
      squares[3] = init_square(INIT_X+LEN,  LEN,  rgb);
      break;
    case I_PIECE: // I type
      squares[0] = init_square(INIT_X-2*LEN,  0,  rgb);
      squares[1] = init_square(INIT_X-LEN,    0,  rgb);
      squares[2] = init_square(INIT_X,        0,  rgb);
      squares[3] = init_square(INIT_X+LEN,    0,  rgb);
      break;
    case S_PIECE: // S type
      squares[0] = init_square(INIT_X,        0,  rgb);
      squares[1] = init_square(INIT_X+LEN,    0,  rgb);
      squares[2] = init_square(INIT_X,      LEN,  rgb);
      squares[3] = init_square(INIT_X-LEN,  LEN,  rgb);
      break;
    case Z_PIECE: // Z type
      squares[0] = init_square(INIT_X-LEN,    0,  rgb);
      squares[1] = init_square(INIT_X,        0,  rgb);
      squares[2] = init_square(INIT_X,      LEN,  rgb);
      squares[3] = init_square(INIT_X+LEN,  LEN,  rgb);
      break;
    case J_PIECE: // J type
      squares[0] = init_square(INIT_X-LEN,    0,  rgb);
      squares[1] = init_square(INIT_X-LEN,  LEN,  rgb);
      squares[2] = init_square(INIT_X,      LEN,  rgb);
      squares[3] = init_square(INIT_X+LEN,  LEN,  rgb);
      break;
    case L_PIECE: // L type
      squares[0] = init_square(INIT_X+LEN,    0,  rgb);
      squares[1] = init_square(INIT_X-LEN,  LEN,  rgb);
      squares[2] = init_square(INIT_X,      LEN,  rgb);
      squares[3] = init_square(INIT_X+LEN,  LEN,  rgb);
      break;
    }
    
  }

  static struct square init_square(byte x, byte y, RGB rgb) {
    struct square s;
    s.x = x; // 48
    s.y = y; // 0
    s.rgb = rgb;
    return s;
  }

  void draw_black(struct square s, Ucglib_ST7735_18x128x160_HWSPI ucg) {
    ucg.setColor(0, 0, 0, 0);
    ucg.drawBox(s.x, s.y, LEN, LEN);
  }

  static void draw_square(struct square s, Ucglib_ST7735_18x128x160_HWSPI ucg) {
    ucg.setColor(0, s.rgb.r, s.rgb.g, s.rgb.b);
    ucg.drawBox(s.x, s.y, LEN, LEN);
  }

  void draw_piece(Ucglib_ST7735_18x128x160_HWSPI ucg, int millis) {
    for(int i = 0; i < SQUARE_COUNT; ++i) {
      draw_square(this->squares[i], ucg);
    }
    delay(millis);
  }


  /* PIECE MOVEMENT */
  bool move_left() {
  
    // check if move is valid
    for(int i = 0; i < SQUARE_COUNT; ++i) {
      if(this->squares[i].x <= 0 || this->squares[i].y >= SCREEN_HEIGHT - LEN) {
        return false;
      }

      int sx = this->squares[i].x / LEN;
      int sy = this->squares[i].y / LEN;

      if(square_map[sy][sx - 1]) {
        return false;
      }
    }

    // move left
    for(int i = 0; i < SQUARE_COUNT; ++i) {
      this->squares[i].x -= LEN;
    }
  
    return true;
  }
  
  bool move_right() {
    for(int i = 0; i < SQUARE_COUNT; ++i) {
      if(this->squares[i].x >= SCREEN_WIDTH - LEN || 
        this->squares[i].y >= SCREEN_HEIGHT - LEN) {
        return false;
      }

      int sx = this->squares[i].x / LEN;
      int sy = this->squares[i].y / LEN;

      if(square_map[sy][sx + 1]) {
        return false;
      }
    }
  
    for(int i = 0; i < SQUARE_COUNT; ++i) {
      this->squares[i].x += LEN;
    }
  
    return true;
  }
  
  bool move_down() {
    for(int i = 0; i < SQUARE_COUNT; ++i) {
      if(this->squares[i].y >= SCREEN_HEIGHT - LEN) {
        return false;
      }

      int sx = this->squares[i].x / LEN;
      int sy = this->squares[i].y / LEN;

      if(square_map[sy + 1][sx]) {
        return false;
      }
      
    }
  
    for(int i = 0; i < SQUARE_COUNT; ++i) {
      this->squares[i].y += LEN;
    }
    
    return true;
  }

  bool rotate_left() {
    struct square aux[4];
    switch(this->type) {
    case(O_PIECE):
      break;
    case(I_PIECE):
      if(this->rotation % 180 == 0) {
        // horizontal -> vertical
        // check lower boundaries and lateral boundaries
        aux[0] = init_square(squares[0].x + 2*LEN,  squares[0].y - 2*LEN,   this->rgb);
        aux[1] = init_square(squares[1].x + LEN,    squares[1].y - LEN,     this->rgb);
        aux[2] = init_square(squares[2].x,          squares[2].y,           this->rgb);
        aux[3] = init_square(squares[3].x - LEN,    squares[3].y + LEN,     this->rgb);
        
      } else {
        // vertical -> horizontal
        aux[0] = init_square(squares[0].x - 2*LEN,  squares[0].y + 2*LEN,   this->rgb);
        aux[1] = init_square(squares[1].x - LEN,    squares[1].y + LEN,     this->rgb);
        aux[2] = init_square(squares[2].x,          squares[2].y,           this->rgb);
        aux[3] = init_square(squares[3].x + LEN,    squares[3].y - LEN,     this->rgb);
        
      }

      for(int i = 0; i < SQUARE_COUNT; ++i) {
        if(aux[i].x < 0 || aux[i].x > SCREEN_WIDTH - LEN || aux[i].y >= SCREEN_HEIGHT) {
          return false;
        }
      }

      memcpy(this->squares, aux, SQUARE_COUNT * sizeof(struct square));
      break;

    case(S_PIECE):
      if(this->rotation % 180 == 0) {
        // horizontal -> vertical
        memcpy(aux, this->squares, SQUARE_COUNT * sizeof(struct square));
        aux[1] = init_square(squares[1].x - 2*LEN,  squares[1].y,         this->rgb);
        aux[3] = init_square(squares[3].x,          squares[3].y - 2*LEN, this->rgb);
        
      } else {
        // vertical -> horizontal
        memcpy(aux, this->squares, SQUARE_COUNT * sizeof(struct square));
        aux[1] = init_square(squares[1].x + 2*LEN,  squares[1].y,         this->rgb);
        aux[3] = init_square(squares[3].x,          squares[3].y + 2*LEN, this->rgb);
        
      }

      for(int i = 0; i < SQUARE_COUNT; ++i) {
        if(aux[i].x < 0 || aux[i].x > SCREEN_WIDTH - LEN || aux[i].y >= SCREEN_HEIGHT) {
          return false;
        }
      }

      memcpy(this->squares, aux, SQUARE_COUNT * sizeof(struct square));
      break;
    case(Z_PIECE):
      if(this->rotation % 180 == 0) {
        // horizontal -> vertical
        // check lower boundaries and lateral boundaries
        aux[0] = init_square(squares[0].x + LEN,    squares[0].y + LEN,   this->rgb);
        aux[1] = init_square(squares[1].x,          squares[1].y,         this->rgb);
        aux[2] = init_square(squares[2].x + LEN,    squares[2].y - LEN,   this->rgb);
        aux[3] = init_square(squares[3].x,          squares[3].y - 2*LEN, this->rgb);
        
      } else {
        // vertical -> horizontal
        aux[0] = init_square(squares[0].x - LEN,    squares[0].y - LEN,   this->rgb);
        aux[1] = init_square(squares[1].x,          squares[1].y,         this->rgb);
        aux[2] = init_square(squares[2].x - LEN,    squares[2].y + LEN,   this->rgb);
        aux[3] = init_square(squares[3].x,          squares[3].y + 2*LEN, this->rgb);
        
      }

      for(int i = 0; i < SQUARE_COUNT; ++i) {
        if(aux[i].x < 0 || aux[i].x > SCREEN_WIDTH - LEN || aux[i].y >= SCREEN_HEIGHT) {
          return false;
        }
      }

      memcpy(this->squares, aux, SQUARE_COUNT * sizeof(struct square));
      break;
    case(T_PIECE):
      switch(this->rotation) {
      case 0:
        // all squares except 1 are the same
        memcpy(aux, this->squares, SQUARE_COUNT * sizeof(struct square));
        aux[1] = init_square(squares[1].x - LEN, squares[1].y - LEN, this->rgb);
        break;
      case 90:
        aux[0] = init_square(squares[0].x,       squares[0].y,        this->rgb);
        aux[1] = init_square(squares[1].x + LEN, squares[1].y + LEN,  this->rgb);
        aux[2] = init_square(squares[2].x - LEN, squares[2].y - LEN,  this->rgb);
        aux[3] = init_square(squares[3].x - LEN, squares[3].y + LEN,  this->rgb);
        break;
      case 180:
        // all squares except 2 are the same
        memcpy(aux, this->squares, SQUARE_COUNT * sizeof(struct square));
        aux[2] = init_square(squares[2].x + LEN, squares[2].y + LEN, this->rgb);
        break;
      case 270:
        // first 3 squares are the same
        memcpy(aux, this->squares, 3 * sizeof(struct square));
        aux[3] = init_square(squares[3].x + LEN, squares[3].y - LEN, this->rgb);
        break;
      }

      for(int i = 0; i < SQUARE_COUNT; ++i) {
        if(aux[i].x < 0 || aux[i].x > SCREEN_WIDTH - LEN || aux[i].y >= SCREEN_HEIGHT) {
          return false;
        }
      }

      memcpy(this->squares, aux, SQUARE_COUNT * sizeof(struct square));
      break;
    case(J_PIECE):
      switch(this->rotation) {
      case 0:
        memcpy(aux, this->squares, 2 * sizeof(struct square));
        aux[2] = init_square(squares[2].x - LEN, squares[2].y - 2*LEN, this->rgb);
        aux[3] = init_square(squares[3].x - LEN, squares[3].y - 2*LEN, this->rgb);
        break;
      case 90:
        memcpy(&aux[2], &this->squares[2], 2 * sizeof(struct square));
        aux[0] = init_square(squares[0].x - 2*LEN, squares[0].y + LEN, this->rgb);
        aux[1] = init_square(squares[1].x - 2*LEN, squares[1].y + LEN, this->rgb);
        break;
      case 180:
        memcpy(aux, this->squares, 2 * sizeof(struct square));
        aux[2] = init_square(squares[2].x + LEN, squares[2].y + 2*LEN, this->rgb);
        aux[3] = init_square(squares[3].x + LEN, squares[3].y + 2*LEN, this->rgb);
        break;
      case 270:
        memcpy(&aux[2], &this->squares[2], 2 * sizeof(struct square));
        aux[0] = init_square(squares[0].x + 2*LEN, squares[0].y - LEN, this->rgb);
        aux[1] = init_square(squares[1].x + 2*LEN, squares[1].y - LEN, this->rgb);
        break;
      }

      for(int i = 0; i < SQUARE_COUNT; ++i) {
        if(aux[i].x < 0 || aux[i].x > SCREEN_WIDTH - LEN || aux[i].y >= SCREEN_HEIGHT) {
          return false;
        }
      }

      memcpy(this->squares, aux, SQUARE_COUNT * sizeof(struct square));
      break;
    case(L_PIECE):
      switch(this->rotation) {
      case 0:
        memcpy(aux, this->squares, SQUARE_COUNT * sizeof(struct square));
        aux[0] = init_square(squares[0].x - 2*LEN, squares[0].y - LEN, this->rgb);
        aux[3] = init_square(squares[3].x - 2*LEN, squares[3].y - LEN, this->rgb);
        break;
      case 90:
        memcpy(aux, this->squares, SQUARE_COUNT * sizeof(struct square));
        aux[1] = init_square(squares[1].x - LEN, squares[1].y + 2*LEN, this->rgb);
        aux[2] = init_square(squares[2].x - LEN, squares[2].y + 2*LEN, this->rgb);
        break;
      case 180:
        memcpy(aux, this->squares, SQUARE_COUNT * sizeof(struct square));
        aux[0] = init_square(squares[0].x + 2*LEN, squares[0].y + LEN, this->rgb);
        aux[3] = init_square(squares[3].x + 2*LEN, squares[3].y + LEN, this->rgb);
        break;
      case 270:
        memcpy(aux, this->squares, SQUARE_COUNT * sizeof(struct square));
        aux[1] = init_square(squares[1].x + LEN, squares[1].y - 2*LEN, this->rgb);
        aux[2] = init_square(squares[2].x + LEN, squares[2].y - 2*LEN, this->rgb);
        break;
      }

      for(int i = 0; i < SQUARE_COUNT; ++i) {
        if(aux[i].x < 0 || aux[i].x > SCREEN_WIDTH - LEN || aux[i].y >= SCREEN_HEIGHT) {
          return false;
        }
      }

      memcpy(this->squares, aux, SQUARE_COUNT * sizeof(struct square));
      break;
    }

    this->rotation -= 90;
   
    if(this->rotation < 0) {
      this->rotation = 270;
    }

    return true;
  }


  bool rotate_right() {
    struct square aux[4];
    switch(this->type) {
    case(O_PIECE):
      return this->rotate_left();
    case(I_PIECE):
      return this->rotate_left();
    case(S_PIECE):
      return this->rotate_left();
    case(Z_PIECE):
      return this->rotate_left();
    case(T_PIECE):
      switch(this->rotation) {
      case 0:
        aux[0] = init_square(squares[0].x,       squares[0].y,        this->rgb);
        aux[1] = init_square(squares[1].x - LEN, squares[1].y - LEN,  this->rgb);
        aux[2] = init_square(squares[2].x + LEN, squares[2].y + LEN,  this->rgb);
        aux[3] = init_square(squares[3].x + LEN, squares[3].y - LEN,  this->rgb);
        break;
      case 90:
        // all squares except 2 are the same
        memcpy(aux, this->squares, SQUARE_COUNT * sizeof(struct square));
        aux[2] = init_square(squares[2].x - LEN, squares[2].y - LEN, this->rgb);
        break;
      case 180:
        // first 3 squares are the same
        memcpy(aux, this->squares, 3 * sizeof(struct square));
        aux[3] = init_square(squares[3].x - LEN, squares[3].y + LEN, this->rgb);
        break;
      case 270:
        // first 3 squares are the same
        memcpy(aux, this->squares, SQUARE_COUNT * sizeof(struct square));
        aux[1] = init_square(squares[1].x + LEN, squares[1].y + LEN, this->rgb);
        break;
      }

      for(int i = 0; i < SQUARE_COUNT; ++i) {
        if(aux[i].x < 0 || aux[i].x > SCREEN_WIDTH - LEN || aux[i].y >= SCREEN_HEIGHT) {
          return false;
        }
      }

      memcpy(this->squares, aux, SQUARE_COUNT * sizeof(struct square));
      break;
    case(J_PIECE):
      switch(this->rotation) {
      case 0:
        memcpy(&aux[2], &this->squares[2], 2 * sizeof(struct square));
        aux[0] = init_square(squares[0].x + 2*LEN, squares[0].y - LEN, this->rgb);
        aux[1] = init_square(squares[1].x + 2*LEN, squares[1].y - LEN, this->rgb);
        break;
      case 90:
        memcpy(aux, this->squares, 2 * sizeof(struct square));
        aux[2] = init_square(squares[2].x - LEN, squares[2].y - 2*LEN, this->rgb);
        aux[3] = init_square(squares[3].x - LEN, squares[3].y - 2*LEN, this->rgb);
        break;
      case 180:
        memcpy(&aux[2], &this->squares[2], 2 * sizeof(struct square));
        aux[0] = init_square(squares[0].x - 2*LEN, squares[0].y + LEN, this->rgb);
        aux[1] = init_square(squares[1].x - 2*LEN, squares[1].y + LEN, this->rgb);
        break;
      case 270:
        memcpy(aux, this->squares, 2 * sizeof(struct square));
        aux[2] = init_square(squares[2].x + LEN, squares[2].y + 2*LEN, this->rgb);
        aux[3] = init_square(squares[3].x + LEN, squares[3].y + 2*LEN, this->rgb);
        break;
      }

      for(int i = 0; i < SQUARE_COUNT; ++i) {
        if(aux[i].x < 0 || aux[i].x > SCREEN_WIDTH - LEN || aux[i].y >= SCREEN_HEIGHT) {
          return false;
        }
      }

      memcpy(this->squares, aux, SQUARE_COUNT * sizeof(struct square));
      break;
    case(L_PIECE):
      switch(this->rotation) {
      case 0:
        memcpy(aux, this->squares, SQUARE_COUNT * sizeof(struct square));
        aux[1] = init_square(squares[1].x + LEN, squares[1].y - 2*LEN, this->rgb);
        aux[2] = init_square(squares[2].x + LEN, squares[2].y - 2*LEN, this->rgb);
        break;
      case 90:
        memcpy(aux, this->squares, SQUARE_COUNT * sizeof(struct square));
        aux[0] = init_square(squares[0].x - 2*LEN, squares[0].y - LEN, this->rgb);
        aux[3] = init_square(squares[3].x - 2*LEN, squares[3].y - LEN, this->rgb);
        break;
      case 180:
        memcpy(aux, this->squares, SQUARE_COUNT * sizeof(struct square));
        aux[1] = init_square(squares[1].x - LEN, squares[1].y + 2*LEN, this->rgb);
        aux[2] = init_square(squares[2].x - LEN, squares[2].y + 2*LEN, this->rgb);
        break;
      case 270:
        memcpy(aux, this->squares, SQUARE_COUNT * sizeof(struct square));
        aux[0] = init_square(squares[0].x + 2*LEN, squares[0].y + LEN, this->rgb);
        aux[3] = init_square(squares[3].x + 2*LEN, squares[3].y + LEN, this->rgb);
        break;
      }

      for(int i = 0; i < SQUARE_COUNT; ++i) {
        if(aux[i].x < 0 || aux[i].x > SCREEN_WIDTH - LEN || aux[i].y >= SCREEN_HEIGHT) {
          return false;
        }
      }

      memcpy(this->squares, aux, SQUARE_COUNT * sizeof(struct square));
      break;
    }

    this->rotation += 90;
    if(this->rotation == 360) {
      this->rotation = 0;
    }

    return true;
  }
  
};

// Create display and define the pins
Ucglib_ST7735_18x128x160_HWSPI ucg(8,10,9);
// The rest of the pins are pre-selected as the default hardware

int var; // Create a variable to have something dynamic
bool started = false;
bool lateral_rotation = false;

Piece curr_piece;

// ======================== SQUARE MAP ===============================

void init_map() {
  for(int i = 0; i < SQR_H; i++) {
    for(int j = 0; j < SQR_W; j++) {
      square_map[i][j] = false;
    }
  }
}

void init_rgb() {
  for(int i = 0; i < SQR_H; i++) {
    for(int j = 0; j < SQR_W; j++) {
      rgb_map[i][j] = 0;
    }
  }
}

void update_square_map() {
  int sx, sy;
  for(int i = 0; i < SQUARE_COUNT; ++i) {
    sx = curr_piece.squares[i].x / LEN;
    sy = curr_piece.squares[i].y / LEN;

    square_map[sy][sx] = true;
    rgb_map[sy][sx] = curr_piece.color_code;
  }
  for(int i = 0; i < SQR_H; i++) {
    if(line_complete(i)) {
        adjust_map(i);
    }
  }
}

bool line_complete(int l) {
  bool complete = true;
  for(int i = 0; i < SQR_W; ++i) {
    complete &= square_map[l][i];
  }
  return complete;
}

void adjust_map(int l) {
  for(int i = l; i > 0; --i) {
    memcpy(square_map[i], square_map[i-1], SQR_W * sizeof(bool));
    memcpy(rgb_map[i], rgb_map[i-1], SQR_W * sizeof(byte));
  }

  // set first line to 0
  memset(square_map, 0, SQR_W * sizeof(bool));
  memset(rgb_map, 0, SQR_W * sizeof(byte));

  redraw_map(l);
}

void change_position(struct square old_squares[]) {
  
  for(int i = 0; i < SQUARE_COUNT; ++i) {
    curr_piece.draw_black(old_squares[i], ucg);
  }
  
  curr_piece.draw_piece(ucg, 50);
  play_change_position_note();
 
}

void redraw_map(int l) {

  play_line_complete_tune();

  
  for(int i = 0; i < SQR_H; ++i) {
    for(int j = 0; j < SQR_W; ++j) {

      byte color_code = rgb_map[i][j];
      byte r = (color_code & 1) * 255;
      byte g = (color_code & 2) * 255;
      byte b = (color_code & 4) * 255;

      Piece::draw_square(
        Piece::init_square(j << 3, i << 3, RGB(r, g, b)),
        ucg
       );
    }
  }
}

// ====================================================================

void print_start() {
   // write to the display the variable var with left alignment:
  ucg.setFont(ucg_font_inb16_mr);
  ucg.setColor(0, 255, 255, 0);
  ucg.setColor(1,0,0,0);
  ucg.setPrintPos(0, 80);
  ucg.print("Press");

  ucg.setPrintPos(0, 100);
  ucg.print("Start");
   
}


/* Set Interrupt for each second */

void set_interrupt() {
  cli(); //stop interrupts

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 7812;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei(); // enable interrupts
}


ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz
  if(started) {
    lateral_rotation = false;
  } 
}


bool game_over() {
  for(int i = 0; i < 2; i++) {
    for(int j = 6; j < 9; j++) {
      if(square_map[i][j]) {
        return true;
      }
    }
  }

  return false;
}


void display_gameover_screen() {
  ucg.clearScreen();
  ucg.setColor(0,255,255,255); // set color (0, r, g, b)
  ucg.setColor(1,0,0,0); // set color of text background
  ucg.setPrintPos(0, 24); // set position(x, y);
  ucg.print("Game");

  // Write tot the display the text "Game":
  ucg.setColor(0, 255, 0, 0);
  ucg.setPrintPos(0, 50);
  ucg.print("Over!");

  play_theme();
}

/* ============================================================== */

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  pinMode(MOVEL_BTN, INPUT_PULLUP);
  pinMode(MOVER_BTN, INPUT_PULLUP);
  pinMode(ROTATEL_BTN, INPUT_PULLUP);
  pinMode(ROTATER_BTN, INPUT_PULLUP);
  pinMode(START_BTN, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  var = 20;

  curr_piece = Piece();
  init_map();
  init_rgb();

  // Display setup:

  // Select a type of text background:
  // ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.begin(UCG_FONT_MODE_SOLID);

  // Clear the screen
  ucg.clearScreen();

  // Set display orientation

  // Set text orientation:
  // It only alters the text, not the entire display
  // ucg.setPrintDir(0); // 0, 1, 2, 3 to change orientation
  
  // set font
  ucg.setFont(ucg_font_inr21_mr);

  // Write to the display the text "Tetris":
  ucg.setColor(0,255,255,255); // set color (0, r, g, b)
  ucg.setColor(1,0,0,0); // set color of text background
  ucg.setPrintPos(0, 24); // set position(x, y);
  ucg.print("Tetris");

  // Write tot the display the text "Game":
  ucg.setColor(0, 255, 0, 0);
  ucg.setPrintPos(0, 50);
  ucg.print("Game");

  print_start();

  // enable move down interrupt
  set_interrupt();
}

void loop() {

  if(!started) {
    // start a new game by pressing the start button
    if(!digitalRead(START_BTN)) {
      started = true;
      ucg.clearScreen();
    }

  } else {

    lateral_rotation = true;
    while(lateral_rotation) {

      // save last state
      struct square old_squares[SQUARE_COUNT];
      memcpy(old_squares, curr_piece.squares, SQUARE_COUNT * sizeof(struct square));
  
      if(!digitalRead(MOVEL_BTN)) {
        
        curr_piece.move_left();
        change_position(old_squares);
  
      } else if(!digitalRead(MOVER_BTN)) {
  
       curr_piece.move_right();
       change_position(old_squares);
      }


      if(!digitalRead(ROTATEL_BTN)) {
      
        curr_piece.rotate_left();
        change_position(old_squares);
        
      } else if(!digitalRead(ROTATER_BTN)) {
        
        curr_piece.rotate_right();
        change_position(old_squares);
      }
      
    }

    struct square old_squares_down[SQUARE_COUNT];
    memcpy(old_squares_down, curr_piece.squares, SQUARE_COUNT * sizeof(struct square));

    // clear screen on previous position
    for(int i = 0; i < SQUARE_COUNT; ++i) {
      curr_piece.draw_black(old_squares_down[i], ucg);
    }

    bool contact = curr_piece.move_down();
    curr_piece.draw_piece(ucg, 0);

    if(contact == false) {
      update_square_map();
      curr_piece = Piece();

      // check if game is over
      if(game_over()) {
        started = false;
        display_gameover_screen();
        setup();
      }
      return;
    }

    // press start during game to go back to main menu
    if(!digitalRead(START_BTN)) {
      started = false;
      setup();
    }
  }
}
