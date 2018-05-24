// Wiring and Wiegand Protocol consts
const int D1 = 6;
const int D0 = 7;
const int WAIT_TIME = 34;

// For static exemple
char packetData[] = "01101011001111011101110101";
int packetLen = strlen( packetData );

// For dynamic exemple
String inData;
int i;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode (D1, OUTPUT);
  pinMode (D0, OUTPUT);
  digitalWrite(D1, HIGH);
  digitalWrite(D0, HIGH);
  Serial.begin(115200);
}

void wait() {
    delayMicroseconds(WAIT_TIME);
}

int oddsToOne(String s) {
    if (s.endsWith("1")) return 1;
    if (s.endsWith("3")) return 1;
    if (s.endsWith("5")) return 1;
    if (s.endsWith("7")) return 1;
    if (s.endsWith("9")) return 1;
    return 0;
}

String divByTwo(String s) {
    String new_s = "";
    int add = 0;
    int chCpt;

    for (chCpt = 0; chCpt < s.length(); chCpt++) {
        char ch = s.charAt(chCpt);
        int new_dgt = floor((ch - '0') / 2) + add;
        new_s.concat(String(new_dgt));
        add = oddsToOne(String(ch)) * 5;
    }

    if (new_s != "0" && new_s.startsWith("0")) {
        new_s = new_s.substring(1, new_s.length());
    }

    return new_s;
}

String getBitsByStringNumber(String num) {
  String stack = "";
  String tmp = "";
  
  if (num == "0") {
    stack = "0";
  } else {
    while (num != "0") {
      tmp = stack;
      stack = String(oddsToOne(num));
      stack.concat(tmp);
      num = divByTwo(num);      
    }
  }
      
  return stack;
}


// the loop function runs over and over again forever
void loop() {
   
    if (Serial.available() > 0) {
      inData = Serial.readString();
      inData.trim();
      Serial.println(inData);  
      Serial.println(inData.length());
      inData = getBitsByStringNumber(inData);
      Serial.println(inData);  

      for (i = 0; i < inData.length(); i++){
          if (inData.charAt(i) == '1') {
              digitalWrite(D1, LOW);
              delayMicroseconds(34);
              digitalWrite(D1, HIGH);
          } else {
              digitalWrite(D0, LOW);
              delayMicroseconds(34);
              digitalWrite(D0, HIGH);
          }
          delay(2);
      }
           
      digitalWrite(LED_BUILTIN, LOW); 
      delay(200);
      digitalWrite(LED_BUILTIN, HIGH); 
    }
}






