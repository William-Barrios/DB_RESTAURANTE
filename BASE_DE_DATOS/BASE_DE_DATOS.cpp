#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;

int q_estado;

string RUC_UNICO;
bool run_my_sucursal = 1;

class Opcion {
public:
    void CREAR();
    void MOSTRAR();
    void ELIMINAR();
    void ACTUALIZAR();
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

class Inventario : public Opcion {
public:
    string NOMBRE;
    string CANTIDAD;
    string ESTADO;
    string SUCURSAL;
    Inventario();
    void CREAR(MYSQL* conectar);
    void MOSTRAR(MYSQL* conectar, string& id_sucursal);
    void ELIMINAR(MYSQL* conectar);
    void ACTUALIZAR(MYSQL* conectar);
};

class ProSur : public Opcion {
public:
    string ID_SUCURSAL;
    string ID_PRODUCTO;
    ProSur();
    void CREAR(MYSQL* conectar, string id_producto);
};

class Producto : public Opcion {
public:
    string PRECIO;
    string TIPO;
    string PROVEEDOR_ID;
    Producto();
    void CREAR(MYSQL* conectar);
    void MOSTRAR(MYSQL* conectar);
};

class Proveedor : public Opcion {
public:
    string TELEFONO;
    string DIRECCION;
    Proveedor();
    void CREAR(MYSQL* conectar);
};

class Datos_Personal : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    void MOSTRAR(MYSQL* conectar);
    Datos_Personal();
    string DNI = " ";
    string NOMBRE = " ";
    string APELLIDO = " ";
    string TELEFONO = " ";
    string SUELDO = " ";
    string FCHA_INGRESO = " ";
};

class Administrador : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    Administrador(string DTO_PRSNAL_, string SUCURSAL_);
    string DTO_PRSNAL;
    string SUCURSAL;
};

class Cocinero : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    Cocinero(string ESPECIAL_, string DTO_PRSNAL_);
    string ESPECIAL;
    string DTO_PRSNAL;
};

class Limpieza : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    Limpieza(string AREA_LIMPZA_, string DTO_PRSNAL_);
    string AREA_LIMPZA;
    string DTO_PRSNAL;
};

class Mesero : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    void MOSTRAR();
    Mesero(string AREA_ENCAR_, string DTO_PRSNAL_);
    string AREA_ENCAR;
    string DTO_PRSNAL;
};

class Turno : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    void MOSTRAR();
    void ELIMINAR();
    Turno(string HRA_E_, string HRA_S_);
    string HRA_E;
    string HRA_S;
};

class Mesero_Turno : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    Mesero_Turno();
    string Mesero_id;
    string Turno_id;
    string Dto;
};

class Pedido : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    void MOSTRAR(MYSQL* conectar);
    Pedido();

    string PRSNA_NTRAL_DNI = " ";
    string EMPRESA_RUC = " ";
};

class PRSNA_NTRAL : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    PRSNA_NTRAL();
    string NOMBRE = " ";
    string DNI = " ";
    string DIRECCION = " ";
    string TELEFONO = " ";
    string EMAIL = " ";
};

class Empresa : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    Empresa();
    string RUC = " ";
    string RZON_SCIAL = " ";
    string DIRECCION = " ";
    string TELEFONO = " ";
    string EMAIL = " ";

};
class Dtlle_pdido : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    void MOSTRAR(MYSQL* conectar);
    Dtlle_pdido();
    string PEDIDO_ID_PEDIDO = " ";
};

class Ped_Prod : public Opcion {
public:
    void CREAR(MYSQL* conectar);
    void MOSTRAR(MYSQL* conectar);
    Ped_Prod();
    string CANTIDAD = " ";
    string PRODUCTO_ID_PRODUCTO = " ";
    string PRODUCTO_PROVEEDOR_ID_PROVEEDOR = " ";
    string DTALLE_PDIDO_ID_DTLLE_PDIDO = " ";
};

class Comprobante : public Opcion {
public:
    string NOMBRE = " ";
    string DIRECCION = " ";
    string FRMA_D_PAGO = " ";
    string PEDIDO_ID_PEDIDO = " ";
    string SUCURSAR_RUC = " ";
    Comprobante();
    void CREAR(MYSQL* conectar);
    void MOSTRAR(MYSQL* conectar, string& id_producto);
};


void INGRESAR_SUCURSAL(MYSQL* conectar, Sucursal& S);

void Inventario_setting(MYSQL* conectar);
void Inventario_Crear(MYSQL* conectar, string& id_sucursal, Inventario& I);

void Log_in(MYSQL* conectar);

void INGRESAR_PERSONAL(MYSQL* conectar);
void INGRESAR_PEDIDO(MYSQL* conectar, Pedido& P);

