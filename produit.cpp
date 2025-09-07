#include <iostream>
#include <list>
#include <string>
#include <algorithm> 
#include <optional>
#include <unordered_map> 
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
class Article {
private:
    string name;
    string reference;
    double prix;
    int quantiteStock;
public:
    Article(const string& nom, const string& ref, double price, int quantity)
        : name(nom), reference(ref), prix(price), quantiteStock(quantity) {}

    const string& getReference() const {
        return reference;
    }
    int getQuantiteStock() const {
        return quantiteStock;
    }
    void setReference(const string& ref) {
        reference = ref;
    }

    const string& getName() const {
        return name;
    }

    void setName(const string& nom) {
        name = nom;
    }

    double getPrix() const {
        return prix;
    }

    void setPrix(double price) {
        prix = price;
    }
    void setQuantiteStock(int quantity) {
        quantiteStock = quantity;
    }
    
};

void saveArticles(const list<Article>& listeArticles) {

    ofstream file("Dossier/article.txt");
    if (!file.is_open()) {
        cout << "Erreur: Impossible d'ouvrir le fichier pour sauvegarde." << endl;
        return;
    }

    for (const auto& article : listeArticles) {
        file << "Référence : " << article.getReference() << endl;
        file << "Nom : " << article.getName() << endl;
        file << "Prix : " << article.getPrix() << " dhs" << endl;
        file << "Quantité en stock : " << article.getQuantiteStock() << endl;
        file << "-------------------------" << endl;
    }

    cout << "Articles sauvegardés avec succès dans article.txt." << endl;

}



void afficherArticle(const Article& article) {
    cout << "\033[1;33mRéférence : \033[0m" << article.getReference() << endl;
    cout << "\033[1;34mNom : \033[0m" << article.getName() << endl;
    cout << "\033[1;35mPrix : \033[0m" << article.getPrix() << " dhs" << endl;
    cout << "\033[1;32mQuantité en stock : \033[0m" << article.getQuantiteStock() << endl;
    cout << "-------------------------" << endl;
}



void ajouterArticle(list<Article>& listeArticles, const Article& nouvelArticle) {
    auto it = find_if(listeArticles.begin(), listeArticles.end(), [&nouvelArticle](const Article& article) {
        return article.getReference() == nouvelArticle.getReference();
    });

    if (it != listeArticles.end()) {
        cout << "Un article avec la même référence existe déjà." << endl;
    } else {
        listeArticles.push_back(nouvelArticle);
        cout << "Article ajouté avec succès." << endl;
    }
    saveArticles(listeArticles);
}

optional<Article> rechercherArticleParRef(const list<Article>& listeArticles, const string& ref) {
    auto it = find_if(listeArticles.begin(), listeArticles.end(), [&ref](const Article& article) {
        return article.getReference() == ref;
    });

    if (it != listeArticles.end()) {
        return *it;
    } else {
        return nullopt;
    }
}

void updateArticleParRef(list<Article>& listeArticles, const string& ref, const string& nom, double newPrice, int newQuantity) {

    auto it = find_if(listeArticles.begin(), listeArticles.end(), [&ref](const Article& article) {
        return article.getReference() == ref;
    });

    if (it != listeArticles.end()) {
        it->setName(nom);
        it->setPrix(newPrice);
        it->setQuantiteStock(newQuantity);
        cout << "Article mis à jour avec succès." << endl;
    } else {
        cout << "Article non trouvé." << endl;
    }
    saveArticles(listeArticles);
}

void supprimerArticleParRef(list<Article>& listeArticles, const string& ref) {
    auto it = find_if(listeArticles.begin(), listeArticles.end(), [&ref](const Article& article) {
        return article.getReference() == ref;
    });
    if (it != listeArticles.end()) {
        listeArticles.erase(it);
        cout << "Article supprimé avec succès." << endl;
    } else {
        cout << "Article non trouvé." << endl;
    }
    saveArticles(listeArticles);
}

