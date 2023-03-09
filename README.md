**FINALNI PROJEKAT 2022 – Dinamičko crtanje Gantovih dijagrama za različite algoritme i različit broj procesa (50 bodova)**

Napraviti Qt aplikaciju koja će za odabrani algoritam i broj procesa nacrtati Gantov dijagram na prikazati ga pomoću **QGraphicsView**-a (pomoću **QGraphicsScene)**.

**Izgled ekrana (10 bodova)**

Potrebno je da Dialog bude dimenzija 800x600px i da sadrži sljedeće elemente:

- **QComboBox** u kojem će se odabirati algoritam pomoću kojeg treba nacrati dijagram i koji treba da ima sljedeće vrijednosti: FCFS, SJF, RR, Prioritet
- **QComboBox** u kojem će se odabirati broj procesa (min:4, max:9)
- **QRadioButton** koji će označavati da li je algoritam sa pretpražnjenjem
- Za svaki od odabranih procesa:
  - **QSpinBox** za trenutak dolaska procesa u sistem (min:0, max:20),
  - **QSpinBox** za trajanje procesa (min:1, max:30)
  - **QSpinBox** za prioritet (min:0, max:9)
- **QPushButton** za crtanje dijagrama
- **QGraphicsView** na kojem će biti nacrtane x-osa koja predstavlja broj ciklusa i y-osa koja predstavlja procese kao na slici ispod kao i **QGraphicsTextItem**-e koji predstavljaju ose.

U zavisnosti od odabranog broja procesa prikazati samo elemente za ispunjavanje tog broja procesa (npr. Ako je odabrano 5 procesa prikazati samo elemente za ispunjavanje procesa od P1-P5).

**Gantov dijagram (40 bodova)**

Na QGraphicsView-u dodati sljedeće elemente nakon pritiskanja QPushButtona „Nacrtaj Gantov dijagram“: 

- Dodati **QGraphicsTextItem**-e koji predstavljaju procese
- Za svaki proces dodati njegov **QGraphicsRectItem** koji predstavlja dužinu (broj ciklusa) trajanja procesa tako da zadovoljavaju odabrani algoritam vodeći se informacijama koje su dodane u već spomenute **QSpinBox**-ove
- Za svaki prelaz između procesa dodati **QGraphicsLineItem** kao isprekidanu liniju

Bez obzira na odabrani broj procesa nacratati procese tako da ispunjavaju visinu koordinatnog sistema (Hint:visina kvadrata koji se crta za određeni proces biti će različita za različit broj procesa). Bez obzira na dužinu procesa nacrtati dijagram tako da ispuni čitavu širinu koordinatnog sistema (Hint: širina kvadrata koji se crta za određeni proces će zavisiti od broja procesa i njihovog trajanja, odnosno od ukupnog trajanja svih odabranih procesa) .

Napomena:

Za prvi rok dovoljno je uraditi zadatak za jedan algoritam. 