int main()
{
    MYSQL* conectar;
    conectar = mysql_init(0);
    conectar = mysql_real_connect(conectar, "localhost", "root", "Mauriciodavidapaza13", "default_schema", 3306, NULL, 0);
    if (conectar) {
        bool run = 0;
        bool run_sucursales = 0;
        int option;
        bool running = 0;
        bool run_empleados = 0;
        Datos_Personal D;
        Sucursal S;
        Producto PD;
        Pedido P;
        Comprobante COMPRO;
        while (!run) {
            cout << "<---- FOGON & CARBON ---->" << endl;
            cout << "1. SUCURSALES" << endl;
            cout << "2. SALIR" << endl;
            cout << "SELECCIONAR: ";
            cin >> option;
            system("cls");
            switch (option) {
            case 1:
                while (!run_sucursales) {
                    cout << "<--- SUCURSALES --->" << endl;
                    cout << "1. CREAR SUCURSAL" << endl;
                    cout << "2. INGRESAR A SUCURSAL" << endl;
                    cout << "3. SALIR" << endl;
                    cout << "SELECCIONAR: ";
                    cin >> option;
                    system("cls");
                    switch (option) {
                    case 1:
                        cout << "<--- NUEVA SUCURSAL --->" << endl;
                        INGRESAR_SUCURSAL(conectar, S);
                        while (option == 1) {
                            cout << "2. SALIR" << endl;
                            cout << "SELECCIONAR: ";
                            cin >> option;
                        }
                        system("cls");
                        break;
                    case 2:
                        Log_in(conectar);
                        system("cls");
                        if (!run_my_sucursal) {
                            while (!run_my_sucursal) {
                                cout << "<--- BIENVENIDO --->" << endl;
                                cout << "1. DATOS SUCURSAL" << endl;
                                cout << "2. INVENTARIO" << endl;
                                cout << "3. EMPLEADOS" << endl;
                                cout << "4. PRODUCTOS" << endl;
                                cout << "5. COMPROBANTES" << endl;
                                cout << "6. PEDIDOS" << endl;
                                cout << "7. SALIR" << endl;
                                cout << "SELECCIONAR: ";
                                cin >> option;
                                system("cls");
                                switch (option) {
                                case 1:
                                    S.MOSTRAR(conectar);
                                    system("pause");
                                    system("cls");
                                    break;
                                case 2:
                                    Inventario_setting(conectar);
                                    break;
                                case 3:
                                    while (!run_empleados) {
                                        cout << "<--- EMPLEADOS --->" << endl;
                                        cout << "1. CREAR EMPLEADO" << endl;
                                        cout << "2. VER EMPLEADOS" << endl;
                                        cout << "3. SALIR" << endl;
                                        cout << "SELECCIONAR: ";
                                        cin >> option;
                                        system("cls");
                                        switch (option) {
                                        case 1:
                                            cout << "<--- NUEVO EMPLEADO --->" << endl;
                                            INGRESAR_PERSONAL(conectar);
                                            while (option == 1) {
                                                cout << "2. SALIR" << endl;
                                                cout << "SELECCIONAR: ";
                                                cin >> option;
                                            }
                                            system("cls");
                                            break;
                                        case 2:
                                            D.MOSTRAR(conectar);
                                            break;
                                        case 3:
                                            run_empleados = 1;
                                            break;
                                        }
                                    }
                                    run_sucursales = 0;
                                    break;
                                case 4:
                                    while (!running) {
                                        cout << "<--- PRODUCTOS --->" << endl;
                                        cout << "1. CREAR NUEVO PRODUCTO" << endl;
                                        cout << "2. VER PRODUCTOS" << endl;
                                        cout << "3. SALIR" << endl;
                                        cout << "SELECCIONAR: ";
                                        cin >> option;
                                        system("cls");
                                        switch (option) {
                                        case 1:
                                            PD.CREAR(conectar);
                                            break;
                                        case 2:
                                            PD.MOSTRAR(conectar);
                                            system("pause");
                                            break;
                                        case 3:
                                            running = 1;
                                            break;
                                        }
                                        system("cls");
                                    }
                                    running = 0;
                                    system("cls");
                                    break;
                                case 5:
                                    COMPRO.MOSTRAR(conectar, RUC_UNICO);
                                    system("pause");
                                    system("cls");
                                    break;
                                case 6:
                                    cout << "<--- PEDIDOS --->" << endl;
                                    cout << "1. NUEVO PEDIDO" << endl;
                                    cout << "2. MOSTRAR PEDIDOS" << endl;
                                    cout << "3. SALIR" << endl;
                                    cin >> option;
                                    switch (option) {
                                    case 1:
                                        INGRESAR_PEDIDO(conectar, P);
                                        break;
                                    case 2:
                                        P.MOSTRAR(conectar);
                                        system("pause");
                                        system("cls");
                                        break;
                                    case 3:
                                        system("cls");
                                        break;
                                    }

                                    break;
                                case 7:
                                    run_my_sucursal = 1;
                                    system("cls");
                                    break;
                                }
                            }
                        }
                        else {
                            system("cls");
                        }
                        break;
                    case 3:
                        run_sucursales = 1;
                        break;
                    }
                }
                run_sucursales = 0;
                break;
            case 2:
                run = 1;
                break;
            }
        }
    }
    else {
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
    consulta = "SELECT * FROM sucursal A, provincia B, distrito C WHERE A.DISTRITO_ID_DISTRITO = C.ID_DISTRITO AND C.PROVINCIA_ID_PROVINCIA = B.ID_PROVINCIA AND A.RUC = '" + RUC_UNICO + "'";
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

void Inventario::ELIMINAR(MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    string opcion;
    const char* c;
    consulta = "SELECT * FROM inventario";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        while (fila = mysql_fetch_row(resultado)) {
            cout << fila[0] << " | " << fila[1] << endl;
        }
        cout << "Escoger: ";
        cin >> opcion;
    }

    string del = "DELETE FROM inventario WHERE ID_INVENTARIO = '" + opcion + "'";
    const char* i = del.c_str();
    q_estado = mysql_query(conectar, i);
}

void Inventario::ACTUALIZAR(MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    string opcion;
    string cantidad_n;
    const char* c;
    consulta = "SELECT * FROM inventario";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        while (fila = mysql_fetch_row(resultado)) {
            cout << fila[0] << " | " << fila[1] << endl;
        }
        cout << "Escoger: ";
        cin >> opcion;
    }

    system("cls");
    cout << "<----Cambio de Cantidad---->" << endl;
    cout << "Ingresar Nueva Cantidad: ";
    cin >> cantidad_n;

    string act = "UPDATE inventario SET CANTIDAD = '"+ cantidad_n +"' WHERE ID_INVENTARIO = '" + opcion + "'";
    const char* i = act.c_str();
    q_estado = mysql_query(conectar, i);

    consulta = "SELECT * FROM inventario";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        while (fila = mysql_fetch_row(resultado)) {
            string id = fila[0];
            string cant = fila[2];
            if (cant == "0") {
                string del = "DELETE FROM inventario WHERE ID_INVENTARIO = '" + id + "'";
                i = del.c_str();
                q_estado = mysql_query(conectar, i);
            }
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

void Inventario_setting(MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    string id_sucursal;
    Inventario I;
    const char* c;
    consulta = "SELECT * FROM sucursal";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        while (fila = mysql_fetch_row(resultado)) {
            if (RUC_UNICO == fila[1]) {
                id_sucursal = fila[0];
            }
        }

    }
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
                cout << "2. ELIMINAR ELEMENTO DE INVENTARIO" << endl;
                cout << "3. ACTUALIZAR CANTIDAD DE INVENTARIO" << endl;
                cout << "4. SALIR" << endl;
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
                    I.ELIMINAR(conectar);
                    break;
                case 3:
                    I.ACTUALIZAR(conectar);
                    break;
                case 4:
                    run = 1;
                    system("cls");
                    break;
                }
            }
            run = 0;
        }
    }
}