void afficherTousLesArticles(const list<Article>& listeArticles) {
    if (listeArticles.empty()) {
        cout << "La liste d'articles est vide." << endl;
    } else {
        for (const Article& article : listeArticles) {
            afficherArticle(article);
        }
    }
}

class Commande {
    
private:
    static int count;
    int id;
    int userId;
    vector<pair<Article, int>> articles;
    double montantTotal;
    string statut;

public:
    Commande(int utilisateurId, const vector<pair<Article, int>>& articleList, double total)
        : id(++count), userId(utilisateurId), articles(articleList), montantTotal(total), statut("En cours") {}

    int getId() const {
        return id;
    }

    int getUserId() const {
        return userId;
    }

    const vector<pair<Article, int>>& getArticles() const {
        return articles;
    }

    double getMontantTotal() const {
        return montantTotal;
    }

    const string& getStatut() const {
        return statut;
    }

    void setStatut(const string& newStatut) {
        statut = newStatut;
    }

    void afficherCommande() const {
        cout << "Commande ID: " << id << ", Statut: " << statut << ", Montant Total: " << montantTotal << " dhs" << endl;
        for (const auto& [article, quantite] : articles) {
            cout << "Référence : " << article.getReference() << ", Article : " << article.getName() << ", Quantité : " << quantite << endl;
        }
        cout << "-------------------------" << endl;
    }
};
vector<Commande> commandes;
void ajouterCommande(const Commande& commande) {
    commandes.push_back(commande);
}

void afficherCommandesParUtilisateur(int userId) {
    for (const auto& commande : commandes) {
        if (commande.getUserId() == userId) {
            commande.afficherCommande();
        }
    }
}

void afficherToutesLesCommandes() {
    for (const auto& commande : commandes) {
        commande.afficherCommande();
    }
}

void modifierStatutCommande(int commandeId, const string& nouveauStatut) {
    auto it = find_if(commandes.begin(), commandes.end(), [commandeId](const Commande& commande) {
        return commande.getId() == commandeId;
    });

    if (it != commandes.end()) {
        it->setStatut(nouveauStatut);
        cout << "Statut de la commande mis à jour avec succès." << endl;
    } else {
        cout << "Commande non trouvée." << endl;
    }
}

class Panier {
private:
    int userId;
    vector<pair<Article, int>> articles;
    double montantTotal;

    double calculerPrixArticle(const Article& article, int quantite) const {
        double prixUnitaire = article.getPrix();
        if ( quantite > 10 ) {
            prixUnitaire *= 0.8; 
        }
        return prixUnitaire * quantite;
    }

    void recalculerMontantTotal() {
        montantTotal = 0.0;
        for (const auto& p : articles) {
            montantTotal += calculerPrixArticle(p.first, p.second);
        }
    }

public:
    Panier(int utilisateurId)
        : userId(utilisateurId), montantTotal(0.0) {}
    
    void ajouterArticle(const Article& article, int quantite = 1) {
        auto it = find_if(articles.begin(), articles.end(), [&article](const pair<Article, int>& p) {
            return p.first.getReference() == article.getReference();
        });

        if (it != articles.end()) {
            montantTotal -= calculerPrixArticle(it->first, it->second);
            it->second += quantite;
        } else {
            articles.push_back(make_pair(article, quantite));
        }
        montantTotal += calculerPrixArticle(article, quantite);
    }
    Commande validerCommande() {
        Commande commande(userId, articles, montantTotal);
        viderPanier(); 
        return commande;
    }
    void modifierQuantiteArticle(const Article& article, int nouvelleQuantite) {
        auto it = find_if(articles.begin(), articles.end(), [&article](const pair<Article, int>& p) {
            return p.first.getReference() == article.getReference();
        });

        if (it != articles.end()) {
            montantTotal -= calculerPrixArticle(it->first, it->second);
            it->second = nouvelleQuantite;
            montantTotal += calculerPrixArticle(it->first, nouvelleQuantite);
        } else {
            cout << "Article non trouvé dans le panier." << endl;
        }
    }

    void viderPanier() {
        articles.clear();
        montantTotal = 0.0;
    }

