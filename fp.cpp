#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

// Abstract Class
class Titik {
protected:
    string* nama_tempat;
    int* x;
    int* y;
    int jumlah_item;

public:
    // Constructor
    Titik(int jumlah_item) : jumlah_item(jumlah_item) {
        nama_tempat = new string[jumlah_item];
        x = new int[jumlah_item];
        y = new int[jumlah_item];
    }

    // Destructor
    virtual ~Titik() {
        delete[] nama_tempat;
        delete[] x;
        delete[] y;
    }

    // Abstract method
    virtual void tampilkanInfo() = 0;

    void setTitik(int index, string nama_tempat, int x, int y) {
        if (index >= 0 && index < jumlah_item) {
            this->nama_tempat[index] = nama_tempat;
            this->x[index] = x;
            this->y[index] = y;
        }
    }

    string getNamaTempat(int index) {
        if (index >= 0 && index < jumlah_item) {
            return nama_tempat[index];
        }
        return "Indeks tidak valid";
    }

    int getX(int index) {
        if (index >= 0 && index < jumlah_item) {
            return x[index];
        }
        return -1;
    }

    int getY(int index) {
        if (index >= 0 && index < jumlah_item) {
            return y[index];
        }
        return -1;
    }
};

// Concrete class
class Peta : public Titik {
private:
    int jumlah_titik;
    list<int>* adjacency_list;
    int** adjacency_matrix;

public:
    // Constructor
    Peta(int jumlah_titik) : Titik(jumlah_titik), jumlah_titik(jumlah_titik) {
        inisialisasiAdjList(jumlah_titik);
        inisialisasiAdjMatrix(jumlah_titik);
    }

    // Destructor
    ~Peta() {
        delete[] adjacency_list;
        for (int i = 0; i < jumlah_titik; i++) {
            delete[] adjacency_matrix[i];
        }
        delete[] adjacency_matrix;
    }

    // Override abstract method
    void tampilkanInfo() override {
        cout << "Ini adalah peta dengan " << jumlah_titik << " titik." << endl;
    }

    void inisialisasiAdjList(int jumlah_titik) {
        adjacency_list = new list<int>[jumlah_titik];
    }

    void inisialisasiAdjMatrix(int jumlah_titik) {
        adjacency_matrix = new int*[jumlah_titik];

        for (int i = 0; i < jumlah_titik; i++) {
            adjacency_matrix[i] = new int[jumlah_titik];

            for (int j = 0; j < jumlah_titik; j++) {
                adjacency_matrix[i][j] = 0;
            }
        }
    }

    void tambahLintasan(int titik_awal, int titik_tujuan) {
        adjacency_list[titik_awal].push_back(titik_tujuan);
        adjacency_matrix[titik_awal][titik_tujuan] = 1;
        adjacency_matrix[titik_tujuan][titik_awal] = 1;
    }

    void tampilkanAdjList() {
        list<int>::iterator i;

        for (int v = 0; v < jumlah_titik; v++) {
            cout << getNamaTempat(v) << " -> ";
            for (i = adjacency_list[v].begin(); i != adjacency_list[v].end(); ++i) {
                cout << getNamaTempat(*i);
                if (next(i, 1) != adjacency_list[v].end()) {
                    cout << " -> ";
                }
            }
            cout << endl;
        }
    }

    void tampilkanAdjMatrix() {
        for (int i = 0; i < jumlah_titik; i++) {
            for (int j = 0; j < jumlah_titik; j++) {
                cout << adjacency_matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

void tambahTitik(Titik* petaKu) {
    petaKu->setTitik(0, "Surabaya", 300, 100);
    petaKu->setTitik(1, "Madiun", 200, 100);
    petaKu->setTitik(2, "Semarang", 100, 200);
    petaKu->setTitik(3, "Cirebon", 100, 200);
    petaKu->setTitik(4, "Tangerang", 100, 200);
    petaKu->setTitik(5, "Cilegon", 400, 100);
    petaKu->setTitik(6, "Jakarta", 400, 200);
    petaKu->setTitik(7, "Jogja", 500, 200);
    petaKu->setTitik(8, "Bandung", 500, 300);
    petaKu->setTitik(9, "Nganjuk", 400, 300);

    // Downcast ke Peta
    Peta* peta = dynamic_cast<Peta*>(petaKu);
    if (peta) {
        peta->tambahLintasan(0, 1);
        peta->tambahLintasan(0, 2);
        peta->tambahLintasan(2, 3);
        peta->tambahLintasan(3, 4);
        peta->tambahLintasan(4, 5);
        peta->tambahLintasan(5, 6);
        peta->tambahLintasan(6, 7);
        peta->tambahLintasan(6, 8);
        peta->tambahLintasan(8, 7);
        peta->tambahLintasan(7, 0);
    }
}

int main() {
    cout << "Yanuar's Courier Route" << endl;
    int jumlah_titik = 10;

    Peta petaKu(jumlah_titik);

    // Menggunakan pointer ke objek Titik
    Titik* petaPointer = &petaKu;
    tambahTitik(petaPointer);

    cout << endl;
    petaKu.tampilkanInfo();

    cout << endl;
    cout << "Adjacency List" << endl;
    petaKu.tampilkanAdjList();

    cout << endl;
    cout << "Adjacency Matrix" << endl;
    petaKu.tampilkanAdjMatrix();

    return 0;
}