void Inventario_Crear(MYSQL* conectar, string& id_sucursal, Inventario& I) {
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

void Log_in(MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    Inventario I;
    const char* c;
    string number;
    consulta = "SELECT * FROM sucursal";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        while (fila = mysql_fetch_row(resultado)) {
            cout << fila[0] << " | " << fila[1] << endl;
        }
        cout << "ESCOGER SUCURSAL: ";
        cin >> number;
        consulta = "SELECT * FROM sucursal WHERE ID_SUCURSAL = '"+ number +"'";
        c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            while (fila = mysql_fetch_row(resultado)) {
                RUC_UNICO = fila[1];
                run_my_sucursal = 0;
            }
        }
        else {
            return;
        }
    }
    else {
        return;
    }
}

ProSur::ProSur() {
    ID_SUCURSAL = " ";
    ID_PRODUCTO = " ";
}

void ProSur::CREAR(MYSQL* conectar, string id_producto) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    string id_sucursal;
    const char* c;
    consulta = "SELECT * FROM sucursal WHERE ruc = '"+ RUC_UNICO +"'";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        while (fila = mysql_fetch_row(resultado)) {
            id_sucursal = fila[0];
        }
    }
    string insert = "insert into sucursal_has_producto(SUCURSAL_RUC, PRODUCTO_ID_PRODUCTO) values('" + id_sucursal + "', '" + id_producto + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
}

Producto::Producto() {
    PRECIO = " ";
    TIPO = " ";
    PROVEEDOR_ID = " ";
}

void Producto::CREAR(MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    string id_proveedor;
    ProSur PS;
    Proveedor Pv;
    int option;
    bool running = 0;
    const char* c;
    consulta = "SELECT * FROM proveedor";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        while (!running) {
            while (fila = mysql_fetch_row(resultado)) {
                cout << fila[0] << " | " << fila[2] << endl;
            }
            cout << "1. Elegir de lista" << endl;
            cout << "2. Crear Proveedor " << endl;
            cout << "3. Salir " << endl;
            cout << "Escoger: ";
            cin >> option;
            switch (option) {
            case 1:
                cout << "Elegir Direccion de Proveedor:";
                cin >> id_proveedor;
                running = 1;
                system("cls");
                break;
            case 2:
                system("cls");
                cout << "<-----CREAR PROVEEDOR----->" << endl;
                Pv.CREAR(conectar);
                consulta = "SELECT * FROM proveedor";
                c = consulta.c_str();
                q_estado = mysql_query(conectar, c);
                if (!q_estado) {
                    resultado = mysql_store_result(conectar);
                    while (fila = mysql_fetch_row(resultado)) {
                        id_proveedor = fila[0];
                    }
                }
                running = 1;
                system("cls");
                break;
            case 3:
                return;
            }
        }
    }
    cout << "Ingresar Precio: ";
    cin >> PRECIO;
    cout << "Ingresar Tipo de Producto: ";
    cin >> TIPO;
    string insert = "insert into producto(PRECIO, TIPO, PROVEEDOR_ID_PROVEEDOR) values('" + PRECIO + "', '" + TIPO + "', '" + id_proveedor + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
    consulta = "SELECT LAST_INSERT_ID()";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        while (fila = mysql_fetch_row(resultado)) {
            PS.CREAR(conectar, fila[0]);
        }

    }
}

void Producto::MOSTRAR(MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    const char* c;
    consulta = "SELECT * FROM producto";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        while (fila = mysql_fetch_row(resultado)) {
            cout << "PRECIO: " << "s/." << fila[1] << endl;
            cout << "TIPO: " << fila[2] << endl;
            cout << "------------------------------" << endl;
        }
    }
}

Proveedor::Proveedor() {
    TELEFONO = " ";
    DIRECCION = " ";
}

void Proveedor::CREAR(MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    cout << "Ingresar Telefono: ";
    cin >> TELEFONO;
    cout << "Ingresar Direccion: ";
    cin >> DIRECCION;
    string insert = "insert into proveedor(TELEFONO, DIRECCION) values('" + TELEFONO + "', '" + DIRECCION + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
}

Datos_Personal::Datos_Personal() {
    DNI = " ";
    NOMBRE = " ";
    APELLIDO = " ";
    TELEFONO = " ";
    SUELDO = " ";
    FCHA_INGRESO = " ";
}

void Datos_Personal::CREAR(MYSQL* conectar) {
    string insert = "insert into dto_prsnal(DNI, NOMBRE, APELLIDO, TELEFONO, SUELDO, FCHA_D_INGRSO) values('" + DNI + "', '" + NOMBRE + "', '" + APELLIDO + "', '" + TELEFONO + "', '" + SUELDO + "', '" + FCHA_INGRESO + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Ingreso Exitoso..." << endl;
    }
    else {
        cout << "Ingreso Fallido..." << endl;
    }
}

