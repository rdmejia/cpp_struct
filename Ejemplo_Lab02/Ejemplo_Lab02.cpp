#include <iostream>

using std::cout;

const int MES_ACTUAL = 8;
const int ANIO_ACTUAL = 2021;
const int MES_BONO14 = 6;

struct Empleado {
    char nombre[30];
    int edad;
    double salario;
    int mesDeContratacion;
    int anioDeContratacion;

    double getBono14() {
        if (MES_ACTUAL > MES_BONO14) {
			return salario * ((double)(MES_ACTUAL - MES_BONO14) / 12);
        }

        if (fueContratadoEsteAnio()) {
			return salario * (((double)MES_BONO14 - mesDeContratacion) / 12);
        }

        if (fueContratadoAnioPasadoDespuesDelBono14()) {
            return salario * ((double)(MES_BONO14 + 12 - mesDeContratacion) / 12);
        }

		return salario * ((double)(MES_ACTUAL + 12 - MES_BONO14) / 12);
    }

    double getAguinaldo() {
        if (fueContratadoEsteAnio()) {
            return salario * ((double)(MES_ACTUAL - mesDeContratacion) / 12);
        }

        return salario * ((double)MES_ACTUAL / 12);
    }

    double getTiempoEnLaEmpresa() {
        double tiempoActual = (ANIO_ACTUAL * 12) + MES_ACTUAL;
        double tiempoContratado = (anioDeContratacion * 12) + mesDeContratacion;

        return (tiempoActual - tiempoContratado) / 12;
    }

    double getIndemnizacion() {
        return getTiempoEnLaEmpresa() * salario;
    }

private:
    bool fueContratadoEsteAnio() {
        return anioDeContratacion == ANIO_ACTUAL;
    }

    bool fueContratadoAnioPasadoDespuesDelBono14() {
		return anioDeContratacion == (ANIO_ACTUAL - 1) && mesDeContratacion > MES_BONO14;
    }
};



void mostrarInformacionDelEmpleado(Empleado empleado) {
    cout << "\n============================";
    cout << "\nNombre: " << empleado.nombre;
    cout << "\nEdad: " << empleado.edad << " anios";
    cout << "\nSalario mensual: Q" << empleado.salario;
    cout << "\nFecha de contratacion: " << empleado.mesDeContratacion << "/" << empleado.anioDeContratacion;
    cout << "\nTiempo en la empresa: " << empleado.getTiempoEnLaEmpresa() << " anios";
    cout << "\nBono 14 acumulado: Q" << empleado.getBono14();
    cout << "\nAguinaldo acumulado: Q" << empleado.getAguinaldo();
    cout << "\nIndemnizacion acumulada: Q" << empleado.getIndemnizacion();
    cout << "\n============================\n";
}

int main()
{
    Empleado carlos = { "Carlos Perez", 20, 1000, 8, 2019 };
    Empleado daniel = { "Daniel Mejia", 27, 2000, 6, 2017 };
    Empleado maria = { "Maria Perez", 20, 3500, 10, 2015 };
    Empleado lucia = { "Lucia Bautista", 20, 1000, 2, 2021 };

    mostrarInformacionDelEmpleado(carlos);
    mostrarInformacionDelEmpleado(daniel);
    mostrarInformacionDelEmpleado(maria);
    mostrarInformacionDelEmpleado(lucia);
}

