
#include <Keypad.h>
#include <Wire.h>  // biblioteca respposnsavel pela comunicação I2C
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x3F,20,4);  // // 0x3F representa o endereço hexadecimal do modulo I2C alguns modulos

//........................................................................................................  
char phone_no[]="111111111";
char vetor[10]; // alterado
int limite = 10;
int contador =0;
int aux =0;
//........................................................................................................
const byte ROWS = 4; //4 linhas
const byte COLS = 4; //3 colunas
//define os caracteres de cada botao
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6',},
  {'7','8','9',},
  {'*','0','#','-'}
};
byte rowPins[ROWS] = {7,6,5,4}; //conexão dos pinos das linhas
byte colPins[COLS] = {11,10,9,8}; //conexão dos pinos das colunas

//iniciliza e instancia o objeto customKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

char customKey; // alterado
char numero; // alterado

//........................................................................................................
void setup()
{
  lcd.init(); 
  Serial.begin(115200);
}
  
void loop()
{
  lcd.backlight();
  lcd.setCursor(4,1);   // assim como as biblioteas comuns para display LCD os comandos para este modulo são bem parecidos
  lcd.print("FAZER LIGACAO");

  lcd.setCursor(6,0);   // assim como as biblioteas comuns para display LCD os comandos para este modulo são bem parecidos
  lcd.print("Cell Duino");

  ligacao();
}

//........................................................................................................
void ligacao()
{
    customKey = customKeypad.getKey(); // comando getKey responsável por recuperar o valor do botao precionado // alterado
    if (customKey) // Verifica se alguma tecla foi precionada
    {
      numero = customKey;
      vetor[contador]=numero;
      lcd.setCursor(contador,3); 
      lcd.print(vetor[contador]);

      contador++;

       if(numero == '*') 
         {
           lcd.clear();
           Serial.println("ATH");
           lcd.setCursor(0,2); 
           lcd.print("CHAMADA ENCERRADA");
           contador =0; 
           delay(1500);
           lcd.clear();      
         }
       }
//........................................................................................................

    if((contador == limite) && (vetor[9]== '#')) // CONDIÇÃO PARA INICIAR A CHAMADA
  { 
    lcd.clear();
    contador =0;
    
    for(int i=0;i<9;i++)
    {
      phone_no[i]= vetor[i];
    }
    
    lcd.setCursor(2,2); 
    lcd.print("CHAMADA INICIADA");
    
    Serial.println("AT");
    delay(1000);
    Serial.print("ATD");
    Serial.println(phone_no);
    Serial.println(";");
    }
}

void sms() // TESTE DE ENVIO DE SMS
{
  Serial.println("AT+CMGF=1");    
  delay(2000);
  Serial.print("AT+CMGS=\"");
  Serial.print(phone_no); 
  Serial.write(0x22);
  Serial.write(0x0D);  // hex equivalent of Carraige return    
  Serial.write(0x0A);  // hex equivalent of newline
  delay(2000);
  Serial.print("Mensagem de teste");
  delay(500);
  Serial.println (char(26));//the ASCII code of the ctrl+z is 26
}
