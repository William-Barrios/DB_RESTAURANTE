#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;

int q_estado;

class Opcion {
    public:
        void CREAR();
        void MOSTRAR();
        void ELIMINAR();
};

class Sucursal : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    void MOSTRAR(MYSQL* conectar);
    Sucursal();
    string RUC = " ";
    string DIRECCION = " ";
    string TELEFONO = " ";
    string DISTRITO = " ";
};

class Distrito : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    Distrito();
    string NOMBRE;
    string PROVINCIA;
};

class Provincia : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    Provincia();
    string NOMBRE;
};

class Inventario : public Opcion{
public:
    string NOMBRE;
    string CANTIDAD;
    string ESTADO;
    string SUCURSAL;
    Inventario();
    void CREAR(MYSQL* conectar);
    void MOSTRAR(MYSQL* conectar, string& id_sucursal);
};

void INGRESAR_SUCURSAL(MYSQL* conectar, Sucursal& S);

void Inventario_setting(MYSQL* conectar, string &id_sucursal);
void Inventario_Crear(MYSQL* conectar, string &id_sucursal, Inventario &I);


int main()
{
    MYSQL* conectar;
    conectar = mysql_init(0);
    conectar = mysql_real_connect(conectar, "localhost", "root", "Mauriciodavidapaza13", "default_schema", 3306, NULL, 0);
    if (conectar) {
        bool run = 0;
        bool run_sucursales = 0;
        int option;
        Sucursal S;
        while (!run) {
            cout << "<---- FOGON & CARBON ---->" << endl;
            cout << "1. SUCURSALES" << endl;
            cout << "2. COMPROBANTES" << endl;
            cout << "3. PEDIDOS" << endl;
            cout << "4. PRODUCTOS" << endl;
            cout << "5. EMPLEADOS" << endl;
            cout << "6. SALIR" << endl;
            cout << "SELECCIONAR: ";
            cin >> option;
            system("cls");
            switch (option) {
            case 1:
                while (!run_sucursales) {
                    cout << "<--- SUCURSALES --->" << endl;
                    cout << "1. CREAR SUCURSAL" << endl;
                    cout << "2. VER SUCURSAL" << endl;
                    cout << "3. SALIR" << endl;
                    cout << "SELECCIONAR: ";
                    cin >> option;
                    system("cls");
                    switch (option) {
                    case 1:
                        cout << "<--- NUEVA SUCURSAL --->" << endl;
                        INGRESAR_SUCURSAL(conectar , S);
                        while (option == 1) {
                            cout << "2. SALIR" << endl;
                            cout << "SELECCIONAR: ";
                            cin >> option;
                        }
                        system("cls");
                        break;
                    case 2:
                        cout << "<--- SUCURSAL --->" << endl;
                        S.MOSTRAR(conectar);
                        break;
                    case 3:
                        run_sucursales = 1;
                        break;
                    }
                }
                run_sucursales = 0;
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                run = 1;
                break;
            }
        }
    }
    else{
        cout << "Error en la Conexion..." << endl;
    }
}

Sucursal::Sucursal() {
    RUC = " ";
    DIRECCION = " ";
    TELEFONO = " ";
    DISTRITO = " ";
}

void Sucursal::CREAR(MYSQL* conectar) {
    string insert = "insert into sucursal(RUC, DIRECCION, TELEFONO, DISTRITO_ID_DISTRITO) values('" + RUC + "', '" + DIRECCION + "', '" + TELEFONO + "', '" + DISTRITO + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
}

void Sucursal::MOSTRAR(MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    const char* c;
    string id_sucursal;
    string ruc;
    cout << "Buscar Sucursal por RUC: ";
    cin >> ruc;
    consulta = "SELECT * FROM sucursal A, provincia B, distrito C WHERE A.DISTRITO_ID_DISTRITO = C.ID_DISTRITO AND C.PROVINCIA_ID_PROVINCIA = B.ID_PROVINCIA AND A.RUC = '" + ruc + "'";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        fila = mysql_fetch_row(resultado);
        id_sucursal = fila[0];
        cout << "RUC: " << fila[1] << endl;
        cout << "DIRECCION: " << fila[2] << endl;
        cout << "TELEFONO: " << fila[3] << endl;
        cout << "DISTRITO: " << fila[8] << endl;
        cout << "PROVINCIA: " << fila[6] << endl;
    }
    Inventario_setting(conectar, id_sucursal);
}

