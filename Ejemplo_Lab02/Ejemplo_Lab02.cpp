#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int ANIO_ACTUAL = 2022;
const int MES_ACTUAL = 8;
const int MES_BONO14 = 6;

struct empleado {
    char nombre[30];
    int edad;
    double salario;
    int mesDeContrato;
    int anioDeContrato;
};

struct calculadoraDeBono {
    virtual double calcularBono(empleado emp) = 0;

    protected:
    bool fueContratadoEsteAnio(empleado emp) {
        return emp.anioDeContrato == ANIO_ACTUAL;
    }
};

struct calculadoraDeAguinaldo : calculadoraDeBono {
    double calcularBono(empleado emp) {
        if (fueContratadoEsteAnio(emp))
        {
            return emp.salario * ((double)(MES_ACTUAL - emp.mesDeContrato) / 12);
        }

        return emp.salario * ((double)MES_ACTUAL / 12);
    }
};

struct calculadoraDeBono14 : calculadoraDeBono {
    double calcularBono(empleado emp) {
        if (MES_ACTUAL > MES_BONO14) {
            return emp.salario * ((double)(MES_ACTUAL - MES_BONO14) / 12);
        }

        if (fueContratadoEsteAnio(emp)) {
            return emp.salario * ((double)(MES_BONO14 - emp.mesDeContrato) / 12);
        }

        if (fueContratadoAnioPasadoDespuesDelBono14(emp)) {
            return emp.salario * ((double)(MES_BONO14 - emp.mesDeContrato) / 12);
        }
        
        return emp.salario * ((double)(MES_ACTUAL + 12 - MES_BONO14) / 12);
    }

    private:
    bool fueContratadoAnioPasadoDespuesDelBono14(empleado emp) {
        return emp.anioDeContrato == (ANIO_ACTUAL - 1)
        && emp.mesDeContrato > MES_BONO14;   
    }
};

int main(int argc, char** argv) {
    empleado carlos = {"Carlos Molina", 27, 1000, 8, 2019};

    calculadoraDeAguinaldo aguinaldo = calculadoraDeAguinaldo();
    calculadoraDeBono14 bono14 = calculadoraDeBono14();

    double aguinaldoDeCarlos = aguinaldo.calcularBono(carlos);
    double bono14DeCarlos = bono14.calcularBono(carlos);

    cout << "Aguinaldo de Carlos: " << aguinaldoDeCarlos << endl;
    cout << "Bono 14 de Carlos: " << bono14DeCarlos << endl;

    return 798423;
}