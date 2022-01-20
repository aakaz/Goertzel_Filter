#include "Arduino.h"       //Стандартная библиотека ядра
#include "Goertzel.h"      //Файл библиотеки

float _SAMPLING_FREQ;
float _TARGET_FREQ;
int _ADC_center;
int M;
float coeff;
float Q1;
float Q2;

int testData[MAXN];

Goertzel::Goertzel(float TARGET_FREQ, float SAMPLING_FREQ, int N, int ADC_center)
{
  _ADC_center = ADC_center;       //Указывается половина всей шкалы АЦП микроконтроллера: 512 для 10-битного АЦП (ARDUINO UNO), 1024 для 12-битного АЦП (ARDUINO DUE)
  _SAMPLING_FREQ = SAMPLING_FREQ;	//Частота сэмплирования  
  _TARGET_FREQ = TARGET_FREQ;     //Центральная частота фильтра (должно выть из диапазона SAMPLING_RATE/N) 
  if(N > MAXN) {
     M = MAXN;
  } else {
    M = N;
  }
  
  float omega = (2.0 * PI * _TARGET_FREQ) / _SAMPLING_FREQ;
  coeff = 2.0 * cos(omega);
  ResetGoertzel();
}

// Сброс переменных перед каждым блоком сэмплов
void Goertzel::ResetGoertzel(void)
{
  Q2 = 0;
  Q1 = 0;
}


void Goertzel::ProcessSample(int sample)
{
  float Q0;
  Q0 = coeff * Q1 - Q2 + (float) (sample - _ADC_center);
  Q2 = Q1;
  Q1 = Q0;
}


// Процедура чтения семплов АЦП и определения частоты дискретизации
long Goertzel::sample(int sensorPin)
{
 long t = micros();
  for (int index = 0; index < M; index++)
  {
    testData[index] = analogRead(sensorPin);
  }
  t = micros()-t;
  return 1000000*M/t;
}

//Функция вычисления модуля амплитуды искомой гармоники(действительня+мнимая части)
float Goertzel::Full_mag()
{
  float	magnitude;

  for (int index = 0; index < M; index++)
  {
    ProcessSample(testData[index]);
  }

// Выполнение стандартного алгоритма Герцеля ДПФ
  magnitude = sqrt(Q1*Q1 + Q2*Q2 - coeff*Q1*Q2);

  ResetGoertzel();
  return magnitude;
}

//Функция вычисления действительной части амплитуды искомой гармоники
float Goertzel::Re_mag()
{
  float  magnitude;

  for (int index = 0; index < M; index++)
  {
    ProcessSample(testData[index]);
  }

//Выполнение стандартного алгоритма Герцеля ДПФ
  magnitude = sqrt(Q1*Q1 + Q2*(Q2-Q1*coeff));

  ResetGoertzel();
  return magnitude;
}