Provincia::Provincia() {
    NOMBRE = " ";
}

void Provincia::CREAR(MYSQL* conectar) {
    string insert = "insert into provincia(NOMBRE) values('" + NOMBRE + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
}

Distrito::Distrito() {
    NOMBRE = " ";
    PROVINCIA = " ";
}

void Distrito::CREAR(MYSQL* conectar) {
    string insert = "insert into distrito(NOMBRE, PROVINCIA_ID_PROVINCIA) values('" + NOMBRE + "', '" + PROVINCIA + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
}

Inventario::Inventario() {
    NOMBRE = " ";
    CANTIDAD = " ";
    ESTADO = " ";
    SUCURSAL = " ";
}

void Inventario::CREAR(MYSQL* conectar) {
    string insert = "insert into inventario(NOMBRE, CANTIDAD, ESTADO, SUCURSAL_RUC) values('" + NOMBRE + "', '" + CANTIDAD + "', '" + ESTADO + "', '" + SUCURSAL + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
}

void Inventario::MOSTRAR(MYSQL* conectar, string& id_sucursal) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    SUCURSAL = id_sucursal;
    const char* c;
    consulta = "SELECT * FROM inventario WHERE SUCURSAL_RUC = '" + SUCURSAL + "'";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        while (fila = mysql_fetch_row(resultado)) {
            cout << "NOMBRE: " << fila[1] << endl;
            cout << "CANTIDAD: " << fila[2] << endl;
            cout << "ESTADO: " << fila[3] << endl;
            cout << "------------------------------" << endl;
        }
    }
}

