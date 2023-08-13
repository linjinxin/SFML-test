#include <SFML/Window.hpp>
//#include <SFML/OpenGL.hpp>
#include <windows.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "base/Camera.h"
#include "base/Cube.h"

using namespace sf;

HWND _workerw = nullptr;

inline BOOL CALLBACK EnumWindowsProc(_In_ HWND tophandle, _In_ LPARAM topparamhandle)
{
    HWND defview = FindWindowEx(tophandle, 0, L"SHELLDLL_DefView", nullptr);
    if (defview != nullptr)
    {
        _workerw = FindWindowEx(0, tophandle, L"WorkerW", 0);
    }
    return true;
}

HWND GetWorkerW(){
    int result;
    HWND windowHandle = FindWindow(L"Progman", nullptr);
    SendMessageTimeout(windowHandle, 0x052c, 0, 0, SMTO_NORMAL, 0x3e8, (PDWORD_PTR)&result);
    EnumWindows(EnumWindowsProc, (LPARAM)nullptr);
    ShowWindow(_workerw, SW_HIDE);
    return windowHandle;
}


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
    auto modes = VideoMode::getFullscreenModes();
    VideoMode mode = modes[0];
    Window window(mode, "", Style::None);

    sf::WindowHandle handle = window.getSystemHandle();
    sf::WindowHandle parent = GetWorkerW();
    SetParent(handle, parent);

    Camera* camera = Camera::getInstance();
    glm::mat4 view = camera->getCameraView();
    glm::mat4 proj = camera->getCameraProjection(1.0f);
    Cube cube(view, proj);

    while (window.isOpen())
    {
        Event evt;
        while (window.pollEvent(evt))
        {
            if (evt.type == Event::Closed)
                window.close();
        }
        cube.render();
        window.display();
    }
    return 0;
}