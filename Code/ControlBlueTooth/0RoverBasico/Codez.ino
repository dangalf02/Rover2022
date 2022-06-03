
 void rover_rojo(){
  
 ValMax1   = 255; //Valor maximo motor izquierdo
 ValMax2   = 235; //Valor maximo motor derecho
 ValM1   = 220; // Potencia Motor Izq
 ValM2   = 170; // Potencia Motor Der // cambie la potencia,estaba en 175
 
 }
 void rover_negro(){
 
 ValMax1   = 255; //Valor maximo motor izquierdo
 ValMax2   = 255; //Valor maximo motor derecho
 ValM1   = 175; // Potencia Motor Izq
 ValM2   = 240; // Potencia Motor Der  
 
  }  

void rover_DC(){
 ValMax1   = 150; //Valor maximo motor izquierdo
 ValMax2   = 150; //Valor maximo motor derecho
 BackFwdIzq=1;
 BackFwdDer=1;
 ValM1   = 100; // Potencia Motor Izq
 ValM2   = 120; // Potencia Motor Der
 PWM1   = 11; // Pin Motor 1  (Der)    PWM1 = ValM1  , PoM1= HIGH => avanza
 PoM1 = 6;   // Pin Motor 1 (Der)  PWM1 = HIGH  , PoM1= ValM1 => retrocede
 PWM2   = 5; // Pin Motor 2  
 PoM2 = 3;   // Pin Motor 2  (Izq)
 BajoTrig = 13; // TRIG Ultrasonido bajo
 BajoEcho = 12;  // ECHO  ultrasonido bajo
    
  }  
  
  void rover_Sab(){
 ValMax1   = 255; //Valor maximo motor izquierdo
 ValMax2   = 255; //Valor maximo motor derecho
 BackFwdIzq=0;
 BackFwdDer=0;
 ValM1   = 250; // Potencia Motor Izq
 ValM2   = 250; // Potencia Motor Der
 PWM1   = 11; // Pin Motor 1  (Der)    PWM1 = ValM1  , PoM1= HIGH => avanza
 PoM1 = 10;   // Pin Motor 1 (Der)  PWM1 = HIGH  , PoM1= ValM1 => retrocede
 PWM2   = 5; // Pin Motor 2  
 PoM2 = 3;   // Pin Motor 2  (Izq)
 BajoTrig = 6; // TRIG Ultrasonido bajo
 BajoEcho = 7;  // ECHO  ultrasonido bajo
    
  }