void Datos_Personal::MOSTRAR(MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_ROW fila1;
    MYSQL_ROW fila2;
    MYSQL_ROW fila3;
    MYSQL_ROW fila4;
    MYSQL_RES* resultado;
    string consulta;
    string consulta1;
    string consulta2;
    string consulta3;
    string consulta4;
    const char* c;
    string id_datos;
    string id_dto;
    string dni;
    cout << "Buscar Personal por DNI: ";
    cin >> dni;
    consulta = "SELECT * FROM dto_prsnal WHERE DNI = '" + dni + "'";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        fila = mysql_fetch_row(resultado);
        id_datos = fila[0];
        cout << id_datos << endl;
        cout << "DNI: " << fila[1] << endl;
        cout << "NOMBRE: " << fila[2] << endl;
        cout << "APELLIDO: " << fila[3] << endl;
        cout << "TELEFONO: " << fila[4] << endl;
        cout << "SUELDO: " << fila[5] << endl;
        cout << "FECHA DE INGRESO: " << fila[6] << endl;
    }
    string trabajo = "administrador";
    cout << "-------TRABAJO-------" << endl;
    consulta1 = "SELECT * FROM dto_prsnal INNER JOIN cocinero on dto_prsnal.ID_DTO_PRSNAL=cocinero.DTO_PRSNAL_ID_DTO_PRSNAL WHERE dto_prsnal.ID_DTO_PRSNAL = '" + id_datos + "'";
    c = consulta1.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        fila1 = mysql_fetch_row(resultado);
        if (fila1) {
            id_dto = fila1[0];
            cout << "COCINERO: " << endl;
            cout << "Especialidad: " << fila1[9] << endl;
            cout << "Id del Personal: " << fila1[10] << endl;
            return;
        }

    }
    consulta2 = "SELECT * FROM dto_prsnal INNER JOIN administrador on dto_prsnal.ID_DTO_PRSNAL=administrador.DTO_PRSNAL_ID_DTO_PRSNAL WHERE dto_prsnal.ID_DTO_PRSNAL = '" + id_datos + "'";
    c = consulta2.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        fila2 = mysql_fetch_row(resultado);
        if (fila2) {
            id_dto = fila2[0];
            cout << "ADMINISTRADOR: " << endl;
            cout << "ESPECIALIDAD: " << fila2[9] << endl;
            cout << "Id del Personal: " << fila2[10] << endl;
            return;
        }

    }
    consulta3 = "SELECT * FROM dto_prsnal INNER JOIN limpieza on dto_prsnal.ID_DTO_PRSNAL=limpieza.DTO_PRSNAL_ID_DTO_PRSNAL WHERE dto_prsnal.ID_DTO_PRSNAL = '" + id_datos + "'";
    c = consulta3.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        fila3 = mysql_fetch_row(resultado);
        if (fila3) {
            id_dto = fila3[0];
            cout << "LIMPIEZA: " << endl;
            cout << "Area de Limpieza: " << fila3[9] << endl;
            cout << "Id del Personal: " << fila3[10] << endl;
            return;
        }


    }
    consulta4 = "SELECT * FROM dto_prsnal INNER JOIN mesero on dto_prsnal.ID_DTO_PRSNAL=mesero.DTO_PRSNAL_ID_DTO_PRSNAL INNER JOIN mesero_has_turno on mesero.ID_MESERO = mesero_has_turno.MESERO_ID_MESERO INNER JOIN turno on mesero_has_turno.TURNO_ID_TURNO = turno.ID_TURNO WHERE dto_prsnal.ID_DTO_PRSNAL = '" + id_datos + "'";
    c = consulta4.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        fila4 = mysql_fetch_row(resultado);
        if (fila4) {
            id_dto = fila4[0];
            cout << "MESERO: " << endl;
            cout << "Hora entrada: " << fila4[15] << endl;
            cout << "Hora salida: " << fila4[16] << endl;
            cout << "Area encargada: " << fila4[9] << endl;
            cout << "Id del Personal: " << fila4[10] << endl;
            return;
        }

    }

}

Administrador::Administrador(string DTO_PRSNAL_, string SUCURSAL_) {
    DTO_PRSNAL = DTO_PRSNAL_;
    SUCURSAL = SUCURSAL_;
}

void Administrador::CREAR(MYSQL* conectar) {
    string insert = "insert into administrador(DTO_PRSNAL_ID_DTO_PRSNAL, SUCURSAL_ID_SUCURSAL) values('" + DTO_PRSNAL + "', '" + SUCURSAL + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Ingreso Exitoso..." << endl;
    }
    else {
        cout << "Ingreso Fallido..." << endl;
    }
}

Cocinero::Cocinero(string ESPECIAL_, string DTO_PRSNAL_) {
    ESPECIAL = ESPECIAL_;
    DTO_PRSNAL = DTO_PRSNAL_;
}

void Cocinero::CREAR(MYSQL* conectar) {
    string insert = "insert into cocinero(ESPECIALIDAD, DTO_PRSNAL_ID_DTO_PRSNAL) values('" + ESPECIAL + "', '" + DTO_PRSNAL + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Ingreso Exitoso..." << endl;
    }
    else {
        cout << "Ingreso Fallido..." << endl;
    }
}

Limpieza::Limpieza(string AREA_LIMPZA_, string DTO_PRSNAL_) {
    AREA_LIMPZA = AREA_LIMPZA_;
    DTO_PRSNAL = DTO_PRSNAL_;
}

void Limpieza::CREAR(MYSQL* conectar) {
    string insert = "insert into limpieza(AREA_D_LMPZA, DTO_PRSNAL_ID_DTO_PRSNAL) values('" + AREA_LIMPZA + "', '" + DTO_PRSNAL + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Ingreso Exitoso..." << endl;
    }
    else {
        cout << "Ingreso Fallido..." << endl;
    }
}

Mesero::Mesero(string AREA_ENCAR_, string DTO_PRSNAL_) {
    AREA_ENCAR = AREA_ENCAR_;
    DTO_PRSNAL = DTO_PRSNAL_;
}

void Mesero::CREAR(MYSQL* conectar) {
    string insert = "insert into mesero(AREA_ENCRGDA, DTO_PRSNAL_ID_DTO_PRSNAL) values('" + AREA_ENCAR + "', '" + DTO_PRSNAL + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Ingreso Exitoso..." << endl;
    }
    else {
        cout << "Ingreso Fallido..." << endl;
    }
}

Turno::Turno(string HRA_E_, string HRA_S_) {
    HRA_E = HRA_E_;
    HRA_S = HRA_S_;
}

void Turno::CREAR(MYSQL* conectar) {
    string insert = "insert into turno(HRA_ENTRDA, HRA_SALDA) values('" + HRA_E + "', '" + HRA_S + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Ingreso Exitoso..." << endl;
    }
    else {
        cout << "Ingreso Fallido..." << endl;
    }
}

