#include <iostream>
using namespace std;

// Cau truc Ngay, Sinh vien, Node, List theo de bai
struct Ngay {
    int ngay, thang, nam;
};
struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};
struct Node {
    SinhVien data;
    Node *link;
};
struct List {
    Node *first;
    Node *last;
};

// Ham so sanh chuoi ky tu
bool soSanhChuoi(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
        { if (a[i] != b[i])
        { return a[i] < b[i]; } // Tra ve true neu ky tu trong chuoi 'a' nho hon chuoi 'b', nguoc lai tra ve false, kiem tra ky tự tiep theo
        i++;
    }
    return a[i] < b[i];
}

// Khoi tao danh sach sinh vien rong va tạo Node moi
void khoiTaoList(List &list) {
    list.first = nullptr; // Gan con tro first va last ve nullptr, List dang rong
    list.last = nullptr;
}
Node* taoNode(SinhVien sv) {
    Node* newNode = new Node; // Cap phat bo nho cho Node moi
    newNode->data = sv; // Gan du lieu
    newNode->link = nullptr; // Thiet lap con tro ve nullptr, do node nay chua lien ket voi node khac
    return newNode;
}

// Them sinh vien vao danh sach da sap xep theo ma sinh vien
void themSinhVienTheoThuTu(List &list, SinhVien sv) {
    Node* newNode = taoNode(sv); // Tao Node moi chua thong tin sinh vien
    // Ham if, neu danh sach rong hoac ma sinh vien cua 'sv' nho hon ma cua Node dau tien
    if (list.first == nullptr || soSanhChuoi(sv.maSV, list.first->data.maSV)) {
        newNode->link = list.first; // Chen node moi vao dau danh sach
        list.first = newNode; // 'first' tro den node moi
        if (list.last == nullptr)
            { list.last = newNode; // Neu danh sach chi co mot node, tro 'last' den node moi
        }
    } else
    {
        Node* current = list.first; // Duyet tu node dau tien
        // Tim vi tri chen node moi sao cho danh sach van giu thu tu tang dan
        while (current->link != nullptr && soSanhChuoi(current->link->data.maSV, sv.maSV)) {
            current = current->link;
        }
        newNode->link = current->link; // Gan link cua node moi den node tiep theo
        current->link = newNode; // Cap nhat link cua node hien tai de tro den node moi
        if (newNode->link == nullptr) {
            list.last = newNode; // Neu node moi duoc chen vao cuoi danh sach, cap nhat 'last'
        }
    }
}

// Nhap thong tin sinh vien
void nhapSinhVien(SinhVien &sv) {
    cout << "Ma sinh vien: ";
    cin >> sv.maSV;
    cout << "Ho ten: ";
    cin.ignore(); // Bo ky tu newline truoc do
    cin.getline(sv.hoTen, 50);
    cout << "Gioi tinh (0-Nu, 1-Nam): ";
    cin >> sv.gioiTinh;
    cout << "Ngay sinh (dd mm yyyy): ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cout << "Dia chi: ";
    cin.ignore(); // Bo ky tu newline truoc do
    cin.getline(sv.diaChi, 100);
    cout << "Lop: ";
    cin >> sv.lop;
    cout << "Khoa: ";
    cin >> sv.khoa;
}

// In danh sach sinh vien
void inDanhSach(const List &list) {
    Node* current = list.first; // Bat dau tu node dau tien
    if (current == nullptr) {
        cout << "Danh sach rong!" << endl; // Thong bao neu danh sach rong
        return;
    } while (current != nullptr) {
        SinhVien sv = current->data; // Lay va in thong tin
        cout << "Ma: " << sv.maSV << ", Ho ten: " << sv.hoTen << ", Ngay sinh: "
             << sv.ngaySinh.ngay << "/" << sv.ngaySinh.thang << "/" << sv.ngaySinh.nam << endl;
        current = current->link; // Di chuyen den node ke tiep
    }
}
// Ham main
int main() {
    List list; // Khai bao mot danh sach sinh vien
    khoiTaoList(list); // Khoi tao danh sach rong
    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        SinhVien sv;
        cout << "Nhap thong tin sinh vien " << i + 1 << ":" << endl;
        nhapSinhVien(sv);
        themSinhVienTheoThuTu(list, sv); // Them sinh vien vao danh sach theo thu tu ma sinh vien
    }
    cout << "\nDanh sach sinh vien sau khi sap xep theo ma:" << endl;
    inDanhSach(list); // In danh sach sinh vien

    return 0;
}
