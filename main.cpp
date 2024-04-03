#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Carte
{
private:
    std::string nume;
    std::string autor;
    int numarPagini;
    int nrZileMaxImprumut;

public:
    Carte(std::string NUME, std::string _autor, int _numarPagini, int _numarZileImprumut)
    {
        nume = std::move(NUME);
        autor = std::move(_autor);
        numarPagini = _numarPagini;
        nrZileMaxImprumut = _numarZileImprumut;
    }
    Carte(const Carte &other)
    {
        nume = other.nume;
        autor = other.autor;
        numarPagini = other.numarPagini;
        nrZileMaxImprumut = other.nrZileMaxImprumut;
    }
    Carte &operator=(const Carte &other)
    = default;
    bool operator==(const Carte &other) const
    {
        return (nume == other.nume) && (autor == other.autor) && (numarPagini == other.numarPagini);
    }
    friend std::ostream &operator<<(std::ostream &os, const Carte &carte)
    {
        os << "Numele cartii este " << carte.nume << ", autorul ei este " << carte.autor << ", cu numar de pagini : " << carte.numarPagini << '\n';
        os << "Numarul de zile pana cand cartea trebuie sa fie returnata este" << carte.nrZileMaxImprumut << '\n';
        return os;
    }
    ~Carte() = default;

    std::string numeCarte()
    {
        return nume;
    }
    /*
    std::string numeAutor()
    {
        return autor;
    }

    [[nodiscard]] int numarPaginiCarte() const
    {
        return numarPagini;
    }
     */
    [[nodiscard]] int maxImprumut() const
    {
        return nrZileMaxImprumut;
    }
};

class Bibliotecar
{
private:
    std::string nume;
    int numarGestiune{};
    std::vector<Carte> gestiuneCarti; /// cartile pentru care bibliotecarul este responsabil
public:
    Bibliotecar()
    = default;

    [[maybe_unused]] explicit Bibliotecar(std::string _nume)
    {
        nume = std::move(_nume);
        numarGestiune = 0;
        gestiuneCarti.clear();
    }
    Bibliotecar(const Bibliotecar &other)
    {
        nume = other.nume;
        numarGestiune = other.numarGestiune;
        gestiuneCarti = other.gestiuneCarti;
    }
    Bibliotecar &operator=(const Bibliotecar &other)
    = default;
    [[nodiscard]] std::string afiseazaNume() const
    {
        return nume;
    }
    friend std::ostream &operator<<(std::ostream &os, const Bibliotecar &bibliotecar)
    {
        os << "Numele bibliotecarului este " << bibliotecar.nume << ", care are in gestiune " << bibliotecar.numarGestiune << " carti." << '\n';
        os << "Cartile pe care acesta le are in gestiune sunt : " << '\n';
        for (Carte it : bibliotecar.gestiuneCarti)
        {
            os << it.numeCarte() << '\n';
        }
        return os;
    }
    ~Bibliotecar() = default;

    std::vector<Carte> CartileDinGestiune()
    {//aaa
        return gestiuneCarti;
    }
    void imprumutaCarte(unsigned idx)
    {
        numarGestiune--;
        gestiuneCarti.erase(gestiuneCarti.begin() + idx);
    }
    void adaugaCarte(Carte &carte)
    {
        numarGestiune++;
        gestiuneCarti.push_back(carte);
    }
};

class SalaDeLectura
{
private:
    std::string nume;
    Bibliotecar bibliotecar;
    int numarCarti;
    std::vector<Carte> cartiDeCitit;

public:
    SalaDeLectura(std::string _nume, int _numarCarti, const Bibliotecar& _bibliotecar)
    {
        nume = std::move(_nume);
        numarCarti = _numarCarti;
        bibliotecar = _bibliotecar;
    }

    SalaDeLectura(const SalaDeLectura &other)
    {
        nume = other.nume;
        bibliotecar = other.bibliotecar;
        numarCarti = other.numarCarti;
        cartiDeCitit = other.cartiDeCitit;
    }

    SalaDeLectura &operator=(const SalaDeLectura &other)
    = default;

    void adaugaCarte(const Carte &carte)
    {
        cartiDeCitit.push_back(carte);
    }

    ~SalaDeLectura() = default;

