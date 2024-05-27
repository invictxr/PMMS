#include "ACS712XX.h"

  // ACS712: tipo de sensor, pino do sensor, tensão de referência ADC e saída em escala total ADC.
ACS712XX::ACS712XX(ACS712XXType _type, uint8_t _pin, uint8_t _adc_ref, int _adc_fs) {
  type = _type;
  adc_fs = _adc_fs;
  
  // Define o pino do sensor
  ACS712XX_pin = _pin;

  // Define o offset do sensor
  offset = _adc_fs/2.0;
  
  // Define a sensibilidade do sensor de acordo com o tipo de sensor.
  inv_sensitivity = 1000.0 / float(sensor_sen[_type]);  // V/A -> A/V

  results_adjuster = float(_adc_ref) / float(_adc_fs);  // V/ADC
  results_adjuster *= inv_sensitivity;                  // V/ADC x A/V -> A/ADC
}

float ACS712XX::autoCalibrate() {  // tempo necessário, cerca de 1 ms
  int _adc = 0,_sample = 0;
  while (_sample < 10) {
    _adc += analogRead(ACS712XX_pin);
    _sample ++;
  }
  
  offset = float(_adc) * 0.1; // média de 10 amostras
  return offset;
}

/* Descrição  : Esta função mede a corrente AC.
 * Argumento(s): Frequência, Número de períodos de medição 
 * Padrão  (s) : Frequência -> 50, Número de períodos de medição -> 1.0
 * Intervalo Arg.(s): Frequência -> Cerca de 1 a 200 Hz, Número de períodos de medição -> 0.5 a 20 (para 50Hz)
 * Retorna       : Corrente AC em Ampère
 */
float ACS712XX::getAC(float _freq, float _n_total_period) {  // Pode medir no mínimo 0,5 máximo
  float _signal_period = 1000000.0 / _freq;                    // Hz -> us
  _signal_period *= _n_total_period;
  
//  Aqui, +8us confirma a última iteração. De acordo com a documentação do Arduino,
//  a função micros() tem uma resolução de 4us.
  unsigned long _total_time = (unsigned long)_signal_period + 8;
  unsigned long _start_time = micros();

  unsigned long _adc_sqr_sum = 0;
  unsigned int _adc_count = 0;
  long _adc;

  while (micros() - _start_time < _total_time) { // capaz de até 4096 amostras.
    _adc_count++;
    _adc = analogRead(ACS712XX_pin) - offset;
    _adc_sqr_sum += _adc*_adc;
  }
  
  float _avg_adc_sqr_sum = _adc_sqr_sum / (float)_adc_count;
  float _rms_current = sqrt(_avg_adc_sqr_sum) * results_adjuster;   // ADC x A/ADC -> A
  return _rms_current;
}

float ACS712XX::getDC(int _count) {  // tempo necessário, cerca de 1 ms para 10 amostras padrão.
  int _adc = 0, _sample = 0;
  while (_sample < _count) {
    _adc += analogRead(ACS712XX_pin);
    _sample ++;
  }
  
  float _adc_avg = (float(_adc) / float(_count)) - offset;  // média de 10 amostras e remoção do offset
  float _current = _adc_avg * results_adjuster;   // ADC x A/ADC -> A
  return _current;
}

void ACS712XX::setSensitivity(float _sen) {
  results_adjuster /= inv_sensitivity;                  // A/ADC / A/V -> V/ADC
  inv_sensitivity = 1000.0 / _sen;                      // V/A -> A/V
  results_adjuster *= inv_sensitivity;                  // V/ADC x A/V -> A/ADC
}

void ACS712XX::reset() {
  float _sen = float(sensor_sen[type]);
  setSensitivity(_sen);
  offset = adc_fs/2.0;
}
