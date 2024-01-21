#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class H {
public:
    int data;
    bool validate;
    H() : data(0), validate(true) {}
    H(int data) : data(data), validate(true) {}
};
void marcar(std::vector<std::vector<H>>& vec, int i, int j, bool p) {
    if(i < vec.size() && j < vec[0].size()) {
        vec[i][j].validate = false;
        (p) ? marcar(vec, i, j + 1, p) : marcar(vec, i + 1, j, p);
    }
}

std::vector<std::pair<int, int>> camino_n(std::vector<std::vector<H>>& vec, const std::vector<int> oferta, const std::vector<int> demanda, int i, int j) {
    std::vector<int> o = oferta;
    std::vector<int> d = demanda;
    std::vector<std::pair<int, int>> result;
    while (vec[i][j].validate) {
        if(o[i] > 0 && d[j] > 0) {
            //cout << vec[i][j].data << " (" << i << " : " << j << ")" << endl;
            if(o[i] <= d[j]) {
                result.push_back(make_pair(o[i], vec[i][j].data));
                d[j] -= o[i];
                o[i] -= o[i];
                marcar(vec, i, 0, true);
                
                std::pair<int, int> tem = make_pair(vec[0][j].data, 0);
                
                // for para buscar el mayor
                for(int k = 0; k < vec.size(); k++) 
                    if(vec[k][j].validate) 
                        if(vec[k][j].data >= tem.first)
                            tem = make_pair(vec[k][j].data, k);
                    
                // for para buscar el menor
                for(int k = 0; k < vec.size(); k++) 
                    if(vec[k][j].validate) 
                        if(vec[k][j].data <= tem.first)
                            tem = make_pair(vec[k][j].data, k);
            
                i = tem.second;
            }
            else {
                result.push_back(make_pair(d[j], vec[i][j].data));
                o[i] -= d[j];
                d[j] -= d[j];

                marcar(vec, 0, j, false);
                
                std::pair<int, int> tem = make_pair(vec[i][0].data, 0);
                
                // for para buscar el mayor
                for(int k = 0; k < vec[0].size(); k++)
                    if(vec[i][k].validate)
                        if(vec[i][k].data >= tem.first)
                            tem = make_pair(vec[i][k].data, k);
                
                // for para buscar el menor
                for(int k = 0; k < vec[0].size(); k++)
                    if(vec[i][k].validate) 
                        if(vec[i][k].data <= tem.first)
                            tem = make_pair(vec[i][k].data, k);
                
                j = tem.second;
            }
        }
    }
    return result;
}

int main() {
    std::vector<std::vector<H>> m = {
        {H(5), H(2), H(7), H(3)},
        {H(3), H(6), H(6), H(1)},
        {H(6), H(1), H(2), H(4)},
        {H(4), H(3), H(6), H(6)}
    };
    std::vector<int> oferta = {80, 30, 60, 4};
    std::vector<int> demanda = {70, 40, 70, 35};
    //std::vector<std::pair<int, int>> p = camino_n(m, oferta, demanda, 1, 3);
    std::vector<std::vector<H>> v = {
        {H(12), H(13), H(4), H(6)},
        {H(6), H(4), H(10), H(11)},
        {H(10), H(5), H(9), H(4)},
        {H(4), H(12), H(8), H(10)}
    };
    std::vector<int> oferta1 = {500, 700, 800, 200};
    std::vector<int> demanda1 = {400, 900, 200, 700};
    /*std::vector<std::pair<int, int>> p = camino_n(v, oferta1, demanda1, 0, 3);

    int contado = 0;
    for(auto i : p)
        contado += i.first * i.second;
    cout << contado << endl;*/
    
    for(int i = 0; i < v.size(); i++) {
        for(int j = 0; j < v[0].size(); j++) {
            cout << v[i][j].data << " (" << i << " : " << j << " = ";
            std::vector<std::vector<H>> cv = v;
            std::vector<std::pair<int, int>> p = camino_n(cv, oferta1, demanda1, i, j);
            int contado = 0;
            for(auto i : p)
                contado += i.first * i.second;
            cout << contado << endl;         
        }
    }
    return 0;
}