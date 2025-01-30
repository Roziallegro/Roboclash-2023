// outside of setup() function, all you need to do is include libraries and define variables

// assign motor pins
const int L_PWM = 53;
const int R_PWM = 52;
const int EN = 6; // EN sets the speed

int turn_Speed = 80;

// put your setup code here, to run once:
void setup() {
  // setting motor pins as output
  pinMode(R_PWM, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(EN, OUTPUT);

  // to set-up wheel movement/direction
  /*digitalWrite(L_PWM, 1); or digitalWrite(L_PWM, true); or digitalWrite(L_PWM, HIGH)
  digitalWrite(L_PWM, 0); or digitalWrite(L_PWM, false); or digitalWrite(L_PWM, LOW) */
  digitalWrite(L_PWM, 0);
  digitalWrite(R_PWM, 1); // refer to truth table

  // to set-up wheel speed
  // analogWrite(EN, turn_Speed); // 255 is more max speed, 127 for half speed
}

// put your main code here, to run repeatedly:
void loop() {
  analogWrite(EN, turn_Speed);
}
