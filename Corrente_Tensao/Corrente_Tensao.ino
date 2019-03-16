/////Coreente///////
int sensorPin =A0; // leitura da corrente 
int sensorValue_aux = 0;
float sensorValue = 0;
float currentValue = 0;
float voltsporUnidade = 0.004887586;// 5%1023
///////////////////////////////////////////////////////

//Sensor de tensão//
int analogInput = A3; // leitura da tensão 
float Vo = 0.0, Vi = 0.0;
float value_aux = 0, value = 0;

//Valores dos Resistores//
float R1 = 91010.0; //Resistência R1 (100K) No meu caso ajustei para "91010.0" que é um valor aproximado real dos meu resistor visto que pode possuir uma taxa de 5% de variação
float R2 = 9949.0; //Resistência R2 (10K)  No meu caso ajustei para "9949.0" que é um valor aproximado real dos meu resistor visto que pode possuir uma taxa de 5% de variação

void setup(){
Serial.begin(9600);                           //Inicializa serial em 115200 baud rate

/////////corrente//////////////////
 pinMode(sensorPin, INPUT);
 ///////////////////////////////

pinMode(analogInput, INPUT);

Serial.println("Voltimetro DC");

Serial.println("V");

}void loop(){

///////Corrente////////////////////

 for(int i=100; i>0; i--){
    sensorValue_aux = (analogRead(sensorPin) -511); // le o sensor na pino analogico A0 e ajusta o valor lido ja que a saída do sensor é (1023)vcc/2 para corrente =0
    sensorValue += pow(sensorValue_aux,2); // somam os quadrados das leituras.
  }
 
  sensorValue = (sqrt(sensorValue/ 100)) * voltsporUnidade; // finaliza o calculo da méida quadratica e ajusta o valor lido para volts
  currentValue = (sensorValue/0.185); // calcula a corrente considerando a sensibilidade do sernsor (185 mV por amper)
 
  // mostra o resultado no terminal
  Serial.print(currentValue,3);
  Serial.print( ":Amperes");
  Serial.print("\n" ); 
 
  sensorValue =0;
 
  delay(100);

/////////////////////////////////////////////

//Aquisição
for(int i=60;i>0;i--){
value_aux = analogRead(analogInput);
value += pow(value_aux,2);
}

value = sqrt(value/60);
Vo = (value * 5.0) / 1023.0;
Vi = Vo / (R2/(R1+R2));
if (Vi<0.09) {Vi=0.0;} //Filtrando medições errôneas!


Serial.println(" ");

Serial.print(Vi);
Serial.println(":Volts");
delay(500);

}