void ComandosSerial() {   // Revisar Arduino: serialEvent() !!!!!!!!!!!
 if (Serial.available() > 0) {
       
    inByte = Serial.read();
    if (inByte == 49){ digitalWrite(LED, HIGH); MotorOnOff=HIGH; } // Motores habilitados
    if (inByte == 50){ digitalWrite(LED, LOW);MotorOnOff=LOW; Para(); } // Motores apagados
    if (inByte == 51){// 3 Avanza por BT 
        digitalWrite(LED, HIGH);
        MotorOnOff=HIGH;
        Avanza(300);//Para(); 
        MotorOnOff=LOW; digitalWrite(LED, LOW);} // Avanza por BT
    if (inByte == 52){// Giro Der por BT 
        digitalWrite(LED, HIGH);
        MotorOnOff=HIGH;
        GiroMotor(150);Avanza(19); //Para(); 
        MotorOnOff=LOW; digitalWrite(LED, LOW); }
    if (inByte == 53){// 5 Giro Izq por BT 
        digitalWrite(LED, HIGH);
        MotorOnOff=HIGH;
        GiroMotor(-150);Avanza(10); //Para(); 
        MotorOnOff=LOW; digitalWrite(LED, LOW); }
    if (inByte == 54){// 6 Retrocede 
        digitalWrite(LED, HIGH);
        MotorOnOff=HIGH;
        Para(); delay(100); Retrocede(400); Para(); 
        MotorOnOff=LOW; digitalWrite(LED, LOW); }  
    

////8  Waypoints1
//  if (inByte == 56){  i= 0; iW=0;//  reinicio recorrido
//    while ( i<14){*( Waypoints+i )= *( Waypoints1+i ); i++;}
//    i=0;
//    while ( i<14) {Serial.print(*(Waypoints+i),5); i++;}
//      Serial.println();}    
////9  Waypoints2
//  if (inByte == 57){  i= 0; iW=0;//  reinicio recorrido
//    while ( i<14){*( Waypoints+i )= *( Waypoints2+i ); i++;}
//    i=0;
//    while ( i<14) {Serial.print(*(Waypoints+i),5); i++;}
//      Serial.println();}    

//0  Comandos Secuenciales
  if (inByte == 48){  // Llama a funcion ComSec
      char Inst[10];    byte Oper[10];
int x=0; char cmd=' '; int Mx=1000; int D;
  while(cmd !='Z'){  //            ***Cargo Instrucciones y Operandos, termino con Z
    Serial.println("");  
    Serial.print("Inst: ");
    while (!Serial.available()){}
    Inst[x]=Serial.read();Println(Inst[x]);
    cmd= Inst[x];               // para ver si es el ultimo
    Serial.print("Oper: ");
    while (!Serial.available()){}
    Oper[x]=Serial.read()-48;   // ASCII a numerico
    Println(Oper[x]);  x++;     // Proximo par Inst/Oper
  } //while cmd 
  Println("fin");Println(cmd);
  delay(2000);  x=0; cmd=' ';
  while(cmd !='Z'){ //             ***Muestra lo cargado
    Print(Inst[x]);Print(",");
    Print(Oper[x]);Print(",");
    cmd=Inst[x]; x++;
    }//while
  Println();delay(4000);
  x=0; cmd=' '; MotorOnOff=HIGH;
  while(cmd !='Z'){  //            ***Barro la tabla y ejecuto comandos
    D = Mx * Oper[x];
    if (Inst[x]=='A'){Print("Avanza,");Println(Oper[x]); Avanza(10); delay(D);}
    if (Inst[x]=='D'){Print("GiroDer,");Println(Oper[x]);GiroMotor(D);}
    if (Inst[x]=='I'){Print("GiroIzq,");Println(-1*Oper[x]);GiroMotor(-1*D);}
    if (Inst[x]=='R'){Print("Retro,");Println(Oper[x]);Retrocede(D);}
    cmd=Inst[x]; x++; Para();delay(100);
  }//while
  MotorOnOff=LOW;
  Println();delay(4000);
  
} // ComSec
  if (inByte >48){ Serial.println(inByte) ; }
  Serial.print("MemFree: "); Serial.println(availableMemory());
  }// Serial
} // ******************* ComandosSerial


void GiroMotor(int Dly) {
// activa motores para girar D o I, segun delay recibido  
if (MotorOnOff==HIGH)  {
  Serial.print("Motor:"); Serial.println(MotorOnOff);
 if (Dly <0) { //Giro a Izq
  Dly = Dly * -1;
//  //digitalWrite(PoM1, LOW) ;   
//  //digitalWrite(PWM1, LOW) ;
//  analogWrite(PoM1, HIGH) ;   //izq avanza
//  analogWrite(PWM1, ValM1) ;//-120
//  analogWrite(PoM2, HIGH) ;  // Derecha Avanza
//  analogWrite(PWM2, ValMax2);//

  analogWrite(PoM1, ValM1) ;   //Motor izq retrocede
  analogWrite(PWM1, HIGH) ;
  analogWrite(PoM2, HIGH) ;
  analogWrite(PWM2, ValM2);
  delay(Dly);
}
 else { // Gira a Derecha
//  analogWrite(PoM1, HIGH) ;   //izq avanza
//  analogWrite(PWM1, ValMax1) ;//
//  //analogWrite(PoM2, LOW) ;       //Derecha frena
//  //analogWrite(PWM2, LOW );
//  analogWrite(PoM2, HIGH) ;   
//  analogWrite(PWM2, ValM2-200);  //-120

//  analogWrite(PoM1, BackFwdIzq) ;   //izq avanza
  analogWrite(PoM1, HIGH) ;   //izq avanza
  analogWrite(PWM1, ValM1) ;
  analogWrite(PoM2, ValM2) ;
//  analogWrite(PWM2, BackFwdDer );
  analogWrite(PWM2, HIGH);  
 
  delay(Dly); }
  }// MotorOnOff
} // Giro

// Chequea memoria RAM libre en tiempo de ejecucion
// SRAM para  ATmega328p = 2048Kb.
int availableMemory() {
    // Use 1024 with ATmega168
    int size = 2048;
    byte *buf;
    while ((buf = (byte *) malloc(--size)) == NULL);
        free(buf);
    return size;
}
