#include <iostream>
#include <vector>
#include <SFML/Network.hpp>

using namespace std;

int main()
{
    sf::TcpListener listener;
    sf::TcpSocket* nouveauClient;
    vector<sf::TcpSocket*> clients; // Vecteur dynamique contenant les sockets de tous les clients
    sf::SocketSelector selecteur;

    sf::Socket::Status etatClient;
    sf::Packet paquetEntrant;
    sf::Packet paquetSortant;

    unsigned short portServeur = 54000;

    string message;

    setlocale(LC_ALL, "");

    // Attacher le listener au port du serveur
    if (listener.listen(portServeur) != sf::Socket::Done) {
        cout << "Une erreur est survenue lors de la cr�ation du listener." << endl;
        return 1;
    }

    // Ajouter le listener au s�lecteur
    selecteur.add(listener);

    cout << "Le serveur �coute sur le port " << portServeur << "." << endl;

    // Tant que le programme n'est pas arr�t� par l'utilisateur
    while (true) {
        // Attendre que des donn�es soient re�ues sur un socket (incluant le listener)
        selecteur.wait();

        // Si le listener a re�u une nouvelle demande de connexion
        if (selecteur.isReady(listener)) {
            nouveauClient = new sf::TcpSocket();
            listener.accept(*nouveauClient);
            clients.push_back(nouveauClient); // On ajoute le socket du nouveau client au vecteur de clients
            selecteur.add(*nouveauClient); // Il faut aussi ajouter le socket au s�lecteur

            cout << "Un nouveau client s'est connect�: "
                    << nouveauClient->getRemoteAddress() << ":" << nouveauClient->getRemotePort() << endl;
        }

        // It�rer sur les sockets de tous les clients
        for (int i = 0; i < clients.size(); i++) {
            // Si ce socket d'un client a re�u de nouvelles donn�es
            if (selecteur.isReady(*clients[i])) {
                etatClient = clients[i]->receive(paquetEntrant);

                // D�tecter la d�connexion du client.
                // � la d�connexion, on re�oit un Packet vide, donc on ne le traitera pas.
                if (etatClient == sf::Socket::Disconnected) {
                    cout << "Le client " << clients[i]->getRemoteAddress()
                        << ":" << clients[i]->getRemotePort()
                        << " s'est d�connect�." << endl;

                    selecteur.remove(*clients[i]); // Retirer le socket client du s�lecteur
                        
                    delete clients[i];
                    clients[i] = nullptr;
                        
                    clients.erase(clients.begin() + i); // Retirer le socket client du vecteur
                }
                else {
                    paquetEntrant >> message;

                    cout << clients[i]->getRemoteAddress() << ":" << clients[i]->getRemotePort()
                            << " a envoy�: " << message << endl;

                    // Renvoyer le m�me message au client
                    paquetSortant << message;
                    clients[i]->send(paquetSortant);

                    paquetSortant.clear(); // On efface le contenu de paquetSortant pour pouvoir le r�utiliser
                }
            }
        }
    }

    for (int i = 0; i < clients.size(); i++) {
        delete clients[i];
        clients[i] = nullptr;
    }
}
