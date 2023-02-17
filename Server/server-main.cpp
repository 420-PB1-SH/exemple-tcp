#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

int main()
{
    sf::TcpListener listener;
    sf::TcpSocket* nouveauClient;
    vector<sf::TcpSocket*> clients; // Vecteur dynamique contenant les sockets de tous les clients
    sf::SocketSelector selecteur;
    sf::Packet paquetEntrant;
    sf::Packet paquetSortant;

    unsigned short portServeur = 54000;
    unsigned short portClient;

    string message;

    setlocale(LC_ALL, "");

    // Ajouter le listener au sélecteur
    selecteur.add(listener);

    // Attacher le listener au port du serveur
    if (listener.listen(portServeur) != sf::Socket::Done) {
        cout << "Une erreur est survenue lors de la création du listener." << endl;
        return 1;
    }

    cout << "Le serveur écoute sur le port " << portServeur << "." << endl;

    // Tant que le programme n'est pas arrêté par l'utilisateur
    while (true) {
        // Attendre un maximum de 10 ms que des données soient reçues sur un socket (incluant le listener)
        if (selecteur.wait(sf::milliseconds(10))) {
            // Si le listener a reçu une nouvelle demande de connexion
            if (selecteur.isReady(listener)) {
                nouveauClient = new sf::TcpSocket();
                listener.accept(*nouveauClient);
                clients.push_back(nouveauClient); // On ajoute le socket du nouveau client au vecteur de clients
                selecteur.add(*nouveauClient); // Il faut aussi ajouter le socket au sélecteur

                cout << "Un nouveau client s'est connecté: " << nouveauClient->getRemoteAddress();
            }

            // Itérer sur les sockets de tous les clients
            for (int i = 0; i < clients.size(); i++) {
                // Si ce socket d'un client a reçu de nouvelles données
                if (selecteur.isReady(*clients[i])) {
                    clients[i]->receive(paquetEntrant);

                    paquetEntrant >> message;

                    cout << clients[i]->getRemoteAddress() << " a envoyé: " << message << endl;

                    // Renvoyer le même message au client
                    paquetSortant << message;
                    clients[i]->send(paquetSortant);
                }
            }
        }

        paquetSortant.clear(); // On efface le contenu de paquetSortant pour pouvoir le réutiliser
    }
}