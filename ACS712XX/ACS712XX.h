#ifndef ACS712XX_h
#define ACS712XX_h

#include <Arduino.h>

// Sensibilidades dos diferentes tipos de sensor ACS712
#define ACS712_05B_SENSITIVITY    185     // mV/A
#define ACS712_20A_SENSITIVITY    100     // mV/A
#define ACS712_30A_SENSITIVITY    66      // mV/A

// Enumeração para os diferentes tipos de sensor ACS712
enum ACS712XXType{
  ACS712_05B = 0,
  ACS712_20A = 1,
  ACS712_30A = 2,
  ACS712XX_N = 3
};

class ACS712XX{
  public:
    // Construtor da classe ACS712XX
    // ACS712XX(ACS712XXType _type, uint8_t _pin, uint8_t _adc_ref = 5 ,int _adc_fs = 1023);
    ACS712XX(ACS712XXType _type, uint8_t _pin, uint8_t _adc_ref = 3.3, int _adc_fs = 4095); // Alteração para o ESP32
    // Função para calibrar automaticamente o sensor
    float autoCalibrate();
    // Função para medir a corrente AC
    float getAC(float _freq = 50.0,float _n_total_period = 1.0);
    // Função para medir a corrente DC
    float getDC(int _count = 10);
    // Função para obter o offset do sensor
    float getOffset()                 { return offset;                  }
    // Função para obter a sensibilidade do sensor
    float getSensitivity()            { return 1000.0/inv_sensitivity;  }
    // Função para definir o offset do sensor
    void setOffset(float _offset)     { offset = _offset;               }
    // Função para definir a sensibilidade do sensor
    void setSensitivity(float _sen);
    // Função para redefinir o sensor para os valores padrão
    void reset();

  private:
    // Array para armazenar as sensibilidades dos diferentes tipos de sensor ACS712
    uint8_t sensor_sen[ACS712XX_N] = {ACS712_05B_SENSITIVITY,
                                      ACS712_20A_SENSITIVITY,
                                      ACS712_30A_SENSITIVITY};
    float inv_sensitivity;      // Inverso da sensibilidade
    float results_adjuster;     // Ajustador de resultados
    float offset;               // Offset
    int adc_fs;                 // Saída de escala completa do ADC
    uint8_t ACS712XX_pin;       // Pino do sensor ACS712
    ACS712XXType type;          // Tipo de sensor ACS712
};

#endif    /*ACS712XX_h*/
