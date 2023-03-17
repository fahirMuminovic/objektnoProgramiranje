#ifndef PROCES_H
#define PROCES_H

class Proces
{
public:
    Proces();
    int trajanje;
    int trenutakDolaska;
    int redniBroj;
    int preostaloVrijemeIzvrsavanja;
    int burst = 0; // koristi se za crtanje procesa ukoliko se proces "razdvaja" na vise dijelova tj. izvrsi se pretpraznjenje
    int prioritet = 0; // koristi se u Priority algoritmu
};

#endif // PROCES_H