    friend std::ostream &operator<<(std::ostream &os, const SalaDeLectura &saladelectura)
    {
        os << "Numele salii de lectura este " << saladelectura.nume << ", bibliotecarul responsabil este " << saladelectura.bibliotecar.afiseazaNume() << " care este responsabil de " << saladelectura.numarCarti << " carti" << '\n';
        os << "Cartile din sala de lectura sunt urmatoarele: ";
        for (Carte it : saladelectura.cartiDeCitit)
        {
            os << it.numeCarte() << '\n';
        }
        return os;
    }
    std::string numeSalaDeLectura()
    {
        return nume;
    }
};

class Biblioteca
{
private:
    std::string nume;
    int numarCarti;
    int numarBibliotecari;
    std::vector<SalaDeLectura> salaDeLectura;

public:///
    Biblioteca(std::string _nume, int _numarCarti, int _numarBibliotecari, std::vector<SalaDeLectura> _saladelectura)
    {
        nume = std::move(_nume);
        numarCarti = _numarCarti;
        numarBibliotecari = _numarBibliotecari;
        salaDeLectura = std::move(_saladelectura);
    }
    Biblioteca(const Biblioteca &other)
    {
        nume = other.nume;
        numarCarti = other.numarCarti;
        numarBibliotecari = other.numarBibliotecari;
        salaDeLectura = other.salaDeLectura;
    }
    Biblioteca &operator=(const Biblioteca &other)
    = default;
    ~Biblioteca() = default;

    friend std::ostream &operator<<(std::ostream &os, const Biblioteca &biblioteca)
    {
        os << "Numele este " << biblioteca.nume << ", numarul de carti este " << biblioteca.numarCarti << ", iar numarul de bibliotecari este " << biblioteca.numarBibliotecari << '\n';
        os << "Biblioteca " << biblioteca.nume << " contine urmatoarele sali de lectura : " << '\n';
        for (auto it : biblioteca.salaDeLectura)
        {
            os << it.numeSalaDeLectura() << '\n';
        }
        return os;
    }
};

class MembruBiblioteca
{
private:
    std::string nume;
    std::vector<Carte> cartiImprumutate;
    int valoareAmenda;
    int valMaxAmenda;

public:
    explicit MembruBiblioteca(std::string _nume, int _valoareAmenda, int _valMaxAmenda)
    {
        nume = std::move(_nume);
        valoareAmenda = _valoareAmenda;
        valMaxAmenda = _valMaxAmenda;
    }
    MembruBiblioteca(const MembruBiblioteca &other)
    {
        nume = other.nume;
        cartiImprumutate = other.cartiImprumutate;
        valoareAmenda = other.valoareAmenda;
        valMaxAmenda = other.valMaxAmenda;
    }
    MembruBiblioteca &operator=(const MembruBiblioteca &other)
    = default;
    ~MembruBiblioteca() = default;

    friend std::ostream &operator<<(std::ostream &os, const MembruBiblioteca &membrubiblioteca)
    {
        os << membrubiblioteca.nume << "are o amenda de " << membrubiblioteca.valoareAmenda << " lei" << '\n';
        os << membrubiblioteca.nume << " a imprumutat urmatoarele carti " << '\n';
        for (Carte it : membrubiblioteca.cartiImprumutate)
        {
            os << it.numeCarte() << '\n';
        }

        return os;
    }
    void imprumutaCarte(Carte &carte, Bibliotecar &bibliotecar)
    {
        for (auto it : cartiImprumutate)
        {
            if (it == carte)
            {
                std::cout << nume << " a imprumutat deja cartea " << it.numeCarte() << '\n';
                return;
            }
        }
        unsigned index = bibliotecar.CartileDinGestiune().size();
        std::vector<Carte> w = bibliotecar.CartileDinGestiune();
        bool ok = false;
        for (unsigned i = 0; i < w.size(); i++)
        {
            Carte it = w[i];
            if (it == carte)
            {
                ok = true;
                index = i;
            }
        }
        if (!ok)
        {
            std::cout << carte.numeCarte() << " nu poate fi imprumutata pentru ca nu exista." << '\n';
            return;
        }
        cartiImprumutate.push_back(carte);
        bibliotecar.imprumutaCarte(index);
    }//asdadsadasdas
    void returneazaCarte(Carte &carte, Bibliotecar &bibliotecar, int nrZileImprumut) {
        unsigned index = -1;
        for (unsigned i = 0; i < cartiImprumutate.size(); i++) {
            Carte it = cartiImprumutate[i];
            if (it == carte) {
                index = i;
                break;
            }
        }
        if (index > -1) {
            if (nrZileImprumut > carte.maxImprumut()) {
                valoareAmenda += 100 * (nrZileImprumut - carte.maxImprumut());
                std::cout << nume << " a fost amendat pentru returnarea cu intarziere a cartii" << '\n';
            }
            cartiImprumutate.erase(cartiImprumutate.begin() + index);
            bibliotecar.adaugaCarte(carte);
        } else {
            std::cout << "Cartea " << carte.numeCarte() << " nu poate fi returnata daca nu a fost imprumutata de "
                      << nume << '\n';
        }
    }
    void verificaAmenda()
    {
        if(valoareAmenda > valMaxAmenda)
        {
            std::cout << nume << " a fost amendat de prea multe ori deci nu va mai putea imprumuta carti din biblioteca" <<
            '\n';
        }
    }
};

