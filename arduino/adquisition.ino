// 1. Definimos en qué pines conectamos el sensor
const int xPin = A0; 
const int yPin = A1;
const int zPin = A2;

void setup() {
  // 2. Iniciamos la comunicación serial a 9600 baudios
  Serial.begin(9600);
}

void loop() {
  // 3. Variables para acumular las lecturas y promediar
  long xRaw = 0, yRaw = 0, zRaw = 0;
  
  // 4. Bucle de filtrado: Leemos 10 veces rápido
  for(int i = 0; i < 10; i++) {
    xRaw += analogRead(xPin); // Sumamos lectura actual de X
    yRaw += analogRead(yPin); // Sumamos lectura actual de Y
    zRaw += analogRead(zPin); // Sumamos lectura actual de Z
    delay(1);                 // Esperamos 1ms entre lecturas
  }

  // 5. Enviamos el promedio al puerto serial separado por comas
  // Esto reduce el "ruido" o saltos bruscos en la gráfica
  Serial.print(xRaw / 10);
  Serial.print(",");
  Serial.print(yRaw / 10);
  Serial.print(",");
  Serial.println(zRaw / 10); // El println hace el salto de línea final

  delay(20); // 6. Pausa de 20ms para no saturar el canal de datos
}
