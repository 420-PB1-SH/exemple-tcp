#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

int main()
{
    sf::TcpSocket socket;
    sf::IpAddress adresseServeur = "127.0.0.1";

    unsigned short portServeur = 54000;
    unsigned short portClient;

    string messageSortant;
    string messageEntrant;
    sf::Packet paquetSortant;
    sf::Packet paquetEntrant;

    setlocale(LC_ALL, "");

    // Se connecter au serveur
    if (socket.connect(adresseServeur, portServeur)) {
        cout << "Une erreur est survenue lors de la connexion au serveur." << endl;
        return 1;
    }
    portClient = socket.getLocalPort();

    cout << "Écho Réseau" << endl;
    cout << "===========" << endl << endl;

    cout << "Connecté au serveur " << adresseServeur << "." << endl;
    cout << "Le client écoute sur le port " << portClient << "." << endl << endl;

    // Tant que le programme n'est pas arrêté par l'utilisateur
    while (true) {
        cout << "Entrer un message: ";
        getline(cin, messageSortant);
        paquetSortant << messageSortant;

        socket.send(paquetSortant);

        socket.receive(paquetEntrant);

        paquetEntrant >> messageEntrant;

        cout << "Le serveur (" << socket.getRemoteAddress() << ":" << socket.getRemotePort()
             << ") a retourné : " << messageEntrant << endl;

        paquetSortant.clear(); // On efface le contenu de paquetSortant pour pouvoir le réutiliser
    }
}