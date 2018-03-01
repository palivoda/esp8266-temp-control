float addr[151][2] = {        
    {-40,190.5562},       
    {-39,183.4132},
    {-38,175.6740},
    {-37,167.6467},
    {-36,159.5647},
    {-35,151.5975},
    {-34,143.8624},
    {-33,136.4361},
    {-32,129.3641},
    {-31,122.6678},
    {-30,116.3519},
    {-29,110.4098},
    {-28,104.8272},
    {-27,99.5847},
    {-26,94.6608},
    {-25,90.0326},
    {-24,85.6778},
    {-23,81.5747},
    {-22,77.7031},
    {-21,74.0442},
    {-20,70.5811},
    {-19,67.2987},
    {-18,64.1834},
    {-17,61.2233},
    {-16,58.4080},
    {-15,55.7284},
    {-14,53.1766},
    {-13,50.7456},
    {-12,48.4294},
    {-11,46.2224},
    {-10,44.1201},
    {-9,42.1180},
    {-8,40.2121},
    {-7,38.3988},
    {-6,36.6746},
    {-5,35.0362},
    {-4,33.4802},
    {-3,32.0035},
    {-2,30.6028},
    {-1,29.2750},
    {0,28.0170},
    {1,26.8255},
    {2,25.6972},
    {3,24.6290},
    {4,23.6176},
    {5,22.6597},
    {6,21.7522},
    {7,20.8916},
    {8,20.0749},
    {9,19.2988},
    {10,18.5600},
    {11,18.4818},
    {12,18.1489},
    {13,17.6316},
    {14,16.9917},
    {15,16.2797},
    {16,15.5350},
    {17,14.7867},
    {18,14.0551},
    {19,13.3536},
    {20,12.6900},
    {21,12.0684},
    {22,11.4900},
    {23,10.9539},
    {24,10.4582},
    {25,10.0000},
    {26,9.5762},
    {27,9.1835},
    {28,8.8186},
    {29,8.4784},
    {30,8.1600},
    {31,7.8608},
    {32,7.5785},
    {33,7.3109},
    {34,7.0564},
    {35,6.8133},
    {36,6.5806},
    {37,6.3570},
    {38,6.1418},
    {39,5.9343},
    {40,5.7340},
    {41,5.5405},
    {42,5.3534},
    {43,5.1725},
    {44,4.9976},
    {45,4.8286},
    {46,4.6652},
    {47,4.5073},
    {48,4.3548},
    {49,4.2075},
    {50,4.0650},
    {51,3.9271},
    {52,3.7936},
    {53,3.6639},
    {54,3.5377},
    {55,3.4146},
    {56,3.2939},
    {57,3.1752},
    {58,3.0579},
    {59,3.9414},
    {60,2.8250},
    {61,2.7762},
    {62,2.7179},
    {63,2.6523},
    {64,2.5817},
    {65,2.5076},
    {66,2.4319},
    {67,2.3557},
    {68,2.2803},
    {69,2.2065},
    {70,2.1350},
    {71,2.0661},
    {72,2.0004},
    {73,1.9378},
    {74,1.8785},
    {75,1.8225},
    {76,1.7696},
    {77,1.7197},
    {78,1.6727},
    {79,1.6282},
    {80,1.5860},
    {81,1.5458},
    {82,1.5075},
    {83,1.4707},
    {84,1.4352},
    {85,1.4006},
    {86,1.3669},
    {87,1.3337},
    {88,1.3009},
    {89,1.2684},
    {90,1.2360},
    {91,1.2037},
    {92,1.1714},
    {93,1.1390},
    {94,1.1067},
    {95,1.0744},
    {96,1.0422},
    {97,1.0104},
    {98,0.9789},
    {99,0.9481},
    {100,0.9480},
    {101,0.8889},
    {102,0.8610},
    {103,0.8346},
    {104,0.8099},
    {105,0.7870},
    {106,0.7665},
    {107,0.7485},
    {108,0.7334},
    {109,0.7214},
    {110,0.7130}

   
}; 

void setup() {                
   Serial.begin(9600);  
   pinMode(A1,INPUT) ;
}

void loop() {
  Serial.println(analogRead(A1));
  Serial.println(getTemp(analogRead(A1)));
  delay(2000);
}

float getR(float V)
{
  float result;
  result=-10*V/(V-1024);
  return result;
}

float getTemp(float V)
{
  float R;
  R=getR(V);
  int i=0;
  while (addr[i][1] >R)
  {
    i++;
  }
 float result;
   result=(R-addr[i][1])*(addr[i-1][0]-addr[i][0])/(addr[i-1][1]-addr[i][1])+addr[i][0];
  return result;
}