void INGRESAR_PERSONAL(MYSQL* conectar) {
    string dni;
    cout << "Ingresa DNI: ";
    cin >> dni;
    string nombre;
    cout << "Ingresa Nombre: ";
    cin >> nombre;
    string apellido;
    cout << "Ingresa Apellido: ";
    cin >> apellido;
    string telefono;
    cout << "Ingresa Telefono: ";
    cin >> telefono;
    string sueldo;
    cout << "Ingresa Sueldo: ";
    cin >> sueldo;
    string fcha_ingreso;
    cout << "Ingresa Fecha de Ingreso: ";
    cin >> fcha_ingreso;
    system("cls");
    Datos_Personal D;
    D.DNI = dni;
    D.NOMBRE = nombre;
    D.APELLIDO = apellido;
    D.TELEFONO = telefono;
    D.SUELDO = sueldo;
    D.FCHA_INGRESO = fcha_ingreso;
    D.CREAR(conectar);
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    const char* c;
    //INGRESAR TRABAJO
    string SUC;
    string suc_id;
    string dato_id;
    bool run = 0;
    int choose = 0;
    int work = 0;
    int espe;
    string especi;
    string turno_id;
    Mesero_Turno M;
    string mese_id;
    while (!run) {
        cout << "1. Elegir Trabajo" << endl;
        cout << "2. Crear Nuevo Trabajo" << endl;
        cout << "3. Salir" << endl;
        cout << "SELECCIONAR: ";
        cin >> choose;
        system("cls");
        switch (choose) {
        case 1:
            cout << "-------TRABAJOS-------" << endl;
            cout << "1. Administrador" << endl;
            cout << "2. Cocinero" << endl;
            cout << "3. Mesero" << endl;
            cout << "4. Limpieza" << endl;
            cout << "SELECCIONAR: ";
            cin >> work;
            system("cls");
            if (work == 1) {
                cout << "------Administrador-------" << endl;
                consulta = "select id_sucursal, ruc, direccion from sucursal";
                c = consulta.c_str();
                q_estado = mysql_query(conectar, c);
                if (!q_estado) {
                    resultado = mysql_store_result(conectar);
                    while (fila = mysql_fetch_row(resultado)) {
                        cout << fila[0] << " | " << fila[1] << " | " << fila[2] << endl;
                    }
                }
                cout << "Ingrese Sucursal: ";
                cin >> SUC;
                consulta = "select id_sucursal from sucursal where id_sucursal = '" + SUC + "'";
                c = consulta.c_str();
                q_estado = mysql_query(conectar, c);
                if (!q_estado) {
                    resultado = mysql_store_result(conectar);
                    while (fila = mysql_fetch_row(resultado)) {
                        suc_id = fila[0];
                    }
                }
                consulta = "select id_dto_prsnal from dto_prsnal where dni = '" + dni + "'";
                c = consulta.c_str();
                q_estado = mysql_query(conectar, c);
                if (!q_estado) {
                    resultado = mysql_store_result(conectar);
                    while (fila = mysql_fetch_row(resultado)) {
                        dato_id = fila[0];
                    }
                }
                Administrador A(dato_id, suc_id);
                A.CREAR(conectar);
                work = 1;
                system("cls");
                break;
            }
            else if (work == 2) {

                cout << "------Cocinero-------" << endl;
                cout << "Elige una especialidad: " << endl;
                cout << "1. Carnes \n2. Mariscos\n3. Postres\n";
                cout << "Ingresa especialidad: "; cin >> espe;
                switch (espe) {
                case 1:
                    especi = "Carnes";

                case 2:
                    especi = "Mariscos";

                case 3:
                    especi = "Postres";
                }

                consulta = "select id_dto_prsnal from dto_prsnal where dni = '" + dni + "'";
                c = consulta.c_str();
                q_estado = mysql_query(conectar, c);
                if (!q_estado) {
                    resultado = mysql_store_result(conectar);
                    while (fila = mysql_fetch_row(resultado)) {
                        dato_id = fila[0];
                    }
                }
                Cocinero A(especi, dato_id);
                A.CREAR(conectar);
                work = 1;
                system("cls");
                break;
            }
            else if (work == 3) {
                cout << "------Mesero-------" << endl;
                cout << "Elige un area encargada: " << endl;
                cout << "1. Local 1 \n2. Local 2\n3. Local 3\n";
                cout << "Ingresa especialidad: "; cin >> espe;
                if (espe == 1) {
                    especi = "Local 1";
                }
                else if (espe == 2) {
                    especi = "Local 2";
                }
                else if (espe == 3) {
                    especi = "Local 3";
                }

                consulta = "select id_dto_prsnal from dto_prsnal where dni = '" + dni + "'";
                c = consulta.c_str();
                q_estado = mysql_query(conectar, c);
                if (!q_estado) {
                    resultado = mysql_store_result(conectar);
                    while (fila = mysql_fetch_row(resultado)) {
                        dato_id = fila[0];
                    }
                }


                Mesero A(especi, dato_id);
                A.CREAR(conectar);
                consulta = "select * from mesero where DTO_PRSNAL_ID_DTO_PRSNAL = '" + dato_id + "'";
                c = consulta.c_str();
                q_estado = mysql_query(conectar, c);
                if (!q_estado) {
                    resultado = mysql_store_result(conectar);
                    while (fila = mysql_fetch_row(resultado)) {
                        mese_id = fila[0];
                        cout << mese_id << endl;
                    }
                }
                work = 1;
                string sale;
                system("cls");
                cout << "---------Elige un turno---------" << endl;
                cout << "1. 8 a.m. - 4 p.m.\n2. 4 p.m. - 12 a.m." << endl;
                cout << "Ingresa un turno: "; cin >> espe;
                if (espe == 1) {
                    especi = "8 a.m.";
                    sale = "4 p.m.";
                }
                else if (espe == 2) {
                    especi = "4 p.m.";
                    sale = "12 a.m.";
                }

                Turno B(especi, sale);
                B.CREAR(conectar);
                consulta = "select * from turno where HRA_ENTRDA = '" + especi + "' and HRA_SALDA = '" + sale + "'";
                c = consulta.c_str();
                q_estado = mysql_query(conectar, c);
                if (!q_estado) {
                    resultado = mysql_store_result(conectar);
                    while (fila = mysql_fetch_row(resultado)) {
                        turno_id = fila[0];
                    }
                }
                M.Dto = dato_id;
                M.Mesero_id = mese_id;
                M.Turno_id = turno_id;
                M.CREAR(conectar);

                break;
            }
            else if (work == 4) {
                cout << "------Limpieza-------" << endl;
                cout << "Elige un area encargada: " << endl;
                cout << "1. Baños \n2. Cocina\n3. Locales\n";
                cout << "Ingresa especialidad: "; cin >> espe;
                switch (espe) {
                case 1:
                    especi = "Baños";

                case 2:
                    especi = "Cocina";

                case 3:
                    especi = "Locales";
                }
                consulta = "select id_dto_prsnal from dto_prsnal where dni = '" + dni + "'";
                c = consulta.c_str();
                q_estado = mysql_query(conectar, c);
                if (!q_estado) {
                    resultado = mysql_store_result(conectar);
                    while (fila = mysql_fetch_row(resultado)) {
                        dato_id = fila[0];
                    }
                }
                Limpieza L(especi, dato_id);
                L.CREAR(conectar);

            }
        case 3:

            return;
        }

    }

}

