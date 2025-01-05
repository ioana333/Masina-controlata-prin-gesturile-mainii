  Mașină Controlată prin Mișcările Mâinii
Acest proiect detaliază crearea unui prototip de vehicul controlat prin gesturi, utilizând un senzor MPU6050 și module NRF24L01 pentru comunicare wireless.

Scopul Proiectului
Proiectul își propune să implementeze un sistem de control intuitiv bazat pe mișcările naturale ale mâinii.

Funcționalități Principale
Detectarea mișcărilor: Utilizarea senzorului MPU6050 pentru a converti mișcările mâinii în comenzi de direcție (înainte, înapoi, stânga, dreapta).
Transmiterea comenzilor: Comunicarea fără fir între controller și vehicul utilizând module NRF24L01.
Reacția vehiculului: Control precis al motoarelor DC prin driver-ul L298N pentru direcție și mișcare.
Instrumente Utilizate
Hardware
2 plăci Arduino Nano
1 senzor MPU6050
2 module NRF24L01
4 motoare DC
1 driver L298N
Șasiu pentru vehicul
Surse de alimentare (baterii)
Software
Arduino IDE: Programare și încărcare cod pe plăcile Arduino.
Biblioteci utilizate:
Wire.h
MPU6050.h
RF24.h
Probleme Nerezolvate
Lipsa senzorilor de proximitate pentru detectarea obstacolelor.
Control limitat al preciziei în viraje.
Interfață dificil de utilizat pentru utilizatorii cu dizabilități motorii complexe.
Integrarea inteligenței artificiale pentru navigare autonomă și adaptarea controlului la utilizator.
Utilizare
Introduceți 6 baterii AA în suportul vehiculului și apăsați comutatorul pe poziția ON.
Puneți telecomanda pe mână și activați comutatorul dedicat.
Controlați vehiculul prin mișcările mâinii pentru a testa funcționalitatea.
Rezultate Obținute
Răspuns rapid (100-200 ms) între gesturi și mișcarea vehiculului.
Stabilitate a comunicării în spațiu deschis până la 15 metri.
Autonomie: ~45 minute pentru vehicul și ~2 ore pentru telecomandă.
Contribuții
Contribuțiile sunt binevenite! Vă rugăm să deschideți un issue sau să creați un pull request pentru sugestii de îmbunătățire.
