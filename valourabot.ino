// vacalourabot.ino

#include <EEPROM.h>

// configuración dos pins do driver dos motores
#define PIN_MOTOR_ESQUERDA_A 10
#define PIN_MOTOR_ESQUERDA_B 11
#define PIN_MOTOR_DEREITA_A 12
#define PIN_MOTOR_DEREITA_B 13

// configuración dos pins dos botóns
#define PIN_BOTON_ESQUERDA 3
#define PIN_BOTON_DEREITA 5
#define PIN_BOTON_ADIANTE 6
#define PIN_BOTON_ATRAS 7
#define PIN_BOTON_IR 8
#define PIN_BOTON_BORRAR 9

// milisegundos que dura o paso
#define PASO_MILLISEGUNDOS 1000

// cada un dous motores
#define MOTOR_DEREITA 0
#define MOTOR_ESQUERDA 1

// grado de xiro (calibrar o tempo que tarda en milisegundos segundo o tipo de motores)
#define ANGULO_90 500 // milisegundos para 90 graos

// capacidade da memoria en movementos (Arduino 1 ten 2 Kb de memoria SRAM total!)
#define MOVEMENTOS_LIMITE 100

// de aquí en diante xa non debería cambiarse nada ;)

// punto de vista para executar os movementos
#define PDV_VACALOURA 0
#define PDV_NENO      1

// punto de vista coa configuración inicial
static byte pov_movementos = PDV_VACALOURA;

// macros para os xiros a esquerda e dereita
#define XIRO byte
#define XIRO_ESQUERDA 1
#define XIRO_DEREITA  2

// macros para a dirección de avance
#define DIRECCION byte
#define DIRECCION_ATRAS   1
#define DIRECCION_ADIANTE 2

// tipo de variable e valores que toman os movementos na memoria
#define MOVEMENTO byte
#define MOVEMENTO_ADIANTE   1
#define MOVEMENTO_DEREITA   2
#define MOVEMENTO_ATRAS     3
#define MOVEMENTO_ESQUERDA  4

// memoria para os movementos
MOVEMENTO memoria_movementos[MOVEMENTOS_LIMITE];

// punteiro para ir acumulando movementos na memoria
int memoria_punteiro;

// memoria para os estados dos botóns
byte estado_boton_esquerda;
byte estado_boton_dereita;
byte estado_boton_adiante;
byte estado_boton_atras;
byte estado_boton_ir;
byte estado_boton_borrar;

void activarMotor(int motor, DIRECCION direccion)
{
  if (motor == MOTOR_DEREITA)
  {
      // motor dereita
      digitalWrite(PIN_MOTOR_DEREITA_A, direccion ? HIGH : LOW);
      digitalWrite(PIN_MOTOR_DEREITA_B, direccion ? LOW : HIGH);
  }
  else
  {
      // motor esquerda
      digitalWrite(PIN_MOTOR_ESQUERDA_A, direccion ? HIGH : LOW);
      digitalWrite(PIN_MOTOR_ESQUERDA_B, direccion ? LOW : HIGH);
  }
}

void desactivarMotor(int motor)
{
  if (motor == MOTOR_DEREITA)
  {
      // motor dereita
      digitalWrite(PIN_MOTOR_DEREITA_A, LOW);
      digitalWrite(PIN_MOTOR_DEREITA_B, LOW);
  }
  else
  {
      // motor esquerda
      digitalWrite(PIN_MOTOR_ESQUERDA_A, LOW);
      digitalWrite(PIN_MOTOR_ESQUERDA_B, LOW);
  }
}

void avanzar(int unidades, DIRECCION direccion)
{
    // activamos os dous motores
    activarMotor(MOTOR_DEREITA, direccion);
    activarMotor(MOTOR_ESQUERDA, direccion);

    delay(unidades * PASO_MILLISEGUNDOS);

    // desactivamos os dous motores
    desactivarMotor(MOTOR_DEREITA);
    desactivarMotor(MOTOR_ESQUERDA);
}

void xirar(XIRO xiro, int milisegundos)
{
   if (xiro == XIRO_DEREITA)
   {
      // xiro en sentido reloxo
      activarMotor(MOTOR_ESQUERDA, DIRECCION_ADIANTE);
      activarMotor(MOTOR_DEREITA, DIRECCION_ATRAS);
   }
   else
   {
     // xiro en sentido anti-reloxo
      activarMotor(MOTOR_DEREITA, DIRECCION_ADIANTE);
      activarMotor(MOTOR_ESQUERDA, DIRECCION_ATRAS);
   }

   delay(milisegundos);

   desactivarMotor(MOTOR_ESQUERDA);
   desactivarMotor(MOTOR_DEREITA);
}

void xirar90(int veces)
{
  // non facer nada cando veces sexa 0
  if (veces != 0)
  {
    // cálculo do xiro e cantidade
    XIRO xiro;
    int cantidade;

    // tipo de xiro e cantidade en positivo
    if (veces > 0)
    {
      xiro = XIRO_DEREITA;
      cantidade = veces;
    }
    else
    {
      xiro = XIRO_ESQUERDA;
      cantidade = -veces;
    }

    // executar os xiros
    while (cantidade-- > 0)
    {
      xirar(xiro, ANGULO_90);
    }
  }
}

void eepromGravar()
{
  // gardamos na EEPROM cando haxa movementos que gardar
  if (memoria_punteiro > 0)
  {
    // o primeiro dato é o número de movementos
    EEPROM.write(0, memoria_punteiro);

    // e de seguido os movementos almacenados
    for (int m = 0; m < memoria_punteiro; m++)
    {
      EEPROM.write(m + 1, memoria_movementos[m]);
    }
  }
}