Empresa::Empresa() {
    RUC = " ";
    RZON_SCIAL = " ";
    DIRECCION = " ";
    TELEFONO = " ";
    EMAIL = " ";
}

void Empresa::CREAR(MYSQL* conectar) {
    string insert = "insert into empresa (RUC,  RZON_SCIAL, DIRECCION, TELEFONO, EMAIL) values('" + RUC + "', '" + RZON_SCIAL + "', '" + DIRECCION + "', '" + TELEFONO + "', '" + EMAIL + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
}

Pedido::Pedido() {

    PRSNA_NTRAL_DNI = " ";
    EMPRESA_RUC = " ";
}

void Pedido::CREAR(MYSQL* conectar) {
    string insert;
    if (EMPRESA_RUC == " ") {
        insert = "insert into pedido (PRSNA_NTRAL_DNI, EMPRESA_RUC) values('" + PRSNA_NTRAL_DNI + "', NULL)";
    }
    if (PRSNA_NTRAL_DNI == " ") {
        insert = "insert into pedido (PRSNA_NTRAL_DNI, EMPRESA_RUC) values( NULL,'" + EMPRESA_RUC + "')";
    }


    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
}

PRSNA_NTRAL::PRSNA_NTRAL() {
    NOMBRE = " ";
    DNI = " ";
    DIRECCION = " ";
    TELEFONO = " ";
    EMAIL = " ";
}

void PRSNA_NTRAL::CREAR(MYSQL* conectar) {
    string insert = "insert into prsna_ntral(NOMBRE, DNI, DIRECCION, TELEFONO,EMAIL) values('" + NOMBRE + "', '" + DNI + "', '" + DIRECCION + "', '" + TELEFONO + "', '" + EMAIL + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
}

Dtlle_pdido::Dtlle_pdido() {
    PEDIDO_ID_PEDIDO = " ";
}

void Dtlle_pdido::CREAR(MYSQL* conectar) {
    string insert = "insert into dtlle_pdido (PEDIDO_ID_PEDIDO) values('" + PEDIDO_ID_PEDIDO + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
}

Ped_Prod::Ped_Prod() {
    CANTIDAD = " ";
    PRODUCTO_ID_PRODUCTO = " ";
    PRODUCTO_PROVEEDOR_ID_PROVEEDOR = " ";
    DTALLE_PDIDO_ID_DTLLE_PDIDO = " ";
}

void Ped_Prod::CREAR(MYSQL* conectar) {
    string insert = "insert into producto_has_dtlle_pdido(PRODUCTO_ID_PRODUCTO, PRODUCTO_PROVEEDOR_ID_PROVEEDOR, DTLLE_PDIDO_ID_DTLLE_PDIDO, CANTIDAD) values('" + PRODUCTO_ID_PRODUCTO + "', '" + PRODUCTO_PROVEEDOR_ID_PROVEEDOR + "', '" + DTALLE_PDIDO_ID_DTLLE_PDIDO + "','" + CANTIDAD + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
}

Comprobante::Comprobante() {
    NOMBRE = " ";
    DIRECCION = " ";
    FRMA_D_PAGO = " ";
    PEDIDO_ID_PEDIDO = " ";
    SUCURSAR_RUC = " ";
}

void Comprobante::CREAR(MYSQL* conectar) {
    string insert = "insert into comprobante(FECHA, NOMBRE, DIRECCION, FRMA_D_PGO, SUCURSAL_RUC,PEDIDO_ID_PEDIDO) values(CURRENT_DATE(),'" + NOMBRE + "', '" + DIRECCION + "', '" + FRMA_D_PAGO + "', '" + SUCURSAR_RUC + "', '" + PEDIDO_ID_PEDIDO + "')";
    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
}

void Comprobante::MOSTRAR(MYSQL* conectar, string& id_sucursal) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    const char* c;

    consulta = "select * from sucursal where RUC = '" + id_sucursal + "'";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        while (fila = mysql_fetch_row(resultado)) {
            id_sucursal = fila[0];
        }
    }


    consulta = " select * , sum(cantidad * PRECIO) from default_schema.producto_has_dtlle_pdido as x inner join(SELECT comprobante.fecha, comprobante.nombre, comprobante.direccion, comprobante.FRMA_D_PGO, comprobante.PEDIDO_ID_PEDIDO, ID_DTLLE_PDIDO, ID_COMPROBANTE FROM default_schema.comprobante inner join default_schema.dtlle_pdido on comprobante.pedido_id_pedido = dtlle_pdido.pedido_id_pedido where sucursal_ruc = '" + id_sucursal + "') as y on x.dtlle_pdido_id_dtlle_pdido = y.id_dtlle_pdido inner join default_schema.producto as q on PRODUCTO_ID_PRODUCTO = q.ID_PRODUCTO where pedido_id_pedido in(select comprobante.PEDIDO_ID_PEDIDO from default_schema.comprobante) group by(comprobante.id_comprobante)";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        while (fila = mysql_fetch_row(resultado)) {
            cout << "FECHA:  " << fila[4] << endl;
            cout << "NOMBRE: " << fila[5] << endl;
            cout << "DIRECCION: " << fila[6] << endl;
            cout << "FORMA DE PAGO: " << fila[7] << endl;
            cout << "ID_PEDIDO: " << fila[8] << endl;
            cout << "TOTAL: " << fila[15] << endl;
            cout << "------------------------------" << endl;
        }
    }
}