    void supprimerArticle(const Article& article) {
        auto it = find_if(articles.begin(), articles.end(), [&](const pair<Article, int>& p) {
            return p.first.getReference() == article.getReference();
        });

        if (it != articles.end()) {
            montantTotal -= calculerPrixArticle(it->first, it->second);
            articles.erase(it);
            cout << "Article supprimé avec succès du panier." << endl;
        } else {
            cout << "Article non trouvé dans le panier." << endl;
        }
    }

    int getUserId() const {
        return userId;
    }

    const vector<pair<Article, int>>& getArticles() const {
        return articles;
    }

    double getMontantTotal() const {
        return montantTotal;
    }

    vector<pair<Article, int>> getArticlesTriesParPrix() const {
        vector<pair<Article, int>> articlesTries = articles;
        sort(articlesTries.begin(), articlesTries.end(), [](const pair<Article, int>& a, const pair<Article, int>& b) {
            return a.first.getPrix() < b.first.getPrix();
        });
        return articlesTries;
    }

    pair<Article, int> getArticleLePlusCher() const {
        if (articles.empty()) {
            throw runtime_error("Le panier est vide.");
        }

        return *max_element(articles.begin(), articles.end(), [](const pair<Article, int>& a, const pair<Article, int>& b) {
            return a.first.getPrix() < b.first.getPrix();
        });
    }

    vector<pair<Article, int>> getArticlesDansTrancheDePrix(double prixMin, double prixMax) const {
        vector<pair<Article, int>> result;
        for (const auto& p : articles) {
            double prixUnitaire = p.first.getPrix();
            if (prixUnitaire >= prixMin && prixUnitaire <= prixMax) {
                result.push_back(p);
            }
        }
        return result;
    }
};
class User {
private:
    static int count;
    int id;
    string nom;
    string email;
    string password;
    string role ;

public:
    User(const string& userNom, const string& userEmail, const string& userPassword,const string&  userRole = "client")
        : id(++count), nom(userNom), email(userEmail), password(userPassword) ,role(userRole) {}

    int getId() const {
        return id;
    }

    const string& getNom() const {
        return nom;
    }

    const string& getRole() const {
        return role;
    }
    void setNom(const string& userNom) {
        nom = userNom;
    }

    const string& getEmail() const {
        return email;
    }

    void setEmail(const string& userEmail) {
        email = userEmail;
    }

    const string& getPassword() const {
        return password;
    }

    void setPassword(const string& userPassword) {
        password = userPassword;
    }

    bool seConnecter(const string& inputEmail, const string& inputPassword) const {
        return (email == inputEmail && password == inputPassword);
    }
    
};

int User::count = 0;

void afficherMenu() {
    cout << "Menu :" << endl;
    cout << "0. Liste des Produits" << endl;
    cout << "1. Ajouter un article au panier" << endl;
    cout << "2. Modifier la quantité d'un article dans le panier" << endl;
    cout << "3. Vider le panier" << endl;
    cout << "4. Afficher le panier" << endl;
    cout << "5. Trier les articles du panier par prix" << endl;
    cout << "6. Calculer le montant total avec remise" << endl;
    cout << "7. Afficher l'article le plus cher du panier" << endl;
    cout << "8. Afficher les articles du panier dans une tranche de prix" << endl;
    cout << "9. Valider la commande" << endl;
    cout << "10. Afficher mes commandes" << endl;
    cout << "11. Quitter" << endl;

}
void chargerArticles(list<Article>& listeArticles, const string& nomFichier) {
    ifstream fichier(nomFichier);
    if (!fichier.is_open()) {
        cout << "Erreur: Impossible d'ouvrir le fichier " << nomFichier << endl;
        return;
    }

    string ligne;
    while (getline(fichier, ligne)) {
        string reference, nom;
        double prix;
        int quantiteStock;

        // Lecture des données de chaque ligne
if (ligne.find("Référence : ") == 0) {
        reference = ligne.substr(14); // Ignorer "Référence : " et lire le reste
        getline(fichier, ligne); // Lire la ligne suivante (Nom)
        nom = ligne.substr(6); // Ignorer "Nom : " et lire le reste
        getline(fichier, ligne); // Lire la ligne suivante (Prix)
        prix = stod(ligne.substr(7)); // Ignorer "Prix : " et lire le reste
        getline(fichier, ligne); // Lire la ligne suivante (Quantité en stock)
        size_t pos = ligne.find("Quantité en stock : ");
        if (pos == 0) {
            string quantityStr = ligne.substr(pos + 21); 
            if (!quantityStr.empty() && all_of(quantityStr.begin(), quantityStr.end(), ::isdigit)) {
                quantiteStock = stoi(quantityStr);
                listeArticles.push_back(Article(nom, reference, prix, quantiteStock));
            } else {
                cout << "Erreur: La quantité en stock n'est pas valide." << endl;
            }
    } else {
        cout << "Erreur de format de ligne : " << ligne << endl;
    }
    getline(fichier, ligne); // Ignorer la ligne de séparation
} else {
    cout << "Erreur de format de ligne : " << ligne << endl;
}
    }

    fichier.close();
}

