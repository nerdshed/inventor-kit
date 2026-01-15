// ROW and COLUMN pins
int R[] = {2,7,A5,5,13,A4,12,A2};
int C[] = {6,11,10,3,A3,4,8,9};

// Push button pin
const int buttonPin = A0;
bool showSmile = true;  
bool lastButtonState = HIGH; 
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;  // 50 ms debounce 

// Smiling face
unsigned char smile[8][8] =
{
  {0,0,1,1,1,1,0,0},
  {0,1,0,0,0,0,1,0},
  {1,0,1,0,0,1,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,1,0,0,1,0,1},
  {1,0,0,1,1,0,0,1},
  {0,1,0,0,0,0,1,0},
  {0,0,1,1,1,1,0,0}
};

// Sad face
unsigned char sad[8][8] =
{
  {0,0,1,1,1,1,0,0},
  {0,1,0,0,0,0,1,0},
  {1,0,1,0,0,1,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,1,1,0,0,1},
  {1,0,1,0,0,1,0,1},
  {0,1,0,0,0,0,1,0},
  {0,0,1,1,1,1,0,0}
};

void setup()
{
  for(int i = 0; i < 8; i++)
  {
    pinMode(R[i], OUTPUT);
    pinMode(C[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP); 
}

void loop()
{
  // Read the button
  bool reading = digitalRead(buttonPin);

  // Debounce
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW) { // Button pressed
      showSmile = !showSmile; // Toggle face
      delay(200); 
    }
  }
  
  lastButtonState = reading;

  // Display the chosen face
  if(showSmile) {
    Display(smile);
  } else {
    Display(sad);
  }
}

void Display(unsigned char dat[8][8])
{
  for(int c = 0; c < 8; c++)
  {
    digitalWrite(C[c], LOW);

    for(int r = 0; r < 8; r++)
    {
      digitalWrite(R[r], dat[r][c]);
    }

    delay(1);
    Clear();
  }
}

void Clear()
{
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(R[i], LOW);
    digitalWrite(C[i], HIGH);
  }
}