void eepromCargar()
{
  // o primeiro dato é o número de movementos
  memoria_punteiro = EEPROM.read(0);

  if (memoria_punteiro > MOVEMENTOS_LIMITE)
  {
    // a memoria EEPROM está corrupta
    memoria_punteiro = 0;
    return;
  }

  // e de seguido os movementos
  for (int m = 0; m < memoria_punteiro; m++)
  {
    memoria_movementos[m] = EEPROM.read(m + 1);
  }
}

void irPdvNeno()
{
  // supoñer que se está detrás da vacalourabot
  byte direccion_actual = DIRECCION_ADIANTE;

  // por cada un dos movementos
  for (int m = 0; m < memoria_punteiro; m++)
  {
    // calcular o xiro dende o punto de vista actual
    int xiro = memoria_movementos[m] - direccion_actual;

    // axustar xiro para o lado máis curto
    if (abs(xiro) == 3) xiro /= -xiro;

    // executar o xiro
    xirar90(xiro);

    // avanzar un paso cara diante
    avanzar(1, DIRECCION_ADIANTE);

    // actualizar dirección actual
    direccion_actual = memoria_movementos[m];
  }
}

void irPdvVacaloura()
{
  // por cada un dos movementos
  for (int m = 0; m < memoria_punteiro; m++)
  {
    // evalúa o tipo e procede
    switch (memoria_movementos[m])
    {
      case MOVEMENTO_DEREITA:
        xirar90(1);
        break;
      case MOVEMENTO_ESQUERDA:
        xirar90(-1);
        break;
      case MOVEMENTO_ADIANTE:
        avanzar(1, DIRECCION_ADIANTE);
        break;
      case MOVEMENTO_ATRAS:
        avanzar(1, DIRECCION_ATRAS);
        break;
    }
  }
}

void ir()
{
  // só imos se hai movementos programados
  if (memoria_punteiro > 0)
  {
    // gardamos o programa de movementos na EEPROM
    eepromGravar();

    // pequena pausa para dar tempo a soltar o botón
    delay(1000);

    // evaluar o punto de vista para execución de movementos
    if (pov_movementos == PDV_VACALOURA)
    {
      // punto de vista da vacaloura
      irPdvVacaloura();
    }
    else
    {
      // punto de vista do neno
      irPdvNeno();
    }
  }
}

void memoria_borrar()
{
  memoria_punteiro = 0;
}


void memorizar(int movemento)
{
  if (memoria_punteiro < MOVEMENTOS_LIMITE)
  {
    memoria_movementos[memoria_punteiro] = movemento;
    memoria_punteiro++;
  }
  else
  {
    ir();
  }
}

void setup()
{
    // configurar motores
    pinMode(PIN_MOTOR_ESQUERDA_A, OUTPUT);
    pinMode(PIN_MOTOR_ESQUERDA_B, OUTPUT);
    pinMode(PIN_MOTOR_DEREITA_A, OUTPUT);
    pinMode(PIN_MOTOR_DEREITA_B, OUTPUT);

    // configurar botóns
    pinMode(PIN_BOTON_ESQUERDA, INPUT);
    pinMode(PIN_BOTON_DEREITA, INPUT);
    pinMode(PIN_BOTON_ADIANTE, INPUT);
    pinMode(PIN_BOTON_ATRAS, INPUT);
    pinMode(PIN_BOTON_IR, INPUT);
    pinMode(PIN_BOTON_BORRAR, INPUT);

    // inicializar os estados dos botóns
    estado_boton_esquerda = LOW;
    estado_boton_dereita = LOW;
    estado_boton_adiante = LOW;
    estado_boton_atras = LOW;
    estado_boton_ir = LOW;
    estado_boton_borrar = LOW;

    // inicializar memoria
    memoria_borrar();

    // cargar os movementos logo dun apagado
    eepromCargar();
}



void loop(){

  // leer os botóns
  if (digitalRead(PIN_BOTON_ESQUERDA) ^ estado_boton_esquerda)
  {
    estado_boton_esquerda = !estado_boton_esquerda;
    if (estado_boton_esquerda == HIGH)
    {
      memorizar(MOVEMENTO_ESQUERDA);
    }
  }

  if (digitalRead(PIN_BOTON_DEREITA) ^ estado_boton_dereita)
  {
    estado_boton_dereita = !estado_boton_dereita;
    if (estado_boton_dereita == HIGH)
    {
      memorizar(MOVEMENTO_DEREITA);
    }
  }

  if (digitalRead(PIN_BOTON_ADIANTE) ^ estado_boton_adiante)
  {
    estado_boton_adiante = !estado_boton_adiante;
    if (estado_boton_adiante == HIGH)
    {
      memorizar(MOVEMENTO_ADIANTE);
    }
  }

  if (digitalRead(PIN_BOTON_ATRAS) ^ estado_boton_atras)
  {
    estado_boton_atras = !estado_boton_atras;
    if (estado_boton_atras == HIGH)
    {
      memorizar(MOVEMENTO_ATRAS);
    }
  }

  if (digitalRead(PIN_BOTON_BORRAR) ^ estado_boton_borrar)
  {
    estado_boton_borrar = !estado_boton_borrar;
    if (estado_boton_borrar == HIGH)
    {
      memoria_borrar();
    }
  }

  if (digitalRead(PIN_BOTON_IR) ^ estado_boton_ir)
  {
    estado_boton_ir = !estado_boton_ir;
    if (estado_boton_ir == HIGH)
    {
      // tempiño para que solten o botón antes de arrancar
      delay(500);

      // executa os movementos
      ir();
    }
  }

}
