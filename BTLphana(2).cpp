#include <bits/stdc++.h>

using namespace std;

class CanBo {
private:
    string maCanBo;
    string hoTen;
    string phongBan;
    string chucVu;
    float heSoLuong;

public:
    CanBo(
	 string ma = "", 
	 string ten = "", 
	 string phong = "", 
	 string chuc = "", 
	 float hsl = 0.0
	)
        : maCanBo(ma), hoTen(ten), phongBan(phong), chucVu(chuc), heSoLuong(hsl) {}

    float tinhLuong() const {
        return heSoLuong * 1350000;
    }

    string getMaCanBo() const { return maCanBo; }
    string getHoTen() const { return hoTen; }
    string getPhongBan() const { return phongBan; }
    string getChucVu() const { return chucVu; }
    float getHeSoLuong() const { return heSoLuong; }
};

class DanhSachCanBo {
private:
    struct Node {
        CanBo data;
        Node* next;
        Node(CanBo cb) : data(cb), next(nullptr) {}
    };
    Node* head;
    
    void inThongTinCanBo(const CanBo& cb) const {
        cout << "Ma CB: " << cb.getMaCanBo() << ", Ho Ten: " << cb.getHoTen()
             << ", Phong Ban: " << cb.getPhongBan() << ", Chuc Vu: " << cb.getChucVu()
             << ", He So Luong: " << cb.getHeSoLuong() << ", Luong: " << cb.tinhLuong() 
			 << endl;
         };
public:
    DanhSachCanBo() : head(nullptr) {}

    void taoDanhSachTuFile() {
        ifstream file("input.txt");
        if (!file.is_open()) {
            cerr << "Khong the mo file" << endl;
            return;
        }

        int n;
        file >> n;
        file.ignore();

        for (int i = 0; i < n; ++i) {
            string ma, hoTen, phongBan, chucVu;
            float heSoLuong;

            getline(file, ma);
            getline(file, hoTen);
            getline(file, phongBan);
            getline(file, chucVu);
            file >> heSoLuong;
            file.ignore();

            CanBo cb(ma, hoTen, phongBan, chucVu, heSoLuong);
            themCanBo(cb);
        }

        file.close();
    }

    void themCanBo(const CanBo& cb, int viTri = -1) {
        Node* newNode = new Node(cb);
        if (!head || viTri == 0) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* curr = head;
        int pos = 1;
        while (curr->next && pos < viTri) {
            curr = curr->next;
            pos++;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }

    void inCanBoHeSoLuongLonHon44() const {
        Node* curr = head;
        while (curr) {
            if (curr->data.getHeSoLuong() >= 4.4) {
                inThongTinCanBo(curr->data);
            }
            curr = curr->next;
        }
    }

    void timCanBoTheoChucVu(const string& chucVu) const {
        Node* curr = head;
        while (curr) {
            if (curr->data.getChucVu() == chucVu) {
                inThongTinCanBo(curr->data);
            }
            curr = curr->next;
        }
    }

    void timCanBoTheoHeSoVaPhongBan(float heSo, const string& phongBan) const {
        Node* curr = head;
        while (curr) {
            if (curr->data.getHeSoLuong() == heSo && curr->data.getPhongBan() == phongBan) {
                inThongTinCanBo(curr->data);
            }
            curr = curr->next;
        }
    }

    void sapXepTheoTen() {
        vector<CanBo> canBos;
        Node* curr = head;
        while (curr) {
            canBos.push_back(curr->data);
            curr = curr->next;
        }

        sort(canBos.begin(), canBos.end(), [](const CanBo& a, const CanBo& b) {
            return a.getHoTen() < b.getHoTen();
        });

        curr = head;
        for (const auto& cb : canBos) {
            curr->data = cb;
            curr = curr->next;
        }
    }

    void timCanBoLuongCaoNhat() const {
        if (!head) {
            cout << "Danh sach trong.\n";
            return;
        }

        Node* curr = head;
        Node* maxNode = head;
        while (curr) {
            if (curr->data.tinhLuong() > maxNode->data.tinhLuong()) {
                maxNode = curr;
            }
            curr = curr->next;
        }

        cout << "Can bo co luong cao nhat:\n";
        inThongTinCanBo(maxNode->data);
    }

    void timCanBoLuongThapNhat() const {
        if (!head) {
            cout << "Danh sach trong.\n";
            return;
        }

        Node* curr = head;
        Node* minNode = head;
        while (curr) {
            if (curr->data.tinhLuong() < minNode->data.tinhLuong()) {
                minNode = curr;
            }
            curr = curr->next;
        }

        cout << "Can bo co luong thap nhat:\n";
        inThongTinCanBo(minNode->data);
    }

    void inDanhSach() const {
        Node* curr = head;
        while (curr) {
            inThongTinCanBo(curr->data);
            curr = curr->next;
        }
    }
};

class App {
public:
    void luachon() {
        DanhSachCanBo ds;
        int choice;
        do {
            cout << "Menu:\n";
            cout << "1. Tao danh sach can bo tu file\n";
            cout << "2. In danh sach can bo\n";
            cout << "3. Them can bo\n";
            cout << "4. Tinh luong can bo\n";
            cout << "5. In can bo co he so luong >= 4.4\n";
            cout << "6. Tim can bo theo chuc vu\n";
            cout << "7. Tim can bo theo he so luong va phong ban\n";
            cout << "8. Sap xep can bo theo ten\n";
            cout << "9. Tim can bo co luong cao nhat\n";
            cout << "10. Tim can bo co luong thap nhat\n";
            cout << "0. Thoat\n";
            cout << "Nhap lua chon: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    ds.taoDanhSachTuFile();
                    break;
                case 2:
                    ds.inDanhSach();
                    break;
                case 3: {
                    CanBo cb;
                    string ma, ten, phong, chuc;
                    float hsl;
                    cout << "Nhap ma can bo: ";
                    cin.ignore(); getline(cin, ma);
                    cout << "Nhap ho ten: "; getline(cin, ten);
                    cout << "Nhap phong ban: "; getline(cin, phong);
                    cout << "Nhap chuc vu: "; getline(cin, chuc);
                    cout << "Nhap he so luong: "; cin >> hsl;
                    cb = CanBo(ma, ten, phong, chuc, hsl);
                    int viTri;
                    cout << "Nhap vi tri can them (-1 de them vao cuoi): ";
                    cin >> viTri;
                    ds.themCanBo(cb, viTri);
                    break;
                }
                case 4:
                    cout << "Luong cua cac can bo:\n";
                    ds.inDanhSach();
                    break;
                case 5:
                    ds.inCanBoHeSoLuongLonHon44();
                    break;
                case 6: {
                    string chucVu;
                    cout << "Nhap chuc vu can tim: ";
                    cin.ignore(); getline(cin, chucVu);
                    ds.timCanBoTheoChucVu(chucVu);
                    break;
                }
                case 7: {
                    float heSo;
                    string phongBan;
                    cout << "Nhap he so luong: ";
                    cin >> heSo;
                    cout << "Nhap phong ban: ";
                    cin.ignore(); getline(cin, phongBan);
                    ds.timCanBoTheoHeSoVaPhongBan(heSo, phongBan);
                    break;
                }
                case 8:
                    ds.sapXepTheoTen();
                    break;
                case 9:
                    ds.timCanBoLuongCaoNhat();
                    break;
                case 10:
                    ds.timCanBoLuongThapNhat();
                    break;
                case 0:
                    cout << "Thoat chuong trinh.\n";
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
            }
        } while (choice != 0);
    }
};

int main() {
    App app;
    app.luachon();
    return 0;
}