void INGRESAR_SUCURSAL(MYSQL* conectar, Sucursal& S) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    const char* c;
    //INGRESAR PROVINCIA
    string Prov_nom;
    string PROV;
    Provincia P;
    bool run = 0;
    int choose = 0;
    while (!run) {
        cout << "1. Elegir Provincia" << endl;
        cout << "2. Crear Nueva Provincia" << endl;
        cout << "3. Salir" << endl;
        cout << "SELECCIONAR: ";
        cin >> choose;
        system("cls");
        switch (choose) {
        case 1:
            consulta = "select id_provincia, nombre from provincia";
            c = consulta.c_str();
            q_estado = mysql_query(conectar, c);
            if (!q_estado) {
                resultado = mysql_store_result(conectar);
                while (fila = mysql_fetch_row(resultado)) {
                    cout << fila[0] << " | " << fila[1] << endl;
                }
            }
            cout << "Ingrese Provincia: ";
            cin >> PROV;
            consulta = "select nombre from provincia where id_provincia = '" + PROV + "'";
            c = consulta.c_str();
            q_estado = mysql_query(conectar, c);
            if (!q_estado) {
                resultado = mysql_store_result(conectar);
                while (fila = mysql_fetch_row(resultado)) {
                    Prov_nom = fila[0];
                }
            }
            run = 1;
            break;
        case 2:
            cout << "Ingrese Provincia: ";
            cin >> Prov_nom;
            P.NOMBRE = Prov_nom;
            P.CREAR(conectar);
            run = 1;
            break;
        case 3:
            return;
        }
    }
    system("cls");
    //INGRESAR DISTRITO
    bool run1 = 0;
    int choose1 = 0;
    string Dis_nom;
    string Prov;
    Distrito D;
    while (!run1) {
        cout << "1. Elegir Distrito" << endl;
        cout << "2. Crear Nuevo Distrito" << endl;
        cout << "3. Salir" << endl;
        cout << "SELECCIONAR: ";
        cin >> choose1;
        system("cls");
        switch (choose1) {
        case 1:
            consulta = "select id_distrito, nombre from distrito";
            c = consulta.c_str();
            q_estado = mysql_query(conectar, c);
            if (!q_estado) {
                resultado = mysql_store_result(conectar);
                while (fila = mysql_fetch_row(resultado)) {
                    cout << fila[0] << " | " << fila[1] << endl;
                }
            }
            cout << "Ingrese Distrito: ";
            cin >> PROV;
            consulta = "select nombre from distrito where id_distrito = '" + PROV + "'";
            c = consulta.c_str();
            q_estado = mysql_query(conectar, c);
            if (!q_estado) {
                resultado = mysql_store_result(conectar);
                while (fila = mysql_fetch_row(resultado)) {
                    Dis_nom = fila[0];
                }
            }
            run1 = 1;
            break;
        case 2:
            cout << "Ingrese Distrito: ";
            cin >> Dis_nom;
            consulta = "select id_provincia from provincia where nombre = '" + Prov_nom + "'";
            c = consulta.c_str();
            q_estado = mysql_query(conectar, c);
            if (!q_estado) {
                resultado = mysql_store_result(conectar);
                while (fila = mysql_fetch_row(resultado)) {
                    Prov = fila[0];
                }
            }
            D.NOMBRE = Dis_nom;
            D.PROVINCIA = Prov;
            D.CREAR(conectar);
            run1 = 1;
            break;
        case 3:
            return;
        }
    }
    system("cls");
    //INGRESAR DATOS SUCURSAL
    string ruc;
    cout << "Ingrese RUC: ";
    cin >> ruc;
    string direccion;
    cout << "Ingrese Direccion: ";
    cin >> direccion;
    string telefono;
    cout << "Ingrese Telefono: ";
    cin >> telefono;
    string Dist;
    consulta = "select id_distrito from distrito where nombre = '" + Dis_nom + "'";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        while (fila = mysql_fetch_row(resultado)) {
            Dist = fila[0];
        }
    }
    S.RUC = ruc;
    S.DIRECCION = direccion;
    S.TELEFONO = telefono;
    S.DISTRITO = Dist;
    S.CREAR(conectar);
}

void Inventario_setting(MYSQL* conectar, string & id_sucursal) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    Inventario I;
    const char* c;
    consulta = "SELECT * FROM inventario WHERE SUCURSAL_RUC ='" + id_sucursal + "'";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        fila = mysql_fetch_row(resultado);
        if (!fila) {
            Inventario_Crear(conectar, id_sucursal, I);
            system("cls");
        }
        else {
            bool run = 0;
            int option = 0;
            cout << endl;
            cout << "<-----Elementos del Inventario----->" << endl;
            I.MOSTRAR(conectar, id_sucursal);
            while (!run) {
                cout << "1. CREAR NUEVO ELEMENTO DE INVENTARIO" << endl;
                cout << "2. SALIR" << endl;
                cout << "SELECCIONAR: ";
                cin >> option;
                system("cls");
                switch (option) {
                case 1:
                    Inventario_Crear(conectar, id_sucursal, I);
                    run = 1;
                    system("cls");
                    break;
                case 2:
                    run = 1;
                    system("cls");
                    break;
                }
            }
            run = 0;
        }
    }
}

void Inventario_Crear(MYSQL* conectar, string & id_sucursal, Inventario &I) {
    string NOMBRE, CANTIDAD, ESTADO, SUCURSAL = id_sucursal;
    cout << endl;
    cout << "<----CREAR ELEMENTO DEL INVENTARIO---->" << endl;
    cout << "Ingresar Nombre de Producto: ";
    cin >> NOMBRE;
    cout << "Ingresar Cantidad: ";
    cin >> CANTIDAD;
    cout << "Ingresar Estado del Elemento: ";
    cin >> ESTADO;
    I.NOMBRE = NOMBRE;
    I.CANTIDAD = CANTIDAD;
    I.ESTADO = ESTADO;
    I.SUCURSAL = SUCURSAL;
    I.CREAR(conectar);
}