void Pedido::MOSTRAR(MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_ROW fila2;
    MYSQL_RES* resultado;
    MYSQL_RES* resultado2;
    string id_ped;
    string consulta;
    string consulta2;
    const char* c;
    const char* c2;
    consulta = "SELECT * FROM pedido";
    c = consulta.c_str();
    q_estado = mysql_query(conectar, c);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        while (fila = mysql_fetch_row(resultado)) {
            cout << "------------------------------" << endl;
            id_ped = fila[0];
            cout << "ID PEDIDO: " << fila[0] << endl;
            consulta2 = "SELECT * FROM default_schema.dtlle_pdido inner join default_schema.producto_has_dtlle_pdido on dtlle_pdido.ID_DTLLE_PDIDO = producto_has_dtlle_pdido.dtlle_pdido_id_dtlle_pdido inner join default_schema.producto on PRODUCTO_ID_PRODUCTO = ID_PRODUCTO where PEDIDO_ID_PEDIDO = '" + id_ped + "'";
            c2 = consulta2.c_str();
            q_estado = mysql_query(conectar, c2);
            if (!q_estado) {
                resultado2 = mysql_store_result(conectar);
                while (fila2 = mysql_fetch_row(resultado2)) {
                    cout << "ID PRODUCTO: " << fila2[6] << endl;
                    cout << "CANTIDAD: " << fila2[5] << endl;
                    cout << "PRECIO: " << "s/." << fila2[7] << endl;
                    cout << "NOMBRE: " << fila2[8] << endl;
                    cout << endl;
                }
            }


        }
    }

}

