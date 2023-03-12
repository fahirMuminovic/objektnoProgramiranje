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
    int burst = 0;
};

#endif // PROCES_H

