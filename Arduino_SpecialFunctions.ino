void setup() {
   delay(100);

// Inicialize serial communication
   Serial.begin(9600);
}

void loop() {

  double numberdDbl_sixDecimals = 37.312456; // Works with dtostrf() 
  double numberdDbl_moreDecimals = 37.31245674323423223; // Not work with dtostrf() 
  
  char* buffer = "";  // Char where we will store the converted number
  dtostrf(numberdDbl_sixDecimals,10,7,buffer);

  Serial.println(buffer);
  
  
  //In cases where the number is greater than seven 7 decimals
  String numberStr = doubleToString((numberdDbl_moreDecimals), DEC);
  
  // Optional, convert string to CharArray
  numberStr.toCharArray(buffer, numberStr.length()+1);

  Serial.println(numberStr);
}


void Blink(byte PIN, int DELAY_MS)
{
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}


// Extracted and modified from original arduino print function
String doubleToString(double number, uint8_t digits) 
{ 
  String str_out;
  
  if (isnan(number)) return "nan";
  if (isinf(number)) return "inf";
  if (number > (1.7e308)) "ovf";         // constant, can be any
  if (number <-(1.7e308)) return "ovf";  // constant, can be any
  
  // Handle negative numbers
  if (number < 0.0)
  {
     str_out += "-";
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  str_out += int_part;

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    str_out += ".";
  }

  // Extract digits from the remainder one at a time
  while (digits -- > 0)
  {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)(remainder);
    str_out += toPrint;
    remainder -= toPrint; 
  }    
  
  return str_out;
}
