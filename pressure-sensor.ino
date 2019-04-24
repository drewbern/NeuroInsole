// the setup function runs once when you press reset or power the board
const int aInPin0 = A0;
const int aInPin1 = A1;
unsigned long delayStart = 0;
unsigned long DELAY_TIME = 2000;
int heel = 0;
int ball = 0;
int gaitStage = 0;
int heelStrikeTime = 0;
int footFlatTime = 0;
int heelToFlatTime = 0;
bool footOffGround = false;
bool toeFirst = false;
bool delayRunning = false;
int totalTime = 0;
int intervalCount = 0;

void setup() {
  // initialize digital pin 13 as an output.
  Serial.begin(9600);

  delayStart = millis();
  delayRunning = true;
}

// the loop function runs over and over again forever
void loop() {

//  if (delayRunning && ((millis() - delayStart) >= DELAY_TIME)) {
//    delayStart += DELAY_TIME;
//    Serial.print("Sensor1 = " );                       
//    Serial.print(heel);
//    Serial.print("\tSensor2 = ");
//    Serial.println(ball);
//  }
  
  heel = analogRead(aInPin0);
  ball = analogRead(aInPin1);
  if ((gaitStage == 0) && (heel > 1015)) {
    Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    box();
    Serial.print("* Gait State: ");
    Serial.println("Heel Strike\t\t*");
    Serial.println("*\t\t\t\t\t*");
    printAverage();
    box();
    heelStrikeTime = millis();
    toeFirst = false;
    footOffGround = false;
    gaitStage++;
  }
  if ((gaitStage == 0) && (ball > 1015) && (toeFirst == false)) {
    Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    box();
    Serial.print("* Gait State: ");
    Serial.println("Foot drop detected\t*");
    Serial.println("*\t\t\t\t\t*");
    printAverage();
    box();
    toeFirst = true;
  }
  if ((gaitStage == 1) && (ball > 1015)) {
    Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    box();
    Serial.print("* Gait State: ");
    Serial.println("Midstance\t\t\t*");
    footFlatTime = millis();
    heelToFlatTime = footFlatTime - heelStrikeTime;
    totalTime += heelToFlatTime;
    intervalCount++;
    Serial.println("*\t\t\t\t\t*");
    printAverage();
    box();
    gaitStage++;
  }
  if ((gaitStage == 2) && (heel < 1015)) {
    Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    box();
    Serial.print("* Gait State: ");
    Serial.println("Heel liftoff\t\t*");
    Serial.println("*\t\t\t\t\t*");
    printAverage();
    box();
    gaitStage++;
  }
  if ((gaitStage == 3) && (ball < 1015)) {
    Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    box();
    Serial.print("* Gait State: ");
    Serial.println("Toe pushoff\t\t*");
    Serial.println("*\t\t\t\t\t*");
    printAverage();
    box();
    footOffGround = true;
    gaitStage = 0;
  }
  if ((ball < 1015) && (heel < 1015) && (footOffGround == false)) {
    Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    box();
    Serial.print("* Gait State: ");
    Serial.println("Food off ground\t\t*");
    Serial.println("*\t\t\t\t\t*");
    printAverage();
    box();
    footOffGround = true;
    gaitStage = 0;
  }
}

float calcAverage() {
  float average = float(totalTime) / float(intervalCount);
  float averageSecs = average / 1000;
  return averageSecs;
}

void printAverage() {
    Serial.print("* Current average: ");
    float average = calcAverage();
    Serial.print(average);
    Serial.println(" seconds\t\t*");
}

void box() {
  Serial.println("*****************************************");
}
