#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

struct Nodo {
    string valor;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(string v) {
        valor = v;
        izquierda = NULL;
        derecha = NULL;
    }
};

int prioridad(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void aplicarOperador(stack<Nodo*>& operandos, stack<char>& operadores) {
    char op = operadores.top();
    operadores.pop();

    Nodo* derecho = operandos.top();
    operandos.pop();

    Nodo* izquierdo = operandos.top();
    operandos.pop();

    Nodo* nuevo = new Nodo(string(1, op));
    nuevo->izquierda = izquierdo;
    nuevo->derecha = derecho;

    operandos.push(nuevo);
}

Nodo* construirArbol(string expresion) {
    stack<Nodo*> operandos;
    stack<char> operadores;

    for (int i = 0; i < expresion.length(); i++) {
        char c = expresion[i];

        if (c == ' ') continue;

        if (isdigit(c)) {
            string numero = "";
            while (i < expresion.length() && isdigit(expresion[i])) {
                numero += expresion[i];
                i++;
            }
            i--;
            operandos.push(new Nodo(numero));
        }
        else if (c == '(') {
            operadores.push(c);
        }
        else if (c == ')') {
            while (!operadores.empty() && operadores.top() != '(') {
                aplicarOperador(operandos, operadores);
            }
            operadores.pop();
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!operadores.empty() && operadores.top() != '(' &&
                   prioridad(operadores.top()) >= prioridad(c)) {
                aplicarOperador(operandos, operadores);
            }
            operadores.push(c);
        }
    }

    while (!operadores.empty()) {
        aplicarOperador(operandos, operadores);
    }

    return operandos.top();
}

void mostrarArbolBonito(Nodo* raiz, int nivel = 0) {
    if (raiz == NULL) return;

    for (int i = 0; i < nivel; i++) {
        cout << "   ";
    }

    cout << "|-- " << raiz->valor << endl;

    mostrarArbolBonito(raiz->izquierda, nivel + 1);
    mostrarArbolBonito(raiz->derecha, nivel + 1);
}

int main() {
    string expresion;

    cout << "Ingrese una expresion aritmetica: ";
    getline(cin, expresion);

    Nodo* arbol = construirArbol(expresion);

    cout << "\nArbol de expresion generado:\n";
    mostrarArbolBonito(arbol);

    return 0;
}