int main()
{
    Carte carte1("Luceafarul", "Mihai Eminescu", 100, 20);
    Carte carte2("Amintiri din Copilarie", "Ion Creanga", 200, 15);
    Carte carte3("Morometii", "Marin Preda", 400, 14);
    Carte carte4("Patul lui Procust", "Camil Petrescu", 178, 6);
    Carte carte5("Pacala", "Ion Creaga", 87, 21);
    Carte carte6("Ursul Pacalit de Vulpe", "Ion Creanga", 55, 7);
    Carte carte7("Baltagul", "Mihail Sadoveanu", 133, 21);
    Carte carte8("Enigma Otiliei", "George Calinescu", 315, 14);
    Carte carte9("Ion", "Liviu Rebreanu", 478, 14);
    Carte carte10("Moara cu Noroc", "Ioan Slavici", 555, 14);

    std::cout << carte3 << '\n';
    std::cout << carte8 << '\n';
    std::cout << carte10 << '\n';

    Bibliotecar bibliotecar1("Valentin");
    bibliotecar1.adaugaCarte(carte1);
    bibliotecar1.adaugaCarte(carte3);
    bibliotecar1.adaugaCarte(carte5);
    bibliotecar1.adaugaCarte(carte7);
    bibliotecar1.adaugaCarte(carte9);
    std::cout << bibliotecar1 << '\n';

    Bibliotecar bibliotecar2("Rares");
    bibliotecar2.adaugaCarte(carte2);
    bibliotecar2.adaugaCarte(carte4);
    bibliotecar2.adaugaCarte(carte6);
    bibliotecar2.adaugaCarte(carte8);
    bibliotecar2.adaugaCarte(carte10);
    std::cout << bibliotecar2 << '\n';

    MembruBiblioteca membrubiblioteca1("Vladut Piele", 0, 1000);
    membrubiblioteca1.imprumutaCarte(carte1, bibliotecar1);
    membrubiblioteca1.imprumutaCarte(carte3, bibliotecar1);
    std::cout << membrubiblioteca1 << '\n';
    membrubiblioteca1.returneazaCarte(carte2, bibliotecar1, 15);
    /// cartea nu a fost imprumutata deci afiseaza "cartea nu poate fi returnata daca .... nu a fost imprumutata".
    std::cout << '\n';
    membrubiblioteca1.imprumutaCarte(carte1, bibliotecar1);
    ///  a imprumutat deja cartea1, deci afiseaza "cartea a fost deja imprumutata..."
    membrubiblioteca1.verificaAmenda();

    SalaDeLectura saladelectura1("Sala de lectura copii", 5, bibliotecar1);
    SalaDeLectura saladelectura2("Sala de lectura adulti", 5, bibliotecar2);

    saladelectura1.adaugaCarte(carte1);
    saladelectura1.adaugaCarte(carte3);
    saladelectura1.adaugaCarte(carte5);
    saladelectura1.adaugaCarte(carte7);
    saladelectura1.adaugaCarte(carte9);

    saladelectura2.adaugaCarte(carte2);
    saladelectura2.adaugaCarte(carte4);
    saladelectura2.adaugaCarte(carte6);
    saladelectura2.adaugaCarte(carte8);
    saladelectura2.adaugaCarte(carte10);

    std::vector<SalaDeLectura> saliDeLectura;
    saliDeLectura.push_back(saladelectura1);
    saliDeLectura.push_back(saladelectura2);
    Biblioteca BibliotecaNationala("Biblioteca Nationala", 10, 2, saliDeLectura);
    std::cout << BibliotecaNationala << '\n';

    std::cout << saladelectura1 << '\n';

    return 0;
}
