#include <iostream>
#include <vector>
using namespace std;

struct GRAPH {
    int sodinh;               // Số đỉnh
    vector<vector<int>> a;    // Ma trận kề
};

// Hàm nhập ma trận kề
void NhapMaTranKe(GRAPH &g) {
    cout << "Nhap so dinh cua do thi: ";
    cin >> g.sodinh;
    g.a.resize(g.sodinh, vector<int>(g.sodinh, 0));
    cout << "Nhap ma tran ke:\n";
    for (int i = 0; i < g.sodinh; i++) {
        for (int j = 0; j < g.sodinh; j++) {
            cin >> g.a[i][j];
        }
    }
}

// Hàm kiểm tra tính hợp lệ của ma trận kề
bool KiemTraMaTranKeHopLe(const GRAPH &g) {
    for (int i = 0; i < g.sodinh; i++) {
        if (g.a[i][i] != 0) {
            return false;
        }
    }
    return true;
}

// Hàm kiểm tra đồ thị có hướng hay vô hướng
bool KiemTraDoThiVoHuong(const GRAPH &g) {
    for (int i = 0; i < g.sodinh; i++) {
        for (int j = i + 1; j < g.sodinh; j++) {
            if (g.a[i][j] != g.a[j][i]) {
                return false;
            }
        }
    }
    return true;
}

// Hàm tính bậc của tất cả các đỉnh
vector<int> TinhBacCuaTatCaDinh(const GRAPH &g, bool voHuong) {
    vector<int> bac(g.sodinh, 0);
    if (voHuong) {
        for (int i = 0; i < g.sodinh; i++) {
            for (int j = 0; j < g.sodinh; j++) {
                bac[i] += g.a[i][j];
            }
        }
    } else {
        vector<int> bacNgoai(g.sodinh, 0), bacTrong(g.sodinh, 0);
        for (int i = 0; i < g.sodinh; i++) {
            for (int j = 0; j < g.sodinh; j++) {
                bacNgoai[i] += g.a[i][j];  // Bậc ngoài
                bacTrong[i] += g.a[j][i];  // Bậc trong
            }
            bac[i] = bacNgoai[i] + bacTrong[i];
        }
    }

    // In bậc của các đỉnh
    cout << "\nBac cua cac dinh:\n";
    for (int i = 0; i < g.sodinh; i++) {
        if (voHuong) {
            cout << "Dinh " << i << ": Bac = " << bac[i] << endl;
        } else {
            cout << "Dinh " << i << ": Bac ngoai = " << bac[i] - bac[i] / 2
                 << ", Bac trong = " << bac[i] / 2
                 << ", Tong bac = " << bac[i] << endl;
        }
    }
    return bac;
}

// Hàm tìm các đỉnh có bậc lớn nhất, nhỏ nhất, bậc chẵn, bậc lẻ, đỉnh cô lập và đỉnh treo
void TimDinhDacBiet(const GRAPH &g, const vector<int> &bac) {
    int bacMax = -1, bacMin = g.sodinh;
    vector<int> dinhBacMax, dinhBacMin, dinhChan, dinhLe, dinhCoLap, dinhTreo;

    for (int i = 0; i < g.sodinh; i++) {
        if (bac[i] > bacMax) {
            bacMax = bac[i];
            dinhBacMax.clear();
            dinhBacMax.push_back(i);
        } else if (bac[i] == bacMax) {
            dinhBacMax.push_back(i);
        }

        if (bac[i] < bacMin) {
            bacMin = bac[i];
            dinhBacMin.clear();
            dinhBacMin.push_back(i);
        } else if (bac[i] == bacMin) {
            dinhBacMin.push_back(i);
        }

        if (bac[i] % 2 == 0) dinhChan.push_back(i);
        else dinhLe.push_back(i);

        if (bac[i] == 0) dinhCoLap.push_back(i);
        if (bac[i] == 1) dinhTreo.push_back(i);
    }

    cout << "\nDinh co bac lon nhat (" << bacMax << "): ";
    for (int d : dinhBacMax) cout << d << " ";
    cout << "\nDinh co bac nho nhat (" << bacMin << "): ";
    for (int d : dinhBacMin) cout << d << " ";
    cout << "\nDinh co bac chan: ";
    for (int d : dinhChan) cout << d << " ";
    cout << "\nDinh co bac le: ";
    for (int d : dinhLe) cout << d << " ";
    cout << "\nDinh co lap: ";
    for (int d : dinhCoLap) cout << d << " ";
    cout << "\nDinh treo: ";
    for (int d : dinhTreo) cout << d << " ";
    cout << endl;
}

int main() {
    GRAPH g;
    NhapMaTranKe(g);

    // Kiểm tra tính hợp lệ của ma trận kề
    if (!KiemTraMaTranKeHopLe(g)) {
        cout << "Ma tran ke khong hop le" << endl;
        return 0;
    }

    // Kiểm tra đồ thị có hướng hay vô hướng
    bool voHuong = KiemTraDoThiVoHuong(g);
    cout << (voHuong ? "Do thi vo huong" : "Do thi co huong") << endl;

    // Tính bậc của tất cả các đỉnh
    vector<int> bac = TinhBacCuaTatCaDinh(g, voHuong);

    // Xác định các đỉnh có bậc đặc biệt
    TimDinhDacBiet(g, bac);

    return 0;
}