#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

int main()
{
    sf::TcpSocket socket;
    sf::SocketSelector selecteur;
    sf::IpAddress adresseServeur = "127.0.0.1";

    unsigned short portServeur = 54000;
    unsigned short portClient;

    string messageSortant;
    string messageEntrant;

    setlocale(LC_ALL, "");

    // Se connecter au serveur
    if (socket.connect(adresseServeur, portServeur)) {
        cout << "Une erreur est survenue lors de la connexion au serveur." << endl;
        return 1;
    }
    portClient = socket.getLocalPort();

    // On associe le socket à un sélecteur.
    // Celui-ci permettra de mettre un temps d'attente maximal sur la réception de données.
    selecteur.add(socket);

    cout << "Écho Réseau" << endl;
    cout << "===========" << endl << endl;

    cout << "Connecté au serveur " << adresseServeur << "." << endl;
    cout << "Le client écoute sur le port " << portClient << "." << endl << endl;

    // Tant que le programme n'est pas arrêté par l'utilisateur
    /*while (true) {
        cout << "Entrer un message: ";
        getline(cin, messageSortant);
        paquetSortant << messageSortant;

        socket.send(paquetSortant, adresseServeur, portServeur);

        // On attend la réception de données sur le socket pour un maximum de 5 secondes.
        // Passé ce délai, la méthode `wait` retournera false.
        if (selecteur.wait(sf::seconds(5))) {
            socket.receive(paquetEntrant, adressePaquetEntrant, portPaquetEntrant);

            paquetEntrant >> messageEntrant;

            cout << "Le serveur (" << adressePaquetEntrant << ":" << portPaquetEntrant
                << ") a retourné : " << messageEntrant << endl;
        }
        else {
            cout << "Le serveur n'a retourné aucune réponse après 5 secondes." << endl;
        }

        paquetSortant.clear(); // On efface le contenu de paquetSortant pour pouvoir le réutiliser
    }*/
}