int Commande::count = 0;
int main(){
    string nomFichier = "Dossier/article.txt";
    list<Article> listeArticles;
    vector<User> users;
    chargerArticles(listeArticles, nomFichier);
    afficherTousLesArticles(listeArticles);

    int utilisateurId;

    User user1("alice","a", "a");
    users.push_back(user1);

    User user2("bob","b", "b","admin");
    users.push_back(user2);
    string inputEmail;
    string inputPassword;

    cout << "Email : ";
    cin >> inputEmail;

    cout << "Mot de passe : ";
    cin >> inputPassword;

    auto it = find_if(users.begin(), users.end(), [&](const User& user) {
        return user.seConnecter(inputEmail, inputPassword);
    });

    if (it != users.end()) {
        cout << "Connexion réussie !" << endl;
        utilisateurId = it->getId();
            if(it->getRole() == "client"){
                Panier panier(utilisateurId);
                int choix;
                string reference;
                    do {
                            afficherMenu();
        cout << "Entrez votre choix : ";
        cin >> choix;

        switch (choix) {
            case 0: {
                afficherTousLesArticles(listeArticles);
                break;
            }
            case 1: {
                string ref;
                cout << "Entrez la référence de l'article à ajouter : ";
                cin >> ref;

                optional<Article> article = rechercherArticleParRef(listeArticles, ref);
                if (article) {
                    panier.ajouterArticle(*article);
                } else {
                    cout << "Article non trouvé." << endl;
                }
                break;
            }
            case 2: {
                string ref;
                int nouvelleQuantite;
                cout << "Entrez la référence de l'article : ";
                cin >> ref;
                cout << "Entrez la nouvelle quantité : ";
                cin >> nouvelleQuantite;

                optional<Article> article = rechercherArticleParRef(listeArticles, ref);
                if (article) {
                    panier.modifierQuantiteArticle(*article, nouvelleQuantite);
                } else {
                    cout << "Article non trouvé." << endl;
                }
                break;
            }
            case 3:
                panier.viderPanier();
                cout << "Panier vidé." << endl;
                break;
            case 4: {
                cout << "Contenu du panier :" << endl;
                for (const auto& [article, quantite] : panier.getArticles()) {
                    cout << "Référence : " << article.getReference() << ", Article : " << article.getName() << ", Quantité : " << quantite << endl;
                }
                cout << "Montant total : " << panier.getMontantTotal() << " dhs" << endl;
                break;
            }
            case 5: {
                cout << "Articles triés par prix :" << endl;
                auto articlesTries = panier.getArticlesTriesParPrix();
                for (const auto& [article, quantite] : articlesTries) {
                    cout << "Référence : " << article.getReference() << ", Article : " << article.getName() << ", Prix : " << article.getPrix() << " dhs, Quantité : " << quantite << endl;
                }
                break;
            }
            case 6: {
                cout << "Montant total avec remise  : " << panier.getMontantTotal() << " dhs" << endl;
                break;
            }
            case 7: {
                try {
                    auto [article, quantite] = panier.getArticleLePlusCher();
                    cout << "Article le plus cher : Référence : " << article.getReference() << ", Article : " << article.getName() << ", Prix : " << article.getPrix() << " dhs, Quantité : " << quantite << endl;
                } catch (const runtime_error& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 8: {
                double prixMin, prixMax;
                cout << "Entrez le prix minimum : ";
                cin >> prixMin;
                cout << "Entrez le prix maximum : ";
                cin >> prixMax;

                auto articlesDansTranche = panier.getArticlesDansTrancheDePrix(prixMin, prixMax);
                if (articlesDansTranche.empty()) {
                    cout << "Aucun article trouvé dans cette tranche de prix." << endl;
                } else {
                    cout << "Articles dans la tranche de prix :" << endl;
                    for (const auto& [article, quantite] : articlesDansTranche) {
                        cout << "Référence : " << article.getReference() << ", Article : " << article.getName() << ", Prix : " << article.getPrix() << " dhs, Quantité : " << quantite << endl;
                    }
                }
                break;
            }
            case 9: {
                        Commande nouvelleCommande = panier.validerCommande();
                        ajouterCommande(nouvelleCommande);
                        cout << "Commande validée avec succès." << endl;
                        break;
            }
            case 10: {
                        afficherCommandesParUtilisateur(utilisateurId);
                        break;
            }
            case 11:
                cout << "Au revoir !" << endl;
            break;
            default:
                cout << "Choix invalide." << endl;
                break;
                            }
                        } while (choix != 11);
            }else{
                while (true) {
        cout << "Menu :" << endl;
        cout << "1. Ajouter un nouvel article" << endl;
        cout << "2. Rechercher un article par référence" << endl;
        cout << "3. Mettre à jour un article par référence" << endl;
        cout << "4. Supprimer un article par référence" << endl;
        cout << "5. Afficher tous les articles" << endl;
        cout << "6. Quitter" << endl;

        int choix;
        cout << "Choisissez une option : ";
        cin >> choix;

        switch (choix) {
            case 1: {
               cout << "Nouvel article" << endl;
               cout << "Veuillez saisir le nom de l'article : ";
               cin.ignore();
               string nom;
               getline(cin, nom);
               cout << "Référence : ";
               string ref;
               cin >> ref;
               cout << "Prix : ";
               double prix;
               cin >> prix;
               cout << "Quantité en stock : ";
               int quantite;
               cin >> quantite;
               Article nouvelArticle(nom, ref, prix, quantite);
               ajouterArticle(listeArticles, nouvelArticle);
               break;
            }
            case 2: {
                cout << "Référence de l'article à rechercher : ";
                string ref;
                cin >> ref;

                optional<Article> articleOptional = rechercherArticleParRef(listeArticles, ref);
                if (articleOptional.has_value()) {
                    Article article = articleOptional.value();
                    afficherArticle(article);
                } else {
                    cout << "Article non trouvé." << endl;
                }
                break;
            }
            case 3: {
                cout << "Référence de l'article à mettre à jour : ";
                string ref;
                cin >> ref;

                cout << "Nouveau nom : ";
                string nom;
                cin >> nom;

                cout << "Nouveau prix : ";
                double prix;
                cin >> prix;

                cout << "Nouvelle quantité en stock : ";
                int quantite;
                cin >> quantite;

                updateArticleParRef(listeArticles, ref, nom,prix, quantite);
                break;
            }
            case 4: {
                cout << "Référence de l'article à supprimer : ";
                string ref;
                cin >> ref;

                supprimerArticleParRef(listeArticles, ref);
                break;
            }
            case 5: {
                afficherTousLesArticles(listeArticles);
                break;
            }
            case 6: {
                cout << "Au revoir !" << endl;
                return 0;
            }
            default:
            
                cout << "Option invalide. Veuillez réessayer." << endl;
        }

    }
            }

    } else {

        cout << "Email ou mot de passe incorrect." << endl;

    }
    return  0 ;
}
