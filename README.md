**ZADAĆA 2022 – Dijagram stanja procesa (50 bodova)**

Napraviti Qt aplikaciju tako da prikazuje dijagram stanja procesa kao na slici. Aplikacija treba da omogući stvaranje novog procesa, pomjeranje procesa kroz dijagram stanja procesa pomoću strelica i uništavanje procesa.

**Izgled ekrana (8 bodova)**

Dijagram stanja procesa treba prikazati u **QGraphicsView** widgetu (pomoću **QGraphicsScene**) koji se nalazi unutar dijaloga. Dijalog pored **QGraphicsView**-a treba da sadrži dva **QPushButtona** koji se koriste za stvaranje (*Kreiraj proces*) i uništavanje procesa (*Uništi proces*) . **(1 bod)** 

Namjestiti **QGraphicsView** da bude iste veličine kao i scena (800x600 px) i ukinuti vertikalnu i horizontalnu napravu za klizanje (**ScrollBar**) i obojiti pozadinu **QGraphicsView**-a. **(1 bod)**

Pritiskom na **QPushButton** *Kreiraj proces* napraviti novi proces u obliku **QGraphicsEllipseItem**a koji će se kreirati u stanju **Start** na jednoj od pozicija u redu čekanja. 
**(2 boda)**

Ne dozvoliti kreiranje procesa ako već postoji 5 procesa u redu čekanja u stanju **Start**. **(2 boda)**

Pritiskom na **QPushButton** *Uništi proces* ukloniti proces sa scene ako postoji u redu čekanja stanja **Stop**. **(2 boda)**


**Klasa Stanje (10 bodova)**

Napraviti novu klasu i nazvati je **Stanje** pomoću koje će se kreirati svih 5 stanja procesa sa pripadajućim elementima kao što su red čekanja i naziv stanja. Klasa **Stanje** treba da nasljeđuje **QGraphicsEllipseItem** klasu i svako stanje (instanca klase) treba da bude veličine 100x100(piksela). **(2 boda)**

Napraviti konstruktor klase **Stanje** tako da se može proslijediti naslov (**QString**) stanja i koordinate na sceni. **(2 boda)**

Overloadati **paint** metodu da bi se nacrtalo **Stanje** kao na slici. Unutar **paint** metode iskoristiti **QPen**, **QBrush**, **QFont**, **QPainterPath** i **QPainter** da bi dobili sve potrebne elemente.**(6 bodova)**

**Klasa Tranzicija (10 bodova)**

Napraviti novu klasu i nazvati je **Tranzicija** pomoću koje će se kreirati sve tranzicije u obliku strelice u dijagramu stanja procesa na slici. Klasa **Tranzicija** treba da nasljeđuje **QObject** i **QGraphicsPolygonItem** klasu. **(2 boda)**

Napraviti konstruktor klase **Tranzicija** tako da se može proslijediti dužina, rotacija i koordinate na sceni (pozicija) strelice. **(2 boda)**

Unutar konstruktora klase **Tranzicija** kreirati poligon u obliku strelice pomoću prethodno navedenih paramatera konstruktora klase. Obojiti strelicu pomoću **QBrush** instance klase.
**(4 boda)**

Za klasu **Tranzicija** overloadati metodu **mousePressEvent()** tako da se pritiskom na strelicu poziva (emituje) signal, koji treba definisati unutar klase **Tranzicija**, koji će pomjerati procese (**pomjeri\_proces()**). **(2 boda)**

**Inicijalizacija svih elemenata (12 bodova)**

U klasi **Dialog** kreirati sva **Stanja** i **Tranzicije** i inicijalizirati ih pomoću konstruktora. Za **Stanja** postaviti parametre naslova i koordinata, a za **Tranzicije** postaviti paramtere dužine, rotacije i koordinate. Imenovati **Stanja** i **Tranzicije** tako da su lako prepoznatljivi u kodu.Sva kreirana **Stanja** i **Tranzicije** dodati u scenu.  **(6 bodova)**

U klasi **Dialog** definisati slotove za pomjeranje iz jednog **Stanja** u drugo **Stanje**. Imenovati ih tako da opisuju šta rade, recimo za slot koji pomjera proces iz stanja **Start** u stanje **Ready** imenovati slot **moveProcessStartToReady()** itd.** Povezati slotove sa signalom **pomjeri\_proces()** preko funkcije **connect()**. **(6 bodova)**

**Animacija (10 bodova)**

Klikom na odgovarajuću **Tranziciju** proces pozivanjem prethodno definisanih slotova prelazi iz reda čekanja jednog **Stanja** u red čekanja drugog **Stanja** (npr. Iz **Start** u **Ready**). **Tranzicije** se mogu obaviti jedino ako postoji proces u redu čekanja u **Stanju** iz kojeg se treba preći. Koristiti **QTimer** za animaciju prelaska iz jednog reda čekanja u drugi. 
