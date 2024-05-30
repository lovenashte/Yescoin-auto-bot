#include <iostream>
#include <string>
#include <Windows.h>

bool final = false;

void escribir(const std::string& text) {
    for (char c : text) {
        INPUT input[2];
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wVk = 0;
        input[0].ki.wScan = c;
        input[0].ki.dwFlags = KEYEVENTF_UNICODE;
        input[0].ki.time = 0;
        input[0].ki.dwExtraInfo = 0;

        input[1] = input[0];
        input[1].ki.dwFlags |= KEYEVENTF_KEYUP;

        SendInput(2, input, sizeof(INPUT));
        Sleep(10);
    }
    final = true;
}

void Enter() {
    keybd_event(VK_RETURN, 0, 0, 0);
}

void soltar_enter() {
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
}

void flood(const std::string& texto, int cantidadVeces) {
    for (int i = 0; i < cantidadVeces; ++i) {
        Sleep(1);
        
        escribir(texto + "\n");
        Enter();
        soltar_enter();

        Sleep(50);
    }
    Sleep(3000);
}

int main() {
    SetConsoleTitle("Text Flooder");
    std::string logo = R"(
 _______               __        _______ __                 __             
|_     _|.-----.--.--.|  |_     |    ___|  |.-----.-----.--|  |.-----.----.
  |   |  |  -__|_   _||   _|    |    ___|  ||  _  |  _  |  _  ||  -__|   _|
  |___|  |_____|__.__||____|    |___|   |__||_____|_____|_____||_____|__|  
    )";

    std::cout << logo << std::endl;

    std::cout << "Ingresa el texto que quieres escribir: ";
    std::string texto;
    getline(std::cin, texto);

    std::cout << "Ingresa la cantidad de veces que deseas escribir el texto: ";
    int cantidadVeces;
    std::cin >> cantidadVeces;

    std::cout << "\nPresiona la tecla SHIFT para iniciar el spam.\n";

    while (1) {
        if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
            std::cout << "\n\nIniciando spam en 5 segundos...\n\n";
            
            Sleep(5000);
            flood(texto, cantidadVeces);

            while (!final) {
                Sleep(1000);
            }
            
            std::cout << "Spam terminado." << std::endl;
            Sleep(2000);
            return 0;
        }
    }

    return 0;
}
