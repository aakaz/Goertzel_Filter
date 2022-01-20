#include "Goertzel.h"
const float CF_FREQUENCY = 1000; // Центральная частота в Гц
const int N = 300; 	             // число выборок (влияет на полосу пропускания фильтра)
float SAMPLING_FREQUENCY = 8900; // Частота сэмплирования 

int f_sampling = 0;

//Goertzel G = Goertzel(Центральная частота фильтра в Гц, Частота сэмплирования, Целое число 5 - 300 определяющее полосу пропускания, Половина всей шкалы АЦП микроконтроллера: 512 для 10-битного АЦП (ARDUINO UNO), 1024 для 12-битного АЦП (ARDUINO DUE) );

Goertzel G = Goertzel(CF_FREQUENCY, SAMPLING_FREQUENCY, N, 512);

void setup(){ 
  Serial.begin(9600);
  delay(1000); 
}

void loop()

{
//Выполняет N выборок и рассчитывает точную частоту выборок АЦП (можно потом ввести это значение SAMPLING_FREQUENCY )  
  f_sampling = G.sample(A0);
  
  Serial.print("Частота работы АЦП:"); Serial.println(f_sampling);
 
  float a1 = G.Full_mag(); //Модуль амплитуды искомой гармоники
  float a2 = G.Re_mag(); //Действительная часть амплитуды искомой гармоник
  
  Serial.print("Модуль амплитуды искомой гармоники:");              Serial.println(a1);
  Serial.print("Действительная часть амплитуды искомой гармоники"); Serial.println(a2);
  Serial.println();

  delay(1000);
}