void INGRESAR_PEDIDO(MYSQL* conectar, Pedido& P) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string Cli_nom;
    string DIR;
    string Telf;
    string Email;
    string consulta;
    string ID;
    string DNI;
    string RUC;
    string proovprod;
    string DPEDIDO_ID;
    string PRODUCT;
    string CANTIDADP;
    string id_producto;
    const char* c;
    char x;
    int selection = 0;
    int choose = 0;
    int generar = 0;
    bool aceptar = false;
    bool running = false;
    bool general = false;
    PRSNA_NTRAL PRNA;
    Empresa EM;
    Dtlle_pdido NDP;
    Ped_Prod NPP;
    Comprobante COMP;



    //INGRESAR PERSONA NATURAL O EMPRESA 
    while (!general) {
        system("cls");
        cout << "<--- INGRESE TIPO DE CLIENTE --->" << endl;
        cout << "1. PERSONA NATURAL" << endl;
        cout << "2. EMPRESA" << endl;
        cout << "3. SALIR" << endl;
        cin >> selection;
        system("cls");
        switch (selection) {
        case 1:
            aceptar = false;
            cout << "1. Cliente Exitente" << endl;
            cout << "2. Nuevo Cliente" << endl;
            cout << "3. Salir" << endl;
            cout << "SELECCIONAR: ";
            cin >> choose;
            system("cls");
            switch (choose) {
            case 1:
                while (!aceptar) {
                    cout << "Ingrese DNI : ";
                    cin >> DNI;
                    consulta = "select * from prsna_ntral where DNI = '" + DNI + "'";
                    c = consulta.c_str();
                    q_estado = mysql_query(conectar, c);
                    if (!q_estado) {
                        resultado = mysql_store_result(conectar);
                        while (fila = mysql_fetch_row(resultado)) {
                            cout << fila[1] << endl;
                            Cli_nom = fila[1];
                            ID = fila[0];
                            DIR = fila[3];
                            Telf = fila[4];
                        }

                    }

                    cout << "-----------------------" << endl;
                    cout << "1. Aceptar" << endl;
                    cout << "2. Cancelar" << endl;
                    cout << "3. Salir" << endl;
                    cin >> choose;

                    if (choose == 1) {

                        P.PRSNA_NTRAL_DNI = ID;

                        P.CREAR(conectar);
                        aceptar = !aceptar;
                        general = !general;
                        break;
                    }
                    else if (choose == 3) {
                        aceptar = !aceptar;

                        break;
                    }
                    else {
                        ID = " ";
                        continue;
                    }
                }
                break;
            case 2:

                cout << "Ingrese Nombre: ";
                cin >> Cli_nom;
                cout << "Ingrese DNI: ";
                cin >> DNI;
                cout << "Ingrese Direccion: ";
                cin >> DIR;
                cout << "Ingrese Telefono: ";
                cin >> Telf;
                cout << "Ingrese Email: ";
                cin >> Email;
                PRNA.NOMBRE = Cli_nom;
                PRNA.DNI = DNI;
                PRNA.DIRECCION = DIR;
                PRNA.TELEFONO = Telf;
                PRNA.EMAIL = Email;

                PRNA.CREAR(conectar);
                consulta = "SELECT LAST_INSERT_ID()";
                c = consulta.c_str();
                q_estado = mysql_query(conectar, c);
                if (!q_estado) {
                    resultado = mysql_store_result(conectar);
                    while (fila = mysql_fetch_row(resultado)) {
                        ID = fila[0];
                    }
                }


                P.PRSNA_NTRAL_DNI = ID;
                P.CREAR(conectar);

                aceptar = !aceptar;
                general = !general;
                break;
            }

            break;
        case 2:
            aceptar = false;
            cout << "1. Empresa Exitente" << endl;
            cout << "2. Nueva Empresa" << endl;
            cout << "3. Salir" << endl;
            cout << "SELECCIONAR: ";
            cin >> choose;
            system("cls");
            switch (choose) {
            case 1:
                while (!aceptar) {
                    cout << "Ingrese RUC : ";
                    cin >> RUC;
                    consulta = "select * from empresa where RUC = '" + RUC + "'";
                    c = consulta.c_str();
                    q_estado = mysql_query(conectar, c);
                    if (!q_estado) {
                        resultado = mysql_store_result(conectar);
                        while (fila = mysql_fetch_row(resultado)) {
                            cout << fila[2] << endl;
                            Cli_nom = fila[2];
                            ID = fila[0];
                            DIR = fila[3];
                            Telf = fila[4];
                        }
                    }

                    cout << "-----------------------" << endl;
                    cout << "1. Aceptar" << endl;
                    cout << "2. Cancelar" << endl;
                    cout << "3. Salir" << endl;
                    cin >> choose;

                    if (choose == 1) {

                        P.EMPRESA_RUC = ID;

                        P.CREAR(conectar);
                        aceptar = !aceptar;
                        general = !general;
                        break;
                    }
                    else if (choose == 3) {
                        aceptar = !aceptar;

                        break;
                    }
                    else {
                        ID = " ";
                        continue;
                    }
                }
                break;
            case 2:
                cout << "Ingrese RUC: ";
                cin >> RUC;
                cout << "Ingrese RAZON SOCIAL: ";
                cin >> Cli_nom;
                cout << "Ingrese DIRECCION: ";
                cin >> DIR;
                cout << "Ingrese TELEFONO: ";
                cin >> Telf;
                cout << "Ingrese EMAIL: ";
                cin >> Email;

                EM.RUC = RUC;
                EM.RZON_SCIAL = Cli_nom;
                EM.DIRECCION = DIR;
                EM.TELEFONO = Telf;
                EM.EMAIL = Email;

                EM.CREAR(conectar);
                consulta = "SELECT LAST_INSERT_ID()";
                c = consulta.c_str();
                q_estado = mysql_query(conectar, c);
                if (!q_estado) {
                    resultado = mysql_store_result(conectar);
                    while (fila = mysql_fetch_row(resultado)) {
                        ID = fila[0];
                    }
                }


                P.EMPRESA_RUC = ID;
                P.CREAR(conectar);

                aceptar = !aceptar;
                general = !general;
                break;
            }
            break;
        case 3:
            general = !general;
            break;



        }
    }
    if (selection != 3 && choose != 3) {


        consulta = "SELECT LAST_INSERT_ID()";
        c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            while (fila = mysql_fetch_row(resultado)) {
                ID = fila[0];
            }
        }

        NDP.PEDIDO_ID_PEDIDO = ID;
        COMP.PEDIDO_ID_PEDIDO = ID;
        NDP.CREAR(conectar);

        consulta = "SELECT LAST_INSERT_ID()";
        c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            while (fila = mysql_fetch_row(resultado)) {
                ID = fila[0];
            }
        }
        DPEDIDO_ID = ID;

        NPP.DTALLE_PDIDO_ID_DTLLE_PDIDO = DPEDIDO_ID;

        ///Detalles del pedido 
        system("cls");

        cout << "<-----------DETALLES DEL PEDIDO------------>" << endl;
        while (!running) {
            consulta = "SELECT * FROM producto";
            c = consulta.c_str();
            q_estado = mysql_query(conectar, c);
            if (!q_estado) {
                resultado = mysql_store_result(conectar);
                while (fila = mysql_fetch_row(resultado)) {
                    cout << fila[0] << " | " << fila[2] << endl;
                }
            }
            cout << "Elegir: ";
            cin >> id_producto;
            NPP.PRODUCTO_ID_PRODUCTO = id_producto;


            consulta = "select * from producto where ID_PRODUCTO = '" + id_producto + "'";
            c = consulta.c_str();
            q_estado = mysql_query(conectar, c);
            if (!q_estado) {
                resultado = mysql_store_result(conectar);
                while (fila = mysql_fetch_row(resultado)) {
                    proovprod = fila[3];
                }
            }
            NPP.PRODUCTO_PROVEEDOR_ID_PROVEEDOR = proovprod;

            cout << "Cantidad: ";
            cin >> CANTIDADP;
            NPP.CANTIDAD = CANTIDADP;
            NPP.CREAR(conectar);


            cout << " Presione x para cerrar" << endl;
            cout << " Presione cualquier tecla para seguir ingresando productos" << endl;
            cin >> x;
            system("cls");
            if (x == 'x') {
                running = !running;
            }
        }


        cout << " ¿DESEA GENERAR COMPROBANTE? " << endl;
        cout << " 1. SI" << endl;
        cout << " 2. NO" << endl;
        cin >> generar;
        system("cls");
        if (generar == 1) {
            cout << "Ingrese Forma de Pago: ";
            cin >> COMP.FRMA_D_PAGO;
            system("cls");

            consulta = "select * from sucursal where RUC = '" + RUC_UNICO + "'";
            c = consulta.c_str();
            q_estado = mysql_query(conectar, c);
            if (!q_estado) {
                resultado = mysql_store_result(conectar);
                while (fila = mysql_fetch_row(resultado)) {
                    COMP.SUCURSAR_RUC = fila[0];
                }
            }

            COMP.NOMBRE = Cli_nom;
            COMP.DIRECCION = DIR;// dir = busqueda usuario;
            COMP.CREAR(conectar);

        }
    }
}

Mesero_Turno::Mesero_Turno() {
    Mesero_id = " ";
    Turno_id = " ";
    Dto = " ";
}

void Mesero_Turno::CREAR(MYSQL* conectar) {
    cout << Mesero_id << endl;
    cout << Turno_id << endl;
    string insert = "insert into mesero_has_turno(MESERO_ID_MESERO, MESERO_DTO_PRSNAL_ID_DTO_PRSNAL, TURNO_ID_TURNO) values('" + Mesero_id + "', '" + Dto + "', '" + Turno_id + "')";

    const char* i = insert.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Ingreso Exitoso..." << endl;
    }
    else {
        cout << "Ingreso Fallido..." << endl;
    }
}